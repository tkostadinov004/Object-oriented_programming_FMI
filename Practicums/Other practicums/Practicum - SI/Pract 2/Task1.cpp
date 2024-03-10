#include <iostream>
#include <fstream>
using namespace std;

void saveToFile(const char* filename, int a, int b)
{
	if (!filename)
	{
		return;
	}
	std::ofstream ofs(filename);
	if (!ofs.is_open())
	{
		return;
	}
	
	ofs << a + b << " " << a - b;
}
void printOriginalNumbers(const char* filename)
{
	if (!filename)
	{
		return;
	}
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return;
	}

	int sum, diff;
	ifs >> sum >> diff;

	cout << "a = " << (sum + diff) / 2 << ", b = " << (-sum + diff) / (-2);
}
int main()
{
	int a = 0, b = 0;
	cin >> a >> b;
	saveToFile("result1.txt", a, b);

	printOriginalNumbers("result1.txt");
}