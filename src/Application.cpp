#include "Application.h"

Application::Application() : m_pathfinder(m_graph), m_pathSize({30, 8}), m_mode(Mode::PlaceWall)
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode({800, 600}), "AStar Pathfinding Demo");

    m_startPos = {7,10};
    m_goalPos = {17,10};

    m_startCircle.setRadius(15);
    m_startCircle.setFillColor(sf::Color::Red);
    m_startCircle.setOrigin({-m_startCircle.getRadius() - 10, m_startCircle.getRadius() - (m_pathSize.y + 2)});
    m_startCircle.setPosition({m_startPos.x * 30.f, m_startPos.y * 30.f});

    m_goalCircle.setRadius(15);
    m_goalCircle.setFillColor(sf::Color::Green);
    m_goalCircle.setOrigin({-m_goalCircle.getRadius(), m_goalCircle.getRadius() - (m_pathSize.y + 2)});
    m_goalCircle.setPosition({m_goalPos.x * 30.f, m_goalPos.y * 30.f});

    m_startIndicator = m_startCircle;
    m_goalIndicator = m_goalCircle;

    auto startColor = m_startCircle.getFillColor();
    auto goalColor = m_goalCircle.getFillColor();
    startColor.a = 100;
    goalColor.a = 100;
    m_startIndicator.setFillColor(startColor);
    m_goalIndicator.setFillColor(goalColor);

    m_indicator.setSize({30,30});
    m_indicator.setFillColor(sf::Color(255,255,255, 100));

    UpdatePath();

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
    DrawPath(m_path);
    DrawGraph(m_graph);
    if (m_mode == Mode::PlaceWall)
    {
        m_window->draw(m_indicator);
    }else if (m_mode == Mode::PlaceStart)
    {
        m_window->draw(m_startIndicator);
    }else if (m_mode == Mode::PlaceGoal)
    {
        m_window->draw(m_goalIndicator);
    }
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
                UpdatePath();
            }
        }
        else if (const sf::Event::MouseMoved* mousePos = event->getIf<sf::Event::MouseMoved>())
        {
            m_currentMouseGridCoords = (mousePos->position / 30) - sf::Vector2i{1, 0};
            m_startIndicator.setPosition({(m_currentMouseGridCoords.x) * 30.f, m_currentMouseGridCoords.y * 30.f});
            m_goalIndicator.setPosition({(m_currentMouseGridCoords.x) * 30.f, m_currentMouseGridCoords.y * 30.f});
            m_indicator.setPosition({(m_currentMouseGridCoords.x + 1) * 30.f, m_currentMouseGridCoords.y * 30.f});
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_mode == Mode::PlaceWall)
            {
                m_graph[{m_currentMouseGridCoords.x + 1, m_currentMouseGridCoords.y}] = 1000;
                UpdatePath();
            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_mode == Mode::PlaceWall)
            {
                m_graph[{m_currentMouseGridCoords.x + 1, m_currentMouseGridCoords.y}] = 0;
                UpdatePath();
            }
        }
        else if (const sf::Event::MouseButtonPressed* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                if (m_mode == Mode::PlaceStart)
                {
                    m_startPos = m_currentMouseGridCoords;
                    m_startCircle.setPosition({m_startPos.x * 30.f, m_startPos.y * 30.f});
                    UpdatePath();
                }
                else if (m_mode == Mode::PlaceGoal)
                {
                    m_goalPos = m_currentMouseGridCoords;
                    m_goalCircle.setPosition({m_goalPos.x * 30.f, m_goalPos.y * 30.f});
                    UpdatePath();
                }
                else if (m_mode == Mode::PlaceWall)
                {
                    m_graph[{m_currentMouseGridCoords.x + 1, m_currentMouseGridCoords.y}] = 1000;
                    UpdatePath();
                }
            }
            else if (mousePressed->button == sf::Mouse::Button::Right)
            {
                if (m_mode == Mode::PlaceWall &&
                    m_graph[{m_currentMouseGridCoords.x + 1, m_currentMouseGridCoords.y}] != 0)
                {
                    m_graph[{m_currentMouseGridCoords.x + 1, m_currentMouseGridCoords.y}] = 0;
                    UpdatePath();
                }
            }
        }
    }
}

void Application::DrawGraph(const Graph& graph)
{

    for (auto pair : graph)
    {
            if (pair.second != 0)
            {
                sf::RectangleShape rect;
                rect.setPosition({pair.first.x * 30.f, pair.first.y * 30.f});
                rect.setSize({30,30});
                m_window->draw(rect);
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

        m_window->draw(rect);
    }
    m_window->draw(m_startCircle);
    m_window->draw(m_goalCircle);
}

bool Application::approx(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}

void Application::UpdatePath()
{
    m_pathfinder.setGraph(m_graph);
    m_path = m_pathfinder.Run(m_startPos, m_goalPos);
}


