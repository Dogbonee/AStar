#include "AStar.h"

AStar::AStar(Graph graph) : m_graph(graph)
{
}

std::vector<sf::Vector2i> AStar::Run(sf::Vector2i startingPoint, sf::Vector2i goalPoint)
{
    m_cameFrom.clear();
    m_costSoFar.clear();
    m_frontier = std::priority_queue<PriorityPoint>();


    m_frontier.push({startingPoint, 0});
    m_costSoFar[startingPoint] = 0;


    while (!m_frontier.empty())
    {
        auto current = m_frontier.top();
        m_frontier.pop();

        if (current.point == goalPoint)
        {
            return createPathFromMap(m_cameFrom, goalPoint);
        }

        for (auto next : getNeighboredGraph(m_graph, current.point))
        {
            auto newCost = m_costSoFar[current.point] + m_graph[next];
            if (!m_costSoFar.contains(next) || newCost < m_costSoFar[next])
            {
                m_costSoFar[next] = newCost;
                auto priority = newCost + heuristic(next, goalPoint);
                m_frontier.push({next, priority});
                m_cameFrom[next] = current.point;
            }
        }

    }

    return createPathFromMap(m_cameFrom, goalPoint);
}

void AStar::setGraph(Graph graph)
{
    m_graph = graph;
}

int AStar::heuristic(sf::Vector2i startingPoint, sf::Vector2i goalPoint)
{
    return abs(goalPoint.x - startingPoint.x) + abs(goalPoint.y - startingPoint.y);
}

std::vector<sf::Vector2i> AStar::getNeighboredGraph(const Graph& graph, const sf::Vector2i& point)
{
    std::vector<sf::Vector2i> neighbors;
    neighbors.emplace_back(point.x + 1, point.y);
    neighbors.emplace_back(point.x - 1, point.y);
    neighbors.emplace_back(point.x, point.y + 1);
    neighbors.emplace_back(point.x, point.y - 1);
    return neighbors;
}

std::vector<sf::Vector2i> AStar::createPathFromMap(const std::unordered_map<sf::Vector2i, sf::Vector2i, Vector2Hash>& cameFrom, sf::Vector2i start)
{
    std::vector<sf::Vector2i> path;
    auto currentPoint = start;
    while (cameFrom.contains(currentPoint))
    {
        path.emplace_back(currentPoint);
        currentPoint = cameFrom.at(currentPoint);
    }
    std::reverse(path.begin(), path.end());
    return path;
}



