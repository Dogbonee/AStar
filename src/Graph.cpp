//
// Created by 101142429 on 4/4/2025.
//

#include "Graph.h"

Graph::Graph(const std::vector<std::vector<int>>& graphArray) : m_graphArray(graphArray)
{
}

std::vector<std::vector<int>> Graph::getGraphArray() const
{
    return m_graphArray;
}

void Graph::set(const sf::Vector2i& pos, int value)
{
    m_graphArray[pos.y][pos.x] = value;
}

int Graph::get(const sf::Vector2i& pos) const
{
    if (pos.x < 0 || pos.x >= m_graphArray.size() || pos.y < 0 || pos.y >= m_graphArray[0].size())
    {
        return 0;
    }
    return m_graphArray[pos.y][pos.x];
}

sf::Vector2i Graph::getSize() const
{
    return sf::Vector2i(m_graphArray[0].size(), m_graphArray.size());
}

const int& Graph::operator[](const sf::Vector2i& index) const
{
    return m_graphArray[index.y][index.x];
}


