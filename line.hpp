#include <iostream>
#include "person.hpp"

using namespace std;

class line
{
  public:
    line();
    line(int fileName);//populate line in here

    int peopleHelped;
    int totalPeople;
    int windowCount;
    int ticks;
    person entered[10];
    bool *windows;
    person *personAtWindow;

  //void addToLine();
    void moveLine(); //This should be the main loop
    int windowsOpen();
    void clearWindows();

    void printLine();//debugging purposes

};
