// snake game
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox;  //background number of pixels in width
int h = size * num_vertBox;    //background number of pixels in height

//Snake variables to dertermine length and direction
int direction1;    //direction the snake is moving
int snake_length1 = 4; //initial size is 4

// second snake variables
int direction2;
int snake_length2 = 4;

//Actual Snake in game is an array of x,y coordinates of sprite2
struct Snake1
{
    int x, y;        //each sprite of snake needs an x,y coordinate
}s1[100];

struct Snake2
{
    int x, y;
}s2[100];

//***NEW*** this is the fruit or food that the snake will eat
struct Fruit
{
    int x, y;    // only need one sprite needed for one food item
}food;

//move snake head based on user input and body by incrementing
//forward by iterating through arrays previous position
void move() {
    //1st update body so everything updates in proper order
    //move the body only!  s[0] = head will not be changed here
    // for snake 1
    for (int i = snake_length1; i > 0; i--)
    {
        s1[i].x = s1[i - 1].x;
        s1[i].y = s1[i - 1].y;
    }
    // for snake 2
    for (int j = snake_length2; j > 0; j--)
    {
        s2[j].x = s2[j - 1].x;
        s2[j].y = s2[j - 1].y;
    }
    
    //2nd update the head
    //Head of snake, s[0] depends on direction user inputs
    // snake 1
    //if user presses up
    if (direction1 == 0)
        s1[0].y -= 1;
    //if user presses down
    if (direction1 == 1)
        s1[0].y += 1;
    //if user presses left
    if (direction1 == 2)
        s1[0].x -= 1;
    //if user presses right
    if (direction1 == 3)
        s1[0].x += 1;
    
    // snake 2
    //if user presses up
    if (direction2 == 4)
        s2[0].y -= 1;
    //if user presses down
    if (direction2 == 5)
        s2[0].y += 1;
    //if user presses left
    if (direction2 == 6)
        s2[0].x -= 1;
    //if user presses right
    if (direction2 == 7)
        s2[0].x += 1;
    
    
    //***NEW*** If Snake eats food it should grow
    //check if snake head = food location
    // snake 1
    if (((s1[0].x) == food.x) && ((s1[0].y) == food.y))
    {
        //increment snake
        snake_length1++;
        
        //Randomly place food somewhere else
        food.x = rand() % num_horzBox;
        food.y = rand() % num_vertBox;
        
        // 2) modify timing as snake eats fruit, game should get faster!
        
    }
    // snake 2
    if (((s2[0].x) == food.x) && ((s2[0].y) == food.y))
    {
        //increment snake
        snake_length2++;
        
        //Randomly place food somewhere else
        food.x = rand() % num_horzBox;
        food.y = rand() % num_vertBox;
        
        // 2) modify timing as snake eats fruit, game should get faster!
        
    }
    
    //***NEW*** Boundary Checking snake as is hits screen end
    //loop snake back on other side
    // snake 1
    //LEFT and RIGHT
    if (s1[0].x > num_horzBox)
        s1[0].x = 0;
    if (s1[0].x < 0)
        s1[0].x = num_horzBox;
    //TOP and BOTTOM
    if (s1[0].y > num_vertBox)
        s1[0].y = 0;
    if (s1[0].y < 0)
        s1[0].y = num_vertBox;
    // snake 2
    //LEFT and RIGHT
    if (s2[0].x > num_horzBox)
        s2[0].x = 0;
    if (s2[0].x < 0)
        s2[0].x = num_horzBox;
    //TOP and BOTTOM
    if (s2[0].y > num_vertBox)
        s2[0].y = 0;
    if (s2[0].y < 0)
        s2[0].y = num_vertBox;
    
    //***NEW*** Check if you eat body of snake
    // snake 1
    for (int i = 1; i < snake_length1; i++)
    {
        //Cut Snake body from place eaten
        if (s1[0].x == s1[i].x && s1[0].y == s1[i].y)
            snake_length1 = i;
    }
    // snake 2
    for (int j = 1; j < snake_length2; j++)
    {
        //Cut Snake body from place eaten
        if (s2[0].x == s2[j].x && s2[0].y == s2[j].y)
            snake_length2 = j;
    }
}

int main()
{
    //Setting pseudorandom time, TODO:discuss true random vs pseudorandom
    srand(time(0));

    //Window that we can play the game in
    sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");
    
    //Textures load an image into the GPU Memory
    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("/Users/michellelim/Desktop/images/white.png");
    // color of first snake
    t2.loadFromFile("/Users/michellelim/Desktop/images/red.png");
    // 1) change the image of the fruit
    t3.loadFromFile("/Users/michellelim/Desktop/images/fox.png");
    // color of second snake
    t4.loadFromFile("/Users/michellelim/Desktop/images/green.png");
    
    //Sprite has physical dimmensions that can be set in
    //coordinate system, setPosition(x,y), and drawn on screen
    sf::Sprite sprite1(t1);
    sf::Sprite sprite2(t2);
    sf::Sprite sprite3(t3);
    sf::Sprite sprite4(t4);
    
    //***NEW*** initially place food somewhere on screen
    food.x = 10;
    food.y = 10;
    
    // initially place snake 1 somewhere
    s1[0].x = 15;
    s1[0].y = 15;
    
    s2[0].x = 5;
    s2[0].y = 5;
    
    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;
    while (window.isOpen())
    {
        //Error in class I placed this before the while loop
        //Should be placed in while loop as shown here to update
        //timer
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        //Allow us to check when a user does something
        sf::Event e;
        
        //Check when the window is closed
        while (window.pollEvent(e))
        {
            //If user presses x in the top right, Windows, top left, Mac,  close the window
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        //Control for Snake by User1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction1 = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction1 = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction1 = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction1 = 3;
        
        //Control for Snake by User2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction2 = 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction2 = 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction2 = 6;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction2 = 7;
        
        if (timer > delay)
        {
            timer = 0; //reset timer
            move();    //move Snake one sprite forward
        }
        
        /*****************
         //Draw in window
         *****************/
        window.clear();    //clear the window so new frame can be drawn in
        
        //NOTE: Order matters as we will draw over items listed first.
        //Hence the background should be the first thing you will always do
        //1st: Draw Background first
        for (int i = 0; i < num_horzBox; i++)
        {
            for (int j = 0; j < num_vertBox; j++)
            {
                //Set position of sprite1 one at a time
                sprite1.setPosition(i*size, j*size);
                //Draw sprite1 but, do not show it on screen.
                window.draw(sprite1);
            }
        }
        
        //2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background
        // snake 1
        for (int i = 0; i < snake_length1; i++)
        {
            //position sprite2 one at a time
            sprite2.setPosition(s1[i].x*size, s1[i].y*size);
            //Draw sprite2 one at a time by drawing over background
            window.draw(sprite2);
        }
        
        // snake 2
        for (int j = 0; j < snake_length2; j++)
        {
            //position sprite4 one at a time
            sprite4.setPosition(s2[j].x*size, s2[j].y*size);
            //Draw sprite4 one at a time by drawing over background
            window.draw(sprite4);
        }
        
        //***NEW*** 3rd: Draw Fruit
        sprite3.setPosition(food.x*size, food.y*size);
        window.draw(sprite3);

        //Show everything we have drawn on the screen
        window.display();
    }
    return 0;
}
