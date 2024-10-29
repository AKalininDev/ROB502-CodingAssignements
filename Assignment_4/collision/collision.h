#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <iostream>
#include <vector>

using Edge = std::pair<Eigen::Vector2d, Eigen::Vector2d>;

// returns true if the equation a*t^2+b*t+c=0 has a solution between 0 and 1 (inclusive)
// HINT: recall your solution to `quadratic` in HW1
bool QuadraticHasValidSolutions(double const a, double const b, double const c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
    }

    double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    if (t1 > 0 && t1 < 1)
    {
        return true;
    }

    if (t1 > 0 && t1 < 1)
    {
        return true;
    }

    return false;
}

class Disc; // forward-declare the type Disc, otherwise we can't use it in the Obstacle base class

class Obstacle
{
public:
    // returns true if the robot is collides with the obstacle
    virtual bool checkCollision(Disc const &robot) const = 0;

    // returns true if whether the point p is within this disc
    virtual bool contains(Eigen::Vector2d const &p) const = 0;
};

class Disc : public Obstacle
{
public:
    Disc(double x, double y, double radius) : pos_(x, y), radius_(radius) {}

    // override checkCollision
    virtual bool checkCollision(Disc const &robot) const override
    {
        if ((robot.getPose() - pos_).norm() <= robot.getRadius() + radius_)
        {
            return true;
        }

        return false;
    }

    // returns true if the point p is within this disc
    bool contains(Eigen::Vector2d const &p) const override
    {
        return (p - pos_).norm() <= radius_;
    }

    Eigen::Vector2d getPose() const
    {
        return pos_;
    }

    double getRadius() const
    {
        return radius_;
    }

    Eigen::Vector2d pos_;
    double radius_;
};
class Rectangle : public Obstacle
{
public:
    Rectangle(double x1, double y1, double x2, double y2) : bottom_left_(x1, y1), top_right_(x2, y2),
                                                            edges_{{{x1, y1}, {x2, y1}}, {{x2, y1}, {x2, y2}}, {{x2, y2}, {x1, y2}}, {{x1, y2}, {x1, y1}}},
                                                            corners_{{x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}}
    {
    }

    // override checkCollision
    // HINT: use the `Rectangle::checkIntersectEdge`, `Rectangle::contains`, and `Disc::contains` functions
    bool checkCollision(Disc const &robot) const override
    {
        if (checkIntersectEdge(robot))
        {
            return true;
        }

        if (checkCornersInDisc(robot))
        {
            return true;
        }

        if (checkIntersectEdge(robot))
        {
            return true;
        }

        return false;
    }

    // Override the `contains` function
    bool contains(Eigen::Vector2d const &p) const override
    {
        bool betweenHorizontal = p.x() >= bottom_left_.x() && p.x() <= top_right_.x();

        bool betweenVertical = p.y() >= bottom_left_.y() && p.y() <= top_right_.y();

        return betweenHorizontal && betweenVertical;
    }

    // (HINT: use the `QuadraticHasValidSolutions` function)
    bool checkCornersInDisc(Disc const &disc) const
    {
        for (Eigen::Vector2d const corner : corners_)
        {
            if (disc.contains(corner))
            {
                return true;
            }
        }

        return false;
    }

    // check whetehr any of the rectangles edges intersect with the disc
    bool checkIntersectEdge(Disc const &disc) const
    {
        for (Edge const &edge : edges_)
        {
            Eigen::Vector2d const &p1 = edge.first;
            Eigen::Vector2d const &p2 = edge.second;

            Eigen::Vector2d const &dc = disc.getPose();
            double const r = disc.getRadius();

            Eigen::Vector2d const v = p2 - p1;
            Eigen::Vector2d const w = dc - p1;

            double const a = v.dot(v);
            double const b = 2 * w.dot(v);
            double const c = w.dot(w) - r * r;

            if (QuadraticHasValidSolutions(a, b, c))
            {
                return true;
            }
        }

        return false;
    }

    Eigen::Vector2d bottom_left_;
    Eigen::Vector2d top_right_;
    std::vector<Edge> edges_;
    std::vector<Eigen::Vector2d> corners_;
};

bool check_collisions(std::vector<Obstacle const *> const &obstacles, Disc const &robot)
{
    for (auto const &obs : obstacles)
    {
        if (obs->checkCollision(robot))
        {
            return true;
        }
    }

    return false;
}