#include <iostream>
#include <fstream>
#include "line.hpp"

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
      entered[counter] = p;
      counter++;
    }
  }
}

void line::printLine(){
  for(int i = 0; i < 3; i++){
    entered[i].printPerson();
  }

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
        //do stat collecting stuff here
      }
    }
  }
}

void line::moveLine(){
    while(peopleHelped < totalPeople){
      //addToLine();
      clearWindows();
      while(windowsOpen() != -1){
        windows[windowsOpen()] = true;

        //person temp = front of queue
        //dequeue person in front of line
        //personAtWindow[windowsOpen()] = temp;
      }
    /*  for(int i = 0; i < length of queue, i++){
        queue[i].isWaiting();
      }*/
      for(int j = 0; j < windowCount; j++){
        personAtWindow[j].isAtWindow();
      }
      ticks++;
  }

}
