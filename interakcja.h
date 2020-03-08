#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "kreator.h"
#include "gra.h"

int tura = 0;


/*
ZAPISYWANIE LOGICZNEJ struktury mapy statkow dla kazdego gracza dziala


*wypisanie 2 plansz , pierwsza ze statkami, druga z trafami ////////////


*klikalna plansza 2 gdziw wybierasz miejsca,
pokazuje ona dodatkowo trafione i nietrafione miejsca //////////

*menu kontekstowe pozwalajace wybrac ktorym statkiem strzelasz

*najechanie na statek pokazuje jego zycie i czas ladowania??
*mechanizm wygrania (wszystkie statki wroga zatopione)


*/

void ekran_ladowania(sf::RenderWindow& window, sf::Event event, int tura, GameStates& current_state) {
	sf::Texture ekran_t;
	sf::Sprite ekran;
	ekran_t.loadFromFile("ekran_ladowania.png");
	ekran.setTexture(ekran_t);
	ekran.setScale({0.62, 0.67});
	//ustawienie tla

	//napisy
	sf::Text tekst;
	sf::Font font;
	{
		font.loadFromFile("OmegaRuby.ttf");
		tekst.setFont(font);
		tekst.setCharacterSize(30);
		std::string numer_gracza = (tura % 2 == 0)? " Gracz 1 " : " Gracz 2 ";
		tekst.setString(numer_gracza);
		tekst.setFillColor(sf::Color::Black);
		tekst.move({ 545, 300 });
	}
	//
	
	sf::Vector2i position;
	position = sf::Mouse::getPosition();

	window.draw(ekran);
	window.draw(tekst);
	window.display();
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
		current_state = STATE_FIGHT;
}

void rysuj_mape(sf::RenderWindow& window, PlanszaGracza& gracz) {
	/////////////////////////////// PASKI ZE WSPOLRZEDNYMI
	sf::Texture pion_t, poziom_t;
	sf::Sprite pion_1, pion_2, poziom_1, poziom_2;
	{pion_t.loadFromFile("pasek_y.png");
	poziom_t.loadFromFile("pasek_x.png");
	pion_1.setScale({ 0.58, 0.58 });
	poziom_1.setScale({ 0.58, 0.58 });
	pion_1.setTexture(pion_t);
	poziom_1.setTexture(poziom_t);
	/////////////STATKI
	pion_2.setScale({ 0.58, 0.58 });
	poziom_2.setScale({ 0.58, 0.58 });
	pion_2.setTexture(pion_t);
	poziom_2.setTexture(poziom_t);

	pion_2.setPosition({ 560, 0 });
	poziom_2.setPosition({ 560, 0 });
	}
	/////////////STRZALY
	window.draw(pion_1);
	window.draw(poziom_1);

	window.draw(pion_2);
	window.draw(poziom_2);
	///////////////

	sf::Vector2f position;
	///rysowanie planszy ze statkami
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (gracz.mapa_statki[i][j] == -1) {
				gracz.tekstura[i][j].loadFromFile("pudlo.png");
				gracz.plansza[i][j].setTexture(gracz.tekstura[i][j]);
			}
			window.draw(gracz.plansza[i][j]);
		}
	}
	//rysowanie planszy ze strza³ami
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			position.x = 560 + ((j + 1) * 46.3);
			position.y = ((i + 1) * 46.2);
			gracz.plansza_strzaly[i][j].setPosition(position);
			if (gracz.mapa_strzaly[i][j] == 1) {//trafione
				gracz.strzaly[i][j].loadFromFile("trafione.png");
				gracz.plansza_strzaly[i][j].setTexture(gracz.strzaly[i][j]);
			}
			else if (gracz.mapa_strzaly[i][j] == -1) {//pudlo
				gracz.strzaly[i][j].loadFromFile("pudlo.png");
				gracz.plansza_strzaly[i][j].setTexture(gracz.strzaly[i][j]);
			}
			window.draw(gracz.plansza_strzaly[i][j]);
		}
	}
}


void podswietl(sf::RenderWindow& window, PlanszaGracza& gracz, sf::Vector2i position, int x, int y) {
	if (gracz.mapa_strzaly[x][y] == 0) {
		gracz.strzaly[x][y].loadFromFile("zielony.png");
		gracz.plansza_strzaly[x][y].setTexture(gracz.strzaly[x][y]);
		window.draw(gracz.plansza_strzaly[x][y]);
	}
}

