#include<iostream>
#include<vector>


void vector_add(
    const std::vector<float>& a,
    const std::vector<float>& b,
    std::vector<float>& output)
{
    if (a.size() != b.size())
    {
        std::cout << "错误：两个输入向量的长度不同。\n";
        return;
    }

    output.resize(a.size());

    for (std::size_t i = 0; i < a.size(); ++i)
    {
        output[i] = a[i] + b[i];
    }
}

int main()
{
    std::vector<float> vec1 = {-1.0f,2.0f};
    std::vector<float> vec2 = {-3.0f,-2.0f};
    std::vector<float> result;

    vector_add(vec1, vec2, result);

    std::cout << "向量相加结果："<<std::endl;
    for(const float& output:result)
    {
        std::cout << output << " ";
    }

    std::cout << std::endl;

    return 0;
}