#include <SFML/Graphics.hpp>
//#include <Sprite.hpp>
#include <SFML/Audio.hpp>


int main()
{
   // Create the main window
    sf::RenderWindow App (sf::VideoMode(800,600, 32), "Movement",sf::Style::Close );
    
	double  ctrx=0, ctry=0;
	int count=0;
	const double delay=0.09;
	const int SPRITEROWS=4; //number of ROWS OF SPRITES
	const int SPRITECOLS=12;
	bool flagback=false;
	int xVelocity =0, yVelocity=0;
	
	// Create a clock for measuring time elapsed
    sf::Clock Clock;
	sf::Time elapsed;

	//load sprite
    sf::Image img;
    img.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/sp2.png");
    if (!img.loadFromFile("/home/simranpreet/Documents/sprite_animations/Final_project/sp2.png"))
        return 1;
	img.createMaskFromColor(sf::Color::White);
	sf::Texture invaderTexture;
	invaderTexture.loadFromImage(img);
	sf::Sprite invaderSprites(invaderTexture);

	int invadersWidth=invaderTexture.getSize().x;
    int invadersHeight=invaderTexture.getSize().y;

    int spaceWidth=invadersWidth/SPRITECOLS;
    int spaceheight=invadersHeight/SPRITEROWS;

	sf::IntRect area(0,0,spaceWidth,spaceheight);
    invaderSprites.setTextureRect(area);
    
    invaderSprites.setPosition(250,250);
	invaderSprites.setScale(2.0f,2.0f);
	invaderTexture.setSmooth(true);

    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();
                
             //   Sprite.setTextureRect(sf::IntRect(+20 * elapsed.asSeconds(),+20 * elapsed.asSeconds(),38.8,38.3));

           if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
           {
			   area.top=0;
                static float spriteTimer=0.0;  //keep track of sprite time
				spriteTimer+=Clock.getElapsedTime().asSeconds();
				if(spriteTimer>delay)
				{
					count++;
					invaderSprites.move(0, 10);
					if(invaderSprites.getPosition().y>=599)
					invaderSprites.setPosition(invaderSprites.getPosition().x,0); 
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
		   }
                
           if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
           {
			   
			   area.top=spaceheight;
                static float spriteTimer=0.0;  //keep track of sprite time
				spriteTimer+=Clock.getElapsedTime().asSeconds();
				if(spriteTimer>delay)
				{
					count++;
					invaderSprites.move(-10, 0);
					if(invaderSprites.getPosition().x==0)
					invaderSprites.setPosition(800,invaderSprites.getPosition().y); 
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
		   }
		   
			
           if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
           {
                area.top=spaceheight*2;
                static float spriteTimer=0.0;  //keep track of sprite time
				spriteTimer+=Clock.getElapsedTime().asSeconds();
				if(spriteTimer>delay)
				{
					count++;
					invaderSprites.move(10, 0);
					if(invaderSprites.getPosition().x>=799)
					invaderSprites.setPosition(0,invaderSprites.getPosition().y); 
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
                
			}
           if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
            {
				
			   area.top=spaceheight*3;;
                static float spriteTimer=0.0;  //keep track of sprite time
				spriteTimer+=Clock.getElapsedTime().asSeconds();
				if(spriteTimer>delay)
				{
					count++;
					invaderSprites.move(0, -10);
					if(invaderSprites.getPosition().y==0)
					invaderSprites.setPosition(invaderSprites.getPosition().x,600); 
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
			}
			   
            
 
        }
        App.clear();
        App.draw(invaderSprites);
        App.display();
    }
}
