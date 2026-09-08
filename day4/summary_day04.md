# Day 4 - 从 C++ 数值与容器走到指针入口

日期：2026-09-09  
状态：已完成数值实验、CPU Vector Add 和指针核心概念学习；CUDA Kernel 延后到 Day 5

## 一、今天实际完成的内容

今天实际学习并经过问答、思考或代码验证的内容包括：

1. 闭卷复习 `int`、`float`、`double`、字面量、`sizeof`、除法和参数传递。
2. 编写并运行数值与除法实验，使用 `auto` 保留表达式推导出的类型。
3. 理解输入检查和安全除法的完整顺序，但没有保留独立的安全除法源码。
4. 复习按值、引用、常量引用、`void` 和函数作用域。
5. 学习 `std::vector` 的长度、判空、下标、追加、修改和范围 `for`。
6. 独立完成 CPU Vector Add，并测试长度不一致、普通数值、零和负数等情况。
7. 从零学习指针：地址、指针声明、取地址、解引用和空指针。
8. 理解 `const float*` 输入与 `float*` 输出的区别。
9. 理解固定数组、指针算术、下标访问和连续内存的关系。
10. 理解 `vector.data()` 返回首元素指针，不会复制数据。
11. 理解 `vector` 扩容后旧元素指针可能失效，需要重新调用 `data()`。

今天没有进入 CUDA 线程索引、Kernel 编写、Kernel 启动和 CUDA 内存 API。这些内容不能标记为已经学习，将进入 Day 5。

与 C++、CUDA 学习无关的模型、应用版本、用量和账户对话不纳入本总结。

## 二、数值类型、字面量与转换

### 2.1 变量类型与右侧表达式

```cpp
int x = 1.9;       // 右侧 double 转为 int，x 保存 1
float y = 1.0;     // 右侧 double 转为 float
double z = 1;      // 右侧 int 转为 double
```

变量声明左侧的类型规定变量最终如何保存数据。右侧表达式先产生自己的类型和值；若类型不同，再转换成左侧变量的类型。变量的类型不会因为后续赋值而改变。

### 2.2 `f` 后缀

```cpp
1.0    // double 字面量
1.0f   // float 字面量
```

`f` 是字面量后缀，不是运算符，也不是先产生 `double` 后再转换。它表示从一开始就创建 `float` 字面量。

加 `f` 不会提高精度。它的作用是明确选择 `float`，使类型一致，并避免不必要或不清晰的 `double -> float` 窄化转换。需要更高精度时应选择 `double`。

### 2.3 除法由操作数决定

```cpp
auto a = 5 / 2;                      // int，值为 2
auto b = 5.0 / 2.0;                  // double，值为 2.5
auto c = 5.0 / 2;                    // double，值为 2.5
auto d = static_cast<double>(5) / 2; // double，值为 2.5
```

```cpp
double result = 5 / 2;
```

上式先完成整数除法得到 `2`，再转换成 `double` 的 `2.0`。结果变量无法恢复已经丢失的小数部分。

## 三、输入检查与安全除法

```cpp
if (!(std::cin >> numerator >> denominator))
{
    std::cout << "输入无效\n";
    return 1;
}

if (denominator == 0.0)
{
    std::cout << "除数不能为0\n";
    return 1;
}
```

逻辑顺序是：

```text
定义 double 变量
-> cin 读取键盘文本
-> 按 double 规则解析
-> 检查读取状态
-> 检查除数是否为 0
-> 执行除法
```

`!` 是逻辑非运算符。读取成功时输入表达式在条件中为真，取反后为假；读取失败时取反后为真，因此进入错误分支。

输入失败和除数为零是两个不同问题：`abc 2` 无法解析为两个 `double`；`5 0` 可以成功读取，但不能继续执行除法。

## 四、参数、`void` 与作用域

```text
int value        -> 按值传递，函数得到副本
int& value       -> 引用传递，可以修改原变量
const int& value -> 常量引用，只读且避免复制
```

`void` 表示函数不向调用者返回普通数值，不表示函数不能做事。`void` 函数仍可输出、修改引用参数，并可用 `return;` 提前结束，但不能写 `return 100;`。

`main` 中的局部变量 `x` 只在 `main` 的作用域可见。另一个函数通过自己的形参名访问传入的数据；引用同一个对象不等于共享变量名。

## 五、`vector` 基础与边界

```cpp
std::vector<float> values = {1.0f, 2.0f, 3.0f};
```

```text
values.size()  -> 3
values.empty() -> false
合法下标       -> 0、1、2
```

