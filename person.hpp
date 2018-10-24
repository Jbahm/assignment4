#include <iostream>


using namespace std;

class person
{
  public:
    person();
    person(int needs, int arrived);
    int timeNeeded;
    int timeSpent;
    int timeWaited;
    int arrivalTime;


    void isWaiting();
    void isAtWindow();

    void printPerson(); //debugging purposes
};
