#pragma once
#include "menu.h"
enum ktory_gracz{PIERWSZY, DRUGI, ZADEN};

enum ktory_statek{MALY, SREDNI, DUZY, WYBRANE};

enum GameFractions {
	PIRACI,
	MAGOWIE,
	WIKINGOWIE
};

enum GameStates {
	STATE_MENU, //0            WYBOR Graj,wyjdz, info... 
	STATE_CHOOSING_TEAMS,//1         graj -> wybierz frakcje 
	STATE_TACTIC, //2          rozmieszczenie
	STATE_FIGHT, //3    walka
	STATE_LADOWANIE, //4 ekran ladowania
	STATE_EXIT, //5    WYLACZENI EGRY
	STATE_KONIEC //6 WYGRANA
};

	//////////// SUPER STATKi
class StatkiSpecjalne {
	GameFractions frakcja;
	
};
////////////////////
class PlanszaGracza {
public:
	int zatopione = 0;
	sf::Texture tekstura[10][10];///tekstury statkow zalezne od frakcji
	sf::Texture strzaly[10][10];
	sf::Sprite sprajtt;  //nie usuwaæ dziwna rzecz xD
	sf::Texture statek_tekstura;
	sf::Sprite plansza[10][10];
	sf::Sprite plansza_strzaly[10][10];
	sf::Vector2f pozycja;
	GameFractions frakcja;

	///////
	int mapa_statki[10][10];
	int mapa_logiczna[14][14];
	int mapa_strzaly[10][10];
	////MAPY

	void zerowanie_mapy() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				mapa_strzaly[i][j] = 0;
			}
		}
	}
	void rysowanie() {/////ZALEZNIE OD FRAKCJI
		
		switch (frakcja) {
		case PIRACI:
			statek_tekstura.loadFromFile("pirat.png");
			break;
		case WIKINGOWIE:
			statek_tekstura.loadFromFile("wiking.png");
			break;
		case MAGOWIE:
			statek_tekstura.loadFromFile("mag.png");
			break;
		default:
			break;
		}

		//sprajt.setTexture(tekstura);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				strzaly[i][j].loadFromFile("kwadrat.png");
				tekstura[i][j].loadFromFile("kwadrat.png");
				pozycja.x = (j + 1) * 46.2;
				pozycja.y = (i + 1) * 46.3;
				plansza[i][j].setTexture(tekstura[i][j]);
				//plansza[i][j].setColor(sf::Color::White);
				plansza[i][j].setPosition(pozycja);
				plansza[i][j].setScale({ 0.58, 0.58 });
				///////////////STATKI PRAWA STRONA
				plansza_strzaly[i][j].setTexture(strzaly[i][j]);
				plansza_strzaly[i][j].setScale({ 0.58, 0.58 });


				if (mapa_statki[i][j] != 0){
					plansza[i][j].setTexture(statek_tekstura);
				}

		}
	}
	}
};


void czy_kliknieto(sf::RenderWindow& window, sf::Vector2i position, sf::Text text[5], ktory_gracz& gracz, GameFractions (&frakcje)[2]) {

	if (position.x >= 465 && position.x <= 465 + text[0].getLocalBounds().width) {
		if (position.y <= 200 && position.y >= 200 - text[0].getLocalBounds().height) {
			if (gracz == PIERWSZY) {
				gracz = DRUGI;
				frakcje[0] = PIRACI;
			}
			else {
				frakcje[1] = PIRACI;
				gracz = ZADEN;
			}
			
		}
	}

	if (position.x >= 440 && position.x <= 440 + text[1].getLocalBounds().width) {
		if (position.y <= 300 && position.y >= 300 - text[1].getLocalBounds().height) {
			if (gracz == PIERWSZY) {
				gracz = DRUGI;
				frakcje[0] = MAGOWIE;
			}
			else {
				frakcje[1]= MAGOWIE;
				gracz = ZADEN;
			}
		}
			
	}

	if (position.x >= 400 && position.x <= 400 + text[2].getLocalBounds().width) {
		if (position.y <= 400 && position.y >= 400 - text[2].getLocalBounds().height){
			if (gracz == PIERWSZY) {
				gracz = DRUGI;
				frakcje[0] = WIKINGOWIE;
			}
			else {
				frakcje[1] = WIKINGOWIE;
				gracz = ZADEN;
			}
		}
			
	}
}





void wybor_frakcji(sf::RenderWindow& window, sf::Event event, GameStates& current_states, ktory_gracz& gracz, GameFractions (&frakcje)[2]) {

	sf::Text tekst[5];  //napisy
	sf::Font font;  //czcionka
	sf::Vector2f wektor;
	sf::Texture tekstura;  //tekstura tla
	sf::Sprite tlo; //stworzenie tla
	tekstura.loadFromFile("papirus.png");
	tlo.setTexture(tekstura);
	window.draw(tlo); //wyswietlenie tla itd...


	font.loadFromFile("Xephyr Shadow.ttf");
	for (int i = 0; i < 5; i++) {
		tekst[i].setFont(font);
		tekst[i].setFillColor(sf::Color::Red);
		tekst[i].setCharacterSize(50);
	}

	wektor.x = window.getSize().x / 2;
	wektor.y = window.getSize().y / 4;
	tekst[0].move(wektor.x - 85, wektor.y);
	tekst[1].move(wektor.x - 110, wektor.y + 100);
	tekst[2].move(wektor.x - 150, wektor.y + 200);
	tekst[3].move(wektor.x - 50, wektor.y - 100);
	tekst[4].move(20, wektor.y - 100);

	tekst[0].setString("Piraci");
	tekst[1].setString("Magowie");
	tekst[2].setString("Wikingowie");
	std::string numer = (gracz == PIERWSZY) ? "pierwszy" : "drugi";
	tekst[3].setString(numer);
	tekst[4].setString("Wybiera gracz: ");

	window.draw(tekst[0]);
	window.draw(tekst[1]);
	window.draw(tekst[2]);
	window.draw(tekst[3]);
	window.draw(tekst[4]);

	window.display();
	sf::Vector2i position;
	

	///INTERAKCJA Z NAPISAMI
	if (gracz == ZADEN)
		current_states = STATE_TACTIC;
	else {
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
			position = sf::Mouse::getPosition(window);
			czy_kliknieto(window, position, tekst, gracz, frakcje); //klikanie w pola + wybor frakcji
		}
	}
}
