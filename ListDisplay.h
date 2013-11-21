#ifndef HEADER_LISTDISPLAY
#define HEADER_LISTDISPLAY

#include <StandardCplusplus.h>
#include <vector>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <utility>
//#include "Globals.h"

using namespace std;

class ListDisplay
{
 public:
 
  ListDisplay();  
  ListDisplay(vector< pair<string, ListDisplay *> > items);
  
  void setItems(vector< pair<string, ListDisplay *> > items);
  void drawItems(Adafruit_PCD8544 LCDdisplay);
  void scrollDown(Adafruit_PCD8544 LCDdisplay);
  void scrollUp(Adafruit_PCD8544 LCDdisplay);
  string getString(int index);
  ListDisplay getListDisplay(int index);

  
 private:

  // String is diplayed on screen, ListDisplay pointer points to next ListDisplay for scroll right
  vector< pair<string, ListDisplay *> > _items;
  
  // Index of item currently highlighted
  int _highlighted_item;
  
  // Index of item currently at the top of the screen
  int _top_item;
  
};

#endif