```cpp
values[1] = 10.0f;
values.push_back(4.0f);
```

`size()` 是元素数量，不是最后一个下标。有 `N` 个元素时，合法下标是 `0` 到 `N-1`，循环条件应写成：

```cpp
for (std::size_t i = 0; i < values.size(); ++i)
```

`values[i]` 通常不检查边界，越界属于未定义行为；`values.at(i)` 会检查边界。程序没有立即崩溃不能证明访问合法。

### 5.1 范围 `for`

```cpp
for (float value : values)              // 复制元素
for (float& value : values)             // 可修改原元素
for (const float& value : values)       // 只读引用
```

输出 `vector` 时不能直接写 `std::cout << values`，需要遍历元素：

```cpp
for (float value : values)
{
    std::cout << value << ' ';
}
```

## 六、CPU Vector Add

今天完成的核心接口：

```cpp
void vector_add(
    const std::vector<float>& a,
    const std::vector<float>& b,
    std::vector<float>& output)
```

参数含义：

```text
a、b   -> 只读引用，避免复制并防止函数修改输入
output -> 可修改引用，把结果写回调用者
```

核心步骤：

```cpp
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
```

关键认识：

```text
resize 保证 output 有可写元素
长度检查保证两个输入能够按相同下标读取
i < a.size() 控制循环下标不越界
范围 for 用于逐个输出结果
```

长度不一致时，`vector_add()` 中的 `return;` 只结束该函数，`main()` 仍会继续执行，因此当前程序仍会打印“向量相加结果”标题，只是结果为空。这不是越界，但以后可以通过返回成功状态改善流程。

## 七、指针基础

```cpp
float value = 1.0f;
float* pointer = &value;
```

```text
value     -> 保存 float 数值
&value    -> 取得 value 的地址
pointer   -> 保存 value 的地址
*pointer  -> 解引用，访问该地址中的 value
```

```cpp
*pointer = 5.0f;
```

这会修改 `value`，不会把地址改成 `5.0f`。需要区分：

```cpp
pointer = &another_value; // 改变指针指向
*pointer = 10.0f;         // 修改当前指向对象的值
```

暂时没有有效目标的指针应初始化为：

```cpp
float* pointer = nullptr;
```

不能解引用空指针。只有指针指向有效对象并且访问范围合法时，才能使用 `*pointer` 或 `pointer[i]`。

## 八、数组、指针算术与索引

```cpp
float values[3] = {1.0f, 2.0f, 3.0f};
float* pointer = values;
```

在这个表达式中，数组名 `values` 转换为首元素地址：

```cpp
pointer == &values[0]
```

核心等价关系：

```cpp
pointer[i] == *(pointer + i)
values[i] == *(values + i)
```

```text
pointer + 1    -> 第二个元素的地址
*(pointer + 1) -> 第二个元素的值
```

指针加一表示移动到下一个相同类型的元素，不是简单增加一个字节。任何指针下标和解引用都不能超出有效元素范围。

## 九、`vector.data()`

```cpp
std::vector<float> values = {1.0f, 2.0f, 3.0f};
float* data = values.data();
```

`values.data()` 返回指向首元素存储区域的指针，不复制数据：

```cpp
data[0] == values[0]
data[i] == *(data + i)
data[i] == values[i]
```

通过 `data` 修改元素会同时改变原 `vector`：

```cpp
data[1] = 10.0f; // values[1] 也变为 10.0f
```

如果 `push_back()` 或增大的 `resize()` 导致重新分配内存，之前保存的元素指针可能失效。改变 `vector` 长度后，应重新取得：

```cpp
data = values.data();
```

空 `vector` 的 `data()` 结果不能被解引用。

## 十、与 CUDA 的连接及未完成内容

今天已经理解 CUDA 常见参数的 C++ 含义：

```cpp
const float* a; // 输入数据，只读
const float* b; // 输入数据，只读
float* output;  // 输出数据，可写
```

CPU 端可以用 `vector` 管理连续数据，并通过 `data()` 获取底层指针。但是今天没有继续学习：

- `threadIdx.x`、`blockIdx.x`、`blockDim.x`；
- 全局线程索引 `i` 的计算；
- `__global__` Kernel；
- `cudaMalloc`、`cudaMemcpy`、Kernel 启动、同步和错误检查；
- 完整 CUDA Vector Add。

这些内容进入 Day 5。当前电脑能够识别 NVIDIA GeForce GTX 1650 Ti，但终端尚不能识别 `nvcc`，Day 5 开始时需要先确认 CUDA Toolkit 是否已安装以及环境变量是否正确。

