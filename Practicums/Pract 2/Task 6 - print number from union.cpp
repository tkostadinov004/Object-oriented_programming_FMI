#include <iostream>
using namespace std;

union Number
{
    int value;
    char arr[4];
};
void printNumber(const Number& num)
{
    int result = 0;
    for (size_t i = 0; i < 4; i++)
    {
        result |= ((0xff & num.arr[i]) << 8 * i);
    }

    cout << result;
}
int main()
{
    Number n;
    n.value = 12345678;

    printNumber(n);
}