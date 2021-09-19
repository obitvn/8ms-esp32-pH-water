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

#include "driver/pcnt.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"
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

float pH_value=0;

// 1 vòng cảm biến lưu lượng ra 3 xung

#define PCNT_TEST_UNIT      PCNT_UNIT_0
#define PCNT_H_LIM_VAL      4000000
#define PCNT_L_LIM_VAL     -4000000
#define PCNT_THRESH1_VAL    1
#define PCNT_THRESH0_VAL   -1
#define PCNT_INPUT_SIG_IO   26  // Pulse Input GPIO, 26 is FlowA, 25 is FlowB, DS18B20 in IO34
#define PCNT_INPUT_CTRL_IO  0  // Control GPIO HIGH=count up, LOW=count down


xQueueHandle pcnt_evt_queue;   // A queue to handle pulse counter events
pcnt_isr_handle_t user_isr_handle = NULL; //user's ISR service handle

/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
    int32_t unit;  // the PCNT unit that originated an interrupt
    uint32_t status; // information on the event type that caused the interrupt
} pcnt_evt_t;

/* Decode what PCNT's unit originated an interrupt
 * and pass this information together with the event type
 * the main program using a queue.
 */
static void IRAM_ATTR pcnt_example_intr_handler(void *arg)
{
    uint32_t intr_status = PCNT.int_st.val;
    int i;
    pcnt_evt_t evt;
    portBASE_TYPE HPTaskAwoken = pdFALSE;

    for (i = 0; i < PCNT_UNIT_MAX; i++) {
        if (intr_status & (BIT(i))) {
            evt.unit = i;
            /* Save the PCNT event type that caused an interrupt
               to pass it to the main program */
            evt.status = PCNT.status_unit[i].val;
            PCNT.int_clr.val = BIT(i);
            xQueueSendFromISR(pcnt_evt_queue, &evt, &HPTaskAwoken);
            if (HPTaskAwoken == pdTRUE) {
                portYIELD_FROM_ISR();
            }
        }
    }
}



/* Initialize PCNT functions:
 *  - configure and initialize PCNT
 *  - set up the input filter
 *  - set up the counter events to watch
 */
static void pcnt_example_init(void)
{
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config = {
        // Set PCNT input signal and control GPIOs
        .pulse_gpio_num = PCNT_INPUT_SIG_IO,
        .ctrl_gpio_num = PCNT_INPUT_CTRL_IO,
        .channel = PCNT_CHANNEL_0,
        .unit = PCNT_TEST_UNIT,
        // What to do on the positive / negative edge of pulse input?
        .pos_mode = PCNT_COUNT_INC,   // Count up on the positive edge
        .neg_mode = PCNT_COUNT_DIS,   // Keep the counter value on the negative edge
        // What to do when control input is low or high?
        .lctrl_mode = PCNT_MODE_REVERSE, // Reverse counting direction if low
        .hctrl_mode = PCNT_MODE_KEEP,    // Keep the primary counter mode if high
        // Set the maximum and minimum limit values to watch
        .counter_h_lim = PCNT_H_LIM_VAL,
        .counter_l_lim = PCNT_L_LIM_VAL,
    };
    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);

    /* Configure and enable the input filter */
    pcnt_set_filter_value(PCNT_TEST_UNIT, 1);
    pcnt_filter_enable(PCNT_TEST_UNIT);

    /* Set threshold 0 and 1 values and enable events to watch */
    pcnt_set_event_value(PCNT_TEST_UNIT, PCNT_EVT_THRES_1, PCNT_THRESH1_VAL);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_THRES_1);
    pcnt_set_event_value(PCNT_TEST_UNIT, PCNT_EVT_THRES_0, PCNT_THRESH0_VAL);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_THRES_0);
    /* Enable events on zero, maximum and minimum limit values */
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_ZERO);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_H_LIM);
    pcnt_event_enable(PCNT_TEST_UNIT, PCNT_EVT_L_LIM);

    /* Initialize PCNT's counter */
    pcnt_counter_pause(PCNT_TEST_UNIT);
    pcnt_counter_clear(PCNT_TEST_UNIT);

    /* Register ISR handler and enable interrupts for PCNT unit */
    pcnt_isr_register(pcnt_example_intr_handler, NULL, 0, &user_isr_handle);
    pcnt_intr_enable(PCNT_TEST_UNIT);

    /* Everything is set up, now go to counting */
    pcnt_counter_resume(PCNT_TEST_UNIT);
}



