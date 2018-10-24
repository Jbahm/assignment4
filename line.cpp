#include <iostream>
#include <fstream>
#include "line.hpp"

using namespace std;

line::line(){
  int peopleHelped = 0;
  int ticks = 0;
}


line::line(int maxPeople){
  ifstream people;
  string currentLine;
  int arrivalTick = 0;
  int counter = 0;

  people.open("test.txt");
  people >> currentLine;
  bool windows[stoi(currentLine)];
  while(!people.eof()){
    people >> currentLine;
    arrivalTick = stoi(currentLine);
    people >> currentLine;
    int peopleArriving = stoi(currentLine);
    for(int i = 0; i < peopleArriving; i++){
      people >> currentLine;
      person p(stoi(currentLine), arrivalTick);
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
