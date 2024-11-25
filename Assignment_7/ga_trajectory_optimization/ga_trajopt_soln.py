import numpy as np
from ga_trajopt import GATrajectoryOptimizer


class GATrajectoryOptimizerSolution(GATrajectoryOptimizer):

    def fitness(self, x):
        fit = 0
        # --- Your code here



        # ---
        return fit

    def crossover(self, parent1, parent2, crossover_point):
        child1, child2 = None, None
        # --- Your code here



        # ---
        return child1, child2

    def select_children(self, parent, child):

        chosen, fitness = None, None

        # --- Your code here



        # ---
        return chosen, fitness


if __name__ == "__main__":
    # GA path planning

    # Setup start, goal and spherical obstacles
    goal = np.array([1.0, 1.0])
    start = np.array([0.0, 0.0])
    obstacle_centres = np.array([
        [0.5, 0.2],
        [0.2, 0.8]
    ])
    obstacle_radii = np.array([0.25, 0.15])

    # Solver parameters
    N = 500
    T = 20
    params = {
        'N': 500,
        'iters': 100,
        'cross_over_p': 0.5,
        'mutate_p': 0.5,
        'select_best_parent_p': 0.9,
        'select_best_child_p': 0.9
    }

    solver = GATrajectoryOptimizerSolution(start, goal, obstacle_radii, obstacle_centres, T, params)
    # Solve to get best trajectory and plot
    best = solver.solve()
    solver.plot_trajectory(best)
