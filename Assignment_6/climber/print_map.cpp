#include <string>
#include <iostream>
#include <map>
#include "climber.h"

void printmap(const std::map<Coordinate, int> &m)
{
    for (auto const &entry : m)
    {
        std::cout << entry.first.x << "," << entry.first.y << " val: " << entry.second << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string infilename = "input.txt";
    std::string outfilename = "output.txt";

    // Allows the user to override the input and output filenames
    // by passing in arguments on the commandline.
    if (argc == 2)
    {
        infilename = argv[1];
    }
    if (argc == 3)
    {
        infilename = argv[1];
        outfilename = argv[2];
    }
    std::map<Coordinate, int> m;
    Coordinate start;

    read_input(m, start, infilename);

    printmap(m);

    return EXIT_SUCCESS;
}