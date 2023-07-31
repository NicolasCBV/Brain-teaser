#include "puzzle.hpp"

Puzzle::Puzzle(const std::vector<int>& nums) {
  initialTime = time(NULL);

  font = std::make_shared<sf::Font>();
  text = std::make_shared<sf::Text>();
  window = std::make_shared<sf::RenderWindow> (
    sf::VideoMode(512, 568),
    "Puzzle:Remix",
    sf::Style::Titlebar | sf::Style::Close
  );
  window->setPosition(sf::Vector2i(50, 50));
  window->setFramerateLimit(60);
  event = std::make_shared<sf::Event>();

  font->loadFromFile("./ethn.otf");
  texture.loadFromFile("./assets/puzzle.png");

  w = {128}; n = x = y = dx = dy = {0};
  grid.fill({0});
  for(size_t i {}; i < 4; ++i)
    for(size_t j {}; j < 4; ++j) {
      ++n;
      sprite[n].setTexture(texture);
      sprite[n].setTextureRect(sf::IntRect(i * w, j * w, w, w));
      grid[i + 1][j + 1] = nums[n - 1];
    }
}

void Puzzle::events() {
  while(window->pollEvent(*event)) 
    if(event->type == sf::Event::Closed)
      window->close();
  
  if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    this->logic();
}

void Puzzle::draw() {
  window->clear(sf::Color::Black);
  time_t currentTime = time(NULL);

  const time_t parsedTime = std::difftime(currentTime, initialTime);
  const std::string minutes = parsedTime / 60 >= 10
    ? std::to_string(parsedTime/60)
    : "0" + std::to_string(parsedTime/60);
  const std::string seconds = parsedTime % 60 >= 10
    ? std::to_string(parsedTime % 60)
    : "0" + std::to_string(parsedTime % 60);

  text->setFont(*font);
  text->setString("Time: " + minutes + ":" + seconds);
  text->setPosition(140, 520);
  text->setCharacterSize(28);
  text->setOutlineColor(sf::Color::Black);
  window->draw(*text);

  for(size_t i {}; i < 4; ++i)
    for(size_t j {}; j < 4; ++j) {
      n = grid[i + 1][j + 1];
      sprite[n].setPosition(i * w, j * w);
      window->draw(sprite[n]);
    }
  window->display();
}

void Puzzle::run() {
  while(window->isOpen()) {
    this->events();
    this->draw();
  }
}

void Puzzle::logic() {
  sf::Vector2i pos = sf::Mouse::getPosition(*window);
  this->x = pos.x / w + 1;
  this->y = pos.y / w + 1;

  if(grid[x + 1][y] == 16)
    dx = 1;

  if(grid[x - 1][y] == 16)
    dx = -1;

  if(grid[x][y + 1] == 16)
    dy = 1;

  if(grid[x][y - 1] == 16)
    dy = -1;

  n = grid[x][y];

  grid[x][y] = 16;
  grid[x + dx][y + dy] = n;

  dx = 0; dy = 0;
}
