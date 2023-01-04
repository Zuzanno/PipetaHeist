#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(900,700),"Pipeta Heist");
    //sound
    sf::SoundBuffer eff;
    sf::Sound sound;
    sound.setBuffer(eff);
    //text
    sf::Font font;
    sf::Text text;
    int cont = 0;
    //BG
    sf::Texture bgText;
    sf::Sprite bg;
    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    //Dallas
    sf::Texture dlsIMG;
    sf::Sprite dls;
    sf::FloatRect Dbbox = dls.getGlobalBounds();
    //pipeta
    sf::Texture pipIMG;
    sf::Sprite pipeta;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);
    
    if(!eff.loadFromFile("/home/zuzanno/cpp/sfml/pipeta/media/Effect.wav"))
    {
        return -1;
    }
    
    if(!font.loadFromFile("/home/zuzanno/cpp/sfml/pipeta/fonts/Symtext.ttf"))
    {
        return -1;
    }
    else
    {
        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
    }
    
    if(!dlsIMG.loadFromFile("/home/zuzanno/cpp/sfml/pipeta/media/Dallas.png"))
    {
        return -1;
    }
    else
    {
        dls.setTexture(dlsIMG);
        dls.setTextureRect(sf::IntRect(0,0,90,90));
        dls.setPosition(100,100);
        dls.setScale(sf::Vector2f(0.7,0.6));
    }
    
    if(!pipIMG.loadFromFile("/home/zuzanno/cpp/sfml/pipeta/media/pipeta.png"))
    {
        return -1;
    }
    else
    {
        pipeta.setTexture(pipIMG);
        pipeta.setTextureRect(sf::IntRect(0,0,170,160));
        pipeta.setPosition(rand() % 900,rand() % 700);
        pipeta.setScale(sf::Vector2f(0.4,0.3));
    }
    
    if(!bgText.loadFromFile("/home/zuzanno/cpp/sfml/pipeta/media/fondo.png"))
    {
        return -1;
    }
    else
    {
        TextureSize = bgText.getSize();
        WindowSize = window.getSize();
        
        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;
        
        bg.setTexture(bgText);
        bg.setScale(ScaleX, ScaleY);
    }
    
    while (window.isOpen())
    {
    
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            dls.move(3.f,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            dls.move(-3.f,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            dls.move(0.f,-3.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            dls.move(0.f,3.f);
        }
        
        if(dls.getPosition().y <= -4)
        {
            dls.setPosition(dls.getPosition().x, -4.f);
        }
        if(dls.getPosition().y >= 646)
        {
            dls.setPosition(dls.getPosition().x, 646.f);
        }
        if(dls.getPosition().x <= -14)
        {
            dls.setPosition(-14.f, dls.getPosition().y);
        }    
        if(dls.getPosition().x >= 838)
        {
            dls.setPosition(838.f, dls.getPosition().y);
        }
                
        if(dls.getGlobalBounds().intersects(pipeta.getGlobalBounds()))
        {
            pipeta.setPosition(rand() % 830,rand() % 630);
            cont++;
            sound.play();
        }

        text.setString("Pipetas: " + std::to_string(cont));
        
        window.clear();
        window.draw(bg);
        window.draw(dls);
        window.draw(pipeta);
        window.draw(text);
        window.display();
    
    }

}