#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

double DEG2RAD = M_PI / 180; //this definition will be useful

using namespace std;

int main() {
  ifstream scanfile("input.txt");
  ofstream outfile("output.txt");
  cout << setprecision(4); //this sets how many decimal places to print
  outfile << setprecision(4);

  
  double robot_width;
  double threshold;

  string input;
  for(int i=0; i < 2; i++)
  {
    scanfile >> input;
    if (input == "width:")
      scanfile >> robot_width;
    else if (input == "threshold:")
      scanfile >> threshold;
  }
  cout << "Width: " << robot_width << ", Threshold: " << threshold << endl;
  double temp;
  vector<double> scan_returns;
  while (scanfile >> temp) {
    scan_returns.push_back(temp);
    cout << scan_returns[scan_returns.size()-1] << " ";
  }
  cout << endl;
  
  double resolution =
      180.0 / (scan_returns.size() - 1); // assume last scan is at 180
  cout << "Resolution: " << resolution << " degrees" << endl;
  

  // convert each scan return to x,y coordinates, and write to output.txt
  // --- Your code here



  // ---

  //check if each point is 1) in front of the robot and 
  //2) closer than the threshold (in y)
  // --- Your code here



  // ---
  return 0;
}
