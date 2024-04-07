#pragma once

template <typename T>
class LList
{
public:
	struct Box
	{
		Box() = default;
		Box(const T& value, Box* next);
		T data;
		Box* next = nullptr;
	};
private:
	Box* head = nullptr;
	void copyFrom(const LList<T>& other);
	void free();
	Box* locate(size_t index);
	T& get_ith(size_t index);
	void append(const LList<T>& list);
	LList<T> concat(const LList<T>& list) const;
public:
	LList() = default;
	LList(int x, int y);
	LList(const LList<T>& other);
	LList<T>& operator=(const LList<T>& other);
	~LList();
	void push(const T& value);
	void pop();
	void push_back(const T& value);
	void removeAll(const T& value);
	LList<T>& operator+=(const T& value);
	LList<T>& operator+=(const LList<T>& list);
	LList<T> operator+(const LList<T>& list) const;
	const T& operator[](int index) const;
	T& operator[](int index);
	void reverse();
	LList<T> mapF(T(*func)(const T&)) const;
	LList<T>& mapD(T(*func)(const T&));
	T reduce(T(*func)(const T& accumulator, const T& currentValue), const T& initialValue) const;
	void insertAt(size_t index, const T& value);
	void deleteAt(size_t index);
	void print() const;
	size_t count(int x) const;
};