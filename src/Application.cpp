//
// Created by 101142429 on 3/19/2025.
//

#include "Application.h"

#include "Data.h"


Application::Application() : m_graph(Data::map2), m_pathfinder(m_graph), m_pathSize({30, 8})
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode({800, 600}), "AStar Pathfinding Demo");


    m_startPos = {1,5};
    m_goalPos = {9,5};

    m_startCircle.setRadius(15);
    m_startCircle.setFillColor(sf::Color::Red);
    m_startCircle.setOrigin({-m_startCircle.getRadius() - 10, m_startCircle.getRadius() - (m_pathSize.y + 2)});
    m_startCircle.setPosition({m_startPos.x * 30.f, m_startPos.y * 30.f});

    m_goalCircle.setRadius(15);
    m_goalCircle.setFillColor(sf::Color::Green);
    m_goalCircle.setOrigin({-m_goalCircle.getRadius(), m_goalCircle.getRadius() - (m_pathSize.y + 2)});
    m_goalCircle.setPosition({m_goalPos.x * 30.f, m_goalPos.y * 30.f});

    m_path = m_pathfinder.Run(m_startPos, m_goalPos);
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
        else if (const sf::Event::KeyPressed* keyEvent = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyEvent->code == sf::Keyboard::Key::S)
            {
                m_mode = Mode::PlaceStart;
            }
            else if (keyEvent->code == sf::Keyboard::Key::G)
            {
                m_mode = Mode::PlaceGoal;
            }else if (keyEvent->code == sf::Keyboard::Key::W)
            {
                m_mode = Mode::PlaceWall;
            }
            else if (keyEvent->code == sf::Keyboard::Key::Enter)
            {
                m_path = m_pathfinder.Run(m_startPos, m_goalPos);
            }
        }
        else if (const sf::Event::MouseMoved* mousePos = event->getIf<sf::Event::MouseMoved>())
        {
            m_currentMouseGridCoords = (mousePos->position / 30) - sf::Vector2i{1, 0};
        }
        else if (const sf::Event::MouseButtonPressed* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                if (m_mode == Mode::PlaceStart)
                {
                    m_startPos = m_currentMouseGridCoords;
                    m_startCircle.setPosition({m_startPos.x * 30.f, m_startPos.y * 30.f});
                }
                else if (m_mode == Mode::PlaceGoal)
                {
                    m_goalPos = m_currentMouseGridCoords;
                    m_goalCircle.setPosition({m_goalPos.x * 30.f, m_goalPos.y * 30.f});
                }
                else if (m_mode == Mode::PlaceWall)
                {
                    //TODO: implement
                }
            }
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

        rect.setSize(m_pathSize);
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
    m_window->draw(m_startCircle);
    m_window->draw(m_goalCircle);
}

bool Application::approx(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}


