#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "gra.h"
#include "interakcja.h"

int ruch = 0;

//////////////////////
//PLANSZA:		   //
//duzy -1x		  //
//sredni - 2x    //
//maly -5x      //
/////////////////

int czyja_tura = 1;
ktory_statek jaki_statek = DUZY; //PIERWSZE WYBIERAMY DUZY STATEK

void render_planszy(sf::RenderWindow& window, sf::Texture(&tekstura)[10][10], sf::Sprite(&plansza)[10][10],sf::Sprite poziom, sf::Sprite pion, int(&mapa_logiczna)[14][14]){
	sf::Vector2f pozycja; 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapa_logiczna[i + 2][j + 2] == 0) {
				tekstura[i][j].loadFromFile("kwadrat.png");
				plansza[i][j].setTexture(tekstura[i][j]);
			}
			//pola_mozliwe[i][j] = 1;
			pozycja.x = (j + 1) * 80;
			pozycja.y = (i + 1) * 52;
			
			plansza[i][j].setColor(sf::Color::White);
			plansza[i][j].setPosition(pozycja);
			plansza[i][j].setScale({ 1, 0.65 });
			window.draw(poziom);
			window.draw(pion);
			window.draw(plansza[i][j]);
		}
	}
}

void pierwsza_mapa_ustawienie(int(&mapa_statki)[10][10], int(&mapa_logiczna)[14][14]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			mapa_logiczna[i + 2][j + 2] = 0;
			mapa_statki[i][j] = 0;
		}
	}

	for (int i = 0; i < 13; i++) {
		mapa_logiczna[i][0] = 9;
		mapa_logiczna[i][1] = 9;
		mapa_logiczna[i][12] = 9;
		mapa_logiczna[i][13] = 9;
		mapa_logiczna[0][i] = 9;
		mapa_logiczna[1][i] = 9;
		mapa_logiczna[12][i] = 9;
		mapa_logiczna[13][i] = 9;
	}
}

