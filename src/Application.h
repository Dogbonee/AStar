//
// Created by 101142429 on 3/19/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

#include "AStar.h"
#include "Graph.h"

class Application {

    std::shared_ptr<sf::RenderWindow> m_window;
    Graph m_graph;
    AStar m_pathfinder;
    std::vector<sf::Vector2i> m_path;


    void Update();
    void Render();
    void HandleEvents();


    void DrawGraph(const Graph& graph);
    void DrawPath(const std::vector<sf::Vector2i>& path);

    bool approx(float a, float b, float epsilon);

public:

    Application();
    ~Application();

    void Run();




};



#endif //APPLICATION_H
