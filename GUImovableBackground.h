#ifndef GUIMOVABLEBACKGROUNDS_H
#define GUIMOVABLEBACKGROUNDS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
/*
class MovableBackground
{
public:
    MovableBackground();
    void Update(sf::RenderWindow &window, float elapsedTime);
    void Render(sf::RenderWindow &window);
   
private:
    sf::Texture bg1Tex;
    sf::Texture bgTex;
    sf::Texture bg2Tex;

    sf::Sprite  bgSprite;
    sf::Sprite  bg2Sprite;

    float bgSpeed;
    float bgY;
    float bg2Y;
    float windowbg1diff;
};
#endif

*/
class MovableBackground
{
public:
    MovableBackground();
    void Update(sf::RenderWindow &window, float elapsedTime);
    void Render(sf::RenderWindow &window);
   
private:
    sf::Texture bgTex;
    sf::Texture bg2Tex;

    sf::RectangleShape bgShape;
    sf::RectangleShape bg2Shape;
    sf::Vector2f bgSize;
sf::Vector2f bg2Size;
    sf::Sprite  bgSprite;
    sf::Sprite  bg2Sprite;

    float bgSpeed;
    float bgY;
    float bg2Y;
    float windowbg1diff;
};
#endif
 
