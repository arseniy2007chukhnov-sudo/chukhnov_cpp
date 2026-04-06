#pragma once
#include <iostream>

const int DEFAULT_CAPACITY = 10;
class ArrayException {};
class Array {
	int* ptr;
	int size, capacity;
	void increaseCapacity(int newCapacity);
public:
	explicit Array(int startCapacity = DEFAULT_CAPACITY);
	~Array();
	Array(const Array& arr);
	Array& operator = (const Array& arr);
	int& operator [](int index);
	void insert(int index, int elem);
	void insert(int elem);
	void remove(int index);
	int getSize() const;
	int* getPtr() const;
	friend std::ostream& operator <<(std::ostream& out, const Array& arr);
};
