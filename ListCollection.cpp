// Author: Casey Anderson
// Date: 11/20/13

#include "ListCollection.h"
#include <serstream>

using namespace std;

ListCollection::ListCollection()
{
  
}

ListCollection::ListCollection(vector<ListDisplay> lists)
{
  _lists = lists;
  _current_list = 0;
}

void ListCollection::setLists(vector<ListDisplay> &lists)
{
  _lists = lists;
/*  
  // Assign indexes for looking up in scrollRight()
  for (int i = 0; i < _lists.size(); i++)
  {
    _lists[i].index = i;
    cout << "Assigning index " << i << " to list" << endl;
  }
*/
}

void ListCollection::scrollDown(Adafruit_PCD8544 LCDdisplay)
{
  _lists[_current_list].scrollDown(LCDdisplay);
}

void ListCollection::scrollUp(Adafruit_PCD8544 LCDdisplay)
{
  _lists[_current_list].scrollUp(LCDdisplay);
}

void ListCollection::scrollLeft(Adafruit_PCD8544 LCDdisplay)
{
  
}

void ListCollection::scrollRight(Adafruit_PCD8544 LCDdisplay)
{
  // update stack with current list index
  _scroll_right_history.push(_current_list);
  
  // update current list index
  _current_list = _lists[_current_list].getNextIndex();
/*
  ListDisplay tmp = _lists[_current_list];
  cout << "Current index: " << tmp.index << endl;
  ListDisplay next = tmp.getNextList();
  cout << "Next index: " << next.index << endl;
  //_current_list = _lists[_current_list].getNextList().index;
  if(_current_list < 2)
    _current_list++;
*/
  cout << "_current_list changed to: " << _current_list << endl;

  
  // display current list
  drawCurrList(LCDdisplay);
}

/*
ListDisplay ListCollection::getCurrList()
{
  return _lists[_current_list];
}
*/

void ListCollection::drawCurrList(Adafruit_PCD8544 LCDdisplay)
{
  _lists[_current_list].drawItems(LCDdisplay);
}
