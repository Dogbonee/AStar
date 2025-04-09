//
// Created by 101142429 on 3/19/2025.
//

#include "Application.h"

#include "Data.h"


Application::Application() : m_graph(Data::map2), m_pathfinder(m_graph)
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode({800, 600}), "AStar Pathfinding Demo");
    m_path = m_pathfinder.Run({1,5}, {9, 5});

}

Application::~Application() = default;

void Application::Run()
{
    while (m_window->isOpen())
    {
        HandleEvents();
        Update();
        Render();
    }
}

void Application::Update()
{
}

void Application::Render()
{
    m_window->clear();
    DrawGraph(m_graph);
    DrawPath(m_path);
    m_window->display();
}

void Application::HandleEvents()
{
    while (const std::optional<sf::Event> event = m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window->close();
        }
    }
}

void Application::DrawGraph(const Graph& graph)
{
    auto size = graph.getSize();
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (graph[{x,y}])
            {
                sf::RectangleShape rect;
                rect.setPosition({x * 30.f, y * 30.f});
                rect.setSize({30,30});
                m_window->draw(rect);
            }
        }
    }
}


void Application::DrawPath(const std::vector<sf::Vector2i>& path)
{

    for (int i = 0; i < path.size() - 1; i++)
    {
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Red);

        rect.setSize({30, 8});
        rect.setPosition({path[i].x * 30.f + 15.f + rect.getSize().y/2, path[i].y * 30.f + 15.f - rect.getSize().y/2});

        auto rotation = atan2(path[i+1].y - path[i].y, path[i+1].x - path[i].x);
        rect.setRotation(sf::radians(rotation));
        if (!approx(rotation, 0.0f, 0.01) && !approx(rotation, 3.14f, 0.01f))
        {
            rect.setSize({rect.getSize().x + rect.getSize().y, rect.getSize().y});
        }
        if (approx(rotation, -1.57, 0.1))
        {
            rect.move({0, rect.getSize().y});
        }
        m_window->draw(rect);
    }
}

bool Application::approx(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}


