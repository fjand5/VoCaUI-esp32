#include <ArduinoJson.h>
#include <WS2812FX.h>
#include "ESP32_RMT_Driver.h"
#include "ws.h"
#include "store.h"
// The ESP32's RMT hardware supports up to 8 channels, so it
// can drive up to 8 independent WS2812FX instances. We'll use 2.
WS2812FX ws2812fx = WS2812FX(270, 23, NEO_GRB + NEO_KHZ800); // 144 RGB LEDs driven by GPIO_12
int ws2812fx_mode = 0;


void responseStatus(){
    DynamicJsonDocument doc(512);
    JsonObject ws2812fxObj = doc.to<JsonObject>();
    ws2812fxObj["mode"] = ws2812fx.getMode(1);
    ws2812fxObj["speed"] = ws2812fx.getSpeed(1);
    ws2812fxObj["brightness"] = ws2812fx.getBrightness();
    ws2812fxObj["color1"] = ws2812fx.getColors(1)[0];
    ws2812fxObj["color2"] = ws2812fx.getColors(1)[1];
    ws2812fxObj["color3"] = ws2812fx.getColors(1)[2];
    String ret;
    serializeJsonPretty(ws2812fxObj,ret);
    webSocket.broadcastTXT(ret);
}
void adaptiveMode(){
  if(ws2812fx_mode == FX_MODE_BLINK){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_BREATH){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_COLOR_WIPE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_COLOR_WIPE_INV){
    ws2812fx_mode = FX_MODE_COLOR_WIPE_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_COLOR_WIPE_REV){
    ws2812fx_mode = FX_MODE_COLOR_WIPE_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_COLOR_WIPE_REV_INV){
    ws2812fx_mode = FX_MODE_COLOR_WIPE_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_COLOR_WIPE_RANDOM){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_RANDOM_COLOR){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_SINGLE_DYNAMIC){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_MULTI_DYNAMIC){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_RAINBOW){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_RAINBOW_CYCLE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_SCAN){
    ws2812fx_mode = FX_MODE_FADE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_DUAL_SCAN){
    ws2812fx_mode = FX_MODE_FADE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FADE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_THEATER_CHASE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 30000);
  }else if(ws2812fx_mode == FX_MODE_THEATER_CHASE_RAINBOW){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 30000);
  }else if(ws2812fx_mode == FX_MODE_RUNNING_LIGHTS){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_TWINKLE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_TWINKLE_RANDOM){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_TWINKLE_FADE){
    ws2812fx_mode = FX_MODE_HYPER_SPARKLE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_TWINKLE_FADE_RANDOM){
    ws2812fx_mode = FX_MODE_HYPER_SPARKLE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_SPARKLE){
    ws2812fx_mode = FX_MODE_HYPER_SPARKLE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FLASH_SPARKLE){
    ws2812fx_mode = FX_MODE_HYPER_SPARKLE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_HYPER_SPARKLE){
    ws2812fx_mode = FX_MODE_HYPER_SPARKLE;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_HYPER_SPARKLE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1000);
  }else if(ws2812fx_mode == FX_MODE_STROBE){
    ws2812fx_mode = FX_MODE_STROBE_RAINBOW;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_STROBE_RAINBOW){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_MULTI_STROBE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_BLINK_RAINBOW){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_WHITE){
    ws2812fx_mode = FX_MODE_CHASE_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_COLOR){
    ws2812fx_mode = FX_MODE_CHASE_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_RANDOM){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_RAINBOW){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_FLASH){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_FLASH_RANDOM){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_RAINBOW_WHITE){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_BLACKOUT){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_CHASE_BLACKOUT_RAINBOW){
    ws2812fx_mode = FX_MODE_COLOR_SWEEP_RANDOM;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_COLOR_SWEEP_RANDOM){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 500);
  }else if(ws2812fx_mode == FX_MODE_RUNNING_COLOR){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_RUNNING_RED_BLUE){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_RUNNING_RANDOM){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_LARSON_SCANNER){
    ws2812fx_mode = FX_MODE_FIREWORKS;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_LARSON_SCANNER){
    ws2812fx_mode = FX_MODE_FIREWORKS;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 100);
  }else if(ws2812fx_mode == FX_MODE_FIREWORKS){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FIREWORKS){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FIREWORKS_RANDOM){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_MERRY_CHRISTMAS){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FIRE_FLICKER){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FIRE_FLICKER_SOFT){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_FIRE_FLICKER_INTENSE){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_CIRCUS_COMBUSTUS){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_HALLOWEEN){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_BICOLOR_CHASE){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_TRICOLOR_CHASE){
    ws2812fx_mode = FX_MODE_TWINKLEFOX;
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }else if(ws2812fx_mode == FX_MODE_TWINKLEFOX){
    ws2812fx.setMode(1,ws2812fx_mode);
    ws2812fx.setSpeed(1, 1);
  }
  responseStatus();

}
void ledFullHandle(void *params)
{
  uint32_t timer = millis();
  while (1)
  {
    ws2812fx.service();
    if (millis() - timer > 30000)
    {
      ws2812fx_mode ++;
      if(ws2812fx_mode > 55)
        ws2812fx_mode =0;
      adaptiveMode();
      timer = millis();
    }
  }
}
void setupLedFull()
{
  ws2812fx.init();

  ws2812fx.setBrightness(getValue("brightness", "128").toInt());
  rmt_tx_int(RMT_CHANNEL_0, ws2812fx.getPin());
  //   ws2812fx.setCustomShow(myCustomShow1);
  // parameters: seg_index, start, stop, mode, color, speed, options
  ws2812fx.setSegment(0, 0, 26, FX_MODE_BREATH, MAGENTA, 100, NO_OPTIONS);
  ws2812fx.setSegment(1, 27, 270 - 1, FX_MODE_BREATH, GREEN, 10000, NO_OPTIONS);
  uint32_t colors[3];
  colors[0] = WHITE;
  colors[1] = RED;
  colors[2] = BLUE;
  ws2812fx.setColors(0, colors);
  colors[0] = CYAN;
  colors[1] = MAGENTA;
  colors[2] = RED;
  ws2812fx.setColors(1, colors);
  ws2812fx.start();

  setOnWSTextIncome([](String msg){
    DynamicJsonDocument doc(512);
    auto error = deserializeJson(doc, msg);
    if(error)
      return;
    JsonObject objData = doc.as<JsonObject>();
    String cmd = objData["cmd"];
    String val = objData["val"];

    // String ledInit = getValue("ledInit", "[]");


    if(cmd == "setMode"){
      ws2812fx_mode=val.toInt();
      ws2812fx.setMode(1, ws2812fx_mode);
    }else if(cmd == "setSpeed"){
      ws2812fx.setSpeed(1, val.toInt());
    }else if(cmd == "nextMode"){
      ws2812fx_mode++;
      if(ws2812fx_mode > 55)
        ws2812fx_mode= 0;
      ws2812fx.setMode(1, ws2812fx_mode);
    }else if(cmd == "preMode"){
      ws2812fx_mode--;
      if(ws2812fx_mode < 0)
        ws2812fx_mode = 55;
      ws2812fx.setMode(1, ws2812fx_mode);
    }else if(cmd == "setBrightness"){
      setValue("brightness", val, true);
      ws2812fx.setBrightness(val.toInt());
    }else if(cmd == "setColor1"){
      uint32_t* colors;
      colors = ws2812fx.getColors(1);
      colors[0] = val.toInt();
      ws2812fx.setColors(1, colors);
    }else if(cmd == "setColor2"){
      uint32_t* colors;
      colors = ws2812fx.getColors(1);
      colors[1] = val.toInt();
      ws2812fx.setColors(1, colors);
    }else if(cmd == "setColor3"){
      uint32_t* colors;
      colors = ws2812fx.getColors(1);
      colors[2] = val.toInt();
      ws2812fx.setColors(1, colors);
    }
    responseStatus();
  });

  xTaskCreatePinnedToCore(
      ledFullHandle,        /* Task function. */
      "ledFullHandle",      /* name of task. */
      30000,                /* Stack size of task */
      NULL,                 /* parameter of the task */
      configMAX_PRIORITIES, /* priority of the task */
      NULL,                 /* Task handle to keep track of created task */
      1);                   /* pin task to core 0 */
}

// Custom show functions which will use the RMT hardware to drive the LEDs.
// Need a separate function for each ws2812fx instance.
// void myCustomShow1(void) {
//   uint8_t *pixels = ws2812fx1.getPixels();
//   // numBytes is one more then the size of the ws2812fx's *pixels array.
//   // the extra byte is used by the driver to insert the LED reset pulse at the end.
//   uint16_t numBytes = ws2812fx1.getNumBytes() + 1;
//   rmt_write_sample(RMT_CHANNEL_0, pixels, numBytes, false); // channel 0
// }

// void myCustomShow2(void) {
//   uint8_t *pixels = ws2812fx2.getPixels();
//   // numBytes is one more then the size of the *pixels array.
//   // the extra byte is used by the driver to insert the LED reset pulse at the end.
//   uint16_t numBytes = ws2812fx2.getNumBytes() + 1;
//   rmt_write_sample(RMT_CHANNEL_1, pixels, numBytes, false); // channel 1
// }