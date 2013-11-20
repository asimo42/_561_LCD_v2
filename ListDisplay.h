#ifndef HEADER_LISTDISPLAY
#define HEADER_LISTDISPLAY

#include <StandardCplusplus.h>
#include <vector>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
//#include "Globals.h"

using namespace std;

class ListDisplay
{
 public:
 
  ListDisplay();  
  ListDisplay(vector<string> items);
  
  void setItems(vector<string> items);
  void drawItems(Adafruit_PCD8544 LCDdisplay);
  void scrollDown(Adafruit_PCD8544 LCDdisplay);
  void scrollUp(Adafruit_PCD8544 LCDdisplay);

  
 private:
 
  vector<string> _items;
  int _highlighted_item;
  int _top_item;
  
};

#endif
