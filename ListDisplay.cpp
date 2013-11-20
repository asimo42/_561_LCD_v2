#include <serstream>
#include "ListDisplay.h"

using namespace std;

ListDisplay::ListDisplay()
{
  
}

ListDisplay::ListDisplay(vector<string> items)
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

void ListDisplay::setItems(vector<string> items)
{
  _items = items;
}

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
      LCDdisplay.println(_items[i].c_str());
    }
    else
    {
      LCDdisplay.setTextColor(BLACK, WHITE);
      LCDdisplay.println(_items[i].c_str());
    }
  }
  LCDdisplay.display();
}

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


