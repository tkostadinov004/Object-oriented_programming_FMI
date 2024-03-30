#pragma once

using TransformerFunction =  int(*)(int num);
class NumberSeries
{
	int initialValue = 0;
	int* nums = nullptr;
	size_t numsCount = 0;
	size_t capacity = 1;
	TransformerFunction transformer = nullptr;
	void copyFrom(const NumberSeries& other);
	void free();
	void grow();
public:
	NumberSeries();
	NumberSeries(int initialValue, TransformerFunction transformer);
	NumberSeries(const NumberSeries& other);
	~NumberSeries();
	NumberSeries& operator=(const NumberSeries& other);

	int getNumber(int i);
	bool isInSequence(int num) const;
	
	void setInitialValue(int initialValue);
	void setTransformerFunction(TransformerFunction transformer);
};