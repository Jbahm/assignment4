#include <iostream>
#include <fstream>
#include "line.hpp"
#include "GenQueue.h"

using namespace std;

line::line(){
  peopleHelped = 0;
  ticks = 0;
}

//from the file, takes how many people have arrived
line::line(string fileName){
  ticks = 0;
  peopleHelped = 0;
  ifstream people;
  string currentLine;
  int arrivalTick = 0;
  totalPeople = 0;
  int counter = 0;

  people.open(fileName); //opens the file
  people >> currentLine;
  windowCount = stoi(currentLine);
  personAtWindow = new person[windowCount];
  windows = new bool[windowCount];
  idleTimes = new int[windowCount];

  while(!people.eof()){
    people >> currentLine;
    arrivalTick = stoi(currentLine);
    people >> currentLine;
    int peopleArriving = stoi(currentLine);

    for(int i = 0; i < peopleArriving; i++){
      people >> currentLine;
      person p(stoi(currentLine), arrivalTick);
      totalPeople++;
      entered.enqueue(p);
    }
  }
  waitTimes = new int[totalPeople];

}

//finds if there is a open window
int line::windowsOpen(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == false){
      return i;
    }
  }
  return -1;
}

//clears a window after a student is done
void line::clearWindows(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == true){
      if(personAtWindow[i].isFinished()){
        windows[i] = false;
        peopleHelped++; //increments the number of people helped
        waitTimes[peopleHelped] = personAtWindow[i].getWaitTime();
        cout << "Person at Window " << i << " is finished!" << endl;
      }
    }
  }
}

//finds the median wait time of the students
int line::findMedian(){
  for(int i = 0; i < totalPeople; i++){
    waitTimes[i].vFront();
    }
  if((totalPeople%2) ==1){ //if odd number of elements, return the middle
    return waitTimes[(totalPeople/2)+1];
  }
  else{ //if even number of elements, find the average of the middle two
    int average = (waitTimes[(totalPeople/2)] + waitTimes[(totalPeople/2) + 1])/2;
    return average;
  }
}
/*if(waitTimes[i] > waitTimes[i+1]){
  int temp = waitTimes[i];
  waitTimes[i] = waitTimes[i+1];
  waitTimes[i+1] = temp;*/

//outputs the stats of the studnet times and window times
void line::outputStats(){
  double meanWait = 0;
  int medianWait = 0;
  averageIdle =
  /*int longestWait = 0;
  int waitedOverTen = 0;
   averageIdle/timesIdle;

  for(int i = 0; i < totalPeople; i++){
    meanWait += waitTimes[i];
    cout <<"HERE" << waitTimes[i] << endl;
    if(longestWait < waitTimes[i]){
      longestWait = waitTimes[i];
    }
    if(waitTimes[i] > 10){
      waitedOverTen++;
    }*/
    medianWait = findMedian();
  //}
    //meanWait = meanWait/totalPeople;

  cout << "The average student wait time is: " << meanWait << " minutes!" << endl;
  cout << "The median student wait time is: " << medianWait << " minutes!" << endl;
  /*cout << "The longest student wait time is: " << longestWait << " minutes!" << endl;
  cout << waitedOverTen << " students waited over 10 minutes" << endl;
  cout << "" << endl;
  cout << "Windows were idle for an average of " << averageIdle << " minutes!" << endl;
  cout << "The longest window idle time is: " << longestIdle << endl;
  cout << windowsOver5 << " windows were idle for over 5 minutes" << endl;*/
}

//
void line::addToLine(){
  person p = entered.vFront();
  while(p.getArrivalTick() == ticks){
    regLine.enqueue(p);
    entered.dequeue();
    p = entered.vFront();
  }
}

//updates the student wait time
void line::updateWaitTime(){
  GenQueue<person> copy;
  while(!regLine.isEmpty()){
    person temp1 = regLine.vFront();
    regLine.dequeue();
    copy.enqueue(temp1);
  }
//while the queue isn't empty
  while(!copy.isEmpty()){
    person temp = copy.vFront();
    copy.dequeue();
    temp.isWaiting();
    regLine.enqueue(temp);
  }

}

//updates the time that a window was free for (helping no students)
void line::updateIdleWindows(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == false){
      idleTimes[i]++;
     }
    if(windows[i] == true){ //finds the number of windows idle for over 5 min
      if(idleTimes[i] > 5){
        windowsOver5++;
      }
      timesIdle++;
      averageIdle += idleTimes[i];

      if(idleTimes[i] > longestIdle){
        longestIdle = idleTimes[i];
      }
      idleTimes[i] = 0;
    }
  }
}

//checks to see if there are any empty windows
bool line::windowsAreEmpty(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == true){
      return false;
    }
  }
  return true;
}


void line::moveLine(){
    while(ticks < 6){///FIX ME
        if(entered.isEmpty() == false){
          addToLine();
        }

      cout << "===========" << endl;
      cout << "Tick: " << ticks << endl;
      cout << "Entered" << endl;
      entered.printQ();
      cout << "--------------" << endl;
      cout << "Line" << endl;
      regLine.printQ();
      cout << "==============" << endl;

      clearWindows();

      while(windowsOpen() != -1 && !regLine.isEmpty()){
        person temp = regLine.vFront();
        int openWindow = windowsOpen();
        windows[openWindow] = true;
        personAtWindow[openWindow] = temp;
        regLine.dequeue();
        cout << "++++" << endl;
        cout << "Is at the window: " << endl;
        temp.printPerson();
        cout << "++++" << endl;
      }
      for(int i = 0; i < windowCount; i++){
        personAtWindow[i].isAtWindow();
      }
      updateWaitTime();
      if(ticks == 5){
        person test = regLine.vFront();
        cout << test.getWaitTime() << endl;

      }
      ticks++;
    }
}
void line::debugLine(){


}
