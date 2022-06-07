#include <SFML/Graphics.hpp>
#include <time.h>
#include <set>

int blockWidth = 64;

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(256, 256), "15-Puzzle");
	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.loadFromFile("data/images/15.png");
	sf::Sprite sprite[17];

	int grid[6][6] = { 0 };

	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sprite[++n].setTexture(texture);
			sprite[n].setTextureRect(sf::IntRect(i * blockWidth, j * blockWidth, blockWidth, blockWidth));
		}
	}

	std::set<int> numbers;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int var = rand() % 17;
			auto it = numbers.insert(var);
			while (!it.second || var == 0) {
				var = rand() % 17;
				it = numbers.insert(var);
				grid[i + 1][j + 1] = var;
			}
			grid[i + 1][j + 1] = var;
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					sf::Vector2i position = sf::Mouse::getPosition(window);
					int x = position.x / blockWidth + 1;
					int y = position.y / blockWidth + 1;
					int dx = 0;
					int dy = 0;

					if (grid[x + 1][y] == 16) { dx = 1; dy = 0; }
					if (grid[x - 1][y] == 16) { dx = -1; dy = 0; }
					if (grid[x][y + 1] == 16) { dx = 0; dy = 1; }
					if (grid[x][y - 1] == 16) { dx = 0; dy = -1; }

					int temp = grid[x][y];
					grid[x][y] = 16;
					grid[x + dx][y + dy] = temp;

					sprite[16].move(-dx * blockWidth, -dy * blockWidth);

					int speed = 6;
					for (int i = 0; i < blockWidth; i += speed) {
						sprite[temp].move(speed * dx, speed * dy);
						window.draw(sprite[16]);
						window.draw(sprite[temp]);
						window.display();
					}
				}
			}
		}

		window.clear(sf::Color::Black);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition(i * blockWidth, j * blockWidth);

				window.draw(sprite[n]);
			}
		}

		window.display();
	}

	return 0;
}