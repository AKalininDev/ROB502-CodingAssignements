#include <iostream>
#include <vector>

using ObjMassPair = std::pair<std::string, double>; // this defines the type ObjMassPair to be std::pair<std::string, double>

// overloading << operator for ObjMassPair
std::ostream &operator<<(std::ostream &os, const ObjMassPair &omp)
{
    os << omp.first << " " << omp.second;

    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<ObjMassPair> &vec)
{
    for (const ObjMassPair &omp : vec)
    {
        os << omp << std::endl;
    }

    return os;
}

// define a function that compares ObjMassPair objects here (for use by std::sort)
bool operator<(const ObjMassPair &omp1, const ObjMassPair &omp2)
{
    return omp1.second < omp2.second;
}

bool customComparator(const ObjMassPair &omp1, const ObjMassPair &omp2)
{
    return omp1.second < omp2.second;
}