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

//increments if there is a student waiting in line
void person::isWaiting(){
  timeWaited += 1;
}

//increments if there is a student at a window
void person::isAtWindow(){
  timeSpent += 1;
}

//returns time it took for the student to be finished
bool person::isFinished(){
  return timeSpent == timeNeeded;
}

//returns the arrival time of a st
int person::getArrivalTick(){
  return arrivalTime;
}

//returns the students wait time
int person::getWaitTime(){
  if(timeWaited == 0){
    return 0;
  }else{
    return timeWaited-1;
  }
  }


//print the student stats
void person::printPerson(){
  cout << "" << endl;
  cout << "Person" << endl;
  cout << "Arrived " << arrivalTime << endl;
  cout << "Needs " << timeNeeded << endl;
}
