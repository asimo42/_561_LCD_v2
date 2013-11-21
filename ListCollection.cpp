// Author: Casey Anderson
// Date: 11/20/13

#include "ListCollection.h"

using namespace std;

ListCollection::ListCollection()
{
  
}

ListCollection::ListCollection(vector<ListDisplay> lists)
{
  _lists = lists;
  _current_list = 0;
}

void ListCollection::setLists(vector<ListDisplay> lists)
{
  _lists = lists;
}

void ListCollection::scrollDown(Adafruit_PCD8544 LCDdisplay)
{
  _lists[_current_list].scrollDown(LCDdisplay);
}

void ListCollection::scrollUp(Adafruit_PCD8544 LCDdisplay)
{
  _lists[_current_list].scrollUp(LCDdisplay);
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
