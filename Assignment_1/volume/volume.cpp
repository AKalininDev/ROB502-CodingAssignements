#include <cmath>
#include <iomanip>
#include <iostream>

double getVolumeOfCone(double radius, double height)
{
    return M_PI * radius * radius * height / 3;
}

int main()
{
    // determines volume of a cone (2 args from stdin)
    // again, you should create the variable `volume` for the output.
    double radius, height;
    std::cout << "Enter the radius and height on separate lines\n";
    std::cin >> radius;
    std::cin >> height;
    double volume = getVolumeOfCone(radius, height);
    std::cout << std::setprecision(3) << volume << std::endl;
    return 0;
}