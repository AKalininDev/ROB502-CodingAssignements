import numpy as np


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def inside_unit_circle(point: Point):
    return point.x**2 + point.y**2 <= 1


def estimate_pi(N):
    pi_estimate = None

    N_circle = 0
    random_X_coordinates = np.random.uniform(-1, 1, N)
    random_Y_coordinates = np.random.uniform(-1, 1, N)

    for x, y in zip(random_X_coordinates, random_Y_coordinates):
        point = Point(x, y)

        if inside_unit_circle(point):
            N_circle += 1

    pi_estimate = 4 * N_circle / N

    return pi_estimate


if __name__ == "__main__":
    N = 1000
    approx_pi = estimate_pi(N)
    print(f"Estimate of pi is {approx_pi}")
