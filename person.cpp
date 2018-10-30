#include <iostream>
#include "person.hpp"


using namespace std;


person::person(){
  timeNeeded = 0;
  timeSpent = 0;
  timeWaited = 0;
  arrivalTime = 0;
}

person::person(int needs, int arrived){
  timeNeeded = needs;
  arrivalTime = arrived;
  timeSpent = 0;
  timeWaited = 0;
}

void person::isWaiting(){
  timeWaited += 1;
}

void person::isAtWindow(){
  timeSpent += 1;
}

bool person::isFinished(){
  return timeSpent == timeNeeded;
}

int person::getArrivalTick(){
  return arrivalTime;
}

int person::getWaitTime(){
  return timeWaited;
}

void person::printPerson(){
  cout << "Person: " << endl;
  cout << "Arrived " << arrivalTime << endl;
  cout << "Needs " << timeNeeded << endl;
}
