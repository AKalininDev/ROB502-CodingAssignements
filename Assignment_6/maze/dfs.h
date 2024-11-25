#pragma once
#include "maze.h"
#include <stack>

/** \brief Depth First Search solver */
class DFS : public TreeSearch
{
public:
    DFS();

    /** \brief Solve the planning problem. Override TreeSearch::solve() */
    bool solve();

    /** \brief add node to the tree */
    bool addNode(const NodePtr &node);

private:
    std::stack<NodePtr> explorationStack;
};
using DFSPtr = std::shared_ptr<DFS>;