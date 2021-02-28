#pragma once

#include <SFML/Graphics.hpp>

class GraphFrame: public sf::RectangleShape
{
public:
	GraphFrame(int, int);
	void calculateSizeAndPos(int, int); // calculates size and position of graph frame based on window parameters
	int getWidth();
	int getHeight();
	int getX();
	int getY();
private:
	float x, y, width, height;
};

