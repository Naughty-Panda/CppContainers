//////////////////////////////////////////
//	C++ Containers
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

//////////////////////////////////////////
//	4.1
//////////////////////////////////////////

class AArray {

private:
	size_t _lenght{ 0 };
	int* _data{ nullptr };

public:
	AArray() : _lenght(0), _data(nullptr) {}
	AArray(const size_t& len);
	~AArray() { if (_data) delete[] _data; }

	int& operator[](const size_t& i) const;

	bool Empty() const { return !_lenght; }
	void Resize(const size_t& newLength);
	void InsertBefore(const int& val, const size_t& pos);
	void PushBack(const int& val) { InsertBefore(val, _lenght); }
	void PopFront();
	void PopBack();
	void Sort();
	void Print() const;
	void Erase();
	int GetLength() const { return _lenght; }
};

AArray::AArray(const size_t& len) : _lenght(len), _data(nullptr) {
	
	assert(_lenght >= 0);
	if (_lenght > 0) _data = new (std::nothrow) int[_lenght];
}

int& AArray::operator[](const size_t& i) const {

	assert(_data && i >= 0 && i < _lenght);
	return _data[i];
}

void AArray::Resize(const size_t& newLenght) {

	if (newLenght == _lenght) return;
	if (!newLenght) {

		Erase();
		return;
	}

	int* data = new (std::nothrow) int[newLenght];
	if (!data) return;

	if (!Empty()) {

		size_t n = newLenght > _lenght ? _lenght : newLenght;
		for (size_t i = 0; i < n; i++) {
			data[i] = _data[i];
		}
	}

	delete[] _data;
	_data = data;
	_lenght = newLenght;	
}

void AArray::InsertBefore(const int& val, const size_t& pos) {

	assert(pos >= 0 && pos <= _lenght);

	int* data = new (std::nothrow) int[_lenght + 1];
	if (!data) return;

	for (size_t i = 0; i < pos; i++) {
		data[i] = _data[i];
	}

	data[pos] = val;

	for (size_t i = pos; i < _lenght; i++) {
		data[i + 1] = _data[i];
	}

	delete[] _data;
	_data = data;
	_lenght++;
}

/*
	I think we should not reallocate the whole array
	each time we pop one of its elements out.
	It'll be much faster to adjust the length only
	and move elements around if necessary.
*/

void AArray::PopFront() {

	if (!_data) return;

	for (size_t i = 1; i < _lenght; i++) {
		_data[i - 1] = _data[i];
	}

	_lenght--;
}

void AArray::PopBack() {

	if (!_data) return;

	_lenght--;
}

void AArray::Sort() {

	if (!_data) return;

	//std::sort<int>(_data[0], _data[_lenght - 1]);
}

void AArray::Print() const {

	if (!_data) return;

	std::cout << "[ ";
	for (size_t i = 0; i < _lenght; i++) {
		std::cout << _data[i] << " ";
	}
	std::cout << "]\n";
}

void AArray::Erase() {

	if (!_data) return;

	delete[] _data;
	_data = nullptr;
	_lenght = 0;
}

//////////////////////////////////////////
//	4.2
//////////////////////////////////////////

//////////////////////////////////////////
//	4.3
//////////////////////////////////////////

class Card {};

class Hand {

protected:
	std::vector<Card*> _hand{};

public:
	void Add() {};
	void Clear() {};
	uint8_t GetValue() const {};

};

int main() {

	return 0;
}
