import numpy as np
from ga_trajopt import GATrajectoryOptimizer
from typing import Tuple


class GATrajectoryOptimizerSolution(GATrajectoryOptimizer):

    def in_obstacle(self, coord: np.ndarray) -> bool:
        """
        Check if a given coordinate is inside any of the obstacles

        Args:
        coord: np.ndarray: The coordinate to check

        Returns:
        bool: True if the coordinate is inside any of the obstacles, False otherwise"""

        for i in range(len(self.obstacle_radii)):
            if (
                np.linalg.norm(coord - self.obstacle_centres[i])
                < self.obstacle_radii[i]
            ):
                return True
        return False

    def fitness(self, x: np.ndarray) -> float:
        """
        Compute the fitness of a given trajectory

        Args:
        x: np.ndarray: The trajectory to evaluate

        Returns:
        float: The fitness of the trajectory"""

        positions = np.concatenate([np.array([self.start]), x])
        positions = np.cumsum(positions, axis=0)

        obstacle_penalty = 100 * sum([self.in_obstacle(pose) for pose in positions])
        distance_to_goal_penalty = np.linalg.norm(positions[-1] - self.goal) ** 2
        path_length_penalty = np.sum(x**2)

        fit = -(distance_to_goal_penalty + obstacle_penalty + path_length_penalty)
        return fit

    def crossover(
        self, parent1: np.ndarray, parent2: np.ndarray, crossover_point: int
    ) -> Tuple[np.ndarray, np.ndarray]:
        """
        Perform crossover between two parents

        Args:
        parent1: np.ndarray: The first parent
        parent2: np.ndarray: The second parent
        crossover_point: int: The point at which to perform crossover

        Returns:
        Tuple[np.ndarray, np.ndarray]: The two children after crossover"""

        # Create copies of parents to form children
        child1 = parent1.copy()
        child2 = parent2.copy()

        # Swap the tails after crossover point
        child1[crossover_point:] = parent2[crossover_point:]
        child2[crossover_point:] = parent1[crossover_point:]

        return child1, child2

    def select_children(
        self, parent: np.ndarray, child: np.ndarray
    ) -> Tuple[np.ndarray, float]:
        """
        Select the better of the two parents and children

        Args:
        parent: np.ndarray: The parent to compare
        child: np.ndarray: The child to compare

        Returns:
        Tuple[np.ndarray, float]: The selected individual and its fitness"""

        # Calculate fitness for both
        parent_fitness = self.fitness(parent)
        child_fitness = self.fitness(child)

        # With probability select_best_child_p, select the better one
        if np.random.rand() < self.params["select_best_child_p"]:
            if child_fitness > parent_fitness:
                return child, child_fitness
            else:
                return parent, parent_fitness
        else:
            # Otherwise select the worse one
            if child_fitness <= parent_fitness:
                return child, child_fitness
            else:
                return parent, parent_fitness


if __name__ == "__main__":
    # GA path planning

    # Setup start, goal and spherical obstacles
    goal = np.array([1.0, 1.0])
    start = np.array([0.0, 0.0])
    obstacle_centres = np.array([[0.5, 0.2], [0.2, 0.8]])
    obstacle_radii = np.array([0.25, 0.15])

    # Solver parameters
    N = 500
    T = 20
    params = {
        "N": 500,
        "iters": 100,
        "cross_over_p": 0.5,
        "mutate_p": 0.5,
        "select_best_parent_p": 0.9,
        "select_best_child_p": 0.9,
    }

    solver = GATrajectoryOptimizerSolution(
        start, goal, obstacle_radii, obstacle_centres, T, params
    )
    # Solve to get best trajectory and plot
    best = solver.solve()
    solver.plot_trajectory(best)
