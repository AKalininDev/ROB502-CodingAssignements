#pragma once
#include "maze.h"
#include <queue>

/** \brief Breadth First Search solver */
class BFS : public TreeSearch
{
public:
    BFS();

    /** \brief Solve the planning problem. Override TreeSearch::solve() */
    bool solve();

    /** \brief add node to the tree */
    bool addNode(const NodePtr &node);

private:
    std::queue<NodePtr> explorationQueue;
};
using BFSPtr = std::shared_ptr<BFS>;
