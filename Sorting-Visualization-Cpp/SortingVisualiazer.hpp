#ifndef SORTING_VISUALIZER_HPP
#define SORTING_VISUALIZER_HPP

#include "ArrayHistory.hpp"

class Sorter;

class SortingVisualizer {
public:
	static SortingVisualizer& getInstance();
	~SortingVisualizer();

	void run();

private:
	SortingVisualizer();
	void update();
	void draw();

private:
	int dataSz;
	ArrayHistory arrayHistory;
	std::vector<Sorter*> sorters;
	int selectedSorter;
	bool sorting;

	sf::Font font;
};

#endif // !SORTING_VISUALIZER_HPP
