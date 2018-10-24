#include <iostream>
#include "person.hpp"

using namespace std;

class line
{
  public:
    line();
    line(int maxPeople);//populate line in here


    int peopleHelped;
    int ticks;
    person entered[10];

    void addToLine();
    void moveLine(); //This should be the main loop
    bool isFinished();

    void printLine();//debugging purposes

};
