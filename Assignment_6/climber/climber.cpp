#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include "climber.h"

int CLIMB_LIMIT = 2;

bool operator==(Coordinate const &c1, Coordinate const &c2)
{
    return (c1.x == c2.x) && (c1.y == c2.y);
}

bool operator<(Coordinate const &c1, Coordinate const &c2)
{
    if (c1.x == c2.x)
    {
        return c1.y < c2.y;
    }
    return c1.x < c2.x;
}

Coordinate operator+(Coordinate const &c1, Coordinate const &c2)
{
    return {c1.x + c2.x, c1.y + c2.y};
}

void read_input(std::map<Coordinate, int> &m, Coordinate &start, std::string const &infilename)
{
    std::ifstream infile(infilename);
    if (!infile.good())
    {
        std::cerr << "No such file " << infilename << '\n';
        throw std::runtime_error("No such file!");
    }

    infile >> start.x;
    infile >> start.y;
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // move to next line

    int x_idx = 0;
    int y_idx = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ssline(line);
        int val;
        while (ssline >> val)
        {
            m[{x_idx, y_idx}] = val;
            x_idx++;
        }
        x_idx = 0;
        y_idx++;
    }
}

Coordinate findMaxCoordinate(const std::map<Coordinate, int> &m)
{
    Coordinate maxCoordinate = {0, 0};

    for (auto const &entry : m)
    {
        if (entry.first.x > maxCoordinate.x)
        {
            maxCoordinate.x = entry.first.x;
        }

        if (entry.first.y > maxCoordinate.y)
        {
            maxCoordinate.y = entry.first.y;
        }
    }

    return maxCoordinate;
}

std::vector<Coordinate> generateOrderedNeighbours(Coordinate const &current_xy)
{
    std::vector<Coordinate> neighbours = {
        {current_xy.x + 1, current_xy.y},
        {current_xy.x - 1, current_xy.y},
        {current_xy.x, current_xy.y + 1},
        {current_xy.x, current_xy.y - 1}};

    return neighbours;
};

bool validNeighbour(Coordinate const &neighbour, const std::map<Coordinate, int> &m, const int currentHeight)
{
    Coordinate maxMapCoordinate = findMaxCoordinate(m);

    // check if neighbour is in bounds
    if ((neighbour.x < 0) || (neighbour.y < 0))
    {
        return false;
    }

    if ((neighbour.x > maxMapCoordinate.x) || (neighbour.y > maxMapCoordinate.y))
    {
        return false;
    }

    // check if neighbour is climbable
    if (m.at(neighbour) > CLIMB_LIMIT + currentHeight)
    {
        return false;
    }

    return true;
};

void climber_algorithm(std::map<Coordinate, int> const &m, Coordinate const &start, std::string const &outfilename)
{
    std::ofstream outfile(outfilename);
    if (!outfile.is_open())
    {
        std::cerr << "Failed to open output file: " << outfilename << std::endl;
        return;
    }

    // Debugging outputs
    std::cout << "height at start: " << m.at(start) << std::endl;

    Coordinate current_xy = start;
    int current_height = m.at(start);

    std::vector<Coordinate> offsets{};

    bool localClimbableMax = false;
    while (!localClimbableMax)
    {
        outfile << current_xy.x << " " << current_xy.y << " " << current_height << std::endl;

        std::vector<Coordinate> neighbours = generateOrderedNeighbours(current_xy);

        int stepHeight = 0;
        Coordinate next_xy = current_xy;
        int neighbourHeight = current_height;

        for (const auto neighbour : neighbours)
        {
            if (!validNeighbour(neighbour, m, current_height))
            {
                continue;
            }

            int newNeighbourHeight = m.at(neighbour);

            if (newNeighbourHeight > neighbourHeight)
            {
                next_xy = neighbour;
                neighbourHeight = newNeighbourHeight;
            }
        }

        if (next_xy == current_xy)
        {
            localClimbableMax = true; // no better climbable neighbour found
        }

        current_xy = next_xy;
        current_height = neighbourHeight;

        // Debugging outputs
        std::cout << "location at end: " << current_xy.x << " " << current_xy.y << std::endl;
        std::cout << "height at end: " << current_height << std::endl;
    }
    outfile.flush();
    outfile.close();
}