void oddaj_strzal(sf::RenderWindow& window, PlanszaGracza& gracz_1, PlanszaGracza& gracz_2, int tura,  int x, int y) {
	//x === i
	//y ==== j

	//gracz1
	if (tura % 2 == 0) {
		if (gracz_2.mapa_statki[x][y] != 0) {////trafiony statek
			gracz_1.mapa_strzaly[x][y] = 1;
			gracz_2.mapa_statki[x][y] = -1;
			gracz_1.strzaly[x][y].loadFromFile("trafione.png");
			gracz_1.plansza_strzaly[x][y].setTexture(gracz_1.strzaly[x][y]);
			window.draw(gracz_1.plansza_strzaly[x][y]);
			gracz_2.zatopione++;
		}
		else {
			gracz_1.mapa_strzaly[x][y] = -1;
			gracz_1.strzaly[x][y].loadFromFile("pudlo.png");
			gracz_1.plansza_strzaly[x][y].setTexture(gracz_1.strzaly[x][y]);
			window.draw(gracz_1.plansza_strzaly[x][y]);
		}
	}
	//gracz2
	else {
		if (gracz_1.mapa_statki[x][y] != 0) {////trafiony statek
			gracz_2.mapa_strzaly[x][y] = 1;
			gracz_1.mapa_statki[x][y] = -1;
			gracz_2.strzaly[x][y].loadFromFile("trafione.png");
			gracz_2.plansza_strzaly[x][y].setTexture(gracz_2.strzaly[x][y]);
			window.draw(gracz_2.plansza_strzaly[x][y]);
			gracz_1.zatopione++;
		}
		else {
			gracz_2.mapa_strzaly[x][y] = -1;
			gracz_2.strzaly[x][y].loadFromFile("pudlo.png");
			gracz_2.plansza_strzaly[x][y].setTexture(gracz_2.strzaly[x][y]);
			window.draw(gracz_2.plansza_strzaly[x][y]);
		}
	}
}

void wybieranie_miejsca(sf::RenderWindow& window, PlanszaGracza& gracz_1, PlanszaGracza& gracz_2,PlanszaGracza& gracz, sf::Event event, sf::Vector2i position, GameStates& current_state) {
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++) {
			if (position.x > (920 + (j + 1) * 75) && position.x < (920 + (j + 2) * 75)) {
				if (position.y > ((i + 1) * 72) && position.y < ((i + 2) * 72)) {
					/////////podswietlanie czy mozna
					podswietl(window, gracz, position, i, j);
					

					//gdy wcisniety zostanie przycisk myszy(lewy)
					if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
						if(gracz.mapa_strzaly[i][j] == 0){
							oddaj_strzal(window, gracz_1, gracz_2, tura, i, j);
							tura++;
							current_state = STATE_LADOWANIE;
						}
						
					}
				}
			}
		}

	}
}


void walka(sf::RenderWindow& window, PlanszaGracza& gracz_1, PlanszaGracza& gracz_2, sf::Event event, GameStates& current_state) {
	window.setSize({ 1800, 900 });
	sf::Vector2i position;
	if (gracz_1.zatopione == 12 || gracz_2.zatopione == 12)
		current_state = STATE_KONIEC;
	if (tura == 0) {
		gracz_1.zerowanie_mapy();
		gracz_2.zerowanie_mapy();
	}
	///KToRY GRACZ TERAZ 
	if (tura % 2 == 0) {
		window.clear();
		gracz_1.rysowanie();
		rysuj_mape(window, gracz_1);
		
		position = sf::Mouse::getPosition(window); ////ktory gracz teraz rusza
		wybieranie_miejsca(window, gracz_1, gracz_2, gracz_1, event, position, current_state);
		window.display();
	}
	else {
		window.clear();
		gracz_2.rysowanie();
		rysuj_mape(window, gracz_2);

		position = sf::Mouse::getPosition(window);   //ktory gracz teraz rusza
		wybieranie_miejsca(window, gracz_1, gracz_2, gracz_2, event, position, current_state);
		window.display();
	}
	////////////////////

}


void koniec_gry(sf::RenderWindow& window, PlanszaGracza& gracz_1, PlanszaGracza& gracz_2, sf::Event event) {
	sf::Text tekst;
	sf::Font font;
	std::string napis;
	{
		font.loadFromFile("OmegaRuby.ttf");
		tekst.setFont(font);
		tekst.setCharacterSize(50);
		tekst.setFillColor(sf::Color::White);
		tekst.setStyle(sf::Text::Bold);
		tekst.move({300, 300});
	}
	if (gracz_1.zatopione == 12) {
		napis = "Wygral gracz drugi!";
		tekst.setString(napis);
	}
	else {
		napis = "Wygral gracz pierwszy!";
		tekst.setString(napis);
	}
	window.draw(tekst);
	window.display();
}