void podswietlanie(sf::RenderWindow& window, sf::Texture(&tekstura)[10][10], sf::Sprite(&plansza)[10][10], sf::Event event, sf::Vector2i pozycja, int(&mapa_statki)[10][10], int(&mapa_logiczna)[14][14], ktory_statek jaki_statek, int x, int y) {
	int wartosc;
	switch (jaki_statek) {
	case DUZY:
		wartosc = 3;
		break;
	case SREDNI:
		wartosc = 2;
		break;
	case MALY:
		wartosc = 1;
		break;
	}//switch works

	int i = x;
	int j = y;
	std::cout << ruch;
	if (ruch == 0) {
		tekstura[i][j].loadFromFile((mapa_statki[i][j] == 0) ? "zielony.png" : "czerwony.png");
		plansza[i][j].setTexture(tekstura[i][j]);
	}

	else if (ruch > 0 && mapa_statki[x][y] == 0) { //&& mapa_statki[i][j] == 0) {
		if (jaki_statek == DUZY) {
			if (ruch < 2) {
				if (mapa_logiczna[x + 1][y + 2] == wartosc || mapa_logiczna[x + 3][y + 2] == wartosc || mapa_logiczna[x + 2][y + 1] == wartosc || mapa_logiczna[x + 2][y + 3] == wartosc) {
					//std::cout << "eloo";
					tekstura[i][j].loadFromFile("zielony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
			}
			else {
				if ((mapa_logiczna[x + 2][y + 3] == wartosc && mapa_logiczna[x + 2][y + 4] == wartosc) || (mapa_logiczna[x + 3][y + 2] == wartosc && mapa_logiczna[x + 4][y + 2] == wartosc) || (mapa_logiczna[x + 1][y + 2] == wartosc && mapa_logiczna[x][y + 2] == wartosc) || (mapa_logiczna[x + 2][y + 1] == wartosc && mapa_logiczna[x + 2][y] == wartosc)) {
					tekstura[i][j].loadFromFile("zielony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}

			}

		}

		else if (jaki_statek == SREDNI) {
			//std::cout << "eldo";
			if (ruch == 3) {
				if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
					tekstura[i][j].loadFromFile("zielony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
			}
			else if (ruch == 5) {
				if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
					if (mapa_logiczna[x + 1][y + 2] != 2 && mapa_logiczna[x + 3][y + 2] != 2 && mapa_logiczna[x + 2][y + 1] != 2 && mapa_logiczna[x + 2][y + 3] != 2) {
						tekstura[i][j].loadFromFile("zielony.png");
						plansza[i][j].setTexture(tekstura[i][j]);
						window.draw(plansza[i][j]);
					}
					else {
						tekstura[i][j].loadFromFile("czerwony.png");
						plansza[i][j].setTexture(tekstura[i][j]);
						window.draw(plansza[i][j]);
					}

				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}

			}


			else if (ruch > 3 && ruch < 5) {
				if (mapa_logiczna[x + 1][y + 2] == wartosc || mapa_logiczna[x + 3][y + 2] == wartosc || mapa_logiczna[x + 2][y + 1] == wartosc || mapa_logiczna[x + 2][y + 3] == wartosc) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
							//DZIALA
							//if (mapa_logiczna[x][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {


							//}
							tekstura[i][j].loadFromFile("zielony.png");
							plansza[i][j].setTexture(tekstura[i][j]);
							window.draw(plansza[i][j]);
						}
						else {
							tekstura[i][j].loadFromFile("czerwony.png");
							plansza[i][j].setTexture(tekstura[i][j]);
							window.draw(plansza[i][j]);
						}
					}
					else {
						tekstura[i][j].loadFromFile("czerwony.png");
						plansza[i][j].setTexture(tekstura[i][j]);
						window.draw(plansza[i][j]);
					}
				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
			}
			else if (ruch > 5) {
				if (mapa_logiczna[x + 1][y + 2] == 22 || mapa_logiczna[x + 3][y + 2] == 22 || mapa_logiczna[x + 2][y + 1] == 22 || mapa_logiczna[x + 2][y + 3] == 22) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
							//DZIALA

							if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
								//if (mapa_logiczna[x][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {


							//}
								tekstura[i][j].loadFromFile("zielony.png");
								plansza[i][j].setTexture(tekstura[i][j]);
								window.draw(plansza[i][j]);
							}
						}
						else {
							tekstura[i][j].loadFromFile("czerwony.png");
							plansza[i][j].setTexture(tekstura[i][j]);
							window.draw(plansza[i][j]);
						}
					}
					else {
						tekstura[i][j].loadFromFile("czerwony.png");
						plansza[i][j].setTexture(tekstura[i][j]);
						window.draw(plansza[i][j]);
					}
				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
			}
		}


		else if (jaki_statek == MALY) {
			if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
				if (mapa_logiczna[x + 1][y + 2] != 2 && mapa_logiczna[x + 3][y + 2] != 2 && mapa_logiczna[x + 2][y + 1] != 2 && mapa_logiczna[x + 2][y + 3] != 2) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 22 && mapa_logiczna[x + 3][y + 2] != 22 && mapa_logiczna[x + 2][y + 1] != 22 && mapa_logiczna[x + 2][y + 3] != 22) {

							tekstura[i][j].loadFromFile("zielony.png");
							plansza[i][j].setTexture(tekstura[i][j]);
							window.draw(plansza[i][j]);
						}
						else {
							tekstura[i][j].loadFromFile("czerwony.png");
							plansza[i][j].setTexture(tekstura[i][j]);
							window.draw(plansza[i][j]);
						}

					}
					else {
						tekstura[i][j].loadFromFile("czerwony.png");
						plansza[i][j].setTexture(tekstura[i][j]);
						window.draw(plansza[i][j]);
					}

				}
				else {
					tekstura[i][j].loadFromFile("czerwony.png");
					plansza[i][j].setTexture(tekstura[i][j]);
					window.draw(plansza[i][j]);
				}
			}
			else {
				tekstura[i][j].loadFromFile("czerwony.png");
				plansza[i][j].setTexture(tekstura[i][j]);
				window.draw(plansza[i][j]);
			}

		}
	}
	//wszystkie opcje ukladania dzialaj¹!
}



