#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "sortmass.h"

using namespace std;

int main() {
  ifstream objects("objects.txt");
  ofstream outfile("output.txt");
  string name;
  double mass;

  vector<ObjMassPair> obj_mass;
  //read the contents of the objects file in to the obj_mass vector
  // --- Your code here



  // ---

  //use std::sort to sort obj_mass. You will need to define
  //a function that compares ObjMassPair objects that is of
  //the form expected by std::sort

  // --- Your code here



  // ---

  //you will need to properly overload the << operator (in sortmass.h)
  //to print obj_mass to cout
  //look at the form expected in the given output.txt
  cout << obj_mass;
  outfile << obj_mass;
}
