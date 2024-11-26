import numpy as np


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def square_distance_from_origin(self):
        return self.x**2 + self.y**2

    def is_inside_unit_circle(self):
        return self.square_distance_from_origin() <= 1


def generate_random_points(N):
    coordinates = np.random.uniform(-1, 1, (N, 2))
    return [Point(x, y) for x, y in coordinates]


def estimate_pi(N):
    pi_estimate = None
    points = generate_random_points(N)
    N_circle = sum(1 for point in points if point.is_inside_unit_circle())
    pi_estimate = 4 * N_circle / N

    return pi_estimate


if __name__ == "__main__":
    N = 1000
    approx_pi = estimate_pi(N)
    print(f"Estimate of pi is {approx_pi}")
