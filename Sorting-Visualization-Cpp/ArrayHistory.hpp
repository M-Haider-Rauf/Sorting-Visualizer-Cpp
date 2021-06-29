#ifndef ARRAY_HISTORY_HPP
#define ARRAY_HISTORY_HPP

#include <vector>
#include <SFML/Graphics.hpp>

struct Bar {
	unsigned n;
	sf::Color color;
};

class ArrayHistory {
public:
	ArrayHistory();

	void feedData(const std::vector<unsigned>& data);
	size_t getLength() const;

	void swap(size_t i, size_t j);
	unsigned operator[](size_t i) const;
	unsigned& operator[] (size_t i);
	Bar& getBar(size_t i);

	void mark(size_t i, sf::Color c);
	void greenAll();
	void clear();
	sf::Color getColor(size_t i) const;


	bool hasNext() const;
	void next();
	void reset();
	void update(bool resetColors = true);

	void draw(bool allWhite = false) const;

private:
	const std::vector<Bar>& getCurrent() const;

private:
	std::vector<std::vector<Bar>> arrayBuffer;
	size_t itIdx;
};

#endif // !ARRAY_HISTORY_HPP
