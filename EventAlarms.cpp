// Author: Casey Anderson
// Date: 12/8/13

#include "EventAlarms.h"
#include <Time.h>
#include <TimeAlarms.h>
#include <serstream>

vector<pair<string, HMS_time> > _events;
int _alarm_index;

using namespace std;
/*
vector<pair<string, HMS_time> > events;
int alarm_index = 0;

void soundAlarm()
{
  cout << events[alarm_index].first << endl;
  ++alarm_index;  
}

void setAlarms(vector<pair<string, HMS_time> > events)
{
  for(int i = 0; i < events.size(); i++)
  {
    Alarm.alarmOnce(events[i].second.hour, events[i].second.min, events[i].second.sec, soundAlarm);
  }
}
*/

void* ptr;


EventAlarms::EventAlarms()
{
  _alarm_index = 0;
}

void EventAlarms::setEvents(vector<pair<string, HMS_time> > &events)
{
  _events = events;
  _alarm_index = 0;
}

void EventAlarms::soundAlarm()
{
  cout << "Alarm index: " << _alarm_index << endl;
  cout << "Sounding alarm: " << _events[_alarm_index].first << endl;
  
  ++_alarm_index;
}

void EventAlarms::wrapper_soundAlarm()
{
  EventAlarms* myself = (EventAlarms*) ptr;
  myself->soundAlarm();
}

void EventAlarms::setAllAlarms()
{
  _alarm_index = 0;
  
  for(int i = 0; i < _events.size(); i++)
  {
    Alarm.alarmOnce(_events[i].second.hour, _events[i].second.min, _events[i].second.sec, wrapper_soundAlarm);
  }

}
