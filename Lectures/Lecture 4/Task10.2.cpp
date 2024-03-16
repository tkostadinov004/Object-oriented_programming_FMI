#include <iostream>
#include <fstream>

class NumbersSummator
{
	int initialSum;
	int totalSum;
	size_t changeCount;
public:
	NumbersSummator(int num = 0)
	{
		initialSum = num;
		totalSum = num;
		changeCount = 0;
	}
	int sum() const
	{
		return totalSum;
	}
	void add(int num)
	{
		totalSum += num;
		changeCount++;
	}
	void sub(int num)
	{
		totalSum -= num;
		changeCount++;
	}
	size_t num() const
	{
		return changeCount;
	}
	float average() const
	{
		return (totalSum - initialSum) / changeCount;
	}
};
int main()
{
	NumbersSummator seq1(10);
	seq1.add(10);
	seq1.add(5);
	seq1.sub(15);
	std::cout << seq1.sum() << std::endl;
	std::cout << seq1.average() << std::endl;
}