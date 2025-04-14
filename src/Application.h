
#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "AStar.h"

class Application {

    typedef std::unordered_map<sf::Vector2i, int, Vector2Hash> Graph;
    enum class Mode
    {
        PlaceStart,
        PlaceGoal,
        PlaceWall
    };

    std::unique_ptr<sf::RenderWindow> m_window;
    Graph m_graph;
    AStar m_pathfinder;
    std::vector<sf::Vector2i> m_path;
    Mode m_mode;

    sf::Vector2i m_startPos;
    sf::Vector2i m_goalPos;
    sf::CircleShape m_startCircle;
    sf::CircleShape m_goalCircle;

    sf::CircleShape m_startIndicator;
    sf::CircleShape m_goalIndicator;

    sf::RectangleShape m_indicator;

    sf::Vector2f m_pathSize;
    sf::Vector2i m_currentMouseGridCoords;




    void Update();
    void Render();
    void HandleEvents();


    void DrawGraph(const Graph& graph);
    void DrawPath(const std::vector<sf::Vector2i>& path);

    bool approx(float a, float b, float epsilon);
    void UpdatePath();

public:

    Application();
    ~Application();

    void Run();




};



#endif //APPLICATION_H
