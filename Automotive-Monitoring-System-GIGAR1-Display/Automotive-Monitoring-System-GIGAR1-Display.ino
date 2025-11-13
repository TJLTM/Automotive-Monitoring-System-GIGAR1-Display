#include <Arduino_CAN.h>
#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include <Arduino_GigaDisplay.h>
#include "lvgl.h"

Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;

GigaDisplayRGB rgb;

lv_obj_t* InformationLabel1A;
lv_obj_t* InformationLabel1B;

lv_obj_t* InformationLabel2A; 
lv_obj_t* InformationLabel2B;


lv_obj_t* Bottom_label1;
lv_obj_t* Bottom_label2;
lv_obj_t* Bottom_label3;

long Timer = 0;
bool Settings = false;

/* Button click event callback */
static void btn_event_cb(lv_event_t* e) {
  static uint32_t cnt = 1;
  lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);
  lv_obj_t* label = lv_obj_get_child(btn, 0);
  lv_label_set_text_fmt(label, "%" LV_PRIu32, cnt);
  cnt++;
}

static void Setting_btn_event_cb(lv_event_t* e) {
  if (Settings == false) {
    Settings = true;
    SettingsPage();
  } else {
    MainPage();
    Settings = false;
  }
}

void setup() {
  Serial.begin(115200);

  rgb.begin();
  
  Display.begin();
  TouchDetector.begin();

  MainPage();
}

void MainPage() {
  /* Create a container with grid 1x3 */
  static lv_coord_t col_dsc[] = { 765, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 350, 80, LV_GRID_TEMPLATE_LAST };
  lv_obj_t* cont = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
  lv_obj_set_size(cont, Display.width(), Display.height());
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x623e27), LV_PART_MAIN);
  lv_obj_center(cont);

  lv_obj_t* obj;

  /* [0;0] - Top Main */
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 0, 1);

  /* [0;1] - Main */
  static lv_point_precise_t line_points[] = { { 0, 45 }, { 240, 45 } };
  static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 8);
  lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
  lv_style_set_line_rounded(&style_line, true);

  /*Create a line and apply the new style*/
  lv_obj_t* line1;
  line1 = lv_line_create(obj);
  lv_line_set_points(line1, line_points, 2); /*Set the points*/
  lv_obj_add_style(line1, &style_line, 0);

  InformationLabel1A = lv_label_create(obj);
  lv_label_set_text(InformationLabel1A, "Label1");

  InformationLabel1B = lv_label_create(obj);
  lv_label_set_text(InformationLabel1B, "Label2");
  lv_obj_set_pos(InformationLabel1B, 100, 0);


  /* [0;1] - Bottom Navigation Section */
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t* Bottom_btn_1 = lv_btn_create(obj);
  lv_obj_set_size(Bottom_btn_1, 210, 75);
  lv_obj_align(Bottom_btn_1, LV_ALIGN_LEFT_MID, 0, 0);
  // lv_obj_add_event_cb(Bottom_btn_1, btn_event_cb, LV_EVENT_CLICKED, NULL);
  Bottom_label1 = lv_label_create(Bottom_btn_1);
  lv_label_set_text(Bottom_label1, "Previous");
  lv_obj_center(Bottom_label1);

  lv_obj_t* Bottom_btn_2 = lv_btn_create(obj);
  lv_obj_set_size(Bottom_btn_2, 210, 75);
  lv_obj_align(Bottom_btn_2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(Bottom_btn_2, Setting_btn_event_cb, LV_EVENT_CLICKED, NULL);
  Bottom_label2 = lv_label_create(Bottom_btn_2);
  lv_label_set_text(Bottom_label2, "Settings");
  lv_obj_center(Bottom_label2);

  lv_obj_t* Bottom_btn_3 = lv_btn_create(obj);
  lv_obj_set_size(Bottom_btn_3, 210, 75);
  lv_obj_align(Bottom_btn_3, LV_ALIGN_RIGHT_MID, 0, 0);
  // lv_obj_add_event_cb(Bottom_btn_2, btn_event_cb, LV_EVENT_CLICKED, NULL);
  Bottom_label3 = lv_label_create(Bottom_btn_3);
  lv_label_set_text(Bottom_label3, "Next");
  lv_obj_center(Bottom_label3);
}


void SettingsPage() {
  /* Create a container with grid 1x3 */
  static lv_coord_t col_dsc[] = { 765, LV_GRID_TEMPLATE_LAST };
  static lv_coord_t row_dsc[] = { 350, 80, LV_GRID_TEMPLATE_LAST };
  lv_obj_t* cont = lv_obj_create(lv_scr_act());
  lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
  lv_obj_set_size(cont, Display.width(), Display.height());
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x623e27), LV_PART_MAIN);
  lv_obj_center(cont);

  lv_obj_t* obj;

  /* [0;0] - Top Banner */
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 0, 1);

  /* [0;1] - Bottom Navigation Section */
  obj = lv_obj_create(cont);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1,
                       LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t* Bottom_btn_2 = lv_btn_create(obj);
  lv_obj_set_size(Bottom_btn_2, 175, 75);
  lv_obj_align(Bottom_btn_2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(Bottom_btn_2, Setting_btn_event_cb, LV_EVENT_CLICKED, NULL);
  Bottom_label2 = lv_label_create(Bottom_btn_2);
  lv_label_set_text(Bottom_label2, "EXIT");
  lv_obj_center(Bottom_label2);

}



void CANBusRecieveCheck() {
  if (CAN.available())
  {
    CanMsg const msg = CAN.read();
    Serial.println(msg);
  }
} 



void loop() {
  CANBusRecieveCheck();

  /* Feed LVGL engine */
  lv_timer_handler();


  long CurrentTime = millis();
  if (abs(CurrentTime - Timer) > 500) {
    lv_label_set_text_fmt(InformationLabel1B, "Value: %d", CurrentTime, LV_FONT_MONTSERRAT_18);
    
    Timer = CurrentTime;
  }
