#include <iostream>
#include <algorithm>
#include "maze.h"
#include "bfs.h"
#include "dfs.h"

NodePtr buildStartNode(const State &state)
{
    NodePtr node = std::make_shared<Node>();
    node->state = state;
    node->parent = nullptr;
    node->cost_to_come = 0;
    return node;
}

NodePtr buildNextNode(const State &state, const NodePtr &parent, const int inCost)
{
    NodePtr node = std::make_shared<Node>();
    node->state = state;
    node->parent = parent;
    node->cost_to_come = parent->cost_to_come + inCost;
    return node;
}

std::vector<State> generateDiagonalNeighbors(const State &state)
{
    std::vector<State> neighbors;
    neighbors.push_back(State(state.x + 1, state.y + 1));
    neighbors.push_back(State(state.x + 1, state.y - 1));
    neighbors.push_back(State(state.x - 1, state.y + 1));
    neighbors.push_back(State(state.x - 1, state.y - 1));
    return neighbors;
}

std::vector<State> generateNormalNeighbors(const State &state)
{
    std::vector<State> neighbors;
    neighbors.push_back(State(state.x + 1, state.y));
    neighbors.push_back(State(state.x - 1, state.y));
    neighbors.push_back(State(state.x, state.y + 1));
    neighbors.push_back(State(state.x, state.y - 1));
    return neighbors;
}

/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const
{

    std::vector<State> validNeighbors;
    std::vector<State> allNeighbors;

    // Generate all neighbors based on the current state and problem definition
    std::vector<State> normalNeighbors = generateNormalNeighbors(state);
    allNeighbors.insert(allNeighbors.end(), normalNeighbors.begin(), normalNeighbors.end());

    if (allow_diagonal_)
    {
        std::vector<State> diagonalNeighbors = generateDiagonalNeighbors(state);
        allNeighbors.insert(allNeighbors.end(), diagonalNeighbors.begin(), diagonalNeighbors.end());
    }

    // Filter out the invalid neighbors
    for (const auto &neighbor : allNeighbors)
    {
        if (isStateValid(neighbor))
        {
            validNeighbors.push_back(neighbor);
        }
    }

    return validNeighbors;
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node)
{
    path_.clear();
    while (node != nullptr)
    {
        path_.push_back(node->state);
        node = node->parent;
    }
    std::reverse(path_.begin(), path_.end());
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {

        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        // std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr startNode = buildStartNode(start);
    explorationQueue.push(startNode);
    visited_.push_back(startNode->state);

    while (!explorationQueue.empty())
    {
        NodePtr current = explorationQueue.front();
        explorationQueue.pop();
        std::vector<State> validNeighbors = pdef_.validStates(current->state);

        for (const auto &neighbor : validNeighbors)
        {
            if (std::find(visited_.begin(), visited_.end(), neighbor) != visited_.end())
            {
                continue;
            }

            // build the next node
            NodePtr neighborNode = buildNextNode(neighbor, current, 1);

            // check if the neighbor is the goal
            if (pdef_.isGoal(neighbor))
            {
                NodePtr solution = neighborNode;
                extractPath(solution);
                return true;
            }

            addNode(neighborNode);
        }
    }

    return false;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node)
{
    explorationQueue.push(node);
    visited_.push_back(node->state);

    return true;
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool DFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {

        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        // std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr startNode = buildStartNode(start);
    explorationStack.push(startNode);
    visited_.push_back(startNode->state);

    while (!explorationStack.empty())
    {
        NodePtr current = explorationStack.top();
        explorationStack.pop();
        std::vector<State> validNeighbors = pdef_.validStates(current->state);

        for (const auto &neighbor : validNeighbors)
        {
            if (std::find(visited_.begin(), visited_.end(), neighbor) != visited_.end())
            {
                continue;
            }

            // build the next node
            NodePtr neighborNode = buildNextNode(neighbor, current, 1);

            // check if the neighbor is the goal
            if (pdef_.isGoal(neighbor))
            {
                NodePtr solution = neighborNode;
                extractPath(solution);
                return true;
            }

            addNode(neighborNode);
        }
    }

    return false;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node)
{
    explorationStack.push(node);
    visited_.push_back(node->state);

    return true;
}