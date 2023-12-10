
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load background
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "background.jpg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    // Load flappy bird
    
    sf::Texture texturetwo;
    if (!texturetwo.loadFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/flappybird.png"))
    {
        return EXIT_FAILURE;
    }
    
    //creating sprite and associated properties
    sf::Sprite flappysprite;
    double y = 0;
    double dropspeedofbird = 0;
    double speedofpillarmove = 0;
    bool drawsprite = false;
    flappysprite.setTexture(texturetwo);
    flappysprite.setScale(sf::Vector2f(0.15f, 0.15f));

    // Opening Game Screen with Text
    sf::Font font;
    if (!font.loadFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/PressStart2P-Regular.ttf"))
    {
        return EXIT_FAILURE;
    }
    sf::Text text("Welcome to Flappy Bird!", font, 25);
    text.setFillColor(sf::Color::White);
    text.setPosition(150, 250);
    sf::Text text_two(">  Press P To Begin", font, 15);
    text_two.setFillColor(sf::Color::White);
    text_two.setPosition(150, 315);

    // Load game screen music to play
    sf::Music gamescreenmusic;
    if (!gamescreenmusic.openFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/049269_funny-fanfare-2wav-65260.mp3"))
    {
        return EXIT_FAILURE;
    }

    // Play game screen music
    //gamescreenmusic.play();
    
    // Load background music for game
    sf::Music music;
    if (!music.openFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/morning-funny-beat-7741.mp3"))
    {
        return EXIT_FAILURE;
    }
    
    //Creating pillars
    sf::RectangleShape rectangle_one(sf::Vector2f(50, 100));
    rectangle_one.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle_two(sf::Vector2f(50, 150));
    rectangle_two.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle_three(sf::Vector2f(50, 52));
    rectangle_three.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle_four(sf::Vector2f(50, 100));
    rectangle_four.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle_five(sf::Vector2f(50, 150));
    rectangle_five.setFillColor(sf::Color::Yellow);
    sf::RectangleShape rectangle_six(sf::Vector2f(50, 150));
    rectangle_six.setFillColor(sf::Color::Yellow);
    
    
    //these keep track of the x-component of position
    double x_rectangle_one = 250.0;
    double x_rectangle_three = 520.0;
    double x_rectangle_five = 800.0;
    //to prevent using magic numbers, as discussed in class, here are constants:
    const double LOWER_BOUND_Y = -20;
    const double UPPER_BOUND_Y = 500;
    float random_y_scale = 0.15;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events & set positions on variables
        sf::Event event;
        flappysprite.setPosition(50, y);
        rectangle_one.setPosition(x_rectangle_one, LOWER_BOUND_Y);
        rectangle_two.setPosition(x_rectangle_one, UPPER_BOUND_Y);
        rectangle_three.setPosition(x_rectangle_three, LOWER_BOUND_Y);
        rectangle_four.setPosition(x_rectangle_three, UPPER_BOUND_Y);
        rectangle_five.setPosition(x_rectangle_five, LOWER_BOUND_Y);
        rectangle_six.setPosition(x_rectangle_five, UPPER_BOUND_Y);
        
        // Always have flappy bird dropping a little
        if (y <=500)
        {
            y += dropspeedofbird;
        }
        
        //moving pillars to the left and having them appear again
        if (x_rectangle_one >= 0)
        {
            x_rectangle_one -= speedofpillarmove;
        }
        else
        {
            x_rectangle_one = 1000.0;
            random_y_scale = (int(rand()) % (4 - 1 + 1)) + 1;
            rectangle_one.setScale(1, random_y_scale);
        }
        
        if (x_rectangle_three >= 0)
        {
            x_rectangle_three -= speedofpillarmove;
        }
        else
        {
            x_rectangle_three = 1000.0;
            random_y_scale = (int(rand()) % (4 - 1 + 1)) + 1;
            rectangle_three.setScale(1, random_y_scale);
        }
        
        if (x_rectangle_five >= 0)
        {
            x_rectangle_five -= speedofpillarmove;
        }
        else
        {
            rectangle_five.setScale(1, random_y_scale);
            x_rectangle_five = 1000.0;
        }
        
        while (window.pollEvent(event))
        {
            //If User Wants to Play Game
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                drawsprite = true;
                gamescreenmusic.stop();
                //music.play();
                dropspeedofbird = 0.25;
                speedofpillarmove = 0.09;
                text.setString(" ");
                text_two.setString(" ");
            }
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            
            // Pressing space moves flappy bird up
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (y >= -25)
                {
                    y-=50;
                }
            }
        }
        // Clear screen
        window.clear();

        // Draw background
        
        //Draw flappy bird
        if (drawsprite == true)
        {
            window.draw(sprite);
            window.draw(rectangle_one);
            window.draw(rectangle_two);
            window.draw(rectangle_three);
            window.draw(rectangle_four);
            window.draw(rectangle_five);
            window.draw(rectangle_six);
            window.draw(flappysprite);
        }

        // Draw the game screen text
        window.draw(text);
        window.draw(text_two);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
