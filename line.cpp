#include <iostream>
#include <fstream>
#include "line.hpp"
#include "GenQueue.h"

using namespace std;

line::line(){
  peopleHelped = 0;
  ticks = 0;
}


line::line(string fileName){
  ticks = 0;
  peopleHelped = 0;
  ifstream people;
  string currentLine;
  int arrivalTick = 0;
  totalPeople = 0;
  int counter = 0;

  people.open(fileName);
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


int line::windowsOpen(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == false){
      return i;
    }
  }
  return -1;
}

void line::clearWindows(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == true){
      if(personAtWindow[i].isFinished()){
        windows[i] = false;
        peopleHelped++;
        waitTimes[peopleHelped] = personAtWindow[i].getWaitTime();
        cout << "Person at Window " << i << " is finished!" << endl;

      }
    }
  }
}

int line::findMedian(){
  for(int i = 0; i < totalPeople-1; i++){
    if(waitTimes[i] > waitTimes[i+1]){
      int temp = waitTimes[i];
      waitTimes[i] = waitTimes[i+1];
      waitTimes[i+1] = temp;
    }
  }
  if((totalPeople%2) != 0){
    return waitTimes[(totalPeople/2)-1];
  }else{
    int average = (waitTimes[(totalPeople/2)] + waitTimes[(totalPeople/2) + 1])/2;
    return average;
  }
}


void line::outputStats(){
  double meanWait = 0;
  int medianWait = 0;
  int longestWait = 0;
  int waitedOverTen = 0;
  averageIdle = averageIdle/timesIdle;

  for(int i = 0; i < totalPeople; i++){
    meanWait += waitTimes[i];
    cout <<"HERE" << waitTimes[i] << endl;
    if(longestWait < waitTimes[i]){
      longestWait = waitTimes[i];
    }
    if(waitTimes[i] > 10){
      waitedOverTen++;
    }
    medianWait = findMedian();
  }
  meanWait = meanWait/totalPeople;

  cout << "The average student wait time is: " << meanWait << " minutes!" << endl;
  cout << "The median student wait time is: " << medianWait << " minutes!" << endl;
  cout << "The longest student wait time is: " << longestWait << " minutes!" << endl;
  cout << waitedOverTen << " students waited over 10 minutes" << endl;
  cout << "" << endl;
  cout << "Windows were idle for an average of " << averageIdle << " minutes!" << endl;
  cout << "The longest window idle time is: " << longestIdle << endl;
  cout << windowsOver5 << " windows were idle for over 5 minutes" << endl;
}





void line::addToLine(){
  person p = entered.vFront();
  while(p.getArrivalTick() == ticks){
    regLine.enqueue(p);
    entered.dequeue();
    p = entered.vFront();
  }
}


void line::updateWaitTime(){
  GenQueue<person> copy;
  while(!regLine.isEmpty()){
    person temp1 = regLine.vFront();
    regLine.dequeue();
    copy.enqueue(temp1);
  }

  while(!copy.isEmpty()){
    person temp = copy.vFront();
    copy.dequeue();
    temp.isWaiting();
    regLine.enqueue(temp);
  }

}

void line::updateIdleWindows(){
  for(int i = 0; i < windowCount; i++){
    if(windows[i] == false){
      idleTimes[i]++;
     }
    if(windows[i] == true){
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
