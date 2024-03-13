#include <iostream>
using namespace std;

union Number
{
    int i;
    double d;
};
int main()
{
    Number num;

    num.i = 2;
    cout << &num.i << endl << num.i << endl;

    num.d = 1.2366577e5;
    cout << &num.d << endl << num.d << endl;
}