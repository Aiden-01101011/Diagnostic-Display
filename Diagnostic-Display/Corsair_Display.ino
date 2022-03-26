#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410




float coolantTemp = 0;
char buff[6];
char buf[20];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(3);

  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.begin(ID);
  tft.setRotation(3);
  tft.setTextColor(WHITE);
  tft.setTextSize(6);
  tft.setFont(NULL);
  tft.setCursor(0, 0);
  tft.fillScreen(BLACK);
}

void loop() {
  if (Serial.available() > 0){
    coolantTemp = Serial.readStringUntil('\n').toFloat();
    dtostrf(coolantTemp, -2, 2, buff);
    Serial.print(x);
    tft.setCursor(0, 0);
    sprintf(buf, "Temp: %03s ", buff);
    tft.fillRect(0,0, 400, 100, BLACK);
    tft.print(buf);
    delay(50);
  }
}
