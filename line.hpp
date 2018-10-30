#include <iostream>
#include "person.hpp"
#include "genQueue.h"

using namespace std;

class line
{
  public:
    line();
    line(string fileName);//populate line in here

    int peopleHelped;
    int totalPeople;
    int windowCount;
    int windowsOver5;
    double averageIdle;
    int timesIdle;
    int longestIdle;
    int ticks;
    DoublyLinkedList<person> entered;

    int *idleTimes;
    int *waitTimes;
    bool *windows;
    person *personAtWindow;

    void addToLine(GenQueue<person> regLine);
    void moveLine(); //This should be the main loop
    int windowsOpen();
    void clearWindows();
    void updateIdleWindows();
    int findMedian();
    void outputStats();
    void updateWaitTime(GenQueue<person> regLine);

    void printLine();//debugging purposes

};
