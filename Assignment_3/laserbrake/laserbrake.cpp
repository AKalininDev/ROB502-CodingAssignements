#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using CartesianPairXY = std::pair<double, double>;
using PolarPairRTh = std::pair<double, double>;

class Point
{
public:
  Point(std::pair<double, double> pair, bool isPolar)
  {
    if (isPolar)
    {
      r = pair.first;
      theta = pair.second;
      x = r * cos(theta);
      y = r * sin(theta);
    }
    else
    {
      x = pair.first;
      y = pair.second;
    }
  }
  double getX() { return x; }

  double getY() { return y; }

  double getR() { return r; }

  double getTheta() { return theta; }

  CartesianPairXY getXY() { return CartesianPairXY(x, y); }

  PolarPairRTh getRP() { return PolarPairRTh(r, theta); }

private:
  double x;
  double y;
  double r;
  double theta;
};

class Robot
{
public:
  Robot(double width, double threshold)
  {
    this->width = width;
    this->threshold = threshold;
  }

  double getWidth() { return width; }

  double getThreshold() { return threshold; }

  void giveScan(const std::vector<Point> &scannedPoints)
  {
    this->scannedPoints = scannedPoints;
  }

  bool isColliding();

  int getCollisionPointIndex() { return collisionPointIndex; }

private:
  double width;
  double threshold;

  std::vector<Point> scannedPoints;
  int collisionPointIndex;
};

bool Robot::isColliding()
{
  for (size_t i = 0; i < scannedPoints.size(); i++)
  {
    Point point = scannedPoints[i];
    if ((point.getY() < threshold) && (abs(point.getX()) < width / 2.0))
    {
      collisionPointIndex = i;
      return true;
    }
  }
  return false;
}

double calculateResolutionDeg(const std::vector<double> &scan_returns, const double &range)
{
  double resolution = range / (scan_returns.size() - 1);

  return resolution;
}

double DEG2RAD = M_PI / 180; // this definition will be useful

using namespace std;

int main()
{
  ifstream scanfile("input.txt");
  ofstream outfile("output.txt");
  cout << setprecision(4); // this sets how many decimal places to print
  outfile << setprecision(4);

  double robot_width;
  double threshold;

  string input;
  for (int i = 0; i < 2; i++)
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
  while (scanfile >> temp)
  {
    scan_returns.push_back(temp);
    cout << scan_returns[scan_returns.size() - 1] << " ";
  }
  cout << endl;

  double resolution = calculateResolutionDeg(scan_returns, 180);
  cout << "Resolution: " << resolution << " degrees" << endl;

  vector<Point> scannedPoints;
  for (size_t i = 0; i < scan_returns.size(); i++)
  {
    double angleRad = i * resolution * DEG2RAD;
    double distance = scan_returns[i];
    PolarPairRTh polarPair(distance, angleRad);
    Point point(polarPair, true);
    scannedPoints.emplace_back(point);
  }
  // convert each scan return to x,y coordinates, and write to output.txt

  for (Point point : scannedPoints)
  {
    CartesianPairXY xy = point.getXY();
    outfile << xy.first << " " << xy.second << endl;
  }

  Robot robot(robot_width, threshold);
  robot.giveScan(scannedPoints);
  if (robot.isColliding())
  {
    outfile << "Stop! " << robot.getCollisionPointIndex() << endl;
  }
  else
  {
    outfile << "OK" << endl;
  }

  return 0;
}
