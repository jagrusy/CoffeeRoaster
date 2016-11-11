// Variables
const int sensorPin = A0;
const float maxtemp = 450.0;
const float mintemp = 420.0;
double TF;                  // Temp read from thermocouple
double runAvg[5];           // Running average array for temperature
int k = 0;                  // Current value of running avg array being overwritten
#define relay1 2
#define relay2 4
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);



void setup(void) {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  delay(1000);
  // large block of text
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.print("Welcome Home, Baby");
  delay(3000);
  // Initialize relay pins as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  // Initialize relays to off
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  for (int i = 0; i < 5; i++) {
    runAvg[i] = getTemp();
  }
  // Call menu
  menu();
  delay(2000);
}

// Main function
void loop() {
  k = (k + 1) % 5;
  tft.invertDisplay(false);
 
  TF = getTemp();
  runAvg[k] = TF;                   // Put current temp in running average
  TF = getAvg(runAvg);              // Update temp from 5 point running average
  //print temperature in Celsius
  Serial.println(TF);
  
  if(TF < mintemp){
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  } else {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  }
  
  tft.setTextWrap(false);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Current Temp: ");
  tft.println(TF);
  tft.println("Current Time: ");
  uint16_t time = millis();
  time = millis() - time;
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds");
  delay(835);
}

double getTemp() {
  // equation to calculated temperature
  int A0 = analogRead(0);
  double Vin=(5*A0);
  float vinl=Vin/1024;
  double Vout=vinl-1.25;
  double T = Vout/0.005;
  TF = (T*1.8)+32;
  return TF;
}

double getAvg(double arr[]) {
  double sum = 0;
  for(int i = 0; i < 5; i++) {
    sum += arr[i];
  }
  return sum / 5;
}

// This function will display a main menu to select roast/temperature
void menu() {

}



