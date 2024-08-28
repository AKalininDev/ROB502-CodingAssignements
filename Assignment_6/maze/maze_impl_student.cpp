#include "maze.h"
#include "bfs.h"
#include "dfs.h"

/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const
{
    // HINT: use isStateValid()
    // --- Your code here



    // ---
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node)
{
    // --- Your code here



    // ---
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

    NodePtr solution;
    // --- Your code here



    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node)
{
    // --- Your code here



    // ---
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
        std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here



    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node)
{
    // --- Your code here



    // ---
}