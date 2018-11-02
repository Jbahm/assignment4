#include <iostream>
#include <fstream>
#include "GenQueue.h"
#include "line.hpp"


int main(int argc, char** argv){
  string fileName;
  cout << "Enter the name of the text file" << endl;
  cin >> fileName;
  ifstream isValid;
  isValid.open(fileName);
  while(isValid.fail()){
    cout << "Error, file does not exsist, enter another file name" << endl;
    cin >> fileName;
    cout << "" << endl;
    isValid.open(fileName);
  }
  isValid.close();
  line L(fileName);
  L.moveLine();

}
