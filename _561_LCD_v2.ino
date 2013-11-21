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

ListDisplay list;
ListDisplay list2;
ListDisplay list3;
char* vec_fruits[] = {"Apple", "Banana", "Peaches", "Strawberries", "melon", "cherry", "tomatoe", "orange"};
char* vec_actions[] = {"Eat", "Smash", "Make pie"};
char* vec_times[] = {"Immediately", "ASAP", "Soon", "In 10 min", "Tomorrow"};
const int NUM_FRUITS = sizeof(vec_fruits) / sizeof(vec_fruits[0]);
const int NUM_ACTIONS = sizeof(vec_actions) / sizeof(vec_actions[0]);
const int NUM_TIMES = sizeof(vec_times) / sizeof(vec_times[0]);
const int NUM_LISTS = 3;

// Top level collection of all ListDisplays
ListCollection master;

void setup()
{
  Serial.begin(9600);
  
  cout << NUM_FRUITS << endl;
  cout << NUM_ACTIONS << endl;
  cout << NUM_TIMES << endl;
  
  LCDdisplay.begin();
  LCDdisplay.setContrast(50);
  LCDdisplay.clearDisplay();
  LCDdisplay.setTextSize(1);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(0,0);
  
  // Initialize fruit list
  vector< pair<string, ListDisplay *> > fruits;
  for(int i = 0; i < NUM_FRUITS; ++i)
  {
    fruits.push_back(make_pair(vec_fruits[i], &list2));
  }
  list.setItems(fruits);
  
  // Initialize actions list
  vector< pair<string, ListDisplay *> > actions;
  for(int i = 0; i < NUM_ACTIONS; ++i)
  {
    actions.push_back(make_pair(vec_actions[i], &list3));
  }
  list2.setItems(actions);
  
  // Initialize times list
  vector< pair<string, ListDisplay *> > times;
  for(int i = 0; i < NUM_TIMES; ++i)
  {
    times.push_back(make_pair(vec_times[i], &list));
  }
  list3.setItems(times);
   
  // Initialize master List Collection
  vector<ListDisplay> lists;
  lists.push_back(list);
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
    Serial.println("x left");
    while(analogRead(xPin) > xLeftThresh);
    xLeftCnt = 0;
  }
  
  if(xRightCnt > cntThresh)
  {
    Serial.println("x right");
/*
    fruits_active = !fruits_active;
    if (fruits_active)
      list.drawItems(LCDdisplay);
    else
      list2.drawItems(LCDdisplay);
*/
    while(analogRead(xPin) < xRightThresh);
    xRightCnt = 0;
  }
  
  if(yUpCnt > cntThresh)
  {
    Serial.println("y up");
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
    Serial.println("y down");
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
