// Author: Casey Anderson
// Date: 12/8/13

#ifndef HEADER_EVENTALARMS
#define HEADER_EVENTALARMS

#include <StandardCplusplus.h>
#include <vector>
#include <string>

using namespace std;

typedef struct HMS_time
{
  int hour;
  int min;
  int sec;
} HMS_time;



class EventAlarms {
 public:
  EventAlarms();
  
  void setEvents(vector<pair<string, HMS_time> > &events);  
  void setAllAlarms();
 
 private:
  void soundAlarm();
  static void wrapper_soundAlarm();
 
  //vector<pair<string, HMS_time> > _events; 
  //int _alarm_index;
};


//void soundAlarm();
//void setAlarms(vector<pair<string, HMS_time> > events);


#endif 
