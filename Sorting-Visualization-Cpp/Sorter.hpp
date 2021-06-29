#ifndef SORTER_HPP
#define SORTER_HPP

#include "ArrayHistory.hpp"
#include <iostream>
#include <random>


//The Sorter ABC
class Sorter {
public:
	Sorter(const std::string& name) : name(name)
	{
	}

	const std::string& getName() const
	{
		return name;
	}

	virtual void sort(ArrayHistory& arr) = 0;

private:
	const std::string name;
};


//Bubble Sort
class BubbleSorter : public Sorter {
public:
	BubbleSorter() : Sorter("Bubble Sort")
	{
	}

	void sort(ArrayHistory& arr) override
	{
		int len = arr.getLength();

		for (int i = 0; i < len; ++i) {

			bool swapHappened = false;

			for (int j = 0; j < len - 1; ++j) {
				arr.mark(j, sf::Color::Red);
				arr.mark(j + 1, sf::Color::Red);

				arr.update();

				if (arr[j] > arr[j + 1]) {
					arr.swap(j, j + 1);
					swapHappened = true;
				}
			}

			if (!swapHappened) {
				break;
			}
		}

		arr.greenAll();
	}
};


//Insertion Sort
class SelectionSorter : public Sorter {
public:
	SelectionSorter() : Sorter("Selection Sort")
	{
	}

	void sort(ArrayHistory& arr) override
	{
		int len = arr.getLength();

		for (int i = 0; i < len; ++i) {

			int minIdx = i;

			for (int j = i + 1; j < len; ++j) {

				int prevMinIdx = minIdx;
				arr.mark(j, sf::Color::Red);
				arr.mark(minIdx, sf::Color::Yellow);
				arr.update();

				if (arr[j] < arr[minIdx]) {
					minIdx = j;
				}
			}

			arr.update();
			arr.swap(i, minIdx);
		}

		arr.greenAll();
	}
};


//InsertionSort
class InsertionSorter : public Sorter {
public:
	InsertionSorter() : Sorter("Insertion Sort")
	{
	}

	void sort(ArrayHistory& arr)
	{
		int len = arr.getLength();

		for (int i = 1; i < len; ++i) {
			int j = i;

			while (j > 0 && arr[j - 1] > arr[j]) {
				arr.mark(j, sf::Color::Red);
				arr.mark(j - 1, sf::Color::Red);
				arr.update();

				arr.swap(j, j - 1);

				--j;
			}
		}

		arr.greenAll();
	}
};


//Merge-Sort
class MergeSorter : public Sorter {
public:
	MergeSorter() : Sorter("Merge Sort"), tempArr(nullptr)
	{
	}

	void sort(ArrayHistory& arr) override
	{
		arr.update();
		int len = arr.getLength();

		delete[] tempArr;
		tempArr = new int[len];

		mergeSort(arr, 0, len - 1);

		arr.greenAll();
	}

private:
	void mergeSort(ArrayHistory& arr, int l, int h)
	{
		if (l < h) {
			int m = (l + h) / 2;
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, h);

			merge(arr, l, m, h);
		}
	}

	void merge(ArrayHistory& arr, int l, int m, int h)
	{
		int idxA = l;
		int idxL = l;
		int idxR = m + 1;

		while (idxL <= m && idxR <= h) {
			arr.mark(l, sf::Color::Yellow);
			arr.mark(m, sf::Color::Cyan);
			arr.mark(h, sf::Color::Yellow);
			arr.mark(idxA, sf::Color::Red);

			arr.update();

			if (arr[idxL] <= arr[idxR]) {
				tempArr[idxA] = arr[idxL];
				++idxL;
			}
			else { 
				tempArr[idxA] = arr[idxR];
				++idxR;
			}

			++idxA;
		}

		while (idxL <= m) {
			arr.mark(l, sf::Color::Yellow);
			arr.mark(m, sf::Color::Cyan);
			arr.mark(h, sf::Color::Yellow);
			arr.mark(idxA, sf::Color::Red);

			arr.update();

			tempArr[idxA] = arr[idxL];
			++idxL;
			++idxA;
		}

		while (idxR <= h) {
			arr.mark(l, sf::Color::Yellow);
			arr.mark(m, sf::Color::Cyan);
			arr.mark(h, sf::Color::Yellow);
			arr.mark(idxA, sf::Color::Red);

			arr.update();

			tempArr[idxA] = arr[idxR];
			++idxR;
			++idxA;
		}

		for (int i = l; i <= h; ++i) {
			arr.mark(l, sf::Color::Yellow);
			arr.mark(h, sf::Color::Yellow);
			arr.mark(i, sf::Color::Red);

			arr.update();

			arr[i] = tempArr[i];
		}
	}

