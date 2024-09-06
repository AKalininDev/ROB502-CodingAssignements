#include <iostream>
#include <iomanip>

double miToKm(const double &miles)
{
    return miles * 1.60934;
}

int main()
{
    double miles, km;

    std::cin >> miles;
    km = miToKm(miles);

    std::cout << std::setprecision(3);
    std::cout << km << std::endl;
    return 0;
}