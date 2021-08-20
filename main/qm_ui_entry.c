/***
* author:xnby
* platform: esp
* version: 1.0.0
* UIResolution: 480*320
*/

#include "qm_ui_entry.h"
#include "cJSON.h"
#include <stdio.h>
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
LV_IMG_DECLARE(img1627285517798_png);
LV_IMG_DECLARE(img1627285477548_png);
LV_IMG_DECLARE(img1627285431674_png);
LV_IMG_DECLARE(img1627284951998_png);
LV_IMG_DECLARE(img1624810488518_JPG);
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
LV_IMG_DECLARE(img1621807987411_jpg);
LV_IMG_DECLARE(img1621807899832_jpg);
LV_IMG_DECLARE(img1621807977916_jpg);
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
LV_IMG_DECLARE(imgbeijing_png);
LV_IMG_DECLARE(img1612941109111_jpg);
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
lv_obj_t * main_screen;
lv_obj_t * image_9f2b;
lv_obj_t * label_ce35;
lv_obj_t * setting_button;
lv_obj_t * phone_button;
lv_obj_t * pH_diss;
lv_obj_t * label_flow_water;
lv_obj_t * pH_7850;
    /*
    * declear setup
    */
lv_obj_t * setup;
lv_obj_t * image_57b1;
lv_obj_t * home_button;
lv_obj_t * mail_button;
lv_obj_t * wifi_button;
lv_obj_t * dropdown_select_filter;
lv_obj_t * info_filter;
lv_obj_t * clear_button;
lv_obj_t * edit_button;
    /*
    * declear login_windows
    */
lv_obj_t * login_windows;
lv_obj_t * image_5de4;
lv_obj_t * seeding_display;
lv_obj_t * return_home;
lv_obj_t * unlock_setting;
lv_obj_t * status_password;

lv_widget_t g_main_screen_ids[]=
{
    {"image_9f2b",&image_9f2b},

    {"label_ce35",&label_ce35},

    {"setting_button",&setting_button},

    {"phone_button",&phone_button},

    {"pH_diss",&pH_diss},

    {"label_flow_water",&label_flow_water},

    {"pH_7850",&pH_7850},
};
lv_widget_t g_setup_ids[]=
{
    {"image_57b1",&image_57b1},

    {"home_button",&home_button},

    {"mail_button",&mail_button},

    {"wifi_button",&wifi_button},

    {"dropdown_select_filter",&dropdown_select_filter},

    {"info_filter",&info_filter},

    {"clear_button",&clear_button},

    {"edit_button",&edit_button},
};
lv_widget_t g_login_windows_ids[]=
{
    {"image_5de4",&image_5de4},

    {"seeding_display",&seeding_display},

    {"return_home",&return_home},

    {"unlock_setting",&unlock_setting},

    {"status_password",&status_password},
};

lv_screen_t g_screens[] =
{
    {"main_screen", &main_screen, g_main_screen_ids, (sizeof(g_main_screen_ids) / sizeof(g_main_screen_ids[0]))},
    {"setup", &setup, g_setup_ids, (sizeof(g_setup_ids) / sizeof(g_setup_ids[0]))},
    {"login_windows", &login_windows, g_login_windows_ids, (sizeof(g_login_windows_ids) / sizeof(g_login_windows_ids[0]))},
};

