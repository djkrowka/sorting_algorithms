#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>

#include "GraphFrame.h"
#include "GraphBar.h"

void mainWindow(); //Creates main window with options
void insertionSort(); //Creates new window with insertion sort algorithm
void selectionSort(); //Creates new window with selection sort algorithm
void bubbleSort(); //Creates new window with bubble sort algorithm

const int MAIN_WINDOW_WIDTH = 400; //Width of main window
const int MAIN_WINDOW_HEIGHT = 110; // Height of main window

const int SORTING_WINDOW_WIDTH = 1600; //Width of window with sorting algorithm
const int SORTING_WINDOW_HEIGHT = 800; //Height of window with sorting algorithm

sf::Font font;

int myrandom(int i) { return std::rand() % i; }

int main()
{
    srand(unsigned(time(0)));

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "ERROR" << std::endl;
    }

    mainWindow();
    

    return 0;
}

void mainWindow() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT), "sorting_algorithms", sf::Style::Default, settings);
    sf::Text text[3];
    for (int i = 0; i < 3; i++) {
        text[i].setFont(font);
        text[i].setCharacterSize(24);
        text[i].setFillColor(sf::Color::White);
        text[i].setStyle(sf::Text::Bold);
    }

    text[0].setString("Insertion sort - PRESS I");
    text[0].setPosition(sf::Vector2f(10.f, 10.f));
    text[1].setString("Selection sort - PRESS S");
    text[1].setPosition(sf::Vector2f(10.f, 40.f));
    text[2].setString("Bubble sort - PRESS B");
    text[2].setPosition(sf::Vector2f(10.f, 70.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::I) insertionSort();
                if (event.key.code == sf::Keyboard::S) selectionSort();
                if (event.key.code == sf::Keyboard::B) bubbleSort();
            }
        }

        window.clear();
        for (int i = 0; i < 3; i++)  window.draw(text[i]);
        window.display();
    }
}

void insertionSort() {
    const int N = 100;
    int num[N];
    GraphFrame graphFrame(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT);
    std::vector<GraphBar> bar(N);

    int comparisons = 0;
    bool sorting = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT), "Insertion sort", sf::Style::Default, settings);

    sf::Text instructions;
    sf::Text comps;
    instructions.setFont(font);
    comps.setFont(font);
    instructions.setString("Press ENTER to start...");
    comps.setString("comparisons: " + std::to_string(comparisons));
    instructions.setCharacterSize(24);
    comps.setCharacterSize(24);
    instructions.setFillColor(sf::Color::White);
    comps.setFillColor(sf::Color::White);
    instructions.setStyle(sf::Text::Bold);
    comps.setStyle(sf::Text::Bold);
    instructions.setPosition(sf::Vector2f(graphFrame.getX(), 10.f));
    comps.setPosition(sf::Vector2f(graphFrame.getX(), graphFrame.getY()+graphFrame.getHeight()));

    for (int i = 0; i < N; i++) num[i] = i + 1;

    std::random_shuffle(&num[0], &num[N], myrandom);

    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    instructions.setString("");
                    sorting = true;
                }

                if (event.key.code == sf::Keyboard::S) {
                    comparisons = 0;
                    instructions.setString("Press ENTER to start...");
                    comps.setString("comparisons: " + std::to_string(comparisons));
                    std::random_shuffle(&num[0], &num[100], myrandom);
                    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                }
            }
        }

        if (sorting) {
            for (int i = 1, j; i < N; i++) {
                int tmp = num[i];
                for (j = i; j > 0 && tmp < num[j - 1]; j--) {
                    num[j] = num[j - 1];
                    bar[j].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[j - 1], j, graphFrame.getX(), graphFrame.getY());
                    bar[j-1].setFillColor(sf::Color::Red);
                    bar[j].setFillColor(sf::Color::White);
                    comparisons++;
                    comps.setString("comparisons: " + std::to_string(comparisons));

                    window.clear();
                    window.draw(graphFrame);
                    window.draw(instructions);
                    window.draw(comps);
                    for (int i = 0; i < bar.size(); i++) {
                        window.draw(bar[i]);
                    }
                    window.display();
                }
                num[j] = tmp;
                bar[j].setParams(graphFrame.getWidth(), graphFrame.getHeight(), tmp, j, graphFrame.getX(), graphFrame.getY());
                bar[i].setFillColor(sf::Color::Red);
                bar[i-1].setFillColor(sf::Color::White);
                comparisons++;
                comps.setString("comparisons: " + std::to_string(comparisons));

                window.clear();
                window.draw(graphFrame);
                window.draw(instructions);
                window.draw(comps);
                for (int i = 0; i < bar.size(); i++) {
                    window.draw(bar[i]);
                }
                window.display();

                if (i == N-1) {
                    bar[i].setFillColor(sf::Color::White);
                    sorting = false;
                    instructions.setString("Press S to shuffle numbers...");
                }
            }
        }
        else {
            window.clear();
            window.draw(graphFrame);
            window.draw(instructions);
            window.draw(comps);
            for (int i = 0; i < bar.size(); i++) {
                window.draw(bar[i]);
            }
            window.display();
        }
    }
}

