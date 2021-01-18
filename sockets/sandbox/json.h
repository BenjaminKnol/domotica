#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>

using namespace std;

class Json {
public:
  Json(); // Default constructor

  // Ask-function
  string split(string message);
  int to_int(string message);

private:
  string delimiter = ":";
  int index = 0;
  string id;
  int status;
};
