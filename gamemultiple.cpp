#include "GUImovableBackground.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <SFML/System.hpp>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

const int SC_WIDTH=800;
const int  SC_HEIGHT= 600;
const double delay=0.09;
const int SPRITEROWS=1; //number of ROWS OF SPRITES
const int SPRITECOLS=6;//number of COLS OF SPRITES
bool flag=false;
bool flagback=false;
bool flagup=false;


//std::string gameOver = "Game Over";

class OrientedBoundingBox // Used in the BoundingBoxTest
    {
    public:
        OrientedBoundingBox (const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
        {
            sf::Transform trans = Object.getTransform();    //Transform combining the position/rotation/scale/origin of the object
            sf::IntRect local = Object.getTextureRect();
            Points[0] = trans.transformPoint(0.f, 0.f);   ////TransformPoint() transforms a position from object space to world space.
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);
        }

        sf::Vector2f Points[4];

        void ProjectOntoAxis (const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
        {
            Min = (Points[0].x*Axis.x+Points[0].y*Axis.y);
            Max = Min;
            for (int j = 1; j<4; j++)
            {
                float Projection = (Points[j].x*Axis.x+Points[j].y*Axis.y);

                if (Projection<Min)
                    Min=Projection;
                if (Projection>Max)
                    Max=Projection;
            }
        }
    };

    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
        OrientedBoundingBox OBB1 (Object1);
        OrientedBoundingBox OBB2 (Object2);

        // Create the four distinct axes that are perpendicular to the edges of the two rectangles
        sf::Vector2f Axes[4] = {
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
            OBB1.Points[1].y-OBB1.Points[0].y),
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
            OBB1.Points[1].y-OBB1.Points[2].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
            OBB2.Points[0].y-OBB2.Points[3].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
            OBB2.Points[0].y-OBB2.Points[1].y)
        };

        for (int i = 0; i<4; i++) // For each axis...
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

            // ... project the points of both OBBs onto the axis ...
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

            // ... and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Seperating Axis Theorem states that there can be no collision between the rectangles
            if (!((MinOBB2<=MaxOBB1)&&(MaxOBB2>=MinOBB1)))
                return false;
        }
        return true;
    }


MovableBackground::MovableBackground()
{
    bgSpeed = 100;

	//upload background image
    bgTex.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/bg3.png");
	bg2Shape.setPosition(0,0);
    bgY = bgShape.getPosition().x + 800;
    bgSize.x = 800;
    bgSize.y = 600;

    bgShape.setTexture(&bgTex);
    bgShape.setSize(bgSize);

    bg2Tex.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/bg3.png");
	bg2Shape.setPosition(801,0);
    bg2Y = bgShape.getPosition().x ;
    bg2Shape.setTexture(&bg2Tex);
    bg2Shape.setSize(bgSize);
  
}


void MovableBackground::Update(sf::RenderWindow &window, float elapsedTime)
{
    if (bgY >=0)
    {
        bgY -= bgSpeed * elapsedTime;
    }
    else
        {
            bgY = 800;
        }
    
    
    if( bg2Y > bgY)
    {
		bg2Y =bgY+1;
    }
    
    if ( bg2Y >= 0)
    {
		
		bg2Y -= bgSpeed * elapsedTime ;
	}
	else
		{
			bg2Y=bgY+1;
		}
	
	bgShape.setPosition(bgY-800,0 );	
	bg2Shape.setPosition(bg2Y,0);
}

void MovableBackground::Render(sf::RenderWindow &window)
{
    window.draw(bgShape);
    window.draw(bg2Shape);
}
 
