/***
* author:xnby
* platform: esp
* version: 1.0.0
* UIResolution: 480*320
*/

#include "qm_ui_entry.h"
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lv_8ms_blockly.h"
#include "wtctrl.h"

typedef struct
{
    char *name;
    lv_obj_t **id;
} lv_widget_t;

typedef struct
{
    char *name;
    lv_obj_t **id;
    lv_widget_t *wids;
    int len;
} lv_screen_t;

void lvgl_blockly_loop();
void lvgl_blockly_init();
/*
* includes
*/
LV_IMG_DECLARE(img1629631902349_png);
LV_IMG_DECLARE(img1629631379159_png);
LV_IMG_DECLARE(img1629631072036_png);
LV_IMG_DECLARE(img1627313837606_png);
LV_IMG_DECLARE(img1627313782026_png);
LV_IMG_DECLARE(img1627300974397_png);
LV_IMG_DECLARE(img1627300907204_png);
LV_IMG_DECLARE(img1627300869095_png);
LV_IMG_DECLARE(img1627300495627_png);
LV_IMG_DECLARE(img1627300475973_png);
LV_IMG_DECLARE(img1627285685903_png);
LV_IMG_DECLARE(img1627285659756_png);
LV_IMG_DECLARE(img1627285614032_png);
LV_IMG_DECLARE(img1627285431674_png);
LV_IMG_DECLARE(img1624810488518_JPG);
LV_IMG_DECLARE(img1627284951998_png);
LV_IMG_DECLARE(img1627285477548_png);
LV_IMG_DECLARE(img1627285517798_png);
LV_IMG_DECLARE(img1624810449186_jpg);
LV_IMG_DECLARE(img1624810438726_jpg);
LV_IMG_DECLARE(img1624810316180_JPG);
LV_IMG_DECLARE(img1624810282247_JPG);
LV_IMG_DECLARE(img1623066088293_jpg);
LV_IMG_DECLARE(img1623066079363_jpg);
LV_IMG_DECLARE(img1623066069081_jpg);
LV_IMG_DECLARE(img1622133209398_png);
LV_IMG_DECLARE(img1622133193178_png);
LV_IMG_DECLARE(img1621964575797_png);
LV_IMG_DECLARE(img1621964562882_jpeg);
LV_IMG_DECLARE(img1621964554083_jpeg);
LV_IMG_DECLARE(img1621808007284_jpg);
LV_IMG_DECLARE(img1621807977916_jpg);
LV_IMG_DECLARE(img1621807987411_jpg);
LV_IMG_DECLARE(img1621807899832_jpg);
LV_IMG_DECLARE(img1621412246918_png);
LV_IMG_DECLARE(img1621411957578_png);
LV_IMG_DECLARE(img1621411781237_png);
LV_IMG_DECLARE(img1621411672830_png);
LV_IMG_DECLARE(img1621411653680_png);
LV_IMG_DECLARE(img1621411366311_png);
LV_IMG_DECLARE(img1621411186442_png);
LV_IMG_DECLARE(img1621411142878_png);
LV_IMG_DECLARE(img1621411133904_png);
LV_IMG_DECLARE(img1620925138709_png);
LV_IMG_DECLARE(img1620925120786_png);
LV_IMG_DECLARE(img1618503703351_jpg);
LV_IMG_DECLARE(img1615470201266_dxf);
LV_IMG_DECLARE(img1615470165637_JPG);
LV_IMG_DECLARE(img1615470154936_JPG);
LV_IMG_DECLARE(img1615470208855_jpeg);
LV_IMG_DECLARE(img1614344958239_jpeg);
LV_IMG_DECLARE(img1614160720599_png);
LV_IMG_DECLARE(img1612941109111_jpg);
LV_IMG_DECLARE(imgbeijing_png);
LV_IMG_DECLARE(img1612941076475_jpg);
LV_IMG_DECLARE(img1612941006287_jpg);
LV_IMG_DECLARE(img1607507036809_png);
LV_IMG_DECLARE(img1606101128378_png);
LV_IMG_DECLARE(img1606100693921_jpg);
LV_IMG_DECLARE(img1606099918107_jpg);
LV_IMG_DECLARE(img1606099887609_jpg);
LV_IMG_DECLARE(img1606099859915_jpg);
LV_IMG_DECLARE(img1603868419064_jpg);
LV_IMG_DECLARE(img1592530624099_png);
LV_IMG_DECLARE(img1592530553072_png);
/*
* declear main_screen
*/
lv_obj_t *main_screen;
lv_obj_t *label_pH;
lv_obj_t *setting_button;
lv_obj_t *water_dis;
lv_obj_t *label_flow_water;
lv_obj_t *pH_dis;
lv_obj_t *bar_hydrogen;
lv_obj_t *text_setting;
lv_obj_t *text_hydro;
/*
* declear config_screen
*/
lv_obj_t *config_screen;
lv_obj_t *home_button;
lv_obj_t *calib_button;
lv_obj_t *wifi_button;
lv_obj_t *dropdown_select_filter;
lv_obj_t *clear_button;
lv_obj_t *edit_button;
lv_obj_t *text_info_filter_water;
/*
* declear login_screen
*/
lv_obj_t *login_screen;
lv_obj_t *image_background_login;
lv_obj_t *seeding_display;
lv_obj_t *return_home;
lv_obj_t *unlock_setting;
lv_obj_t *status_password;
/*
* declear calib_screen
*/
lv_obj_t *calib_screen;
lv_obj_t *start_calib_b;
lv_obj_t *start_calib_a;
lv_obj_t *start_calib_c;
lv_obj_t *pH_pos_a;
lv_obj_t *pH_pos_b;
lv_obj_t *pH_pos_c;
lv_obj_t *calib_to_home;

