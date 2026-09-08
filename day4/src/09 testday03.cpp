// #include<iostream>

// double a=5/2;
// int b=5.0/2.0;
// float c=5.0/2;
// double d=static_cast<double>(5) / 2;

// int main()
// {
//    std::cout << "a = " << a << ",sizeof(a)=" << sizeof(a) << std::endl;
//    std::cout << "b = " << b << ",sizeof(b)=" << sizeof(b) << std::endl;
//    std::cout << "c = " << c << ",sizeof(c)=" << sizeof(c) << std::endl;
//    std::cout << "d = " << d << ",sizeof(d)=" << sizeof(d) << std::endl;

//     return 0;
// }

#include <iostream>

int main()
{
    // 除法表达式实验：auto 保留表达式推导出的类型
    auto a = 5 / 2;
    auto b = 5.0 / 2.0;
    auto c = 5.0 / 2;
    auto d = static_cast<double>(5) / 2;

    std::cout << "a = " << a
              << ", sizeof(a) = " << sizeof(a) << '\n';

    std::cout << "b = " << b
              << ", sizeof(b) = " << sizeof(b) << '\n';

    std::cout << "c = " << c
              << ", sizeof(c) = " << sizeof(c) << '\n';

    std::cout << "d = " << d
              << ", sizeof(d) = " << sizeof(d) << '\n';

    // int、float、double 类型实验
    int integer_value = 10;
    float float_value = 3.14f;
    double double_value = 3.14;

    std::cout << "integer_value = " << integer_value
              << ", sizeof(integer_value) = "
              << sizeof(integer_value) << '\n';

    std::cout << "float_value = " << float_value
              << ", sizeof(float_value) = "
              << sizeof(float_value) << '\n';

    std::cout << "double_value = " << double_value
              << ", sizeof(double_value) = "
              << sizeof(double_value) << '\n';

    return 0;
}