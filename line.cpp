#include <iostream>
#include <fstream>
#include "line.hpp"
#include "GenQueue.h"

using namespace std;

line::line(){
  int peopleHelped = 0;
  int ticks = 0;
}


line::line(string fileName){
  ticks = 0;
  peopleHelped = 0;
  ifstream people;
  string currentLine;
  int arrivalTick = 0;
  int totalPeople = 0;
  int counter = 0;

  people.open(fileName);
  people >> currentLine;
  windowCount = stoi(currentLine);
  personAtWindow = new person[windowCount];
  windows = new bool[windowCount];
  while(!people.eof()){
    people >> currentLine;
    arrivalTick = stoi(currentLine);
    people >> currentLine;
    int peopleArriving = stoi(currentLine);
    for(int i = 0; i < peopleArriving; i++){
      people >> currentLine;
      person p(stoi(currentLine), arrivalTick);
      totalPeople++;
      entered.insertBack(p);
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
  int meanWait = 0;
  int medianWait = 0;
  int longestWait = 0;
  int waitedOverTen = 0;

  for(int i = 0; i < totalPeople; i++){
    meanWait += waitTimes[i];
    if(longestWait < waitTimes[i]){
      longestWait = waitTimes[i];
    }
    if(waitTimes[i] > 10){
      waitedOverTen++;
    }
    medianWait = findMedian();
  }
}




/*
void line::addToLine(GenQueue<person> regLine){
  ListNode node = entered.getFront();
  while(node->next != NULL){
    person temp = node->data;
    if(temp.getArrivalTick() == ticks){
      regLine.enqueue(temp);
    }
    node = node->next;
  }
}
*/

void line::updateWaitTime(GenQueue<person> regLine){
  GenQueue<person> copy;
  while(!regLine.isEmpty()){
    regLine.dequeue();
  }
  while(!copy.isEmpty()){
    person temp = copy.vFront();
    copy.dequeue();
    temp.isWaiting();
    regLine.enqueue(temp);
  }

}

void line::moveLine(){
    GenQueue<person> regLine;
    while(peopleHelped < totalPeople){
      addToLine(regLine);
      clearWindows();
      while(windowsOpen() != -1){
        windows[windowsOpen()] = true;
        person temp = regLine.vFront();
        regLine.dequeue();
        personAtWindow[windowsOpen()] = temp;
      }
      updateWaitTime(regLine);
      for(int j = 0; j < windowCount; j++){
        personAtWindow[j].isAtWindow();
      }
      ticks++;
  }
  outputStats();
}
