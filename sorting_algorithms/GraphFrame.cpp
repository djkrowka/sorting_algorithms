#include "GraphFrame.h"
#include <SFML/Graphics.hpp>

GraphFrame::GraphFrame(int w, int h) {
	calculateSizeAndPos(w, h);
	setSize(sf::Vector2f(width, height));
	setPosition(sf::Vector2f(x, y));
	setFillColor(sf::Color::Transparent);
	setOutlineThickness(2.f);
	setOutlineColor(sf::Color::White);
}

void GraphFrame::calculateSizeAndPos(int w, int h) {
	width = 0.9 * w;
	height = 0.8 * h;
	x = 0.05 * w;
	y = 0.1 * h;
}

int GraphFrame::getWidth() {
	return width;
}

int GraphFrame::getHeight() {
	return height;
}

int GraphFrame::getX() {
	return x;
}

int GraphFrame::getY() {
	return y;
}
