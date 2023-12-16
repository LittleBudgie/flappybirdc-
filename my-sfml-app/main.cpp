/*
Flappy Bird Project sPeriod 2
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourcePath.hpp"


/** This function reads in the app icon
 @param: the SFML window of the game
 */

void load_app_icon(sf::RenderWindow& app_window)
{
    sf::Image icon;
    if (!icon.loadFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/flappybird.png"))
    {
        return EXIT_FAILURE;
    }
    app_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

/** This function creates a pillar (RectangleShape from SFML)
 @param: width and height of rectangle
 @return: rectangle created
 */

sf::RectangleShape create_pillar(int width, int height)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(4);
    return rectangle;
}

/** This function creates a bounding box around the pillars to use for collision checks
 @param: sf::RectangleShape rectangle (a pillar)
 @return: sf::FloatRect adjusted_rect (the bounding box)
 */

sf::FloatRect adjusted_bounds(sf::RectangleShape rectangle)
{
    sf::FloatRect adjusted_rect(
        rectangle.getGlobalBounds().width * 0.1 + rectangle.getGlobalBounds().left,
        rectangle.getGlobalBounds().height * 0.1 + rectangle.getGlobalBounds().top,
        rectangle.getGlobalBounds().width * 0.2,
        rectangle.getGlobalBounds().height * 0.2
    );
    return adjusted_rect;
}

int main(int, char const**)
{
    // GAME SETUP
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    load_app_icon(window);

    // Load background
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "background.jpg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    // Load flappy bird
    sf::Texture texture_two;
    if (!texture_two.loadFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/flappybird.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite flappy_sprite;
    flappy_sprite.setTexture(texture_two);
    flappy_sprite.setScale(sf::Vector2f(0.15f, 0.15f));
    
    //Global variables
    double flappy_sprite_y = 0;
    double drop_speed_of_bird = 0;
    double speed_of_pillar_move = 0;
    bool draw_sprite = false;
    
    //these keep track of the x-component of position
    double x_rectangle_one = 250.0;
    double x_rectangle_three = 520.0;
    double x_rectangle_five = 800.0;
    
    //to prevent using magic numbers, as discussed in class, here are constants:
    const double LOWER_BOUND_Y = -20;
    const double UPPER_BOUND_Y = 500;
    float random_y_scale = 0.15;

    // OPENING GAME SCREEN STYLE
    // Getting text
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
    sf::Music game_screen_music;
    if (!game_screen_music.openFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/049269_funny-fanfare-2wav-65260.mp3"))
    {
        return EXIT_FAILURE;
    }

    // Play game screen music
    //game_screen_music.play();
    
    // Load background music for game
    sf::Music music;
    if (!music.openFromFile("/Users/suhanashrivastava/SFML project/flappybirdc-/my-sfml-app/morning-funny-beat-7741.mp3"))
    {
        return EXIT_FAILURE;
    }
    
    //Creating pillars
    sf::RectangleShape rectangle_one = create_pillar(50, 100);
    sf::RectangleShape rectangle_two = create_pillar(50, 150);
    sf::RectangleShape rectangle_three = create_pillar(50, 52);
    sf::RectangleShape rectangle_four = create_pillar(50, 100);
    sf::RectangleShape rectangle_five = create_pillar(50, 150);
    sf::RectangleShape rectangle_six = create_pillar(50, 150);
    
    //GAME WINDOW CONTROL FUNCTIONS
    while (window.isOpen())
    {
        // Process events & set positions on variables
        sf::Event event;
        flappy_sprite.setPosition(50, flappy_sprite_y);
        rectangle_one.setPosition(x_rectangle_one, LOWER_BOUND_Y);
        rectangle_two.setPosition(x_rectangle_one, UPPER_BOUND_Y);
        rectangle_three.setPosition(x_rectangle_three, LOWER_BOUND_Y);
        rectangle_four.setPosition(x_rectangle_three, UPPER_BOUND_Y);
        rectangle_five.setPosition(x_rectangle_five, LOWER_BOUND_Y);
        rectangle_six.setPosition(x_rectangle_five, UPPER_BOUND_Y);
        
        // Always have flappy bird dropping a little
        if (flappy_sprite_y <=500)
        {
            flappy_sprite_y += drop_speed_of_bird;
        }
        
        //moving pillars to the left and having them appear again
        if (x_rectangle_one >= 0)
        {
            x_rectangle_one -= speed_of_pillar_move;
        }
        else
        {
            x_rectangle_one = 1000.0;
            random_y_scale = (int(rand()) % (2 - 1 + 1)) + 1;
            rectangle_one.setScale(1, random_y_scale);
            //update_pillar(rectangle_one, x_rectangle_one, random_y_scale);
        }
        
        if (x_rectangle_three >= 0)
        {
            x_rectangle_three -= speed_of_pillar_move;
        }
        else
        {
            x_rectangle_three = 1000.0;
            random_y_scale = (int(rand()) % (2 - 1 + 1)) + 1;
            rectangle_three.setScale(1, random_y_scale);
        }
        
        if (x_rectangle_five >= 0)
        {
            x_rectangle_five -= speed_of_pillar_move;
        }
        else
        {
            random_y_scale = (int(rand()) % (2 - 1 + 1)) + 1;
            rectangle_five.setScale(1, random_y_scale);
            x_rectangle_five = 1000.0;
        }
        
        //create the bounding boxes for the six pillars
        sf::FloatRect adjusted_bounds_rect1 = adjusted_bounds(rectangle_one);
        sf::FloatRect adjusted_bounds_rect2 = adjusted_bounds(rectangle_two);
        sf::FloatRect adjusted_bounds_rect3 = adjusted_bounds(rectangle_three);
        sf::FloatRect adjusted_bounds_rect4 = adjusted_bounds(rectangle_four);
        sf::FloatRect adjusted_bounds_rect5 = adjusted_bounds(rectangle_five);
        sf::FloatRect adjusted_bounds_rect6 = adjusted_bounds(rectangle_six);
        sf::FloatRect flappy_sprite_bounds = flappy_sprite.getGlobalBounds();
    
        //check if flappy sprite intersects the bounding boxes around pillars
        if (flappy_sprite_bounds.intersects(adjusted_bounds_rect1)
            || flappy_sprite_bounds.intersects(adjusted_bounds_rect2)
            || flappy_sprite_bounds.intersects(adjusted_bounds_rect3)
            || flappy_sprite_bounds.intersects(adjusted_bounds_rect4)
            || flappy_sprite_bounds.intersects(adjusted_bounds_rect5)
            || flappy_sprite_bounds.intersects(adjusted_bounds_rect6)
        )
        {
            draw_sprite = false;
            drop_speed_of_bird = 0;
            speed_of_pillar_move = 0;
            text.setString("GAME OVER! :(");
            text_two.setString("Press R to play again.");
        }
                
        while (window.pollEvent(event))
        {
            //If User Wants to Play Game
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                window.clear();
                draw_sprite = true;
                game_screen_music.stop();
                //music.play();
                drop_speed_of_bird = 0.25;
                speed_of_pillar_move = 0.09;
                text.setString(" ");
                text_two.setString(" ");
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                x_rectangle_one = -200.0;
                x_rectangle_three = 500.0;
                x_rectangle_five = 1000.0;
                draw_sprite = true;
                //music.play();
                drop_speed_of_bird = 0.25;
                speed_of_pillar_move = 0.09;
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
                if (flappy_sprite_y >= -25)
                {
                    flappy_sprite_y-=50;
                }
            }
        }
        // Clear screen
        window.clear();
        
        //Draw all sprites
        if (draw_sprite == true)
        {
            window.draw(sprite);
            window.draw(rectangle_one);
            window.draw(rectangle_two);
            window.draw(rectangle_three);
            window.draw(rectangle_four);
            window.draw(rectangle_five);
            window.draw(rectangle_six);
            window.draw(flappy_sprite);
        }

        // Draw the game screen text
        window.draw(text);
        window.draw(text_two);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
