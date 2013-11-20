#ifndef HEADER_LISTCOLLECTION
#define HEADER_LISTCOLLECTION

#include "ListDisplay.h"

class ListDisplay
{
  public:
  ListDisplay();
  ListDisplay(vector<ListDisplay> lists);
  
  void setLists(vector<ListDisplay> lists);
  void scrollDown(Adafruit_PCD8544 LCDdisplay);
  void scrollUp(Adafruit_PCD8544 LCDdisplay);
  void scrollLeft(Adafruit_PCD8544 LCDdisplay);
  void scrollRight(Adafruit_PCD8544 LCDdisplay);

  private:
  vector<ListDisplay> _lists;
}

#endif

