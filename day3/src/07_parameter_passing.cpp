#include <iostream>

// 1. 按值传递：复制一份
void pass_by_value(int value)
{
    std::cout << "进入 pass_by_value 时，value = " << value << std::endl;

    value = 100;

    std::cout << "在 pass_by_value 中修改后，value = " << value << std::endl;
}

// 2. 引用传递：直接操作原变量
void pass_by_reference(int& value)
{
    std::cout << "进入 pass_by_reference 时，value = " << value << std::endl;

    value = 200;

    std::cout << "在 pass_by_reference 中修改后，value = " << value << std::endl;
}

// 3. const 引用：引用原变量，但只能读不能改
void pass_by_const_reference(const int& value)
{
    std::cout << "进入 pass_by_const_reference 时，value = " << value << std::endl;

    // value = 300;   // 如果取消注释，会报错，因为 const 不允许修改
}

int main()
{
    int x = 5;

    std::cout << "最开始 x = " << x << std::endl;
    std::cout << "----------------------" << std::endl;

    pass_by_value(x);

    std::cout << "pass_by_value 结束后，x = " << x << std::endl;
    std::cout << "----------------------" << std::endl;

    pass_by_reference(x);

    std::cout << "pass_by_reference 结束后，x = " << x << std::endl;
    std::cout << "----------------------" << std::endl;

    pass_by_const_reference(x);

    std::cout << "pass_by_const_reference 结束后，x = " << x << std::endl;

    return 0;
}