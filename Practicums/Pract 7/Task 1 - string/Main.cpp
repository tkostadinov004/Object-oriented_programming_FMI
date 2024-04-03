#include <iostream>
#include "MyString.h"

int main()
{
    MyString str = "testString";
    std::cout << str.at(0) << ", " << str.at(10) << ", " << str.at(10000) << std::endl;
    std::cout << str.front() << std::endl;
    std::cout << str.back() << std::endl;
    std::cout << str.contains('e') << std::endl;
    std::cout << str.contains('2') << std::endl;
    std::cout << str.contains("testString") << std::endl;
    std::cout << str.contains("test") << std::endl;
    std::cout << str.contains("String") << std::endl;
    std::cout << str.contains("Stringg") << std::endl;
    std::cout << str.contains("testd") << std::endl;
    std::cout << str.contains("") << std::endl;

    std::cout << cmp("", "") << std::endl;
    std::cout << cmp("", "a") << std::endl;
    std::cout << cmp("a", "a") << std::endl;
    std::cout << cmp("abc", "a") << std::endl;
    std::cout << cmp("abc", "abcd") << std::endl;
    std::cout << cmp("abc", "abc") << std::endl;

    std::cout << str.equals("testString") << std::endl;

    std::cout << str.find("String") << std::endl;
    str.append('a').append("example").append("anotherString");
    str.shrinkToFit();
    std::cout << str.str() << std::endl;

    MyString str2 = "exampleOfString";
    swap(str, str2);

    std::cout << str.empty() << std::endl;
    str.clear();
    std::cout << str.empty() << std::endl;
}