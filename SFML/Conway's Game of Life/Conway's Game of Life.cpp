#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameOfLife.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Conway's Game of Life");

    window.setVerticalSyncEnabled(true);

    vector<vector<sf::RectangleShape>> board(100, vector<sf::RectangleShape>(80, sf::RectangleShape(sf::Vector2f(20, 20))));

    int x = 50, y = 40;

    GameOfLife game(x, y);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            board[i][j].setPosition(i * 20, j * 20);
            board[i][j].setFillColor(sf::Color::Black);
        }
    }

    bool started = false;
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

            /*if (!started && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
					int x = event.mouseButton.x / 20;
					int y = event.mouseButton.y / 20;

					game.setCell(x, y, true);
				}

                if (event.mouseButton.button == sf::Mouse::Right) {
                    int x = event.mouseButton.x / 20;
                    int y = event.mouseButton.y / 20;

                    game.setCell(x, y, false);
                }
            }*/

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (!started)
                        window.setFramerateLimit(2);
                    else
                        window.setFramerateLimit(60);
					started = !started;
				}
                else if (!started && event.key.code == sf::Keyboard::BackSpace) {
                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
							game.setCell(i, j, false);
						}
					}
                }
			}
		}

        if (!started && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = sf::Mouse::getPosition(window).x / 20;
			int y = sf::Mouse::getPosition(window).y / 20;

			game.setCell(x, y, true);
		}

        if (!started &&  sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			int x = sf::Mouse::getPosition(window).x / 20;
			int y = sf::Mouse::getPosition(window).y / 20;

			game.setCell(x, y, false);
		}

        window.clear(sf::Color::Black);

        vector<vector<bool>> grid = game.getGrid();

        if (started) {
            game.evolve();
        }

         for (int i = 0; i < x; i++)
         {
             for (int j = 0; j < y; j++)
             {
                 if (grid[i][j])
                     board[i][j].setFillColor(sf::Color::White);
                 else
                     board[i][j].setFillColor(sf::Color::Black);

                 window.draw(board[i][j]);
             }
         }

		window.display();
    }
}
