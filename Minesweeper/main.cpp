#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int WH = 12;
int cellWidth = 32;

int main() {
	srand(time(0));
	RenderWindow app(VideoMode(WH * cellWidth, WH * cellWidth), "Minesweeper");
	app.RenderWindow::setFramerateLimit(60);

	
	int gridLogic[WH][WH];
	int gridView[WH][WH];
	int buttons[2][5];
	buttons[0][0] = 12;
	bool beginGame = true;

	Texture tiles;
	tiles.loadFromFile("data/images/minesweeper.png");
	Sprite sprite(tiles);
	Sprite sprite1(tiles);
	sprite1.setPosition(0, 0);
	sprite1.setTextureRect(IntRect(cellWidth * 12, 0, cellWidth, cellWidth));

	for (int i = 1; i <= WH - 2; i++) {
		for (int j = 1; j <= WH - 2; j++) {
			gridView[i][j] = 10;
		}
	}

	while (app.isOpen()) {
		Vector2i position = Mouse::getPosition(app);
		int x = position.x / cellWidth;
		int y = position.y / cellWidth;

		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					if (beginGame) {
						for (int i = 1; i <= WH - 2; i++) {
							for (int j = 1; j <= WH - 2; j++) {
								gridView[i][j] = 10;
								if (rand() % 5 == 0) gridLogic[i][j] = 9;
								else gridLogic[i][j] = 0;
							}
						}
						gridLogic[x][y] = 0;
						for (int i = 1; i <= WH - 2; i++) {
							for (int j = 1; j <= WH - 2; j++) {
								if (gridLogic[i][j] == 9) continue;
								int n = 0;
								if (gridLogic[i + 1][j] == 9) n++;
								if (gridLogic[i - 1][j] == 9) n++;
								if (gridLogic[i + 1][j + 1] == 9) n++;
								if (gridLogic[i + 1][j - 1] == 9) n++;
								if (gridLogic[i - 1][j + 1] == 9) n++;
								if (gridLogic[i - 1][j - 1] == 9) n++;
								if (gridLogic[i][j + 1] == 9) n++;
								if (gridLogic[i][j - 1] == 9) n++;

								gridLogic[i][j] = n;
							}
						}
						beginGame = false;
					}
					if (gridLogic[x][y] == 9) {
						for (int i = 1; i <= WH - 2; i++) {
							for (int j = 1; j <= WH - 2; j++) {
								gridView[i][j] = gridLogic[i][j];
							}
						}
					}
					if (buttons[x][y] == 12) {
						for (int i = 1; i <= WH - 2; i++) {
							for (int j = 1; j <= WH - 2; j++) {
								gridView[i][j] = 10;
							}
						}
						beginGame = true;
					}
					else { gridView[x][y] = gridLogic[x][y]; }
				}
				if (e.key.code == Mouse::Right) {
					if (gridView[x][y] != gridLogic[x][y] && !beginGame) gridView[x][y] = 11;
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (buttons[x][y] == 12) {
					sprite1.setTextureRect(IntRect(cellWidth * 13, 0, cellWidth, cellWidth));
				}
			}
			else sprite1.setTextureRect(IntRect(cellWidth * 12, 0, cellWidth, cellWidth));
		}

		app.clear(Color::White);

		app.draw(sprite1);

		for (int i = 1; i <= WH - 2; i++) {
			for (int j = 1; j <= WH - 2; j++) {
				sprite.setTextureRect(IntRect(cellWidth * gridView[i][j], 0, cellWidth, cellWidth));
				sprite.setPosition(cellWidth * i, cellWidth * j);
				app.draw(sprite);
			}
		}
		app.display();
	}
	return 0;
}