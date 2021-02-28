#include "GraphBar.h"

GraphBar::GraphBar() {
	
}

void GraphBar::calculateSizeAndPos(double w, double h, int numVal, int i, int frameX, int frameY) {
	width = w / 100;
	height = h / 100 * numVal;
	x = (i * width) + frameX;
	y = frameY + (h - height);
}

void GraphBar::setParams(double w, double h, int numVal, int i, int frameX, int frameY) {
	calculateSizeAndPos(w, h, numVal, i, frameX, frameY);
	setSize(sf::Vector2f(width, height));
	setPosition(sf::Vector2f(x, y));
	setFillColor(sf::Color::White);
	setOutlineThickness(0.05 * width);
	setOutlineColor(sf::Color::Black);
}