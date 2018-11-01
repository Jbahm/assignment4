#include <iostream>
#include "GenQueue.h"
#include "line.hpp"


int main(int argc, char** argv){
  line L("test.txt");
  L.findMedian();
//  L.moveLine();
  L.outputStats();
}
