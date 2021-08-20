/* LVGL Example project
 *
 * Basic project to test LVGL on ESP32 based projects.
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "nvs_flash.h"

/* Littlevgl specific */
#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"
#include "qm_ui_entry.h"
#include "wtctrl.h"



#include <mcp4725_t.h>

#define ADDR MCP4725A0_I2C_ADDR0
#define SDA_GPIO 18
#define SCL_GPIO 19
#define VDD 3.3

/*********************
 *      DEFINES
 *********************/
#define TAG "main"
#define LV_TICK_PERIOD_MS 10

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
void guiTask(void *pvParameter);
void mcp4725_task(void *pvParameter);
/**********************
 *   APPLICATION MAIN
 **********************/
static void user_nvs_init()
{
    esp_err_t ret;
    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main()
{
    user_nvs_init();
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);
    vTaskDelay(2000);
    xTaskCreate(mcp4725_task, "mcp4725", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);

#ifdef LV_8MS_UART_CTRL
    lv_8ms_uart_ctrl_init(UART_NUM_0);
#endif
}

static void lv_tick_task(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

extern void lv_8ms_init(void);

//Creates a semaphore to handle concurrent call to lvgl stuff
//If you wish to call *any* lvgl function from other threads/tasks
//you should lock on the very same semaphore!
SemaphoreHandle_t xGuiSemaphore;

void guiTask(void *pvParameter)
{

    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    static lv_color_t buf1[DISP_BUF_SIZE];
#ifndef CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    static lv_color_t buf2[DISP_BUF_SIZE];
#endif
    static lv_disp_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LVGL_TFT_DISPLAY_CONTROLLER_IL3820
    /* Actual size in pixel, not bytes and use single buffer */
    size_in_px *= 8;
    lv_disp_buf_init(&disp_buf, buf1, NULL, size_in_px);
#elif defined CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    lv_disp_buf_init(&disp_buf, buf1, NULL, size_in_px);
#else
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);
#endif

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

#ifdef CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    const esp_timer_create_args_t periodic_timer_args =
    {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    lv_8ms_init();

    lv_qm_ui_entry();
    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        //Try to lock the semaphore, if success, call lvgl stuff
        if (xSemaphoreTake(xGuiSemaphore, (TickType_t)10) == pdTRUE)
        {
            lv_qm_ui_loop();
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    //A task should NEVER return
    vTaskDelete(NULL);
}


static void mcp4725_wait_for_eeprom()
{
    bool busy;
    while (true)
    {
        ESP_ERROR_CHECK(mcp4725_eeprom_busy( &busy));
        if (!busy)
            return;
        printf("...DAC is busy, waiting...\n");
        vTaskDelay(1);
    }
}

float vout_read=0;
void mcp4725_task(void *pvParameters)
{

    printf("mcp4725 task init\n");
    // i2c_dev_t dev;
    // memset(&dev, 0, sizeof(i2c_dev_t));

    // Init device descriptor
    //ESP_ERROR_CHECK(mcp4725_init_desc(&dev, 0, ADDR, SDA_GPIO, SCL_GPIO));

    mcp4725_power_mode_t pm;
    ESP_ERROR_CHECK(mcp4725_get_power_mode( true, &pm));
    if (pm != MCP4725_PM_NORMAL)
    {
        printf("DAC was sleeping... Wake up Neo!\n");
        ESP_ERROR_CHECK(mcp4725_set_power_mode( true, MCP4725_PM_NORMAL));
        mcp4725_wait_for_eeprom();
    }

    printf("Set default DAC output value to MAX...\n");
    ESP_ERROR_CHECK(mcp4725_set_raw_output( MCP4725_MAX_VALUE, true));
    mcp4725_wait_for_eeprom();

    printf("Now let's generate the sawtooth wave in slow manner\n");

    float vout = 0;
    while (1)
    {
        vout += 0.1;
        if (vout > VDD) vout = 0;

        printf("Vout: %.02f\n", vout);

        ESP_ERROR_CHECK(mcp4725_set_voltage( VDD, vout, false));


        // It will be very low freq wave
        vTaskDelay(pdMS_TO_TICKS(1000));

        // ESP_ERROR_CHECK(mcp4725_get_voltage( VDD, false, &vout_read)); // get val sai, nhưng set val đúng
        // printf("Vout read: %.02f\n", vout_read);

    }
}