int main()
{

    // Create the main window
    sf::RenderWindow App (sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "Space Invaders!",sf::Style::Close );

    // Create a clock for measuring time elapsed
    sf::Clock Clock;
	sf::Time elapsed;

    //background texture
    MovableBackground mvb;
    
    //load the invaders images
	sf::Image img;
    img.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/as2.png");
    if (!img.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/as2.png"))
        return 1;
	img.createMaskFromColor(sf::Color::White);
	sf::Texture invaderTexture;
	invaderTexture.loadFromImage(img);
	sf::Sprite invaderSprites(invaderTexture);
	
	//load the obstacle images
	sf::Image obstacle;
    obstacle.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/obstacle.png");
    if (!obstacle.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/obstacle.png"))
        return 1;
	obstacle.createMaskFromColor(sf::Color::White);
	sf::Texture invaderTextureObs;
	invaderTextureObs.loadFromImage(obstacle);
	sf::Sprite Obs(invaderTextureObs);

    int invadersWidth=invaderTexture.getSize().x;
    int invadersHeight=invaderTexture.getSize().y;

	/*int ObsWidth=invaderTextureObs.getSize().x;
    int ObsHeight=invaderTextureObs.getSize().y;*/
    
    int spaceWidth=invadersWidth/SPRITECOLS;
    int spaceheight=invadersHeight/SPRITEROWS;

    sf::IntRect area(0,0,spaceWidth,spaceheight);
    invaderSprites.setTextureRect(area);
    
	static int ctry=0;
	static int count=0;
	static float spriteTimerJump=0.0;  //keep track of sprite time

	invaderSprites.setPosition(50,460);
	invaderSprites.setScale(2.0f,2.0f);
	invaderTexture.setSmooth(true);

	Obs.setPosition(800,510);
	Obs.setScale(0.8f,0.8f);


    // Start game loop  
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();
                
             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::LShift))
			{
			   flagback=true;
			}
		   
		   if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up) && flagback==true)
           {
				flagup=true;
				float temp;
				if(spriteTimerJump==0)
				{
					for(float y = 0; y <18; y++)
					{
						Obs.move(-1.7,0);
						invaderSprites.move(0,-y);
						App.clear();
						invaderSprites.setTextureRect(area);
						mvb.Update(App,Clock.getElapsedTime().asSeconds());
						Clock.restart();
						mvb.Render(App);
						App.draw(invaderSprites);
						App.draw(Obs);
						App.display();
						spriteTimerJump=Clock.getElapsedTime().asSeconds();
						
					}
				}
				temp=spriteTimerJump;
				cont:		
						Obs.move(-1.7,0);
						mvb.Update(App,Clock.getElapsedTime().asSeconds());
						Clock.restart();
						mvb.Render(App);
						App.draw(invaderSprites);
						App.draw(Obs);
						App.display();
				if(temp++> 30)
				{
					for(float y = 0; y < 18; y++)
					{	
						Obs.move(-1.7,0);
						invaderSprites.move(0,y);
						App.clear();
						invaderSprites.setTextureRect(area);
						App.clear();
						mvb.Update(App,Clock.getElapsedTime().asSeconds());
						Clock.restart();
						mvb.Render(App);
						App.draw(invaderSprites);
						App.draw(Obs);
						App.display();
					}
				spriteTimerJump =0;	
				}
				else
				goto cont;
				//check for collide
				if(BoundingBoxTest(invaderSprites, Obs))
				{
					sf::Text text;
					sf::Font font;
					if (!font.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/ufonts.com_cosmic.ttf"))
					{
						return 0;
					}
					// select the font
					text.setFont(font); // font is a sf::Font

					std::ostringstream ss; //string buffer to convert numbers to string
					ss << "Game Over" ;
					
					// set the string to display
					text.setString(ss.str()); //ss.str() converts the string buffer into a regular string 

					// set the character size
					text.setCharacterSize(24); // in pixels, not points!
					//text.setPosition(sf::Vector2f(10, 50));
					// set the color
					text.setColor(sf::Color::Red);

					// set the text style
					text.setStyle(sf::Text::Bold | sf::Text::Underlined);
				
					App.clear();
					App.draw(text);
					App.display();
					sf::sleep(sf::milliseconds(7000));
					App.close();
					return 0;
					
				}	
				
		   }
        }
   
		// mvoing background image and sprite on it
		if(flagback==true)
        {
			mvb.Update(App,Clock.getElapsedTime().asSeconds());
			
			   static float spriteTimer=0.0;  //keep track of sprite time
				spriteTimer+=Clock.getElapsedTime().asSeconds();
				if(spriteTimer>delay)
				{
					count++;
					invaderSprites.setTextureRect(area);
					if(count==SPRITECOLS)
					{
						area.left=0;
						count=0;   
					}
					else
					{
						area.left+=spaceWidth; //move texture rect right
					
					}
					spriteTimer=0;
				}
				
				Clock.restart();
				
				Obs.move(-1.7,0);	//moving obstacle
				
				//check for collide
				if(BoundingBoxTest(invaderSprites, Obs))
				{
					sf::Text text;
					sf::Font font;
					if (!font.loadFromFile("/home/jasmine/Documents/animation/font/vtks giz.ttf"))
					{
						return 0;
					}
					// select the font
					text.setFont(font); // font is a sf::Font

					std::ostringstream ss; //string buffer to convert numbers to string
					ss << "Game Over" ;
					
					// set the string to display
					text.setString(ss.str()); //ss.str() converts the string buffer into a regular string 

					// set the character size
					text.setCharacterSize(24); // in pixels, not points!
					//text.setPosition(sf::Vector2f(10, 50));
					// set the color
					text.setColor(sf::Color::Red);

					// set the text style
					text.setStyle(sf::Text::Bold | sf::Text::Underlined);
				
					App.clear();
					App.draw(text);
					App.display();
					sf::sleep(sf::milliseconds(7000));
					App.close();
					return 0;
					
				}
		}
		
		if(flagup==true  && spriteTimerJump > 0.1)
		{
			flagup=false;
			for(float y = 0; y < 30; y++)
			{
				Obs.move(-1.7,0);
				invaderSprites.move(0,y);
				App.clear();
				invaderSprites.setTextureRect(area);
				App.clear();
				mvb.Update(App,Clock.getElapsedTime().asSeconds());
				Clock.restart();
		
				mvb.Render(App);
				App.draw(invaderSprites);
				App.draw(Obs);
				App.display();
				
			}
			spriteTimerJump =0;	
		}

        // Finally, display the rendered frame on screen
          App.clear();
          mvb.Render(App);
          App.draw(invaderSprites);
          App.draw(Obs);
		  App.display();
    }

    return EXIT_SUCCESS;
}
