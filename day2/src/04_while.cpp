#include <iostream>

int main()
{
    int number = -1;

    while (number != 0)
    {
        std::cout << "请输入一个整数，输入0结束：";
        std::cin >> number;
        std::cout << "你输入了：" << number << '\n';
    }

    return 0;
}