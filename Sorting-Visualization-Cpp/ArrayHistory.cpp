#include "ArrayHistory.hpp"
#include "Constants.hpp"
#include "Window.hpp"

#include <exception>
#include <SFML/Graphics.hpp>
#include <cassert>

ArrayHistory::ArrayHistory() : itIdx(0)
{
}

void ArrayHistory::feedData(const std::vector<unsigned>& data)
{
	itIdx = 0;
	arrayBuffer.clear();
	arrayBuffer.push_back(std::vector<Bar>());

	for (unsigned n : data) {
		arrayBuffer.back().push_back({ n, sf::Color::White });
	}
}

size_t ArrayHistory::getLength() const
{
	if (arrayBuffer.empty()) {
		return 0;
	}
	else {
		return arrayBuffer.front().size();
	}
}

void ArrayHistory::swap(size_t i, size_t j)
{
	size_t len = getLength();
	auto& arr = arrayBuffer.back();

	if (i >= len) {
		throw std::exception("left-side index out of range!");
	}
	if (j >= len) {
		throw std::exception("right-side index out of range!");
	}

	std::swap(arr[i], arr[j]);
}


unsigned ArrayHistory::operator[](size_t i) const
{
	if (i >= getLength()) {
		throw std::exception("index out of range!");
	}
	else {
		return arrayBuffer.back()[i].n;
	}
}

unsigned& ArrayHistory::operator[](size_t i)
{
	if (i >= getLength()) {
		throw std::exception("index out of range!");
	}
	else {
		return arrayBuffer.back()[i].n;
	}
}

Bar& ArrayHistory::getBar(size_t i)
{
	return arrayBuffer.back()[i];
}

void ArrayHistory::mark(size_t i, sf::Color c)
{
	auto& arr = arrayBuffer.back();
	arr[i].color = c;
}

void ArrayHistory::greenAll()
{
	int len = getLength();

	for (int i = 0; i < len; ++i) {
		mark(i, sf::Color::Green);
		update(false);
	}
}

void ArrayHistory::clear()
{
	while (arrayBuffer.size() > 1) {
		arrayBuffer.pop_back();
	}
}

sf::Color ArrayHistory::getColor(size_t i) const
{
	return arrayBuffer.back()[i].color;
}

bool ArrayHistory::hasNext() const
{
	if (itIdx >= arrayBuffer.size() - 1) {
		return false;
	}
	else {
		return true;
	}
}

void ArrayHistory::next()
{
	++itIdx;
}

const std::vector<Bar>& ArrayHistory::getCurrent() const
{
	assert(itIdx >= 0 && itIdx < arrayBuffer.size());
	return arrayBuffer[itIdx];
}

void ArrayHistory::reset()
{
	itIdx = 0;
}

void ArrayHistory::update(bool resetColors)
{
	std::vector<Bar> nextArr;
	nextArr.reserve(getLength());

	for (auto b : arrayBuffer.back()) {
		if (resetColors) {
			nextArr.push_back({ b.n, sf::Color::White });
		}
		else {
			nextArr.push_back(b);
		}
	}

	arrayBuffer.push_back(std::move(nextArr));
}

void ArrayHistory::draw(bool allWhite) const
{
	const auto& data = getCurrent();
	size_t len = getLength();

	const float BAR_WIDTH = (float) WIN_WIDTH / len;

	for (size_t i = 0; i < len; ++i) {
		float val = data[i].n;
		sf::Color color = data[i].color;

		sf::RectangleShape rect;

		if (allWhite) {
			rect.setFillColor(sf::Color::White);
		}
		else {
			rect.setFillColor(color);
		}


		if (BAR_WIDTH >= 4.0f) {
			rect.setSize({ BAR_WIDTH - 1.0f, (float)val });
			rect.setOutlineThickness(1.0f);
			rect.setOutlineColor(sf::Color::Black);
		}
		else {
			rect.setSize({ BAR_WIDTH, (float)val });
		}


		float xPos = i * BAR_WIDTH;
		float yPos = WIN_HEIGHT - val;

		rect.setPosition(xPos, yPos);
		gWindow->draw(rect);
	}
}