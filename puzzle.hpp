#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <bits/types/time_t.h>
#include <memory>
#include <iostream>
#include <ctime>

class Puzzle {
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<sf::Text> text;
  std::shared_ptr<sf::Event> event;
  std::shared_ptr<sf::Font> font;

  sf::Texture texture;

  time_t initialTime;
  int w, n, x, y, dx, dy;

  std::array<std::array<int, 6>, 6> grid;
  std::array<sf::Sprite, 17> sprite;

  protected:
	void events();
	void draw();
    void logic();

  public:
	Puzzle(const std::vector<int>&);
	void run();
};