void selectionSort() {
    const int N = 100;
    int num[N];
    GraphFrame graphFrame(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT);
    std::vector<GraphBar> bar(N);

    int comparisons = 0;
    bool sorting = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT), "Selection sort", sf::Style::Default, settings);

    sf::Text instructions;
    sf::Text comps;
    instructions.setFont(font);
    comps.setFont(font);
    instructions.setString("Press ENTER to start...");
    comps.setString("comparisons: " + std::to_string(comparisons));
    instructions.setCharacterSize(24);
    comps.setCharacterSize(24);
    instructions.setFillColor(sf::Color::White);
    comps.setFillColor(sf::Color::White);
    instructions.setStyle(sf::Text::Bold);
    comps.setStyle(sf::Text::Bold);
    instructions.setPosition(sf::Vector2f(graphFrame.getX(), 10.f));
    comps.setPosition(sf::Vector2f(graphFrame.getX(), graphFrame.getY() + graphFrame.getHeight()));

    for (int i = 0; i < N; i++) num[i] = i + 1;

    std::random_shuffle(&num[0], &num[N], myrandom);

    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    instructions.setString("");
                    sorting = true;
                }

                if (event.key.code == sf::Keyboard::S) {
                    comparisons = 0;
                    instructions.setString("Press ENTER to start...");
                    comps.setString("comparisons: " + std::to_string(comparisons));
                    std::random_shuffle(&num[0], &num[100], myrandom);
                    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                }
            }
        }

        if (sorting) {
            for (int i = 0, least, j; i < N - 1; i++) {
                for (j = i + 1, least = i; j < N; j++) {
                    if(j == i + 1) bar[N-1].setFillColor(sf::Color::White);
                    bar[j-1].setFillColor(sf::Color::White);
                    bar[j].setFillColor(sf::Color::Red);
                    if (num[j] < num[least])
                        least = j;
                    comparisons++;
                    comps.setString("comparisons: " + std::to_string(comparisons));

                    window.clear();
                    window.draw(graphFrame);
                    window.draw(instructions);
                    window.draw(comps);
                    for (int i = 0; i < bar.size(); i++) {
                        window.draw(bar[i]);
                    }
                    window.display();
                }
                std::swap(num[least], num[i]);
                bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                bar[least].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[least], least, graphFrame.getX(), graphFrame.getY());
                comps.setString("comparisons: " + std::to_string(comparisons));
                window.clear();
                window.draw(graphFrame);
                window.draw(instructions);
                window.draw(comps);
                for (int i = 0; i < bar.size(); i++) {
                    window.draw(bar[i]);
                }
                window.display();
                if (i == N - 2) {
                    sorting = false;
                    instructions.setString("Press S to shuffle numbers...");
                }
            }
        }
        else {
            window.clear();
            window.draw(graphFrame);
            window.draw(instructions);
            window.draw(comps);
            for (int i = 0; i < bar.size(); i++) {
                bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                window.draw(bar[i]);
            }
            window.display();
        }
    }
}

void bubbleSort() {
    const int N = 100;
    int num[N];
    GraphFrame graphFrame(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT);
    std::vector<GraphBar> bar(N);

    int comparisons = 0;
    bool sorting = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SORTING_WINDOW_WIDTH, SORTING_WINDOW_HEIGHT), "Bubble sort", sf::Style::Default, settings);

    sf::Text instructions;
    sf::Text comps;
    instructions.setFont(font);
    comps.setFont(font);
    instructions.setString("Press ENTER to start...");
    comps.setString("comparisons: " + std::to_string(comparisons));
    instructions.setCharacterSize(24);
    comps.setCharacterSize(24);
    instructions.setFillColor(sf::Color::White);
    comps.setFillColor(sf::Color::White);
    instructions.setStyle(sf::Text::Bold);
    comps.setStyle(sf::Text::Bold);
    instructions.setPosition(sf::Vector2f(graphFrame.getX(), 10.f));
    comps.setPosition(sf::Vector2f(graphFrame.getX(), graphFrame.getY() + graphFrame.getHeight()));

    for (int i = 0; i < N; i++) num[i] = i + 1;

    std::random_shuffle(&num[0], &num[N], myrandom);

    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    instructions.setString("");
                    sorting = true;
                }

                if (event.key.code == sf::Keyboard::S) {
                    comparisons = 0;
                    instructions.setString("Press ENTER to start...");
                    comps.setString("comparisons: " + std::to_string(comparisons));
                    std::random_shuffle(&num[0], &num[100], myrandom);
                    for (int i = 0; i < N; i++) bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                }
            }
        }

        if (sorting) {
            for (int i = 0; i < N - 1; i++) {
                for (int j = N - 1; j > i; --j) {
                    if (num[j] < num[j - 1]) {
                        std::swap(num[j], num[j - 1]);
                        bar[j].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[j], j, graphFrame.getX(), graphFrame.getY());
                        bar[j-1].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[j-1], j-1, graphFrame.getX(), graphFrame.getY());
                        comparisons++;
                        comps.setString("comparisons: " + std::to_string(comparisons));

                        window.clear();
                        window.draw(graphFrame);
                        window.draw(instructions);
                        window.draw(comps);
                        for (int i = 0; i < bar.size(); i++) {
                            window.draw(bar[i]);
                        }
                        window.display();
                    }
                }
                if (i == N - 2) {
                    sorting = false;
                    instructions.setString("Press S to shuffle numbers...");
                }
            }
        }
        else {
            window.clear();
            window.draw(graphFrame);
            window.draw(instructions);
            window.draw(comps);
            for (int i = 0; i < bar.size(); i++) {
                bar[i].setParams(graphFrame.getWidth(), graphFrame.getHeight(), num[i], i, graphFrame.getX(), graphFrame.getY());
                window.draw(bar[i]);
            }
            window.display();
        }
    }
}