#ifndef ASTAR_H
#define ASTAR_H

#include <memory>
#include <queue>
#include <unordered_map>
#include "Vector2Hash.h"


class AStar {
    typedef std::unordered_map<sf::Vector2i, int, Vector2Hash> Graph;
    struct PriorityPoint
    {
        sf::Vector2i point = sf::Vector2i(0, 0);
        int cost = 0;
        bool operator<(const PriorityPoint& other) const
        {
            return cost > other.cost;
        }
    };

    Graph m_graph;

    std::priority_queue<PriorityPoint> m_frontier;
    std::unordered_map<sf::Vector2i, sf::Vector2i, Vector2Hash> m_cameFrom;
    std::unordered_map<sf::Vector2i, int, Vector2Hash> m_costSoFar;





    int heuristic(sf::Vector2i startingPoint, sf::Vector2i goalPoint);
    std::vector<sf::Vector2i> getNeighboredGraph(const Graph& graph, const sf::Vector2i& point);

    std::vector<sf::Vector2i> createPathFromMap(const std::unordered_map<sf::Vector2i, sf::Vector2i, Vector2Hash>& cameFrom, sf::Vector2i start);



public:
    AStar(Graph graph);
    std::vector<sf::Vector2i> Run(sf::Vector2i startingPoint, sf::Vector2i goalPoint);
    void setGraph(Graph graph);



};



#endif //ASTAR_H
