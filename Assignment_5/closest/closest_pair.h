#include <vector>
#include <math.h>
#include <algorithm>

struct Point
{
    int id;
    double x, y;
};

std::vector<Point> sortPointsByX(const std::vector<Point> &points)
{
    std::vector<Point> sorted = points;
    std::sort(sorted.begin(), sorted.end(),
              [](const Point &p1, const Point &p2)
              { return p1.x < p2.x; });
    return sorted;
}

std::pair<Point, Point> smallestIDPair(const std::pair<Point, Point> &pair1, const std::pair<Point, Point> &pair2)
{
    int minID1 = std::min(pair1.first.id, pair1.second.id);
    int minID2 = std::min(pair2.first.id, pair2.second.id);

    return minID1 < minID2 ? pair1 : pair2;
}

double distSquared(const Point &p1, const Point &p2)
{
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

std::pair<Point, Point> bruteCheck(const std::vector<Point> &points, const size_t start, const size_t end)
{
    double minDist = std::numeric_limits<double>::max();
    std::pair<Point, Point> closestPair;

    for (size_t i = start; i < end; ++i)
    {
        const Point &p1 = points[i];
        for (size_t j = i + 1; j < end; ++j)
        {
            const Point &p2 = points[j];
            const double d = distSquared(p1, p2);

            if (d < minDist)
            {
                minDist = d;
                closestPair = {p1, p2};
            }
            else if (d == minDist)
            {
                closestPair = smallestIDPair(closestPair, std::make_pair(points[i], points[j]));
            }
        }
    }
    return closestPair;
}

void getStripStartEnd(const std::vector<Point> &sortedPoints, const double midX, const double stripWidth, const int start, const int end, int &stripStart, int &stripEnd)
{
    for (int i = start; i < end; i++)
    {
        if (std::abs(sortedPoints[i].x - midX) <= stripWidth)
        {
            stripStart = std::min(stripStart, i);
            stripEnd = std::max(stripEnd, i);
        }
    }
}

std::pair<Point, Point> closestPairSortedX(const std::vector<Point> &sortedPoints, const int start, const int end)
{
    // base case
    if ((end - start) <= 32)
    {
        return bruteCheck(sortedPoints, start, end);
    }

    // find the middle point
    int mid = start + (end - start) / 2;
    double midX = sortedPoints[mid].x;

    // find closest pair in left and right halves
    std::pair<Point, Point> leftClosestPair, rightClosestPair;
    leftClosestPair = closestPairSortedX(sortedPoints, start, mid);
    rightClosestPair = closestPairSortedX(sortedPoints, mid, end);

    double leftClosestDist = distSquared(leftClosestPair.first, leftClosestPair.second);
    double rightClosestDist = distSquared(rightClosestPair.first, rightClosestPair.second);
    double minDist = std::min(leftClosestDist, rightClosestDist);
    auto closestPair = leftClosestDist < rightClosestDist ? leftClosestPair : rightClosestPair;
    if (leftClosestDist == rightClosestDist)
    {
        closestPair = smallestIDPair(leftClosestPair, rightClosestPair);
    }

    // get the strip start and end
    std::vector<Point> stripPoints;
    int stripStart = -1;
    int stripEnd = -1;
    getStripStartEnd(sortedPoints, midX, minDist, start, end, stripStart, stripEnd);

    // find closest pair in strip
    std::pair<Point, Point> stripClosestPair;
    double stripClosestDist = std::numeric_limits<double>::max();
    if (stripStart - stripEnd >= 2)
    {
        stripClosestPair = closestPairSortedX(sortedPoints, stripStart, stripEnd);
        stripClosestDist = distSquared(stripClosestPair.first, stripClosestPair.second);
    }

    // handle the case where the closest pair is in the strip
    if (stripClosestDist == minDist)
    {
        return smallestIDPair(closestPair, stripClosestPair);
    }

    return minDist < stripClosestDist ? closestPair : stripClosestPair;
}

std::pair<Point, Point> closest_pair(const std::vector<Point> &points)
{
    std::vector<Point> sortedPoints = sortPointsByX(points);

    std::pair<Point, Point> closestPair;
    closestPair = closestPairSortedX(sortedPoints, 0, points.size());

    // swap the points if the first point has a higher id
    if (closestPair.first.id > closestPair.second.id)
    {
        return std::make_pair(closestPair.second, closestPair.first);
    }
    return closestPair;
}