LV_FONT_DECLARE(ali_font_16);
LV_FONT_DECLARE(ali_font_21);
LV_FONT_DECLARE(ali_font_38);
LV_FONT_DECLARE(ali_font_87);
LV_FONT_DECLARE(ali_font_26);


    void show_screen_main_screen();
    void show_screen_setup();
    void show_screen_login_windows();
    void del_screen_login_windows();
    /*
    * keyboard
    */
    lv_obj_t * g_kb = NULL;

    void setting_button_event_handler(lv_obj_t * event_kb, lv_event_t event)
    {
        show_screen_login_windows();
    }

    void return_home_event_handler(lv_obj_t * event_kb, lv_event_t event)
    {
        // del_screen_login_windows();
        show_screen_main_screen();
    }

    void unlock_setting_event_handler(lv_obj_t * event_kb, lv_event_t event)
    {
        // del_screen_login_windows();
        show_screen_setup();
    }

    void home_button_event_handler(lv_obj_t * event_kb, lv_event_t event)
    {
        show_screen_main_screen();
    }


    static void g_kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
    {
    /* Just call the regular event handler */
    if(event == LV_EVENT_APPLY) {
    lv_obj_set_hidden(event_kb, true);
    } else if(event == LV_EVENT_CANCEL) {
    lv_obj_set_hidden(event_kb, true);
    } else {
    lv_keyboard_def_event_cb(event_kb, event);
    }
    }
    static void g_create_kb_ifneeded() {
    if(g_kb == NULL) {
    g_kb = lv_keyboard_create(lv_scr_act(), NULL);
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
    lv_obj_align(g_kb,NULL,LV_ALIGN_IN_BOTTOM_MID,0,0);
}

    /**
    *开机启动屏相关
    */
    static lv_style_t style_star, style_black, style_url;
    LV_IMG_DECLARE(img_8ms_png);
    LV_IMG_DECLARE(img_star);
    lv_obj_t * logo;
    lv_obj_t * logo_star;
    lv_obj_t * url_label;
    lv_obj_t * url_mask;
    lv_obj_t * mask_layer;
    int timer_cnt = 0;
    /****
    * 临时变量用于数据传输
    */
    char _tmpbuf[32];

  

    
    /*
    * declear codes
    */



#ifndef LV_8MS_PRESET_UART_QUEUE
void lv_8ms_uart_queue_ana(uint8_t* data,int size){   
    printf("ana:%s\n",wtctrl_json_parse((char *)data));
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

    void lv_8ms_image_9f2b_create()
{
    image_9f2b = lv_img_create(main_screen, NULL);
    lv_img_set_src(image_9f2b, &img1627284951998_png);
    lv_obj_set_pos(image_9f2b, 0, 0);
#ifdef BLOCKLY_image_9f2b_EVENT_HANDLER
    lv_obj_set_event_cb(image_9f2b, image_9f2b_event_handler);
#endif
}
    void lv_8ms_label_ce35_create()
{
	label_ce35 = lv_label_create(main_screen, NULL);
	lv_label_set_long_mode(label_ce35,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(label_ce35, 360, 89);
//set label style
	lv_obj_set_style_local_radius(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,11);
	lv_obj_set_style_local_border_color(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
	lv_obj_set_style_local_border_width(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,2);
	lv_obj_set_style_local_text_color(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0xf5, 0x6c, 0x23));
	lv_obj_set_style_local_text_font(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_87);

	lv_label_set_text(label_ce35, "10.69");
	lv_label_set_align(label_ce35, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_label_ce35_EVENT_HANDLER
	lv_obj_set_event_cb(label_ce35, label_ce35_event_handler);
#endif
	if(label_ce35->coords.x2-label_ce35->coords.x1<360)
	{
		int x_offset=(360-(label_ce35->coords.x2-label_ce35->coords.x1))/2;
		lv_obj_set_style_local_pad_left(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(label_ce35->coords.y2-label_ce35->coords.y1<89)
	{
		int y_offset=(89-(label_ce35->coords.y2-label_ce35->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(label_ce35,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(label_ce35, 9, 16);

}
    void lv_8ms_setting_button_create()
{
    setting_button = lv_img_create(main_screen, NULL);
    lv_img_set_src(setting_button, &img1627285477548_png);
    lv_obj_set_pos(setting_button, 305, 246);
    lv_obj_set_click(setting_button,true);
    lv_obj_set_style_local_image_recolor(setting_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(setting_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
// #ifdef BLOCKLY_setting_button_EVENT_HANDLER
    lv_obj_set_event_cb(setting_button, setting_button_event_handler);
// #endif
}
    void lv_8ms_phone_button_create()
{
    phone_button = lv_img_create(main_screen, NULL);
    lv_img_set_src(phone_button, &img1627285517798_png);
    lv_obj_set_pos(phone_button, 133, 246);
    lv_obj_set_click(phone_button,true);
    lv_obj_set_style_local_image_recolor(phone_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(phone_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
#ifdef BLOCKLY_phone_button_EVENT_HANDLER
    lv_obj_set_event_cb(phone_button, phone_button_event_handler);
#endif
}
    void lv_8ms_pH_diss_create()
{
	pH_diss = lv_label_create(main_screen, NULL);
	lv_label_set_long_mode(pH_diss,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(pH_diss, 65, 46);
//set label style
	lv_obj_set_style_local_text_color(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x7e, 0xd3, 0x21));
	lv_obj_set_style_local_text_font(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_38);

	lv_label_set_text(pH_diss, "Lit");
	lv_label_set_align(pH_diss, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_diss_EVENT_HANDLER
	lv_obj_set_event_cb(pH_diss, pH_diss_event_handler);
#endif
	if(pH_diss->coords.x2-pH_diss->coords.x1<65)
	{
		int x_offset=(65-(pH_diss->coords.x2-pH_diss->coords.x1))/2;
		lv_obj_set_style_local_pad_left(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(pH_diss->coords.y2-pH_diss->coords.y1<46)
	{
		int y_offset=(46-(pH_diss->coords.y2-pH_diss->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(pH_diss,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(pH_diss, 389, 171);

}
    void lv_8ms_label_flow_water_create()
{
	label_flow_water = lv_label_create(main_screen, NULL);
	lv_label_set_long_mode(label_flow_water,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(label_flow_water, 360, 95);
//set label style
	lv_obj_set_style_local_radius(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,12);
	lv_obj_set_style_local_border_color(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
	lv_obj_set_style_local_border_width(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,2);
	lv_obj_set_style_local_text_color(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x7e, 0xd3, 0x21));
	lv_obj_set_style_local_text_font(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_87);

	lv_label_set_text(label_flow_water, "123124");
	lv_label_set_align(label_flow_water, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_label_flow_water_EVENT_HANDLER
	lv_obj_set_event_cb(label_flow_water, label_flow_water_event_handler);
#endif
	if(label_flow_water->coords.x2-label_flow_water->coords.x1<360)
	{
		int x_offset=(360-(label_flow_water->coords.x2-label_flow_water->coords.x1))/2;
		lv_obj_set_style_local_pad_left(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(label_flow_water->coords.y2-label_flow_water->coords.y1<95)
	{
		int y_offset=(95-(label_flow_water->coords.y2-label_flow_water->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(label_flow_water,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(label_flow_water, 9, 122);

}
    void lv_8ms_pH_7850_create()
{
	pH_7850 = lv_label_create(main_screen, NULL);
	lv_label_set_long_mode(pH_7850,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(pH_7850, 65, 46);
//set label style
	lv_obj_set_style_local_text_color(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0xf5, 0x6c, 0x23));
	lv_obj_set_style_local_text_font(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_38);

	lv_label_set_text(pH_7850, "pH");
	lv_label_set_align(pH_7850, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_pH_7850_EVENT_HANDLER
	lv_obj_set_event_cb(pH_7850, pH_7850_event_handler);
#endif
	if(pH_7850->coords.x2-pH_7850->coords.x1<65)
	{
		int x_offset=(65-(pH_7850->coords.x2-pH_7850->coords.x1))/2;
		lv_obj_set_style_local_pad_left(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(pH_7850->coords.y2-pH_7850->coords.y1<46)
	{
		int y_offset=(46-(pH_7850->coords.y2-pH_7850->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(pH_7850,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(pH_7850, 389, 62);

}
    void lv_8ms_image_57b1_create()
{
    image_57b1 = lv_img_create(setup, NULL);
    lv_img_set_src(image_57b1, &img1627285614032_png);
    lv_obj_set_pos(image_57b1, 0, 0);
#ifdef BLOCKLY_image_57b1_EVENT_HANDLER
    lv_obj_set_event_cb(image_57b1, image_57b1_event_handler);
#endif
}
    void lv_8ms_home_button_create()
{
    home_button = lv_img_create(setup, NULL);
    lv_img_set_src(home_button, &img1627285431674_png);
    lv_obj_set_pos(home_button, 211, 243);
    lv_obj_set_click(home_button,true);
    lv_obj_set_style_local_image_recolor(home_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(home_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
// #ifdef BLOCKLY_home_button_EVENT_HANDLER
    lv_obj_set_event_cb(home_button, home_button_event_handler);
// #endif
}
    void lv_8ms_mail_button_create()
{
    mail_button = lv_img_create(setup, NULL);
    lv_img_set_src(mail_button, &img1627285659756_png);
    lv_obj_set_pos(mail_button, 119, 243);
    lv_obj_set_click(mail_button,true);
    lv_obj_set_style_local_image_recolor(mail_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(mail_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
#ifdef BLOCKLY_mail_button_EVENT_HANDLER
    lv_obj_set_event_cb(mail_button, mail_button_event_handler);
#endif
}
    void lv_8ms_wifi_button_create()
{
    wifi_button = lv_img_create(setup, NULL);
    lv_img_set_src(wifi_button, &img1627285685903_png);
    lv_obj_set_pos(wifi_button, 303, 243);
    lv_obj_set_click(wifi_button,true);
    lv_obj_set_style_local_image_recolor(wifi_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(wifi_button,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
#ifdef BLOCKLY_wifi_button_EVENT_HANDLER
    lv_obj_set_event_cb(wifi_button, wifi_button_event_handler);
#endif
}
    void lv_8ms_dropdown_select_filter_create()
{
    dropdown_select_filter = lv_dropdown_create(setup, NULL);
    lv_obj_set_size(dropdown_select_filter, 123, 86);
    lv_obj_set_pos(dropdown_select_filter, 8, 11);
    lv_dropdown_set_options(dropdown_select_filter,
    "Lõi 1""\n"
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
    lv_obj_set_style_local_text_color(dropdown_select_filter,LV_DROPDOWN_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x15, 0x7a, 0xe9));
    lv_obj_set_style_local_text_color(dropdown_select_filter,LV_DROPDOWN_PART_LIST,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x15, 0x7a, 0xe9));
/*
设置字体大小颜色结束
*/
}
    void lv_8ms_info_filter_create()
{
	info_filter = lv_label_create(setup, NULL);
	lv_label_set_long_mode(info_filter,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(info_filter, 216, 193);
//set label style
	lv_obj_set_style_local_radius(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,12);
	lv_obj_set_style_local_border_width(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,2);
	lv_obj_set_style_local_text_color(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x4a, 0x90, 0xe2));
	lv_obj_set_style_local_text_font(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_16);

	lv_label_set_text(info_filter, "Filter 1: 124124 Lit");
	lv_label_set_align(info_filter, LV_LABEL_ALIGN_LEFT);
#ifdef BLOCKLY_info_filter_EVENT_HANDLER
	lv_obj_set_event_cb(info_filter, info_filter_event_handler);
#endif
	if(info_filter->coords.x2-info_filter->coords.x1<216)
	{
		int x_offset=(216-(info_filter->coords.x2-info_filter->coords.x1))/2;
		lv_obj_set_style_local_pad_left(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(info_filter->coords.y2-info_filter->coords.y1<193)
	{
		int y_offset=(193-(info_filter->coords.y2-info_filter->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(info_filter,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(info_filter, 142, 11);

}
    void lv_8ms_clear_button_create()
{
    clear_button = lv_img_create(setup, NULL);
    lv_img_set_src(clear_button, &img1627300475973_png);
    lv_obj_set_pos(clear_button, 399, 20);
#ifdef BLOCKLY_clear_button_EVENT_HANDLER
    lv_obj_set_event_cb(clear_button, clear_button_event_handler);
#endif
}
    void lv_8ms_edit_button_create()
{
    edit_button = lv_img_create(setup, NULL);
    lv_img_set_src(edit_button, &img1627300495627_png);
    lv_obj_set_pos(edit_button, 399, 125);
#ifdef BLOCKLY_edit_button_EVENT_HANDLER
    lv_obj_set_event_cb(edit_button, edit_button_event_handler);
#endif
}
    void lv_8ms_image_5de4_create()
{
    image_5de4 = lv_img_create(login_windows, NULL);
    lv_img_set_src(image_5de4, &img1627285614032_png);
    lv_obj_set_pos(image_5de4, 0, 0);
#ifdef BLOCKLY_image_5de4_EVENT_HANDLER
    lv_obj_set_event_cb(image_5de4, image_5de4_event_handler);
#endif
}
    void lv_8ms_seeding_display_create()
{
	seeding_display = lv_label_create(login_windows, NULL);
	lv_label_set_long_mode(seeding_display,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(seeding_display, 245, 40);
//set label style
	lv_obj_set_style_local_radius(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,12);
	lv_obj_set_style_local_border_width(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,1);
	lv_obj_set_style_local_text_color(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0x90, 0x13, 0xfe));
	lv_obj_set_style_local_text_font(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_21);

	lv_label_set_text(seeding_display, "12E32A3CF5A1");
	lv_label_set_align(seeding_display, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_seeding_display_EVENT_HANDLER
	lv_obj_set_event_cb(seeding_display, seeding_display_event_handler);
#endif
	if(seeding_display->coords.x2-seeding_display->coords.x1<245)
	{
		int x_offset=(245-(seeding_display->coords.x2-seeding_display->coords.x1))/2;
		lv_obj_set_style_local_pad_left(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(seeding_display->coords.y2-seeding_display->coords.y1<40)
	{
		int y_offset=(40-(seeding_display->coords.y2-seeding_display->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(seeding_display,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(seeding_display, 114, 18);

}
    void lv_8ms_return_home_create()
{
    return_home = lv_img_create(login_windows, NULL);
    lv_img_set_src(return_home, &img1627313782026_png);
    lv_obj_set_pos(return_home, 123, 216);
    lv_obj_set_click(return_home,true);
    lv_obj_set_style_local_image_recolor(return_home,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(return_home,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
// #ifdef BLOCKLY_return_home_EVENT_HANDLER
    lv_obj_set_event_cb(return_home, return_home_event_handler);
// #endif
}
    void lv_8ms_unlock_setting_create()
{
    unlock_setting = lv_img_create(login_windows, NULL);
    lv_img_set_src(unlock_setting, &img1627313837606_png);
    lv_obj_set_pos(unlock_setting, 295, 216);
    lv_obj_set_click(unlock_setting,true);
    lv_obj_set_style_local_image_recolor(unlock_setting,LV_IMG_PART_MAIN,LV_STATE_PRESSED,LV_COLOR_BLACK);
    lv_obj_set_style_local_image_recolor_opa(unlock_setting,LV_IMG_PART_MAIN,LV_STATE_PRESSED,60);
// #ifdef BLOCKLY_unlock_setting_EVENT_HANDLER
    lv_obj_set_event_cb(unlock_setting, unlock_setting_event_handler);
// #endif
}
    void lv_8ms_status_password_create()
{
	status_password = lv_label_create(login_windows, NULL);
	lv_label_set_long_mode(status_password,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(status_password, 354, 40);
//set label style
	lv_obj_set_style_local_text_color(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_MAKE(0xe6, 0x0f, 0x0f));
	lv_obj_set_style_local_text_font(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_26);

	lv_label_set_text(status_password, "enter password");
	lv_label_set_align(status_password, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_status_password_EVENT_HANDLER
	lv_obj_set_event_cb(status_password, status_password_event_handler);
#endif
	if(status_password->coords.x2-status_password->coords.x1<354)
	{
		int x_offset=(354-(status_password->coords.x2-status_password->coords.x1))/2;
		lv_obj_set_style_local_pad_left(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(status_password->coords.y2-status_password->coords.y1<40)
	{
		int y_offset=(40-(status_password->coords.y2-status_password->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(status_password,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(status_password, 63, 78);

}

void show_screen_main_screen()
{
        lv_scr_load(main_screen);
//生成动态页面的style
    
}
void show_screen_setup()
{
        lv_scr_load(setup);
//生成动态页面的style
    
}
void show_screen_login_windows()
{
        if(!login_windows)
        {
        login_windows = lv_obj_create(NULL, NULL);
        lv_8ms_image_5de4_create();
        lv_8ms_seeding_display_create();
        lv_8ms_return_home_create();
        lv_8ms_unlock_setting_create();
        lv_8ms_status_password_create(); 
        }
        lv_scr_load(login_windows);
//生成动态页面的style
    
}
void del_screen_login_windows()
{
    if(login_windows)
    lv_obj_del(login_windows);
    login_windows=NULL;
}

int screen_loop_enter = 0;
int _delay = 0;
void lv_qm_ui_loop(void)
{
        /**
* image_9f2b动画切换
*/
// if(image_9f2b_anmi_on) {
//     if((image_9f2b_anmi_index % 20) == 0) {
//     lv_img_set_src(image_9f2b, image_9f2b_anmi[image_9f2b_anmi_index/20]);
//     if(image_9f2b_anmi_index == 0*20) {
//     image_9f2b_anmi_index = -19;
//     }
//     }
//     image_9f2b_anmi_index ++;
// }
        
        
        
        
        
        
        
        
        
        
        
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
    setup = lv_obj_create(NULL, NULL);
    
    lv_scr_load(main_screen);

//CREATE STATIC OBJ
    lv_8ms_image_9f2b_create();
    lv_8ms_label_ce35_create();
    lv_8ms_setting_button_create();
    lv_8ms_phone_button_create();
    lv_8ms_pH_diss_create();
    lv_8ms_label_flow_water_create();
    lv_8ms_pH_7850_create();
    lv_8ms_image_57b1_create();
    lv_8ms_home_button_create();
    lv_8ms_mail_button_create();
    lv_8ms_wifi_button_create();
    lv_8ms_dropdown_select_filter_create();
    lv_8ms_info_filter_create();
    lv_8ms_clear_button_create();
    lv_8ms_edit_button_create();
  
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
    if (!obj) {
        return NULL;
    }

    int i = 0, j = 0;
    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        if (*(g_screens[i].id) == obj) {
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