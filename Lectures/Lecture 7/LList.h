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
public:
	LList() = default;
	LList(const LList<T>& other);
	LList<T>& operator=(const LList<T>& other);
	~LList();
	void push(const T& value);
	void pop();
	void insertAt(size_t index, const T& value);
	void deleteAt(size_t index);
	void print() const;
	size_t count(int x) const;
};