/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
void guiTask(void *pvParameter);
void mcp4725_task(void *pvParameter);
void adc_task(void *pvParameter);
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
    /* Initialize PCNT event queue and PCNT functions */
    pcnt_evt_queue = xQueueCreate(10, sizeof(pcnt_evt_t));
    pcnt_example_init();
    user_nvs_init();
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);
    vTaskDelay(500);
    xTaskCreate(adc_task, "adc", configMINIMAL_STACK_SIZE * 8, NULL, 4, NULL);
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

float vout_read = 0;
int32_t count = 0;
int32_t flow_count = 0;
void mcp4725_task(void *pvParameters)
{

    printf("mcp4725 task init\n");


        
    pcnt_evt_t evt;
    portBASE_TYPE res;
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
    pH_value = 2;
    vTaskDelay(pdMS_TO_TICKS(2000));
    mcp4725_set_voltage( VDD, 0.8, false);
    while (1)
        {
        // pH_value += 0.1;
        // if(pH_value>13.9) pH_value =2;
        // vout += 0.1;
        // if (vout > 1.400) vout = 0;

        // printf("Vout: %.02f\n", vout);

        // ESP_ERROR_CHECK(mcp4725_set_voltage( VDD, vout, false));


        // //It will be very low freq wave
        
        vTaskDelay(pdMS_TO_TICKS(200));
        res = xQueueReceive(pcnt_evt_queue, &evt, 100 / portTICK_PERIOD_MS);
        if (res == pdTRUE) {
            pcnt_get_counter_value(PCNT_TEST_UNIT, &count);
            printf("Event PCNT unit[%d]; cnt: %d\n", evt.unit, count);
            if (evt.status & PCNT_EVT_THRES_1) {
                printf("THRES1 EVT\n");
            }
            if (evt.status & PCNT_EVT_THRES_0) {
                printf("THRES0 EVT\n");
            }
            if (evt.status & PCNT_EVT_L_LIM) {
                printf("L_LIM EVT\n");
            }
            if (evt.status & PCNT_EVT_H_LIM) {
                printf("H_LIM EVT\n");
            }
            if (evt.status & PCNT_EVT_ZERO) {
                printf("ZERO EVT\n");
            }
        } else {
            pcnt_get_counter_value(PCNT_TEST_UNIT, &count);
            flow_count += count;
            printf("Current counter value :%d\n", flow_count);
            pcnt_counter_clear(PCNT_TEST_UNIT);
            count = 0;
        }

        // ESP_ERROR_CHECK(mcp4725_get_voltage( VDD, false, &vout_read)); // get val sai, nhưng set val đúng
        // printf("Vout read: %.02f\n", vout_read);

    }
}



#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static esp_adc_cal_characteristics_t *adc_chars_pH_vref;
static esp_adc_cal_characteristics_t *adc_chars_pH;
static esp_adc_cal_characteristics_t *adc_chars_vref2048;

static const adc_bits_width_t width = ADC_WIDTH_BIT_12;


// static const adc_channel_t adc_2048_channel = ADC_CHANNEL_7;     //GPIO34 if ADC1, GPIO14 if ADC2
// static const adc_atten_t adc_2048_atten = ADC_ATTEN_DB_11;

static const adc_channel_t adc_pH_channel = ADC_CHANNEL_4;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_atten_t adc_pH_atten = ADC_ATTEN_DB_6;

// static const adc_channel_t adc_vref_pH_channel = ADC_CHANNEL_5;     //GPIO34 if ADC1, GPIO14 if ADC2
// static const adc_atten_t adc_vref_pH_atten = ADC_ATTEN_DB_6;


