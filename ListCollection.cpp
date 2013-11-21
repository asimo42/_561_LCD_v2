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
