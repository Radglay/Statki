#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gra.h"


class Kwadrat_1 {
    sf::Texture kw;
    sf::Sprite sprajt;

public:
    Kwadrat_1(sf::Vector2f wektor, sf::IntRect& r1, sf::Vector2f skala_wekt) {
        //kw.loadFromFile("puste.png");
        
        //sprajt.setTexture(kw);
        sprajt.setTextureRect(r1);
        sprajt.setPosition(wektor);
        //sprajt.setColor(sf::Color::White);
        sprajt.setScale(skala_wekt);
    };

    void wypisz(sf::RenderWindow& window) {
        window.draw(sprajt);
    }

    void _czy_kliknieto(sf::RenderWindow& window, sf::Vector2i position, GameStates& currentState) {
        if (position.x >= sprajt.getPosition().x && position.x <= sprajt.getPosition().x + sprajt.getLocalBounds().width) {
            if (position.y >= sprajt.getPosition().y && position.y <= sprajt.getPosition().y + sprajt.getLocalBounds().height) {
                if (position.y <= 390)
                    currentState = STATE_CHOOSING_TEAMS;
           
                else if (position.y > 390 && position.y <= 440) {
                    sf::Text text;
                    sf::Font font;
                    font.loadFromFile("arial.ttf");
                    text.setFont(font);
                    text.setCharacterSize(20);
                    text.setString("Informacje o grze: twórcy Szymon Cygan & £ukasz Dyrlaga");
                    
                    window.clear();
                    window.draw(text);
                   
 
                    window.display();
                     sf::sleep(sf::seconds(10));
                }
                    
                else if (position.y > 440 && position.y <= 490)
                    currentState = STATE_EXIT;
            }
                
        }
    }
};

class Napisy{
    sf::Text text;
    sf::Font font;
   
public:
    Napisy();
    Napisy(std::string tresc, int rozmiar, sf::Vector2f wektor); //konstruktor, wartosci DEFAULT
    
    void wypisz(sf::RenderTarget& window);
};

Napisy::Napisy(std::string tresc, int rozmiar, sf::Vector2f wektor) { //konstruktor, wartosci DEFAULT
    font.loadFromFile("Xephyr Shadow.ttf");
    text.setString(tresc);
    text.setCharacterSize(rozmiar);
    text.move(wektor);
    text.setFillColor(sf::Color::Red);
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
}

void Napisy::wypisz(sf::RenderTarget& window) {
    window.draw(text);
}

void _text(sf::RenderWindow& window, sf::Event event, GameStates& currentState) { //WYSWIETLANIE MENU

    sf::Vector2f wektor;
    wektor.x = 250.f;
    wektor.y = 200.f;
    Napisy text("SHIP WARS", 100, wektor);
    Napisy graj("graj", 30, { 505.f, 350.f });
    Napisy informacje("informacje", 30, { 450.f, 400.f });
    Napisy wyjdz("wyjdz", 30, { 500.f, 450.f });

    //sprite pod napisy w menu gry!
    sf::Vector2f wektra[3];
    wektra[0].x = (window.getSize().x) / 2 - 50;  //POLOZENIE
    wektra[0].y = (window.getSize().y) / 2 + 50;

    wektra[1].x = (window.getSize().x) / 2 - 120;  //POLOZENIE
    wektra[1].y = (window.getSize().y) / 2 + 100;

    wektra[2].x = (window.getSize().x) / 2 - 70;  //POLOZENIE
    wektra[2].y = (window.getSize().y) / 2 + 150;

    sf::IntRect r1(0, 0, 100, 40);  //ROZMIAR
    sf::IntRect r2(0, 0, 240, 40);  //ROZMIAR
    sf::IntRect r3(0, 0, 140, 40);  //ROZMIAR
    
    Kwadrat_1 menu_1(wektra[0], r1, { 1.5, 1.25 });        //graj
    Kwadrat_1 menu_2(wektra[1], r2, { 3, 1.25 });       //info
    Kwadrat_1 menu_3(wektra[2], r3, { 1.5, 1.25 });      //wyjdz


    
    //Kwadrat info;
    //Kwadrat koniec;
    window.clear();
    menu_1.wypisz(window);
    menu_2.wypisz(window);
    menu_3.wypisz(window);
    text.wypisz(window);
    graj.wypisz(window);
    informacje.wypisz(window);
    wyjdz.wypisz(window);
    window.display();

    sf::Vector2i position;
    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
        position = sf::Mouse::getPosition(window);//pozycja myszki
        menu_1._czy_kliknieto(window, position, currentState);
        menu_2._czy_kliknieto(window, position, currentState);
        menu_3._czy_kliknieto(window, position, currentState);
    }
}