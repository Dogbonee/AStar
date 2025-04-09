//
// Created by 101142429 on 4/4/2025.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>


class Graph {

  private:
    std::vector<std::vector<int>> m_graphArray;


  public:
    explicit Graph(const std::vector<std::vector<int>>& graphArray);

    std::vector<std::vector<int>> getGraphArray() const;
    void set(const sf::Vector2i& pos, int value);
    int get(const sf::Vector2i& pos) const;
    sf::Vector2i getSize() const;
    const int& operator [] (const sf::Vector2i& index) const;

};



#endif //GRAPH_H
