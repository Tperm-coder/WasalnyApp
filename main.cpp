#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(800,800), "Graph Visualizer");
    bool canPressL = true, canPressR = true;
    vector<CircleShape>nodes;
    while (window.isOpen())
    {
        Event event{};
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(Mouse::isButtonPressed(Mouse::Left) && canPressL)
            {
                canPressL = false;
                CircleShape node;
                node.setRadius(50.0);
                node.setOutlineColor(Color::White);
                node.setOutlineThickness(5);
                node.setOrigin (50,50);
                node.setPosition((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y);
                window.draw(node);
                nodes.push_back(node);
                cout << "Drawn\n";
            }
            if(!Mouse::isButtonPressed(Mouse::Left))
                canPressL = true;

            if(Mouse::isButtonPressed(Mouse::Right) && canPressR)
            {
                canPressR = false;
                for(auto &i : nodes)
                {
                    float x = i.getPosition().x;
                    float y = i.getPosition().y;
                    float r = i.getRadius();
                    float mx = Mouse::getPosition(window).x;
                    float my = Mouse::getPosition(window).y;

                    if(y - r <= my && y + r >= my && x - r <= mx && x + r >= mx)
                        cout << "Connection\n";
                }
            }
            if(!Mouse::isButtonPressed(Mouse::Right))
                canPressR = true;
        }
        window.display();
    }

}