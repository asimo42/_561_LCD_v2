#ifndef HEADER_LISTCOLLECTION
#define HEADER_LISTCOLLECTION

#include <stack>
#include "ListDisplay.h"
//#include <stack>

using namespace std;

class ListCollection
{
  public:
  ListCollection();
  ListCollection(vector<ListDisplay> lists);
  
  void setLists(vector<ListDisplay> lists);
  void scrollDown(Adafruit_PCD8544 LCDdisplay);
  void scrollUp(Adafruit_PCD8544 LCDdisplay);
  void scrollLeft(Adafruit_PCD8544 LCDdisplay);
  void scrollRight(Adafruit_PCD8544 LCDdisplay);

  private:
  // Holds all unique lists. e.g. list of people, list of actions, list of messages
  vector<ListDisplay> _lists;
  
  // Holds index of current list being displayed
  int _current_list;
  
  // Holds indices of ListDisplays that have been navigated right through so scrollLeft() can retrace steps backward
  stack<int> _scroll_right_history;
};

#endif

