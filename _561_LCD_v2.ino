#include <StandardCplusplus.h>
#include <serstream>
#include <vector>
#include <iterator>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "ListDisplay.h"

using namespace std;

// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

Adafruit_PCD8544 LCDdisplay = Adafruit_PCD8544(7, 6, 5, 4, 3);
ListDisplay list;
char* vec_fruits[] = {"Apple", "Banana", "Peach", "Strawberries", "melon", "cherry", "tomatoe", "orange"};
const int NUM_FRUITS = sizeof(vec_fruits) / sizeof(vec_fruits[0]);


void setup()
{
  Serial.begin(9600);
  
  cout << NUM_FRUITS << endl;
  
  LCDdisplay.begin();
  LCDdisplay.setContrast(50);
  LCDdisplay.clearDisplay();
  LCDdisplay.setTextSize(1);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(0,0);
  
  vector<string> fruits;
  for(int i = 0; i < NUM_FRUITS; ++i)
  {
    fruits.push_back(vec_fruits[i]);
  }
 
  list.setItems(fruits);
  
  list.drawItems(LCDdisplay);
}

//Analog input pins
const int xPin = A0;
const int yPin = A1;
// slider x and y analog values
int xVal = 0;
int yVal = 0;
// threshoold values for x and y on push button (center is about (500,500) )
const int xLeftThresh = 600;
const int xRightThresh = 400;
const int yUpThresh = 400;
const int yDownThresh = 600;
//counters to debounce slider
int xLeftCnt = 0;
int xRightCnt = 0;
int yUpCnt = 0;
int yDownCnt = 0;
// Number of consecutive times above/below threshold to trigger a left/right/up/down
const int cntThresh = 10; 

void loop()
{
  //***********************************
  // Read slider values and update counters

  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  
  if(xVal > xLeftThresh)
    ++xLeftCnt;
  else
    xLeftCnt = 0;
    
  if(xVal < xRightThresh)
    ++xRightCnt;
  else
    xRightCnt = 0;
    
  if(yVal < yUpThresh)
    ++yUpCnt;
  else
    yUpCnt = 0;
    
  if(yVal > yDownThresh)
    ++yDownCnt;
  else
    yDownCnt = 0;

//****************************************************
// Check if left/right/up/down triggered

  if(xLeftCnt > cntThresh)
  {
    Serial.println("x left");
    while(analogRead(xPin) > xLeftThresh);
    xLeftCnt = 0;
  }
  
  if(xRightCnt > cntThresh)
  {
    Serial.println("x right");
    while(analogRead(xPin) < xRightThresh);
    xRightCnt = 0;
  }
  
  if(yUpCnt > cntThresh)
  {
    Serial.println("y up");
    list.scrollUp(LCDdisplay);
    while(analogRead(yPin) < yUpThresh);
    yUpCnt = 0;
  }
  
  if(yDownCnt > cntThresh)
  {
    Serial.println("y down");
    list.scrollDown(LCDdisplay);
    while(analogRead(yPin) > yDownThresh);
    yDownCnt = 0;
  }
}
