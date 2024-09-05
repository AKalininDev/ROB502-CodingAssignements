#include <cmath>
#include <iostream>
#include <fstream>

double getCuboidInertia(const double &mass, const double &width, const double &length)
{
    double I = 0.0;
    I = static_cast<double>(1 / 12.0) * mass * (pow(width, 2) + pow(length, 2));
    return I;
}

int main()
{
    double mass, w, h, d;
    std::ifstream ifs("inertia_input.txt");
    ifs >> mass;
    ifs >> w;
    ifs >> h;
    ifs >> d;

    double Ih;
    double Iw;
    double Id;

    Ih = getCuboidInertia(mass, w, d);
    Iw = getCuboidInertia(mass, d, h);
    Id = getCuboidInertia(mass, w, h);

    std::cout << "<ixx>" << Ih << "</ixx>\n";
    std::cout << "<iyy>" << Iw << "</iyy>\n";
    std::cout << "<izz>" << Id << "</izz>\n";
    return 0;
}