#include "SortingVisualiazer.hpp"

#include "Constants.hpp"
#include "Window.hpp"
#include "Util.hpp"
#include "Sorter.hpp"

#include <SFML/Graphics.hpp>


SortingVisualizer& SortingVisualizer::getInstance()
{
	static SortingVisualizer instance;
	return instance;
}

SortingVisualizer::~SortingVisualizer()
{
	for (Sorter* sorter : sorters) {
		delete sorter;
	}

	delete gWindow;
	gWindow = nullptr;
}

void SortingVisualizer::run()
{
	while (gWindow->isOpen()) {
		update();
		draw();
	}
}

SortingVisualizer::SortingVisualizer()
	: font(), selectedSorter(0), sorting(false), dataSz(40)
{
	gWindow = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SFML", sf::Style::Close);
	gWindow->setVerticalSyncEnabled(true);

	font.loadFromFile("RobotoMono-Regular.ttf");

	arrayHistory.feedData(getRandomArray(dataSz));
	sorters.push_back(new BubbleSorter);
	sorters.push_back(new SelectionSorter);
	sorters.push_back(new InsertionSorter);
	sorters.push_back(new MergeSorter);
	sorters.push_back(new QuickSorter);
	sorters.push_back(new HeapSorter);
	//sorters.push_back(new ShellSorter);
}

void SortingVisualizer::update()
{
	sf::Event eventQ;
	while (gWindow->pollEvent(eventQ)) {
		if (eventQ.type == sf::Event::Closed) {
			gWindow->close();
		}
		else if (eventQ.type == sf::Event::KeyPressed) {
			auto keyCode = eventQ.key.code;
			
			if (keyCode == sf::Keyboard::S) {
				if (!sorting) {
					arrayHistory.clear();
					Sorter* sorter = sorters[selectedSorter];
					sorter->sort(arrayHistory);
					sorting = true;
				}
			}
			else if (keyCode == sf::Keyboard::N) {
				if (!sorting) {
					arrayHistory.feedData(getRandomArray(dataSz));
				}
			}
			else if (keyCode == sf::Keyboard::X) {
				if (sorting) {
					arrayHistory.reset();
					sorting = false;
				}
			}
			else if (keyCode == sf::Keyboard::Right) {
				if (!sorting) {
					++selectedSorter;
					if (selectedSorter >= sorters.size()) {
						selectedSorter = 0;
					}
				}
			}
			else if (keyCode == sf::Keyboard::Left) {
				if (!sorting) {
					--selectedSorter;
					if (selectedSorter < 0) {
						selectedSorter = sorters.size() - 1;
					}
				}
			}
			else if (keyCode == sf::Keyboard::Up) {
				if (!sorting && dataSz < MAX_DATA_SZ) {
					dataSz += 20;
					arrayHistory.feedData(getRandomArray(dataSz));
				}
			}
			else if (keyCode == sf::Keyboard::Down) {
				if (!sorting && dataSz > MIN_DATA_SZ) {
					dataSz -= 20;
					arrayHistory.feedData(getRandomArray(dataSz));
				}
			}
		}
	}
}

void SortingVisualizer::draw() 
{
	gWindow->clear();

	Sorter* sorter = sorters[selectedSorter];
	std::string string = "Sort Algorithm: ";
	string += sorter->getName();
	string += "\t";
	string += "Array Size: ";
	string += std::to_string(arrayHistory.getLength());
		
	sf::Text text (string, font, 24);
	gWindow->draw(text);

	if (sorting) {
		arrayHistory.draw();
	}
	else {
		arrayHistory.draw(true);
	}

	if (sorting && arrayHistory.hasNext()) {
		arrayHistory.next();
	}
	else if (!arrayHistory.hasNext()) {
		sorting = false;
	}

	gWindow->display();
}