lv_widget_t g_main_screen_ids[] =
{
    {"label_pH", &label_pH},

    {"setting_button", &setting_button},

    {"water_dis", &water_dis},

    {"label_flow_water", &label_flow_water},

    {"pH_dis", &pH_dis},

    {"bar_hydrogen", &bar_hydrogen},

    {"text_setting", &text_setting},

    {"text_hydro", &text_hydro},
};
lv_widget_t g_config_screen_ids[] =
{
    {"home_button", &home_button},

    {"calib_button", &calib_button},

    {"wifi_button", &wifi_button},

    {"dropdown_select_filter", &dropdown_select_filter},

    {"clear_button", &clear_button},

    {"edit_button", &edit_button},

    {"text_info_filter_water", &text_info_filter_water},
};
lv_widget_t g_login_screen_ids[] =
{
    {"image_background_login", &image_background_login},

    {"seeding_display", &seeding_display},

    {"return_home", &return_home},

    {"unlock_setting", &unlock_setting},

    {"status_password", &status_password},
};
lv_widget_t g_calib_screen_ids[] =
{
    {"start_calib_b", &start_calib_b},

    {"start_calib_a", &start_calib_a},

    {"start_calib_c", &start_calib_c},

    {"pH_pos_a", &pH_pos_a},

    {"pH_pos_b", &pH_pos_b},

    {"pH_pos_c", &pH_pos_c},

    {"calib_to_home", &calib_to_home},
};

lv_screen_t g_screens[] =
{
    {"main_screen", &main_screen, g_main_screen_ids, (sizeof(g_main_screen_ids) / sizeof(g_main_screen_ids[0]))},
    {"config_screen", &config_screen, g_config_screen_ids, (sizeof(g_config_screen_ids) / sizeof(g_config_screen_ids[0]))},
    {"login_screen", &login_screen, g_login_screen_ids, (sizeof(g_login_screen_ids) / sizeof(g_login_screen_ids[0]))},
    {"calib_screen", &calib_screen, g_calib_screen_ids, (sizeof(g_calib_screen_ids) / sizeof(g_calib_screen_ids[0]))},
};

LV_FONT_DECLARE(ali_font_16);
LV_FONT_DECLARE(ali_font_100);
LV_FONT_DECLARE(ali_font_20);
LV_FONT_DECLARE(ali_font_21);
LV_FONT_DECLARE(ali_font_38);
LV_FONT_DECLARE(ali_font_26);
LV_FONT_DECLARE(ali_font_58);
LV_FONT_DECLARE(ali_font_30);
LV_FONT_DECLARE(ali_font_31);


void show_screen_main_screen();
void show_screen_config_screen();
void show_screen_login_screen();
void show_screen_calib_screen();
/*
* keyboard
*/
lv_obj_t *g_kb = NULL;

/////////////////////////////////////////
void setting_button_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    show_screen_login_screen();
}

void return_home_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    // del_screen_login_windows();
    show_screen_main_screen();
}

void unlock_setting_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    // del_screen_login_windows();
    show_screen_config_screen();
}

void home_button_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    show_screen_main_screen();
}

void calib_button_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    show_screen_calib_screen();
}

void calib_to_home_event_handler(lv_obj_t *event_kb, lv_event_t event)
{
    show_screen_main_screen();
}
////////////////////////////////////////

