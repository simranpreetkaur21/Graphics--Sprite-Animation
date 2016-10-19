#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

int spriteWalkSpeed = 10;
int DownspriteWalkSpeed = 5;
int up=-spriteWalkSpeed, down=DownspriteWalkSpeed, left=-spriteWalkSpeed, right=spriteWalkSpeed;

int xVelocity =0, yVelocity=0;

const int SC_WIDTH=800;
const int  SC_HEIGHT= 600;
const float  REFRESH_RATE =0.01f; //how often we draw the frame in seconds

const double delay=0.05;
const int SPRITEROWS=4; //number of ROWS OF SPRITES
const int SPRITECOLS=2;//number of COLS OF SPRITES
bool flag=false;

std::string gameOver = "Game Over";

int main()
{


    // Create the main window
    sf::RenderWindow App (sf::VideoMode(SC_WIDTH, SC_HEIGHT, 32), "Space Invaders!",sf::Style::Close );

    // Create a clock for measuring time elapsed
    sf::Clock Clock;
 
    //load the invaders images
    sf::Texture invaderTexture;
    invaderTexture.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/lion.png");
    sf::Sprite invaderSprites(invaderTexture);
    //std::vector<sf::Sprite> invaderSprites(10, sf::Sprite(invaderTexture));
    

	//load the invaders images
	/*sf::Image img;
    img.loadFromFile("/home/simranpreet/Documents/index.png");
    if (!img.loadFromFile("/home/simranpreet/Documents/index.png"))
        return 1;
	img.createMaskFromColor(sf::Color::White);
	sf::Texture invaderTexture;
	invaderTexture.loadFromImage(img);
	sf::Sprite invaderSprites(invaderTexture);*/
	

    int invadersWidth=invaderTexture.getSize().x;
    int invadersHeight=invaderTexture.getSize().y;

    int spaceWidth=invadersWidth/SPRITECOLS;
    int spaceheight=invadersHeight/SPRITEROWS;

    sf::IntRect area(0,0,spaceWidth,spaceheight);
    invaderSprites.setTextureRect(area);
	static int ctry=0;

 
	invaderSprites.setPosition(50,50);
	invaderSprites.setScale(2.0f,2.0f);
	invaderTexture.setSmooth(true);


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
			   flag=true;
		   }
        }

        if(flag==true)
        {
            //carry out updating tasks
            static float spriteTimer=0.0;  //keep track of sprite time
            spriteTimer+=Clock.getElapsedTime().asSeconds();

            static int count=0; //keep track of where the sub rect is
            
            if(spriteTimer>delay)
            {
                invaderSprites.setTextureRect(area);
                ++count;
               // invaderSprites.move(xVelocity+=10, yVelocity);   
                if(count==SPRITECOLS) //we have move off right off the texture
                {
                    area.left=0;            //reset texture rect at left
					area.top+=spaceheight;
					ctry++;
                    count=0;                //reset count
                }
                else
                {
                    area.left+=spaceWidth; //move texture rect right

                }
				
                if(ctry==(SPRITEROWS-1))
                {
					area.left=0;
					area.top=0;
					ctry=0;
				}
				
                spriteTimer=0; //we have made one move in the sprite tile - start timing for the next move
            }
           // invaderSprites.move(xVelocity+=1, yVelocity);   
            Clock.restart();
                
        
        }
			// Finally, display the rendered frame on screen
    
			App.clear();
			App.draw(invaderSprites);
			App.display();
    }

    return EXIT_SUCCESS;
}
