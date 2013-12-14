// Author: Casey Anderson
// Date: 11/20/13

#include "ListCollection.h"
#include <serstream>

#define PIN_BUZZER  8

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
  
  if(!_scroll_right_history.empty())
  {
    // update current index with stack value
    _current_list = _scroll_right_history.top();
    
    // pop current list index off stack
    _scroll_right_history.pop();
  
    // display current list
    drawCurrList(LCDdisplay);
  }
}

void ListCollection::scrollRight(Adafruit_PCD8544 LCDdisplay)
{
  if(_lists[_current_list].getNextIndex() >= 0)  // keep traversing right
  {
    // update stack with current list index
    _scroll_right_history.push(_current_list);
    
    // update current list index
    _current_list = _lists[_current_list].getNextIndex();
    
 //   cout << "_current_list changed to: " << _current_list << endl;
    
    // display current list
    drawCurrList(LCDdisplay);
  }
  else  // send messge (should probably make this its own private function
        // because it's going to get a lot more complicated)
  {
    cout << endl;
    while(!_scroll_right_history.empty())
    {
      cout << _lists[_current_list].getString() << " ";
      _current_list = _scroll_right_history.top();
      _scroll_right_history.pop();     
    }
    cout << _lists[_current_list].getString() << endl;
    
    // TODO: Print message sent on screen
/*    
    // vibrate buzzer
    digitalWrite(PIN_BUZZER, LOW);  // buzzer on
    delay(500);
    digitalWrite(PIN_BUZZER, HIGH);  // buzzer off
*/    
    // display current list (should be starting point now)
    drawCurrList(LCDdisplay);
  }
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
