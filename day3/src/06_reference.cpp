#include <iostream>

void change(int& value)
{
    std::cout << "进入 change 时，value = " << value << std::endl;

    value = 10;

    std::cout << "修改后，value = " << value << std::endl;
}

int main()
{
    int x = 5;

    std::cout << "调用 change 前，x = " << x << std::endl;

    change(x);

    std::cout << "调用 change 后，x = " << x << std::endl;

    return 0;
}