private:
	int* tempArr;
};


//QuickSort
class QuickSorter : public Sorter {
public:
	QuickSorter() : Sorter("Quick Sort")
	{
	}

	void sort(ArrayHistory& arr) override
	{
		int len = arr.getLength();
		quickSort(arr, 0, len - 1);

		arr.greenAll();
	}

private:
	void quickSort(ArrayHistory& arr, int l, int h)
	{
		if (l < h) {
			int p = partition(arr, l, h);
			quickSort(arr, l, p - 1);
			quickSort(arr, p + 1, h);
		}
	}

	int partition(ArrayHistory& arr, int l, int h)
	{
		int pivotVal = arr[h];
		int pivotIdx = l;

		for (int i = l; i <= h - 1; ++i) {
			arr.mark(l, sf::Color::Yellow);
			arr.mark(h, sf::Color::Yellow);
			arr.mark(pivotIdx, sf::Color::Blue);
			arr.mark(i, sf::Color::Red);
			
			arr.update();

			if (arr[i] < pivotVal) {
				arr.swap(i, pivotIdx);
				++pivotIdx;
			}
		}

		arr.mark(pivotIdx, sf::Color::Blue);
		arr.mark(h, sf::Color::Red);
		arr.update();
		arr.swap(pivotIdx, h);
		return pivotIdx;
	}
};


//HeapSort
class HeapSorter : public Sorter {
public:
	HeapSorter() : Sorter("Heap Sorter")
	{
	}

	void sort(ArrayHistory& arr) override
	{
		int len = arr.getLength();

		for (int i = len / 2 - 1; i >= 0; --i) {
			heapify(arr, i, len);
		}


		int heapSz = len;
		while (heapSz > 0) {
			--heapSz;
			arr.mark(0, sf::Color::Red);
			arr.mark(heapSz, sf::Color::Red);
			arr.update();

			arr.swap(heapSz, 0);
			heapify(arr, 0, heapSz);
		}

		arr.greenAll();
	}

private:
	void heapify(ArrayHistory& arr, int i, int heapSz)
	{
		int largest = i;
		int leftChild = i * 2 + 1;
		int rightChild = i * 2 + 2;

		if (leftChild < heapSz) {

			arr.mark(leftChild, sf::Color::Red);
			arr.mark(largest, sf::Color::Red);
			if (arr[leftChild] > arr[largest]) {
				arr.update();

				largest = leftChild;
			}
		}

		if (rightChild < heapSz) {

			arr.mark(rightChild, sf::Color::Red);
			arr.mark(largest, sf::Color::Red);
			if (arr[rightChild] > arr[largest]) {
				arr.update();


				largest = rightChild;
			}
		}

		if (largest != i) {
			arr.mark(largest, sf::Color::Red);
			arr.mark(i, sf::Color::Red);
			arr.update();

			arr.swap(i, largest);
			heapify(arr, largest, heapSz);
		}
	}
};





/* //Shell Sort
class ShellSorter : public Sorter {
public:
	ShellSorter() : Sorter("Shell Sort")
	{
	}

	void sort(ArrayHistory& arr) override
	{
		int len = arr.getLength();
		int gap = len / 2;

		while (gap > 0) {
			for (int i = gap; i < len; ++i) {
				int j = i;

				while (j >= gap && arr[j - gap] > arr[j]) {
					arr.mark(j, sf::Color::Red);
					arr.mark(j - gap, sf::Color::Red);
					arr.update();
					arr.swap(j, j - gap);
					j -= gap;
				}
			}
			gap /= 2;
		}

		arr.greenAll();
	}

};

*/
#endif