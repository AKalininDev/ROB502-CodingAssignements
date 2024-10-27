#include <random>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <vector>

struct Plane
{
    double a;
    double b;
    double c;
    double d;
};

struct FitResult
{
    Plane plane;
    int n_inliers = -1;
};

void pretty_print(std::string const &input_filename, Plane const &plane)
{
    std::cout << std::setprecision(3) << "--infile " << input_filename << " -a " << plane.a << " -b " << plane.b << " -c " << plane.c << " -d " << plane.d << '\n';
}

std::ostream &operator<<(std::ostream &os, Plane const &plane)
{
    os << std::setprecision(3) << plane.a << " " << plane.b << " " << plane.c << " " << plane.d;
    return os;
}

class BaseFitter
{
public:
    BaseFitter(int num_points) : mt(rd()), dist(0, num_points - 1)
    {
        mt.seed(0);
    }

    /**
     * Given all of the data `points`, select a random subset and fit a plane to that subset.
     * the parameter points is all of the points
     * the return value is the FitResult which contains the parameters of the plane (a,b,c,d) and the number of inliers
     */
    virtual FitResult fit(Eigen::MatrixXd const &points) = 0;

    int get_random_point_idx()
    {
        return dist(mt);
    };

    double const inlier_threshold_{0.02};

protected:
    int countInliers(Eigen::MatrixXd const &points, Plane const &plane);
    Eigen::MatrixXd getRandomPoints(Eigen::MatrixXd const &points, int n_points);

private:
    // These are for generating random indices, you don't need to know how they work.
    // Just use `get_random_point_idx()` and `points.row(rand_idx)`
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

class AnalyticFitter : public BaseFitter
{
public:
    AnalyticFitter(int num_points) : BaseFitter(num_points) {}

    // by writing `override`, the compiler will check that this function actually overrides something
    // in the base class. Always use this to prevent mistakes in the function signature!
    FitResult fit(Eigen::MatrixXd const &points) override
    {
        // 1. select 3 points from `points` randomly
        // 2. compute the equation of the plane (HINT: use compute_plane_from_points)
        // 3. compute the `n_inliers` given that plane equation
        // (HINT: multiply the points matrix by the normal vector)
        // --- Your code here

        Eigen::MatrixXd random_points = getRandomPoints(points, 3);

        Plane analytic_plane = compute_plane_from_points(random_points.row(0), random_points.row(1), random_points.row(2));
        int n_inliers = countInliers(points, analytic_plane);
        // ---

        return {analytic_plane, n_inliers};
    }

private:
    Plane compute_plane_from_points(Eigen::Vector3d const &p0, Eigen::Vector3d const &p1, Eigen::Vector3d const &p2);
};

class LeastSquaresFitter : public BaseFitter
{
public:
    LeastSquaresFitter(int num_points, int n_sample_points) : BaseFitter(num_points), n_sample_points_(n_sample_points) {}

    // You should override the `fit` method here
    // --- Your code here

    // ---

    int const n_sample_points_;
};

Plane ransac(BaseFitter &fitter, Eigen::MatrixXd const &points)
{
    // --- Your code here

    // ---

    // HINT: the number of inliers should be between 20 and 80 if you did everything correctly
    std::cout << best_result.n_inliers << std::endl;
    return best_result.plane;
}

int BaseFitter::countInliers(Eigen::MatrixXd const &points, Plane const &plane)
{
    int n_inliers = 0;
    for (int i = 0; i < points.rows(); i++)
    {
        Eigen::Vector3d point = points.row(i);
        double distance = std::abs(plane.a * point.x() + plane.b * point.y() + plane.c * point.z() + plane.d) / std::sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
        if (distance < inlier_threshold_)
        {
            n_inliers++;
        }
    }
    return n_inliers;
}

Eigen::MatrixXd BaseFitter::getRandomPoints(Eigen::MatrixXd const &points, int n_points)
{
    Eigen::MatrixXd random_points(n_points, 3);
    for (int i = 0; i < n_points; i++)
    {
        random_points.row(i) = points.row(get_random_point_idx());
    }
    return random_points;
};

Plane AnalyticFitter::compute_plane_from_points(Eigen::Vector3d const &p0, Eigen::Vector3d const &p1, Eigen::Vector3d const &p2)
{
    // 1. given p0, p1, and p2 form two vectors v1 and v2 which lie on the plane
    // 2. use v1 and v2 to find the normal vector of the plane `n`
    // 3. set a,b,c from the normal vector `n`
    // 4. set `d = -n.dot(p0)`

    Eigen::Vector3d v1 = p1 - p0;
    Eigen::Vector3d v2 = p2 - p0;

    Eigen::Vector3d n = v1.cross(v2);

    Plane plane;

    plane.a = n.x();
    plane.b = n.y();
    plane.c = n.z();
    plane.d = -n.dot(p0);

    return plane;
}