void sprawdz_czy_mozna(sf::RenderWindow& window, sf::Texture(&tekstura)[10][10], sf::Sprite(&plansza)[10][10], sf::Event event, sf::Vector2i pozycja, int(&mapa_statki)[10][10], int(&mapa_logiczna)[14][14], ktory_statek jaki_statek, int x, int y) {
	int wartosc;
	switch (jaki_statek) {
	case DUZY:
		wartosc = 3;
		break;
	case SREDNI:
		wartosc = 2;
		break;
	case MALY:
		wartosc = 1;
		break;
	}
	if (ruch == 0) {
		mapa_statki[x][y] = wartosc;
		mapa_logiczna[x + 2][y + 2] = wartosc;
		//obszar nietykalny
	
		/////
		plansza[x][y].setColor(sf::Color(0, 0, 0, 255));
		window.draw(plansza[x][y]);
		ruch++;
	}
	else {
		if (jaki_statek == DUZY && mapa_statki[x][y] == 0) {
			if (ruch < 2) {
				if (mapa_logiczna[x + 1][y + 2] == wartosc || mapa_logiczna[x + 3][y + 2] == wartosc || mapa_logiczna[x + 2][y + 1] == wartosc || mapa_logiczna[x + 2][y + 3] == wartosc) {
					//if (mapa_logiczna[x][y + 2] != 1 && mapa_logiczna[x + 4][y + 2] != wartosc && mapa) {
					plansza[x][y].setColor(sf::Color(0, 0, 0, 255));
					mapa_statki[x][y] = wartosc;
					mapa_logiczna[x + 2][y + 2] = wartosc;

					window.draw(plansza[x][y]);
					ruch++;
					//}
				}
			}
			else {
				if ((mapa_logiczna[x + 2][y + 3] == wartosc && mapa_logiczna[x + 2][y + 4] == wartosc) || (mapa_logiczna[x + 3][y + 2] == wartosc && mapa_logiczna[x + 4][y + 2] == wartosc) || (mapa_logiczna[x + 1][y + 2] == wartosc && mapa_logiczna[x][y + 2] == wartosc) || (mapa_logiczna[x + 2][y + 1] == wartosc && mapa_logiczna[x + 2][y] == wartosc)) {
					mapa_statki[x][y] = wartosc;
					mapa_logiczna[x + 2][y + 2] = wartosc;
					ruch++;
				}
			}

		}

		else if (jaki_statek == SREDNI && mapa_statki[x][y] == 0) {
			if (ruch == 3) {
				if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
					if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
						mapa_logiczna[x + 2][y + 2] = wartosc;
						mapa_statki[x][y] = wartosc;
						ruch++;
					}
				}
			}
			else if (ruch == 5) {
				if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
					if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
						if (mapa_logiczna[x + 1][y + 2] != 2 && mapa_logiczna[x + 3][y + 2] != 2 && mapa_logiczna[x + 2][y + 1] != 2 && mapa_logiczna[x + 2][y + 3] != 2) {
							mapa_logiczna[x + 2][y + 2] = 22;//wartosc odrózniaj¹ca statek nr2  od nr1 rozmiaru 2
							mapa_statki[x][y] = 2;
							ruch++;
						}
					}
				}
			}
			else if(ruch > 3 && ruch < 5){
				if (mapa_logiczna[x + 1][y + 2] == wartosc || mapa_logiczna[x + 3][y + 2] == wartosc || mapa_logiczna[x + 2][y + 1] == wartosc || mapa_logiczna[x + 2][y + 3] == wartosc) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
							mapa_logiczna[x + 2][y + 2] = wartosc;
							mapa_statki[x][y] = wartosc;
							ruch++;
						}
					}
				}
			}
			//WYBOR 2 statku o wielkosci 2(SREDNI)
			else if (ruch > 5 && ruch < 7) {
				if (mapa_logiczna[x + 1][y + 2] == 22 || mapa_logiczna[x + 3][y + 2] == 22 || mapa_logiczna[x + 2][y + 1] == 22 || mapa_logiczna[x + 2][y + 3] == 22) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
							if (mapa_logiczna[x + 1][y + 2] != 2 && mapa_logiczna[x + 3][y + 2] != 2 && mapa_logiczna[x + 2][y + 1] != 2 && mapa_logiczna[x + 2][y + 3] != 2) {
								mapa_logiczna[x + 2][y + 2] = 22;
								mapa_statki[x][y] = 2;
								ruch++;
							}
						}
					}
				}
			}

		}
		//MALY STATEK
		else if (jaki_statek == MALY && mapa_statki[x][y] == 0) {
			if (mapa_logiczna[x + 1][y + 2] != 3 && mapa_logiczna[x + 3][y + 2] != 3 && mapa_logiczna[x + 2][y + 1] != 3 && mapa_logiczna[x + 2][y + 3] != 3) {
				if (mapa_logiczna[x + 1][y + 2] != 2 && mapa_logiczna[x + 3][y + 2] != 2 && mapa_logiczna[x + 2][y + 1] != 2 && mapa_logiczna[x + 2][y + 3] != 2) {
					if (mapa_logiczna[x + 1][y + 2] != 1 && mapa_logiczna[x + 3][y + 2] != 1 && mapa_logiczna[x + 2][y + 1] != 1 && mapa_logiczna[x + 2][y + 3] != 1) {
						if (mapa_logiczna[x + 1][y + 2] != 22 && mapa_logiczna[x + 3][y + 2] != 22 && mapa_logiczna[x + 2][y + 1] != 22 && mapa_logiczna[x + 2][y + 3] != 22) {
							mapa_logiczna[x + 2][y + 2] = 1;
							mapa_statki[x][y] = 1;
							ruch++;
						}
					}
				}
			}

		}

	}
	/*r (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			std::cout << mapa_logiczna[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
}



void mouseOn(sf::RenderWindow& window, sf::Texture(&tekstura)[10][10], sf::Sprite(&plansza)[10][10], sf::Event event, sf::Vector2i pozycja, int(&mapa_statki)[10][10], int(&mapa_logiczna)[14][14], ktory_statek jaki_statek) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pozycja.x > (j + 1) * 65 && pozycja.x < (j + 2) * 65) {
				if (pozycja.y > (i + 1) * 80 && pozycja.y < (i + 2) * 80) {
						
					int x = i;
					int y = j;
					podswietlanie(window, tekstura, plansza, event, pozycja, mapa_statki, mapa_logiczna, jaki_statek, x, y);
					if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) 
						sprawdz_czy_mozna(window, tekstura, plansza, event, pozycja, mapa_statki, mapa_logiczna, jaki_statek, x, y);
					//std::cout << i << " " << j << std::endl;
				}
			}

		}
	}
}

void _utworz_plansze(sf::RenderWindow& window, sf::Event event, GameStates& current_state, GameFractions(&frakcje)[2], PlanszaGracza& gracz_1, PlanszaGracza& gracz_2){//, int (&mapa_statki)[10][10], int (&mapa_logiczna)[14][14]) {
	gracz_1.frakcja = frakcje[0];
	gracz_2.frakcja = frakcje[1];
	sf::Vector2i pozycja = sf::Mouse::getPosition(window);

	//if (ruch == 0)
	//	pierwsza_mapa_ustawienie(mapa_statki, mapa_logiczna);

	//NAPISY PO PRAWEJ STRONIE
	sf::Text text[2];
	sf::Font font;
	font.loadFromFile("arial.ttf");
	for (int i = 0; i < 2; i++) {
		text[i].setFont(font);
		text[i].setCharacterSize(30);
		text[i].setFillColor(sf::Color::White);
		text[i].setStyle(sf::Text::Bold);
	}
	text[0].move({ 900.f, 100.f });
	text[1].move({ 900.f, 150.f });

	text[0].setString((czyja_tura == 1) ? "pierwszy" : "drugi");

	if (ruch < 3)
		jaki_statek = DUZY;
	else if (ruch >= 3 && ruch < 7)
		jaki_statek = SREDNI;
	else if (ruch >= 7 && ruch < 12)
		jaki_statek = MALY;
	else if (ruch == 12)//wybranie wszystkich 5 statkow malych
		jaki_statek = WYBRANE;

	if (jaki_statek == WYBRANE) {
		czyja_tura++;
		ruch = 0;
	}
	

	if (jaki_statek == DUZY) 
		text[1].setString("DUZY");
	else if (jaki_statek == SREDNI)
		text[1].setString("SREDNI");
	else
		text[1].setString("MALY");
	//OKNO WYGLAD/ROZMIAR
	window.setSize({ 900, 900 });
	sf::Sprite pola[10][10];
	sf::Texture t_pola[10][10];
	sf::Sprite poziom, pion;
	sf::Texture t_poziom, t_pion;
	//t_poziom.create(900, 900);
	t_poziom.loadFromFile("pasek_x.png");
	t_pion.loadFromFile("pasek_y.png");

	poziom.setTexture(t_poziom);
	pion.setTexture(t_pion);
	pion.setScale({ 1, 0.65 });
	poziom.setScale({ 1, 0.65 });
	window.clear();

	if (czyja_tura == 1) {
		render_planszy(window, t_pola, pola, poziom, pion, gracz_1.mapa_logiczna);
		mouseOn(window, t_pola, pola, event, pozycja, gracz_1.mapa_statki, gracz_1.mapa_logiczna, jaki_statek);
	}
	else if (czyja_tura == 2) {
		render_planszy(window, t_pola, pola, poziom, pion, gracz_2.mapa_logiczna);
		mouseOn(window, t_pola, pola, event, pozycja, gracz_2.mapa_statki, gracz_2.mapa_logiczna, jaki_statek);
	}
	else {
		current_state = STATE_FIGHT;
	}
	window.display();
	//UTWORZENIE PIERWSZYCH TEKSTUR I PLANSZY


}