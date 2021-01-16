#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

int main () {
  string furniture = "stoel";
  string stat = "1";
  string str = "{\"" + furniture + "\":\"" + stat + "\"}";
  // string str = "{Stoel:1}";
  cout << str << endl;

  // string id = strtok(str, ":");
  // printf("%s\n", id);
  // string status = strtok(NULL, ":");
  // printf("%s\n", status);
  return 0;
}
