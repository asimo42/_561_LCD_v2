// Author: Casey Anderson
// Date: 11/20/13

#include <serstream>
#include "ListDisplay.h"

using namespace std;

ListDisplay::ListDisplay()
{
  
}

ListDisplay::ListDisplay(vector< pair<string, ListDisplay *> > items)
{
  _items = items;
  _highlighted_item = 0;
  _top_item = 0;
}

/*
void ListDisplay::printItems()
{
  for(int i = 0; i < _items.size(); i++)
    cout << _items[i];
}
*/

void ListDisplay::setItems(vector< pair<string, ListDisplay *> > items)
{
  _items = items;
}

// Draws six items on the screen starting with _top_item.
// This only works for strings that only take up one line.
void ListDisplay::drawItems(Adafruit_PCD8544 LCDdisplay)
{
  LCDdisplay.clearDisplay();
  LCDdisplay.setCursor(0,0);  
  
  for(int i = _top_item; i < _top_item+6 && i < _items.size(); i++)
  {
    cout << "printing " << i << "th item" << endl;
    if(_highlighted_item == i)
    {
      LCDdisplay.setTextColor(WHITE, BLACK);
      LCDdisplay.println(getString(i).c_str());
    }
    else
    {
      LCDdisplay.setTextColor(BLACK, WHITE);
      LCDdisplay.println(getString(i).c_str());
    }
  }
  LCDdisplay.display();
}

// Scrolls down the list. i.e. increments _highlighted_item.
// If bottom of screen is reached, _top_item is adjusted.
void ListDisplay::scrollDown(Adafruit_PCD8544 LCDdisplay)
{ 
  if(_highlighted_item < _items.size() - 1)
    _highlighted_item++;
    
  if((_top_item == _highlighted_item - 6))
    _top_item += 6;
  
  cout << "Highlighted item: " << _highlighted_item << endl;
  cout << "Top item: " << _top_item << endl;
    
  drawItems(LCDdisplay);
}

// Scrolls up the list. i.e. decrements _highlighted_item.
// If top of screen is reached, _top_item is adjusted.
void ListDisplay::scrollUp(Adafruit_PCD8544 LCDdisplay)
{
  if(_highlighted_item > 0) 
    _highlighted_item--;
  
  if(_top_item == _highlighted_item + 1)
    _top_item -= 6;
  
  cout << "Highlighted item: " << _highlighted_item << endl;
  cout << "Top item: " << _top_item << endl;
  
  drawItems(LCDdisplay);
}

// Return string at index
string ListDisplay::getString(int index)
{
   return _items[index].first; 
}

// Return ListDisplay at index
ListDisplay ListDisplay::getListDisplay(int index)
{
  ListDisplay *tmp = _items[index].second;
  return *tmp;
}
