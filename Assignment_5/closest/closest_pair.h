#include <vector>
#include <math.h>
#include <algorithm>

struct Point {
    int id;
    double x, y;
};

double dist(const Point& p1, const Point& p2) {
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}

// --- Your code here



// ---

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
    // --- Your code here



    // ---
}