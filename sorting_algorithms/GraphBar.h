#pragma once

#include <SFML/Graphics.hpp>

class GraphBar : public sf::RectangleShape
{
public:
	GraphBar();
	void calculateSizeAndPos(double, double, int, int, int, int); // calculates size and position of single graph bar based on bar number and parameters of graph frame 
	void setParams(double, double, int, int, int, int); // sets parameters of single bar based on bar number and its value
private:
	float x, y, width, height;
};

