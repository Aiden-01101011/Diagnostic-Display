#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

const int numDev = 0;




String coolantTemp = "";
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
    tft.fillRect(0,0, 400, 100, BLACK);
    displaySerial(0, 0, "Temp: ");
  }
  
  
  void displaySerial(int x, int y, char* prefix){
    char[20] messsage = Serial.readStringUntil('\n');
    Serial.print(message);
    tft.setCursor(x, y);
    sprintf(buf, "%03s %03s ",prefix , message);
    tft.print(buf);
    delay(50);
  }
}
