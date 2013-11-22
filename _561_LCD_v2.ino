// Author: Casey Anderson
// Date: 11/20/13

#include <StandardCplusplus.h>
#include <serstream>
#include <vector>
#include <stack>
#include <iterator>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "ListDisplay.h"
#include "ListCollection.h"

using namespace std;

// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.
namespace std
{
  ohserialstream cout(Serial);
}

Adafruit_PCD8544 LCDdisplay = Adafruit_PCD8544(7, 6, 5, 4, 3);

ListDisplay list0;
ListDisplay list1;
ListDisplay list2;
ListDisplay list3;
/*
char* vec_fruits[] = {"Apple", "Banana", "Peaches", "Strawberries", "melon", "cherry", "tomatoe", "orange"};  //Index 0
char* vec_actions[] = {"Eat", "Smash", "Make pie"};                                                           //Index 1
char* vec_times[] = {"Immediately", "ASAP", "Soon", "In 10 min", "Tomorrow"};                                //Index 2
*/
#define  ADVERBS  0
#define  CLOTHES  1
#define  PERSON   2
#define  ACTION   3
char* vec0[] = {"immediately", "quickly", "slowly", "violently", "seductively", "angrily", "in 5 min.", "eventually"};           //Index 0
char* vec1[] = {"jacket", "pants", "shirt", "socks", "underwear", "bra", };          //Index 1
char* vec2[] = {"your", "my", "both of our", "Miley Cyrus's"};              //Index 2
char* vec3[] = {"Take off", "Rip off", "Put on", "Destroy", "Obliterate", "Ignite", "Eat", "Lick", "Clean", "Idolize"};        //Index 3
const int NUM0 = sizeof(vec0) / sizeof(vec0[0]);
const int NUM1 = sizeof(vec1) / sizeof(vec1[0]);
const int NUM2 = sizeof(vec2) / sizeof(vec2[0]);
const int NUM3 = sizeof(vec3) / sizeof(vec3[0]);
const int NUM_LISTS = 4;

// Top level collection of all ListDisplays
ListCollection master;

void setup()
{
  Serial.begin(9600);
  
  LCDdisplay.begin();
  LCDdisplay.setContrast(50);
  LCDdisplay.clearDisplay();
  LCDdisplay.setTextSize(1);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(0,0);
  
  // Initialize list0
  vector< pair<string, int> > vector0;
  for(int i = 0; i < NUM0; ++i)
  {
    vector0.push_back(make_pair(vec0[i], CLOTHES));
  }
  list0.setItems(vector0);
  list0.setIndex(ADVERBS);
  
  // Initialize list1
  vector< pair<string, int> > vector1;
  for(int i = 0; i < NUM1; ++i)
  {
    vector1.push_back(make_pair(vec1[i], PERSON));
  }
  list1.setItems(vector1);
  list1.setIndex(CLOTHES);
  
  // Initialize list2
  vector< pair<string, int> > vector2;
  for(int i = 0; i < NUM2; ++i)
  {
    vector2.push_back(make_pair(vec2[i], ACTION));
  }
  list2.setItems(vector2);
  list2.setIndex(PERSON);
  
  // Initialize list3
  vector< pair<string, int> > vector3;
  for(int i = 0; i < NUM3; ++i)
  {
    vector3.push_back(make_pair(vec3[i], -1));
  }
  list3.setItems(vector3);
  list3.setIndex(ACTION);
   
  // Initialize master List Collection
  vector<ListDisplay> lists;
  lists.push_back(list0);
  lists.push_back(list1);
  lists.push_back(list2);
  lists.push_back(list3);
  master.setLists(lists);
  
//  list.drawItems(LCDdisplay);
  master.drawCurrList(LCDdisplay);
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
//    Serial.println("x left");
    master.scrollLeft(LCDdisplay);
    while(analogRead(xPin) > xLeftThresh);
    xLeftCnt = 0;
  }
  
  if(xRightCnt > cntThresh)
  {
//    Serial.println("x right");
/*
    fruits_active = !fruits_active;
    if (fruits_active)
      list.drawItems(LCDdisplay);
    else
      list2.drawItems(LCDdisplay);
*/
    master.scrollRight(LCDdisplay);
    while(analogRead(xPin) < xRightThresh);
    xRightCnt = 0;
  }
  
  if(yUpCnt > cntThresh)
  {
//    Serial.println("y up");
    master.scrollUp(LCDdisplay);
/*
    if (fruits_active)
      list.scrollUp(LCDdisplay);
    else
      list2.scrollUp(LCDdisplay);
*/
    while(analogRead(yPin) < yUpThresh);
    yUpCnt = 0;
  }
  
  if(yDownCnt > cntThresh)
  {
//    Serial.println("y down");
    master.scrollDown(LCDdisplay);
/*
    if (fruits_active)
      list.scrollDown(LCDdisplay);
    else
      list2.scrollDown(LCDdisplay);
*/
    while(analogRead(yPin) > yDownThresh);
    yDownCnt = 0;
  }
}
