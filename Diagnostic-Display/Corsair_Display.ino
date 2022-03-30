#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
#define TEXT_SIZE 6


int devCount = 2;
float coolantTemp = 0;
int x1, y1, w, h;
char buff[5];
char buf[20];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);

  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.begin(ID);
  tft.setRotation(3);
  tft.setTextColor(WHITE);
  tft.setTextSize(TEXT_SIZE);
  tft.setFont(NULL);
  tft.setCursor(0, 0);
  tft.fillScreen(BLACK);
}

void loop() {
  if (Serial.available() > 0){
    for(int i; i < devCount; i++){
      displayFloat(i * (TEXT_SIZE * 8), 0, "Temp: ")
    }
    delay(3000);
  }
}
void displayFloat(int x, int y, char* prefix){
    float val = Serial.readStringUntil('\n').toFloat();
    dtostrf(val, -2, 2, buff);
    Serial.print(val + String("\n"));
    tft.setCursor(x, y);
    sprintf(buf, "%03s %03s", prefix, buff);
    tft.getTextBounds(buf, x, y, x1, y1, w, h);
    tft.fillRect(x, y, w, h, BLACK);
    tft.print(buf);
}