static void check_efuse(void)
{
    //Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK)
    {
        printf("eFuse Two Point: Supported\n");
    }
    else
    {
        printf("eFuse Two Point: NOT supported\n");
    }
    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK)
    {
        printf("eFuse Vref: Supported\n");
    }
    else
    {
        printf("eFuse Vref: NOT supported\n");
    }

}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP)
    {
        printf("Characterized using Two Point Value\n");
    }
    else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
    {
        printf("Characterized using eFuse Vref\n");
    }
    else
    {
        printf("Characterized using Default Vref\n");
    }
}

#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
uint32_t raw_ph, raw_2048, raw_vref;
extern float calib_val, calib_val_a, calib_val_b, calib_val_c;
void adc_task(void *pvParameters)
{
    //Check if Two Point or Vref are burned into eFuse

    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle in main.c... \r\n");
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else 
    {
        printf("Done\n");

        // Read
        printf("Reading calib pH_value from NVS ... ");
        calib_val_a = 0;
        calib_val_b = 0;
        calib_val_c = 0;
        uint32_t val = 0;
        err = nvs_get_u32(my_handle, "test", &val);
        printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$test = %d\n", val);
        err = nvs_get_u32(my_handle, "pH_point1", &calib_val_a);
        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("calib_val_a = %f\n", calib_val_a);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
        err = nvs_get_u32(my_handle, "pH_point2", &calib_val_b);
        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("calib_val_b = %f\n", calib_val_b);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
        err = nvs_get_u32(my_handle, "pH_point3", &calib_val_c);
        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("calib_val_c = %f\n", calib_val_c);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
        nvs_close(my_handle);
    }

    check_efuse();

    //Configure ADC

    adc1_config_width(width);

    //Characterize ADC
    adc_chars_pH       = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    // adc_chars_pH_vref  = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    // adc_chars_vref2048 = calloc(1, sizeof(esp_adc_cal_characteristics_t));

    esp_adc_cal_value_t val_type_pH = esp_adc_cal_characterize(ADC_UNIT_1, adc_pH_atten, width, DEFAULT_VREF, adc_chars_pH);
    print_char_val_type(val_type_pH);

    // esp_adc_cal_value_t val_type_pH_vref = esp_adc_cal_characterize(ADC_UNIT_1, adc_vref_pH_atten, width, DEFAULT_VREF, adc_chars_pH_vref);
    // print_char_val_type(val_type_pH_vref);

    // esp_adc_cal_value_t val_type_vref2048 = esp_adc_cal_characterize(ADC_UNIT_1, adc_2048_atten, width, DEFAULT_VREF, adc_chars_vref2048);
    // print_char_val_type(val_type_vref2048);

    //Continuously sample ADC1
    while (1)
    {


        //Convert adc_reading to voltage in mV
        // adc1_config_channel_atten(adc_2048_channel, adc_2048_atten);
        // raw_2048 = adc1_get_raw((adc1_channel_t)adc_2048_channel);

        adc1_config_channel_atten(adc_pH_channel, adc_pH_atten);
        raw_ph   = adc1_get_raw((adc1_channel_t)adc_pH_channel);

        // adc1_config_channel_atten(adc_vref_pH_channel, adc_vref_pH_atten);
        // raw_vref = adc1_get_raw((adc1_channel_t)adc_vref_pH_channel);
        
        
        
        uint32_t pH_voltage = esp_adc_cal_raw_to_voltage(raw_ph, adc_chars_pH);
        // uint32_t vref2048_voltage = esp_adc_cal_raw_to_voltage(raw_2048, adc_chars_vref2048);
        // // printf("raw %d, vol:%d \r\n", raw_2048, vref2048_voltage);
        // uint32_t vrefpH_voltage = esp_adc_cal_raw_to_voltage(raw_vref, adc_chars_pH_vref);
        printf("raw pH: %d pH: %dmV \r\n", raw_ph, pH_voltage);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}