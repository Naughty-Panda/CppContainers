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
	void Sort(size_t begin, size_t end);
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
	I think we should not reallocate whole array
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

void SwapInt(int& a, int& b) { int t = a; a = b; b = t; }

size_t Partition(int* arr, size_t begin, size_t end) {

	size_t pivot = arr[end];
	size_t i = begin - 1;

	for (size_t j = begin; j <= end - 1; j++) {

		if (arr[j] <= static_cast<int>(pivot)) {

			i++;
			SwapInt(arr[i], arr[j]);
		}
	}

	SwapInt(arr[i + 1], arr[end]);
	return i + 1;
}

void AArray::Sort(size_t begin, size_t end) {

	assert(_data && end < _lenght);

	if (begin < end) {

		size_t part_index = Partition(_data, begin, end);

		Sort(begin, part_index - 1);
		Sort(part_index + 1, end);
	}
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

auto unique(std::vector<int>::iterator first, std::vector<int>::iterator last) {

	if (first == last) return last;

	auto result = first;

	while (++first != last) {

		if (!(*result == *first) && ++result != first) {

			*result = std::move(*first);
		}
	}

	return ++result;
}

//////////////////////////////////////////
//	4.3
//////////////////////////////////////////

enum class ECardSuit : uint8_t {

	Clubs = 1U, Diamonds, Hearts, Spades,
	Undefined = 0U
};

enum class ECardValue : uint8_t {

	Two = 2U, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
	Jack = 10U, Queen = 10U, King = 10U, Ace = 1U,
	Undefined = 0U
};

class Card {

protected:
	ECardSuit _suit{ ECardSuit::Undefined };
	ECardValue _value{ ECardValue::Undefined };
	bool _bVisible{ false };

public:
	Card(ECardSuit suit, ECardValue val) : _suit(suit), _value(val) {}

	ECardValue GetValue() const { return _value; }
	void Flip() { _bVisible = !_bVisible; }
};

class Hand {

protected:
	std::vector<Card*> _hand;

public:
	void Add(Card* card);
	void Clear();
	uint8_t GetValue() const;
};

void Hand::Add(Card* card) {

	assert(card);

	_hand.push_back(card);
}

void Hand::Clear() {

	_hand.erase(_hand.begin(), _hand.end());
}

uint8_t Hand::GetValue() const {

	uint8_t result{ 0U };
	uint8_t AceCount{ 0U };

	for (auto i : _hand) {

		if (i->GetValue() == ECardValue::Ace)
			AceCount++;
		else
			result += static_cast<int>(i->GetValue());
	}

	if (AceCount > 0U) {

		// Here we choose value of Ace based on
		// current hand value and number of aces
		while (AceCount != 0U && result <= 21U - 11U - (AceCount - 1U)) {
			
			result += 11U;
			AceCount--;
		}

		while (AceCount != 0U) {

			result += 1U;
			AceCount--;
		}
	}

	return result;
}


int main() {

	//////////////////////////////////////////
	//	4.1
	//////////////////////////////////////////

	AArray arr{ 10 };

	for (int i = 0; i < 10; i++) {
		arr[i] = i + rand() % 100;
	}
	std::cout << "Random array: ";
	arr.Print();

	arr.Sort(0, 9);

	std::cout << "Sorted array: ";
	arr.Print();

	//////////////////////////////////////////
	//	4.2
	//////////////////////////////////////////

	std::vector<int> vec{ 1,5,4,3,4,6,1,0,5 };
	std::vector<int>::iterator begin = vec.begin();
	std::vector<int>::iterator end = vec.end();

	std::cout << "\nGiven vector: ";
	for (auto i : vec) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	auto last = unique(begin, end);
	vec.erase(last, end);
	std::sort(begin, end);

	std::cout << "Sorted vector: ";
	for (auto i : vec) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	last = unique(begin, end);
	vec.erase(last, end);

	std::cout << "Unique vector: ";
	for (auto i : vec) {
		std::cout << i << " ";
	}
	std::cout << "\n# unique elements: " << vec.size() << '\n';

	//////////////////////////////////////////
	//	4.3
	//////////////////////////////////////////

	Hand hand;
	Card crd1{ ECardSuit::Clubs, ECardValue::Ace };
	Card crd2{ ECardSuit::Diamonds, ECardValue::Five };
	Card crd3{ ECardSuit::Hearts, ECardValue::Eight };

	hand.Add(&crd1);
	hand.Add(&crd2);
	hand.Add(&crd1);
	hand.Add(&crd3);

	std::cout <<"\nHand value: " << static_cast<int>(hand.GetValue());
	
	hand.Clear();

	return 0;
}