static void g_kb_event_cb(lv_obj_t *event_kb, lv_event_t event)
{
    /* Just call the regular event handler */
    if(event == LV_EVENT_APPLY)
    {
        lv_obj_set_hidden(event_kb, true);
    }
    else if(event == LV_EVENT_CANCEL)
    {
        lv_obj_set_hidden(event_kb, true);
    }
    else
    {
        lv_keyboard_def_event_cb(event_kb, event);
    }
}
static void g_create_kb_ifneeded()
{
    if(g_kb == NULL)
    {
        g_kb = lv_keyboard_create(main_screen, NULL);
        lv_obj_set_pos(g_kb, 5, 90);
        lv_obj_set_event_cb(g_kb, g_kb_event_cb); /* Setting a custom event handler stops the keyboard from closing automatically */
        lv_obj_set_size(g_kb,  LV_HOR_RES - 10, 140);
        lv_keyboard_set_cursor_manage(g_kb, true); /* Automatically show/hide cursors on text areas */
        lv_obj_set_hidden(g_kb, true);
    }
}
static void g_show_kb()
{
    g_create_kb_ifneeded();
    lv_obj_set_parent(g_kb, lv_scr_act());
    lv_obj_set_hidden(g_kb, false);
    lv_obj_align(g_kb, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
}

/**
*开机启动屏相关
*/
static lv_style_t style_star, style_black, style_url;
LV_IMG_DECLARE(img_8ms_png);
LV_IMG_DECLARE(img_star);
lv_obj_t *logo;
lv_obj_t *logo_star;
lv_obj_t *url_label;
lv_obj_t *url_mask;
lv_obj_t *mask_layer;
int timer_cnt = 0;
/****
* 临时变量用于数据传输
*/
char _tmpbuf[32];




/*
* declear codes
*/



#ifndef LV_8MS_PRESET_UART_QUEUE
void lv_8ms_uart_queue_ana(uint8_t *data, int size)
{
    printf("ana:%s\n", wtctrl_json_parse((char *)data));
}
#endif
#ifndef CUSTOM_MQTT_PARSE
void lv_8ms_mqtt_received(const char *data)
{
    printf("custom:%s\n", data);
}
#endif
/*
 * callback functions begins
 */
/*
 * callback functions ends
 */
/*
* init codes
*/
void init_function()
{
#ifdef BLOCKLY_init
    blockly_init();
#endif
}

void lv_8ms_label_pH_create()
{
    label_pH = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(label_pH, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label_pH, 360, 89);
    //set label style
    lv_obj_set_style_local_border_color(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_text_color(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xf3, 0x0a, 0x0e));
    lv_obj_set_style_local_text_font(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_100);

    lv_label_set_text(label_pH, "10.69");
    lv_label_set_align(label_pH, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_label_pH_EVENT_HANDLER
    lv_obj_set_event_cb(label_pH, label_pH_event_handler);
#endif
    if(label_pH->coords.x2 - label_pH->coords.x1 < 360)
    {
        int x_offset = (360 - (label_pH->coords.x2 - label_pH->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(label_pH->coords.y2 - label_pH->coords.y1 < 89)
    {
        int y_offset = (89 - (label_pH->coords.y2 - label_pH->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(label_pH, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(label_pH, 53, 48);

}
void lv_8ms_setting_button_create()
{
    setting_button = lv_img_create(main_screen, NULL);
    lv_img_set_src(setting_button, &img1627285477548_png);
    lv_obj_set_pos(setting_button, 402, 222);
    lv_obj_set_click(setting_button, true);
    lv_obj_set_style_local_image_recolor(setting_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(setting_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_setting_button_EVENT_HANDLER
    lv_obj_set_event_cb(setting_button, setting_button_event_handler);
    // #endif
}
void lv_8ms_water_dis_create()
{
    water_dis = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(water_dis, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(water_dis, 261, 53);
    //set label style
    lv_obj_set_style_local_text_color(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x7e, 0xd3, 0x21));
    lv_obj_set_style_local_text_font(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_20);

    lv_label_set_text(water_dis, "Lít H2O Hydrogen đã dùng");
    lv_label_set_align(water_dis, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_water_dis_EVENT_HANDLER
    lv_obj_set_event_cb(water_dis, water_dis_event_handler);
#endif
    if(water_dis->coords.x2 - water_dis->coords.x1 < 261)
    {
        int x_offset = (261 - (water_dis->coords.x2 - water_dis->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(water_dis->coords.y2 - water_dis->coords.y1 < 53)
    {
        int y_offset = (53 - (water_dis->coords.y2 - water_dis->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(water_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(water_dis, 205, 159);

}
void lv_8ms_label_flow_water_create()
{
    label_flow_water = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(label_flow_water, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(label_flow_water, 178, 54);
    //set label style
    lv_obj_set_style_local_radius(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 12);
    lv_obj_set_style_local_border_color(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_text_color(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x7e, 0xd3, 0x21));
    lv_obj_set_style_local_text_font(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_31);

    lv_label_set_text(label_flow_water, "123124");
    lv_label_set_align(label_flow_water, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_label_flow_water_EVENT_HANDLER
    lv_obj_set_event_cb(label_flow_water, label_flow_water_event_handler);
#endif
    if(label_flow_water->coords.x2 - label_flow_water->coords.x1 < 178)
    {
        int x_offset = (178 - (label_flow_water->coords.x2 - label_flow_water->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(label_flow_water->coords.y2 - label_flow_water->coords.y1 < 54)
    {
        int y_offset = (54 - (label_flow_water->coords.y2 - label_flow_water->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(label_flow_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(label_flow_water, 20, 158);

}
void lv_8ms_pH_dis_create()
{
    pH_dis = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(pH_dis, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(pH_dis, 65, 46);
    //set label style
    lv_obj_set_style_local_text_color(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xf3, 0x0a, 0x0e));
    lv_obj_set_style_local_text_font(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_38);

    lv_label_set_text(pH_dis, "pH");
    lv_label_set_align(pH_dis, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_dis_EVENT_HANDLER
    lv_obj_set_event_cb(pH_dis, pH_dis_event_handler);
#endif
    if(pH_dis->coords.x2 - pH_dis->coords.x1 < 65)
    {
        int x_offset = (65 - (pH_dis->coords.x2 - pH_dis->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(pH_dis->coords.y2 - pH_dis->coords.y1 < 46)
    {
        int y_offset = (46 - (pH_dis->coords.y2 - pH_dis->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(pH_dis, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(pH_dis, 355, 21);

}
void lv_8ms_bar_hydrogen_create()
{
    bar_hydrogen = lv_bar_create(main_screen, NULL);
    lv_obj_set_size(bar_hydrogen, 348, 40);
    lv_obj_set_pos(bar_hydrogen, 30, 234);
    lv_bar_set_anim_time(bar_hydrogen, 1000);
    lv_bar_set_value(bar_hydrogen, 48, LV_ANIM_ON);

    /*Create a bar, an indicator and a knob style*/
    //set main part style
    lv_obj_set_style_local_bg_color(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
    lv_obj_set_style_local_bg_grad_color(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
    lv_obj_set_style_local_pad_top(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_bottom(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_left(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(bar_hydrogen, LV_BAR_PART_BG, LV_STATE_DEFAULT, 0);
    //set indic style
    lv_obj_set_style_local_bg_color(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_bg_grad_color(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_radius(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
    lv_obj_set_style_local_pad_top(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_bottom(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_left(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_right(bar_hydrogen, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, 0);
}
void lv_8ms_text_setting_create()
{
    text_setting = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(text_setting, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(text_setting, 92, 21);
    //set label style
    lv_obj_set_style_local_text_color(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xdd, 0xdf, 0xc1));
    lv_obj_set_style_local_text_font(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_20);

    lv_label_set_text(text_setting, "Setting");
    lv_label_set_align(text_setting, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_text_setting_EVENT_HANDLER
    lv_obj_set_event_cb(text_setting, text_setting_event_handler);
#endif
    if(text_setting->coords.x2 - text_setting->coords.x1 < 92)
    {
        int x_offset = (92 - (text_setting->coords.x2 - text_setting->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(text_setting->coords.y2 - text_setting->coords.y1 < 21)
    {
        int y_offset = (21 - (text_setting->coords.y2 - text_setting->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(text_setting, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(text_setting, 388, 286);

}
void lv_8ms_text_hydro_create()
{
    text_hydro = lv_label_create(main_screen, NULL);
    lv_label_set_long_mode(text_hydro, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(text_hydro, 156, 40);
    //set label style
    lv_obj_set_style_local_text_color(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_text_font(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_30);

    lv_label_set_text(text_hydro, "Hydrogen");
    lv_label_set_align(text_hydro, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_text_hydro_EVENT_HANDLER
    lv_obj_set_event_cb(text_hydro, text_hydro_event_handler);
#endif
    if(text_hydro->coords.x2 - text_hydro->coords.x1 < 156)
    {
        int x_offset = (156 - (text_hydro->coords.x2 - text_hydro->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(text_hydro->coords.y2 - text_hydro->coords.y1 < 40)
    {
        int y_offset = (40 - (text_hydro->coords.y2 - text_hydro->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(text_hydro, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(text_hydro, 136, 274);

}
void lv_8ms_home_button_create()
{
    home_button = lv_img_create(config_screen, NULL);
    lv_img_set_src(home_button, &img1627285431674_png);
    lv_obj_set_pos(home_button, 211, 243);
    lv_obj_set_click(home_button, true);
    lv_obj_set_style_local_image_recolor(home_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(home_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_home_button_EVENT_HANDLER
    lv_obj_set_event_cb(home_button, home_button_event_handler);
    // #endif
}
void lv_8ms_calib_button_create()
{
    calib_button = lv_img_create(config_screen, NULL);
    lv_img_set_src(calib_button, &img1629631072036_png);
    lv_obj_set_pos(calib_button, 119, 243);
    lv_obj_set_click(calib_button, true);
    lv_obj_set_style_local_image_recolor(calib_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(calib_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_calib_button_EVENT_HANDLER
    lv_obj_set_event_cb(calib_button, calib_button_event_handler);
    // #endif
}
void lv_8ms_wifi_button_create()
{
    wifi_button = lv_img_create(config_screen, NULL);
    lv_img_set_src(wifi_button, &img1627285685903_png);
    lv_obj_set_pos(wifi_button, 303, 243);
    lv_obj_set_click(wifi_button, true);
    lv_obj_set_style_local_image_recolor(wifi_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(wifi_button, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
#ifdef BLOCKLY_wifi_button_EVENT_HANDLER
    lv_obj_set_event_cb(wifi_button, wifi_button_event_handler);
#endif
}
void lv_8ms_dropdown_select_filter_create()
{
    dropdown_select_filter = lv_dropdown_create(config_screen, NULL);
    lv_obj_set_size(dropdown_select_filter, 123, 86);
    lv_obj_set_pos(dropdown_select_filter, 8, 11);
    lv_dropdown_set_options(dropdown_select_filter,
                            "Filter 1""\n"
                            "Filter 2""\n"
                            "Filter 3""\n"
                            "Filter 4""\n"
                            "Filter 5""\n"
                            "Filter 6""\n"
                            "Filter 7""\n"
                            "Filter 8""\n"
                            ""
                           );
    lv_dropdown_set_draw_arrow(dropdown_select_filter, true);
#ifdef BLOCKLY_dropdown_select_filter_EVENT_HANDLER
    lv_obj_set_event_cb(dropdown_select_filter, dropdown_select_filter_event_handler);
#endif
    /*
    设置字体大小颜色
    */
    lv_obj_set_style_local_text_color(dropdown_select_filter, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x15, 0x7a, 0xe9));
    lv_obj_set_style_local_text_color(dropdown_select_filter, LV_DROPDOWN_PART_LIST, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x15, 0x7a, 0xe9));
    /*
    设置字体大小颜色结束
    */
}
void lv_8ms_clear_button_create()
{
    clear_button = lv_img_create(config_screen, NULL);
    lv_img_set_src(clear_button, &img1627300475973_png);
    lv_obj_set_pos(clear_button, 399, 20);
#ifdef BLOCKLY_clear_button_EVENT_HANDLER
    lv_obj_set_event_cb(clear_button, clear_button_event_handler);
#endif
}
void lv_8ms_edit_button_create()
{
    edit_button = lv_img_create(config_screen, NULL);
    lv_img_set_src(edit_button, &img1627300495627_png);
    lv_obj_set_pos(edit_button, 399, 125);
#ifdef BLOCKLY_edit_button_EVENT_HANDLER
    lv_obj_set_event_cb(edit_button, edit_button_event_handler);
#endif
}
void lv_8ms_text_info_filter_water_create()
{
    text_info_filter_water = lv_label_create(config_screen, NULL);
    lv_label_set_long_mode(text_info_filter_water, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(text_info_filter_water, 227, 215);
    //set label style
    lv_obj_set_style_local_radius(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_border_color(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_border_width(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_local_text_color(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
    lv_obj_set_style_local_text_font(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_20);

    lv_label_set_text(text_info_filter_water, "Thông tin lõi 1");
    lv_label_set_align(text_info_filter_water, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_text_info_filter_water_EVENT_HANDLER
    lv_obj_set_event_cb(text_info_filter_water, text_info_filter_water_event_handler);
#endif
    if(text_info_filter_water->coords.x2 - text_info_filter_water->coords.x1 < 227)
    {
        int x_offset = (227 - (text_info_filter_water->coords.x2 - text_info_filter_water->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(text_info_filter_water->coords.y2 - text_info_filter_water->coords.y1 < 215)
    {
        int y_offset = (215 - (text_info_filter_water->coords.y2 - text_info_filter_water->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(text_info_filter_water, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(text_info_filter_water, 140, 12);

}
void lv_8ms_image_background_login_create()
{
    image_background_login = lv_img_create(login_screen, NULL);
    lv_img_set_src(image_background_login, &img1627285614032_png);
    lv_obj_set_pos(image_background_login, 0, 0);
#ifdef BLOCKLY_image_background_login_EVENT_HANDLER
    lv_obj_set_event_cb(image_background_login, image_background_login_event_handler);
#endif
}
void lv_8ms_seeding_display_create()
{
    seeding_display = lv_label_create(login_screen, NULL);
    lv_label_set_long_mode(seeding_display, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(seeding_display, 245, 40);
    //set label style
    lv_obj_set_style_local_radius(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 12);
    lv_obj_set_style_local_border_width(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_text_color(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x90, 0x13, 0xfe));
    lv_obj_set_style_local_text_font(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_21);

    lv_label_set_text(seeding_display, "12E32A3CF5A1");
    lv_label_set_align(seeding_display, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_seeding_display_EVENT_HANDLER
    lv_obj_set_event_cb(seeding_display, seeding_display_event_handler);
#endif
    if(seeding_display->coords.x2 - seeding_display->coords.x1 < 245)
    {
        int x_offset = (245 - (seeding_display->coords.x2 - seeding_display->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(seeding_display->coords.y2 - seeding_display->coords.y1 < 40)
    {
        int y_offset = (40 - (seeding_display->coords.y2 - seeding_display->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(seeding_display, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(seeding_display, 114, 18);

}
void lv_8ms_return_home_create()
{
    return_home = lv_img_create(login_screen, NULL);
    lv_img_set_src(return_home, &img1627313782026_png);
    lv_obj_set_pos(return_home, 123, 216);
    lv_obj_set_click(return_home, true);
    lv_obj_set_style_local_image_recolor(return_home, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(return_home, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_return_home_EVENT_HANDLER
    lv_obj_set_event_cb(return_home, return_home_event_handler);
    // #endif
}
void lv_8ms_unlock_setting_create()
{
    unlock_setting = lv_img_create(login_screen, NULL);
    lv_img_set_src(unlock_setting, &img1627313837606_png);
    lv_obj_set_pos(unlock_setting, 295, 216);
    lv_obj_set_click(unlock_setting, true);
    lv_obj_set_style_local_image_recolor(unlock_setting, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(unlock_setting, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_unlock_setting_EVENT_HANDLER
    lv_obj_set_event_cb(unlock_setting, unlock_setting_event_handler);
    // #endif
}
void lv_8ms_status_password_create()
{
    status_password = lv_label_create(login_screen, NULL);
    lv_label_set_long_mode(status_password, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(status_password, 354, 40);
    //set label style
    lv_obj_set_style_local_text_color(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xe6, 0x0f, 0x0f));
    lv_obj_set_style_local_text_font(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_26);

    lv_label_set_text(status_password, "enter password");
    lv_label_set_align(status_password, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_status_password_EVENT_HANDLER
    lv_obj_set_event_cb(status_password, status_password_event_handler);
#endif
    if(status_password->coords.x2 - status_password->coords.x1 < 354)
    {
        int x_offset = (354 - (status_password->coords.x2 - status_password->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(status_password->coords.y2 - status_password->coords.y1 < 40)
    {
        int y_offset = (40 - (status_password->coords.y2 - status_password->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(status_password, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(status_password, 63, 78);

}
void lv_8ms_start_calib_b_create()
{
    start_calib_b = lv_img_create(calib_screen, NULL);
    lv_img_set_src(start_calib_b, &img1629631902349_png);
    lv_obj_set_pos(start_calib_b, 294, 117);
    lv_obj_set_click(start_calib_b, true);
    lv_obj_set_style_local_image_recolor(start_calib_b, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(start_calib_b, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
#ifdef BLOCKLY_start_calib_b_EVENT_HANDLER
    lv_obj_set_event_cb(start_calib_b, start_calib_b_event_handler);
#endif
}
void lv_8ms_start_calib_a_create()
{
    start_calib_a = lv_img_create(calib_screen, NULL);
    lv_img_set_src(start_calib_a, &img1629631902349_png);
    lv_obj_set_pos(start_calib_a, 294, 25);
    lv_obj_set_click(start_calib_a, true);
    lv_obj_set_style_local_image_recolor(start_calib_a, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(start_calib_a, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
#ifdef BLOCKLY_start_calib_a_EVENT_HANDLER
    lv_obj_set_event_cb(start_calib_a, start_calib_a_event_handler);
#endif
}
void lv_8ms_start_calib_c_create()
{
    start_calib_c = lv_img_create(calib_screen, NULL);
    lv_img_set_src(start_calib_c, &img1629631902349_png);
    lv_obj_set_pos(start_calib_c, 294, 209);
    lv_obj_set_click(start_calib_c, true);
    lv_obj_set_style_local_image_recolor(start_calib_c, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(start_calib_c, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
#ifdef BLOCKLY_start_calib_c_EVENT_HANDLER
    lv_obj_set_event_cb(start_calib_c, start_calib_c_event_handler);
#endif
}
void lv_8ms_pH_pos_a_create()
{
    pH_pos_a = lv_label_create(calib_screen, NULL);
    lv_label_set_long_mode(pH_pos_a, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(pH_pos_a, 280, 79);
    //set label style
    lv_obj_set_style_local_text_color(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x0d, 0xa2, 0xdb));
    lv_obj_set_style_local_text_font(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_58);

    lv_label_set_text(pH_pos_a, "calib 4.00");
    lv_label_set_align(pH_pos_a, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_pos_a_EVENT_HANDLER
    lv_obj_set_event_cb(pH_pos_a, pH_pos_a_event_handler);
#endif
    if(pH_pos_a->coords.x2 - pH_pos_a->coords.x1 < 280)
    {
        int x_offset = (280 - (pH_pos_a->coords.x2 - pH_pos_a->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(pH_pos_a->coords.y2 - pH_pos_a->coords.y1 < 79)
    {
        int y_offset = (79 - (pH_pos_a->coords.y2 - pH_pos_a->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(pH_pos_a, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(pH_pos_a, 0, 17);

}
void lv_8ms_pH_pos_b_create()
{
    pH_pos_b = lv_label_create(calib_screen, NULL);
    lv_label_set_long_mode(pH_pos_b, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(pH_pos_b, 280, 79);
    //set label style
    lv_obj_set_style_local_text_color(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x0d, 0xa2, 0xdb));
    lv_obj_set_style_local_text_font(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_58);

    lv_label_set_text(pH_pos_b, "calib 7.00");
    lv_label_set_align(pH_pos_b, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_pos_b_EVENT_HANDLER
    lv_obj_set_event_cb(pH_pos_b, pH_pos_b_event_handler);
#endif
    if(pH_pos_b->coords.x2 - pH_pos_b->coords.x1 < 280)
    {
        int x_offset = (280 - (pH_pos_b->coords.x2 - pH_pos_b->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(pH_pos_b->coords.y2 - pH_pos_b->coords.y1 < 79)
    {
        int y_offset = (79 - (pH_pos_b->coords.y2 - pH_pos_b->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(pH_pos_b, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(pH_pos_b, 0, 110);

}
void lv_8ms_pH_pos_c_create()
{
    pH_pos_c = lv_label_create(calib_screen, NULL);
    lv_label_set_long_mode(pH_pos_c, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(pH_pos_c, 280, 79);
    //set label style
    lv_obj_set_style_local_text_color(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x0d, 0xa2, 0xdb));
    lv_obj_set_style_local_text_font(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &ali_font_58);

    lv_label_set_text(pH_pos_c, "calib 9.18");
    lv_label_set_align(pH_pos_c, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_pos_c_EVENT_HANDLER
    lv_obj_set_event_cb(pH_pos_c, pH_pos_c_event_handler);
#endif
    if(pH_pos_c->coords.x2 - pH_pos_c->coords.x1 < 280)
    {
        int x_offset = (280 - (pH_pos_c->coords.x2 - pH_pos_c->coords.x1)) / 2;
        lv_obj_set_style_local_pad_left(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
        lv_obj_set_style_local_pad_right(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, x_offset);
    }
    if(pH_pos_c->coords.y2 - pH_pos_c->coords.y1 < 79)
    {
        int y_offset = (79 - (pH_pos_c->coords.y2 - pH_pos_c->coords.y1)) / 2;
        lv_obj_set_style_local_pad_bottom(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
        lv_obj_set_style_local_pad_top(pH_pos_c, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, y_offset);
    }
    lv_obj_set_pos(pH_pos_c, 0, 203);

}
void lv_8ms_calib_to_home_create()
{
    calib_to_home = lv_img_create(calib_screen, NULL);
    lv_img_set_src(calib_to_home, &img1627285431674_png);
    lv_obj_set_pos(calib_to_home, 392, 209);
    lv_obj_set_click(calib_to_home, true);
    lv_obj_set_style_local_image_recolor(calib_to_home, LV_IMG_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(calib_to_home, LV_IMG_PART_MAIN, LV_STATE_PRESSED, 60);
    // #ifdef BLOCKLY_calib_to_home_EVENT_HANDLER
    lv_obj_set_event_cb(calib_to_home, calib_to_home_event_handler);
    // #endif
}

void show_screen_main_screen()
{
    lv_scr_load(main_screen);
    //生成动态页面的style

}
void show_screen_config_screen()
{
    lv_scr_load(config_screen);
    //生成动态页面的style

}
void show_screen_login_screen()
{
    lv_scr_load(login_screen);
    //生成动态页面的style

}
void show_screen_calib_screen()
{
    lv_scr_load(calib_screen);
    //生成动态页面的style

}

extern float pH_value;
char ph_buf[10];
int screen_loop_enter = 0;
int _delay = 0;
void lv_qm_ui_loop(void)
{

sprintf(ph_buf,"%0.2f", pH_value);
lv_label_set_text(label_pH, ph_buf);










#ifdef BLOCKLY_loop
    blockly_loop();
#endif
}

void lv_qm_ui_entry(void)
{

    /*
    * create screens
    */
    main_screen = lv_obj_create(NULL, NULL);
    config_screen = lv_obj_create(NULL, NULL);
    login_screen = lv_obj_create(NULL, NULL);
    calib_screen = lv_obj_create(NULL, NULL);
    //CREATE STATIC OBJ
    lv_8ms_label_pH_create();
    lv_8ms_setting_button_create();
    lv_8ms_water_dis_create();
    lv_8ms_label_flow_water_create();
    lv_8ms_pH_dis_create();
    lv_8ms_bar_hydrogen_create();
    lv_8ms_text_setting_create();
    lv_8ms_text_hydro_create();
    lv_8ms_home_button_create();
    lv_8ms_calib_button_create();
    lv_8ms_wifi_button_create();
    lv_8ms_dropdown_select_filter_create();
    lv_8ms_clear_button_create();
    lv_8ms_edit_button_create();
    lv_8ms_text_info_filter_water_create();
    lv_8ms_image_background_login_create();
    lv_8ms_seeding_display_create();
    lv_8ms_return_home_create();
    lv_8ms_unlock_setting_create();
    lv_8ms_status_password_create();
    lv_8ms_start_calib_b_create();
    lv_8ms_start_calib_a_create();
    lv_8ms_start_calib_c_create();
    lv_8ms_pH_pos_a_create();
    lv_8ms_pH_pos_b_create();
    lv_8ms_pH_pos_c_create();
    lv_8ms_calib_to_home_create();

    static lv_style_t style_main_main_screen;
    lv_style_init(&style_main_main_screen);
    lv_style_set_bg_color(&style_main_main_screen, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));
    //lv_style_set_border_color(&style_main_main_screen,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x00, 0x00, 0x00));
    lv_obj_add_style(main_screen, LV_CONT_PART_MAIN, &style_main_main_screen);
    static lv_style_t style_main_config_screen;
    lv_style_init(&style_main_config_screen);
    lv_style_set_bg_color(&style_main_config_screen, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xda, 0xda, 0xda));
    //lv_style_set_border_color(&style_main_config_screen,LV_STATE_DEFAULT,LV_COLOR_MAKE(0xda, 0xda, 0xda));
    lv_obj_add_style(config_screen, LV_CONT_PART_MAIN, &style_main_config_screen);
    static lv_style_t style_main_calib_screen;
    lv_style_init(&style_main_calib_screen);
    lv_style_set_bg_color(&style_main_calib_screen, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xf1, 0xf1, 0xf1));
    //lv_style_set_border_color(&style_main_calib_screen,LV_STATE_DEFAULT,LV_COLOR_MAKE(0xf1, 0xf1, 0xf1));
    lv_obj_add_style(calib_screen, LV_CONT_PART_MAIN, &style_main_calib_screen);
    lv_scr_load(main_screen);
    init_function();
}
/**
* @brief blockly initialization
*/

void lvgl_blockly_init()
{
#ifdef WT_WIFI
    blockly_wifi_init();
#endif // DEBUG
#ifdef WT_BLUFI
    blockly_blufi_init();
#endif // DEBUG
#ifdef WT_HTTP_REQUEST
    blockly_http_init();
#endif // WT_HTTP_REQUEST
}

/**
* @brief blockly loop
*/

void lvgl_blockly_loop()
{
#ifdef WT_BLUFI
    blockly_blufi_loop();
#endif // DEBUG
#ifdef WT_WIFI
    blockly_wifi_loop();
#endif // DEBUG
#ifdef WT_HTTP_REQUEST
    blockly_http_loop();
#endif // WT_HTTP_REQUEST
}

void lvgl_device_init(void)
{
#ifdef ESP32_GPIO
    lv_8ms_gpio_setup();
#endif
#ifdef ESP32_TIMER
    lv_8ms_timer_setup();
#endif
#ifdef ESP32_UART
    lv_8ms_uart_setup();
#endif
}

void lvgl_device_loop(void)
{
#ifdef ESP32_GPIO
    lv_8ms_gpio_loop();
#endif
#ifdef ESP32_TIMER
    lv_8ms_timer_loop();
#endif
#ifdef ESP32_UART
    lv_8ms_uart_loop();
#endif
}
lv_obj_t *lv_8ms_get_screen(char *name)
{
    int i = 0;
    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        if (!strcmp(name, g_screens[i].name))
        {
            return *(g_screens[i].id);
        }
    }
    return NULL;
}

lv_obj_t *lv_8ms_get_widget(char *w_name)
{
    int i = 0, j = 0;

    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        for (j = 0; j <  g_screens[i].len; j++)
        {
            if (!strcmp(w_name, g_screens[i].wids[j].name))
            {
                return *(g_screens[i].wids[j].id);
            }
        }
    }

    return NULL;
}

const char *lv_8ms_get_obj_name(lv_obj_t *obj)
{
    if (!obj)
    {
        return NULL;
    }

    int i = 0, j = 0;
    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        if (*(g_screens[i].id) == obj)
        {
            return g_screens[i].name;
        }

        for (j = 0; j <  g_screens[i].len; j++)
        {
            if (*(g_screens[i].wids[j].id) == obj)
            {
                return g_screens[i].wids[j].name;
            }
        }
    }

    return NULL;
}