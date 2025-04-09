//
// Created by 101142429 on 4/4/2025.
//

#ifndef ASTAR_H
#define ASTAR_H

#include <memory>
#include <queue>
#include "Graph.h"
#include "Data.h"
#include "Vector2Hash.h"

class AStar {

    struct PriorityPoint
    {
        sf::Vector2i point = sf::Vector2i(0, 0);
        int cost = 0;
        bool operator<(const PriorityPoint& other) const
        {
            return cost > other.cost;
        }
    };

    std::unique_ptr<Graph> m_graph;

    std::priority_queue<PriorityPoint> m_frontier;
    std::unordered_map<sf::Vector2i, sf::Vector2i, Vector2Hash> m_cameFrom;
    std::unordered_map<sf::Vector2i, int, Vector2Hash> m_costSoFar;





    int heuristic(sf::Vector2i startingPoint, sf::Vector2i goalPoint);
    std::vector<sf::Vector2i> getNeighboredGraph(const Graph& graph, const sf::Vector2i& point);

    std::vector<sf::Vector2i> createPathFromMap(const std::unordered_map<sf::Vector2i, sf::Vector2i, Vector2Hash>& cameFrom, sf::Vector2i start);



public:
    AStar(Graph graph);
    std::vector<sf::Vector2i> Run(sf::Vector2i startingPoint, sf::Vector2i goalPoint);



};



#endif //ASTAR_H
