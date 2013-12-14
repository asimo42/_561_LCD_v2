// Author: Casey Anderson
// Date: 11/20/13

#include <StandardCplusplus.h>
#include <serstream>
#include <vector>
#include <stack>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Time.h>
#include <TimeAlarms.h>
#include "ListDisplay.h"
#include "ListCollection.h"
//#include "EventAlarms.h"

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
char* vec_times[] = {"Immediately", "ASAP", "Soon", "In 10 min", "Tomorrow"};                                 //Index 2
*/
#define  ADVERB   3
#define  WHO      2
#define  ACTION   1
#define  TOWHO    0

#define PIN_BUZZER  8

char* vec0[] = {"immediately", "quickly", "soon", "in 5 min.", "eventually"};           //Index 0
char* vec1[] = {" ", "John", "Bob", "Ryan", "Sally", "Kevin", "Casey", "Amanda"};          //Index 1
char* vec2[] = {"Find", "Help", "Serve food", "Cut the cake", "Play music"};              //Index 2
char* vec3[] = {"To All:", "To John:", "To Bob:", "To Ryan:", "To Sally:", "To Kevin:", "To Casey:", "To Amanda:"};        //Index 3
const int NUM0 = sizeof(vec0) / sizeof(vec0[0]);
const int NUM1 = sizeof(vec1) / sizeof(vec1[0]);
const int NUM2 = sizeof(vec2) / sizeof(vec2[0]);
const int NUM3 = sizeof(vec3) / sizeof(vec3[0]);
const int NUM_LISTS = 4;

int myInt;

// Top level collection of all ListDisplays
ListCollection master;

char buffer[64];
int bufferIndex = 0;

typedef struct HMS_time
{
  int hour;
  int min;
  int sec;
} HMS_time;

// Alarm stuff
vector<pair<string, HMS_time> > event_list;
int alarm_index = 0;

// sets alarms for scheduled events
//EventAlarms event_alarms;
char* events[] = {"Everyone seated.", "Bride and groom enter.", "Serve food."};
const int NUM_EVENTS = sizeof(events) / sizeof(events[0]);

void setup()
{
  Serial.begin(9600);
  
  setTime(17,0,0,12,1,13); // set time to Saturday 5:00:00pm Dec 1 2013
  //Alarm.timerRepeat(0, 0, 15, Repeats);
  
  // Set buzzer pin as output
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, HIGH);  //buzzer off
  
  LCDdisplay.begin();
  LCDdisplay.setContrast(50);
  LCDdisplay.clearDisplay();
  LCDdisplay.setTextSize(1);
  LCDdisplay.setTextColor(BLACK);
  LCDdisplay.setCursor(0,0);
  
//  LCDdisplay.println("Starting...");
//  delay(500);
  
  // Initialize events
  HMS_time time0 = {17, 0, 10};
  HMS_time time1 = {17, 0, 15};
  HMS_time time2 = {17, 0, 30};
  
  event_list.push_back(make_pair(events[0], time0));
  event_list.push_back(make_pair(events[1], time1));
  event_list.push_back(make_pair(events[2], time2));
  
  for(int i = 0; i < event_list.size(); i++)
  {
    Alarm.alarmOnce(event_list[i].second.hour, event_list[i].second.min, event_list[i].second.sec, soundAlarm);
  }
  
  // Initialize list0
  vector< pair<string, int> > vector0;
  for(int i = 0; i < NUM0; ++i)
  {
    vector0.push_back(make_pair(vec0[i], -1));
  }
  list0.setItems(vector0);
  list0.setIndex(ADVERB);
  
  // Initialize list1
  vector< pair<string, int> > vector1;
  for(int i = 0; i < NUM1; ++i)
  {
    vector1.push_back(make_pair(vec1[i], ADVERB));
  }
  list1.setItems(vector1);
  list1.setIndex(WHO);
  
  // Initialize list2
  vector< pair<string, int> > vector2;
  for(int i = 0; i < NUM2; ++i)
  {
    vector2.push_back(make_pair(vec2[i], WHO));
  }
  list2.setItems(vector2);
  list2.setIndex(ACTION);
  
  // Initialize list3
  vector< pair<string, int> > vector3;
  for(int i = 0; i < NUM3; ++i)
  {
    vector3.push_back(make_pair(vec3[i], ACTION));
  }
  list3.setItems(vector3);
  list3.setIndex(TOWHO);
   
  // Initialize master List Collection
  vector<ListDisplay> lists;
  lists.push_back(list3);
  lists.push_back(list2);
  lists.push_back(list1);
  lists.push_back(list0);
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
  /*
  LCDdisplay.clearDisplay();
  LCDdisplay.setCursor(0,0); 
  LCDdisplay.println("Loop");
  LCDdisplay.display();
  delay(100);
  */
 // myInt = Serial.read();

if (Serial.available() > 0){  
  while(Serial.available() > 0)
  {
    char ch = Serial.read();
    if (ch == '\r')
    {
      buffer[bufferIndex] = 0;
      bufferIndex = 0;
      
      LCDdisplay.clearDisplay();
      LCDdisplay.setCursor(0,0);
      LCDdisplay.print("From PC>> ");
      LCDdisplay.println(buffer);
      LCDdisplay.print(" at ");
      digitalClockDisplay();
      LCDdisplay.display();
      
      buffer[0] = 0;
      // buz  
      digitalWrite(PIN_BUZZER, LOW);  // buzzer on
      delay(250);
      digitalWrite(PIN_BUZZER, HIGH); //buzzer off
      delay(150);
      digitalWrite(PIN_BUZZER, LOW);
      delay(250);
      digitalWrite(PIN_BUZZER, HIGH);
    }
    else buffer[bufferIndex++] = ch;
  }
}

  Alarm.delay(0);  // must include this delay function to service alarms
  
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
    master.scrollRight(LCDdisplay);
    while(analogRead(xPin) < xRightThresh);
    xRightCnt = 0;
  }
  
  if(yUpCnt > cntThresh)
  {
//    Serial.println("y up");
    master.scrollUp(LCDdisplay);
    while(analogRead(yPin) < yUpThresh);
    yUpCnt = 0;
  }
  
  if(yDownCnt > cntThresh)
  {
//    Serial.println("y down");
    master.scrollDown(LCDdisplay);
    while(analogRead(yPin) > yDownThresh);
    yDownCnt = 0;
  }
}

void soundAlarm()
{
  cout << "Event update: " << event_list[alarm_index].first << endl;
  LCDdisplay.clearDisplay();
  LCDdisplay.setCursor(0,0);
  LCDdisplay.print("Event update: ");
  LCDdisplay.println(event_list[alarm_index].first.c_str());
  digitalClockDisplay();
  LCDdisplay.display();
  
  // buzz
  digitalWrite(PIN_BUZZER, LOW);  // buzzer on
  delay(250);
  digitalWrite(PIN_BUZZER, HIGH); //buzzer off
  delay(150);
  digitalWrite(PIN_BUZZER, LOW);
  delay(250);
  digitalWrite(PIN_BUZZER, HIGH);
  
  ++alarm_index;
}

void Timer()
{
  cout << "Timer." << endl;
}

void Repeats(){
  Serial.println("15 second timer");         
}

void digitalClockDisplay()
{
  // digital clock display of the time
  LCDdisplay.print(hour());
  printDigits(minute());
  printDigits(second());
  LCDdisplay.println(); 
}

void printDigits(int digits)
{
  LCDdisplay.print(":");
  if(digits < 10)
    LCDdisplay.print('0');
  LCDdisplay.print(digits);
}

