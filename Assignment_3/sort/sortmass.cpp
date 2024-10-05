#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include "sortmass.h"

using namespace std;

ObjMassPair getObjMassPair(const string &objectLine)
{
  istringstream iss(objectLine);
  string name;
  double mass;

  iss >> name >> mass;

  return ObjMassPair(name, mass);
}

void readObjects(ifstream &objects, vector<ObjMassPair> &obj_mass)
{
  string objectLine;

  while (!objects.eof())
  {
    getline(objects, objectLine);

    if (!objectLine.empty())
    {
      ObjMassPair object = getObjMassPair(objectLine);
      obj_mass.emplace_back(object);
    }
  }
}

int main()
{
  ifstream objects("objects.txt");
  ofstream outfile("output.txt");
  string name;
  double mass;

  vector<ObjMassPair> obj_mass;
  // read the contents of the objects file in to the obj_mass vector
  //  --- Your code here

  // ---
  readObjects(objects, obj_mass);
  sort(obj_mass.begin(), obj_mass.end(), customComparator);

  // you will need to properly overload the << operator (in sortmass.h)
  // to print obj_mass to cout
  // look at the form expected in the given output.txt
  cout << obj_mass;
  outfile << obj_mass;
}
