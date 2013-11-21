// Author: Casey Anderson
// Date: 11/20/13

#ifndef HEADER_LISTCOLLECTION
#define HEADER_LISTCOLLECTION

#include <stack>
#include "ListDisplay.h"
//#include <stack>

using namespace std;

/*
This class is used as an object to store and display a collection of ListDisplays on a PCD8544
monochrome display. It allows the user to scroll up and down the ListDisplays as well as 
scroll left and right to change ListDisplays. Each item in a ListDisplay also contains a pointer 
to another ListDisplay that gets displayed when the user scrolls right on that item.
A stack saves the "scroll right" history so scroll left knows how to navigate back through the Lists.
*/

class ListCollection
{
  public:
  ListCollection();
  ListCollection(vector<ListDisplay> lists);
  
  void setLists(vector<ListDisplay> &lists);
  void scrollDown(Adafruit_PCD8544 LCDdisplay);
  void scrollUp(Adafruit_PCD8544 LCDdisplay);
  void scrollLeft(Adafruit_PCD8544 LCDdisplay);
  void scrollRight(Adafruit_PCD8544 LCDdisplay);
//  ListDisplay getCurrList();
  void drawCurrList(Adafruit_PCD8544 LCDdisplay);

  private:
  // Holds all unique lists. e.g. list of people, list of actions, list of messages
  vector<ListDisplay> _lists;
  
  // Holds index of current list being displayed
  int _current_list;
  
  // Holds indices of ListDisplays that have been navigated right through so scrollLeft() can retrace steps backward
  stack<int> _scroll_right_history;
};

#endif

