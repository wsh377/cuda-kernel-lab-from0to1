# Day 2 - 检查点 B：C++ 最小基础（知识补齐版）

状态：部分知识已补齐；`float`、`double` 等内容尚未学习，检查点 B 未完成  
教材进度：《Accelerated C++》第 0-2 章相关基础  
补充日期：2026-09-04

## 1. C++ 程序的基本结构

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    return 0;
}
```

- `#include <iostream>`：引入标准输入输出相关声明，使编译器认识 `std::cout`、`std::cin` 等名称。
- `int main()`：定义程序入口函数；`int` 表示该函数返回一个整数状态码。
- `{}`：限定函数体或语句块的范围，同时形成作用域。
- `return 0;`：向操作系统返回 `0`，通常表示程序正常结束，不会自动显示在终端。

源文件需要先经过编译和链接才能生成可执行程序：

```text
.cpp 源文件 -> 编译器检查并翻译 -> 链接 -> .exe -> 操作系统加载运行
```

- 少分号、名称未声明等通常是编译错误。
- 除以零、无限循环或结果错误通常发生在运行阶段。

## 2. 核心语言、标准库和 `std`

- **核心语言**：C++ 自身提供的类型和语法，如 `int`、`float`、`double`、`char`、`bool`、`if`、`while` 和 `for`。
- **标准库**：在语言之上提供的通用工具，如 `std::string`、`std::cout`、`std::cin` 和 `std::vector`。
- **头文件**：提供名称的声明，使编译器知道标准库工具的类型和用法。

常见对应关系：

```text
<iostream> -> std::cout、std::cin、std::endl
<string>   -> std::string
<vector>   -> std::vector
```

`std` 是标准库主要使用的命名空间，`::` 是作用域解析运算符：

```cpp
std::string name;
std::cout << name;
```

普通的 `int` 属于核心语言，因此不能写成 `std::int`。

## 3. 变量、定义、初始化和赋值

```cpp
int age = 20;
std::string name = "Alice";
```

- **定义**：创建变量并确定其类型和名称。
- **初始化**：变量创建时获得第一个值。
- **赋值**：变量已经存在，随后用新值替换旧值。

```cpp
std::string name = "Alice"; // 定义并初始化
name = "Bob";               // 赋值
```

变量应定义在能够满足需要的最小作用域中。只在 `main` 使用的变量通常放在 `main` 的花括号内，而不是定义成全局变量。

## 4. 基本数据类型（尚未全部学习）

```cpp
int count = 7;
char letter = 'A';
bool finished = false;
```

- `int`：保存整数，已经初步学习。
- `char`：保存单个字符。
- `bool`：保存 `true` 或 `false`。

以下内容属于检查点 B 的后续学习任务，目前不能标记为掌握：

```cpp
float temperature = 23.5f;
double average = 23.5;
```

- `float` 与 `double` 分别适合保存什么数据。
- 两者在精度和占用空间方面的主要区别。
- 浮点数字面量中的 `f` 表示什么。
- 整数除法和浮点除法的区别。

这些内容需要经过讲解、小程序实验和闭卷回答后再补充结论。

## 5. 字符、字符串和字符串构造

```text
'A'   -> 单个字符，类型为 char
"A"   -> 字符串字面量
```

```cpp
char letter = 'A';
std::string text = "A";
std::string copy = text;
std::string spaces(10, ' ');
```

`std::string spaces(10, ' ')` 表示创建一个由 10 个空格字符组成的字符串。这个特定构造方式要求第二个参数是单个字符，不能写成 `"wu"`。

变量本身不是字符串字面量，使用变量时不加引号：

```cpp
std::string name = "Alice";
std::string copy = name;
```

## 6. 对象、成员和字符串长度

```cpp
std::string greeting = "Hello";
auto length = greeting.size();
```

`greeting.size()` 的结构是：

```text
对象.成员函数()
```

- `greeting`：具体的字符串对象。
- `.`：访问该对象的成员。
- `size`：成员函数名称。
- `()`：调用函数；括号为空表示不需要提供参数。

`size()` 返回字符数量，而不是字符串：

```cpp
std::string::size_type length = greeting.size();
```

- `std::string::size_type`：`std::string` 内部提供的类型名称，用于表示字符串长度和下标，通常是无符号整数类型。
- `size_type` 是类型，`size()` 是成员函数，二者不是同一种东西。
- 不能直接写 `std::string length = greeting.size();`，因为右侧是数字，左侧要求字符串。
- 现代 C++ 中可以使用 `auto` 让编译器推断正确类型。

当前常用的字符串成员函数：

```cpp
text.size();          // 字符数量
text.empty();         // 是否为空
text.clear();         // 清空
text.push_back('!');  // 追加一个字符
text.at(0);           // 访问并检查下标
```

## 7. 标准输入与输出

```cpp
std::string name;
std::cout << "Enter your name: ";
std::cin >> name;
std::cout << "Hello, " << name << "!\n";
```

- `std::cout << value`：把值送到标准输出。
- `std::cin >> variable`：从标准输入读取数据并保存到变量。
- 连续输出按从左到右的顺序进行，C++ 不会自动添加空格。
- `std::cin >> name` 通常读取到空白字符为止，整行输入需要使用 `std::getline`。

## 8. 赋值和比较

```cpp
number = 5;       // 把 5 赋给 number
number == 5;      // 比较 number 是否等于 5，结果为 bool
number != 0;      // 比较 number 是否不等于 0
```

常见比较运算符：

```text
==  等于
!=  不等于
<   小于
<=  小于等于
>   大于
>=  大于等于
```

不要把赋值 `=` 误写成相等比较 `==`。

## 9. `if` 条件语句

```cpp
if (number > 0)
{
    std::cout << "positive\n";
}
else if (number < 0)
{
    std::cout << "negative\n";
}
else
{
    std::cout << "zero\n";
}
```

同一组 `if` / `else if` / `else` 中，只执行第一个条件成立的分支；如果前面的条件都不成立，则执行 `else`。

安全除法需要先检查除数：

```cpp
if (divisor != 0)
{
    std::cout << dividend / divisor << '\n';
}
else
{
    std::cout << "Cannot divide by zero.\n";
}
```

## 10. 逻辑运算和短路求值

```text
&&  并且：两边都为 true 时结果才为 true
||  或者：至少一边为 true 时结果就为 true
!   取反：true 变 false，false 变 true
```

```cpp
if (divisor != 0 && dividend / divisor > 2)
{
    std::cout << "condition is true\n";
}
```

`&&` 从左向右判断。若 `divisor != 0` 为假，整体必然为假，右侧除法不会执行，这叫短路求值。把零检查放在前面可以避免除以零。

## 11. `while` 循环

```cpp
int number = -1;

while (number != 0)
{
    std::cout << "Enter an integer (0 to stop): ";
    std::cin >> number;
    std::cout << "You entered: " << number << '\n';
}
```

`while` 先判断条件，再决定是否执行循环体：

```text
初始化 -> 判断条件 -> 执行循环体 -> 更新状态 -> 再次判断
```

示例中：

- `number` 初始化为 `-1`，保证第一次判断 `number != 0` 成立。
- `std::cin` 读取的新输入负责更新 `number`。
- 输入 `0` 后，下一次条件判断为假，循环结束。

正确的循环需要明确：

1. 初始状态。
2. 继续条件。
3. 每轮执行的任务。
4. 让程序接近结束条件的更新方式。

如果循环变量不更新，可能形成无限循环。

## 12. `for` 循环和计数

```cpp
for (int i = 0; i < 5; ++i)
{
    std::cout << i << '\n';
}
```

`for` 的三个组成部分是：

```cpp
for (初始化; 条件; 更新)
```

执行顺序：

```text
初始化一次 -> 判断 -> 循环体 -> 更新 -> 判断 -> 循环体 -> ...
```

上面的程序输出 `0`、`1`、`2`、`3`、`4`。当 `i == 5` 时，`i < 5` 为假，循环结束。

- 循环次数比较明确时常使用 `for`。
- 执行次数未知、主要由某个状态控制时常使用 `while`。

## 13. 嵌套循环

```cpp
for (int row = 0; row < 2; ++row)
{
    for (int column = 0; column < 3; ++column)
    {
        std::cout << '*';
    }

    std::cout << '\n';
}
```

- 外层循环控制行。
- 内层循环控制每一行中的列。
- 每开始新的一行，`column` 都重新初始化为 `0`。

输出：

```text
***
***
```

行、列索引的思想以后会用于矩阵、图像以及 CUDA 的二维线程索引。

## 14. 下标从 0 开始

```cpp
std::string text = "Hello";
char first = text[0];
```

下标可以理解为元素相对起始位置的偏移量：

- 第一个元素距离起点 0 个位置，所以其下标是 `0`。
- 第二个元素距离起点 1 个位置，所以其下标是 `1`。

如果一个容器有 `N` 个元素，合法下标通常是：

```text
0 到 N-1
```

因此常见循环条件是：

```cpp
for (std::size_t i = 0; i < container.size(); ++i)
```

使用 `<` 而不是 `<=`，可以避免访问下标 `N` 导致越界。

## 15. 有符号与无符号类型

`int` 通常是有符号整数，可以表示负数；`std::string::size_type` 通常是无符号整数，不能表示负数。

无符号数从 `0` 再减 `1` 时不会得到普通意义上的 `-1`，而可能变成一个很大的正数。因此用无符号类型倒序计数时必须谨慎。

## 16. 花括号和作用域

第一组花括号可以属于函数：

```cpp
int main()
{
    // main 的函数体
}
```

第二组花括号可以属于循环或条件语句：

```cpp
while (condition)
{
    // 循环体
}
```

花括号的两个作用：

1. 把多条语句组成一个整体。
2. 建立变量的作用域。

外层定义的变量通常可被内层使用；内层定义的变量离开花括号后便不能再使用。

## 17. 编译与运行中的实际错误记录

本阶段遇到过以下问题：

### 找不到源文件

```text
No such file or directory
```

原因：终端当前目录与源文件所在目录不一致。  
解决：切换到正确目录，或在编译命令中使用正确的相对路径。

### 找不到可执行文件

原因：前一步编译失败，所以 `.exe` 没有生成。它是编译失败后的连锁结果。

### 无法覆盖可执行文件

```text
Permission denied
```

原因：旧程序仍在运行并占用 `.exe`。  
解决：输入结束值让程序退出，或停止旧进程后重新编译。

### 中文乱码

原因：源文件、编译器执行字符集和终端代码页不一致。  
解决：统一使用 UTF-8，并区分 PowerShell、`cmd` 和实际执行的 C++ 程序。

## 18. 检查点 B 闭卷验收题

1. `#include <iostream>` 有什么作用？
2. `main` 为什么返回 `int`？`return 0;` 表示什么？
3. 编译和运行有什么区别？
4. `int`、`float`、`double` 的主要区别是什么？
5. `=` 和 `==` 有什么区别？
6. `for` 循环的三个组成部分是什么？
7. 为什么字符串、数组或向量下标通常从 0 开始？

变式验收还需要能够：

- 独立写出一个输入、判断并输出结果的小程序。
- 找出缺少更新导致的无限循环。
- 使用 `if` 安全处理除以零。
- 解释 `&&` 的短路求值。
- 写出输出 `0` 到 `N-1` 的循环。
- 解释 `greeting.size()`、`std::string::size_type` 和 `auto` 的区别。

## 19. 当前阶段结论

当前已经学习的内容从程序结构扩展到整数、字符、输入输出、字符串成员、条件、逻辑运算、循环、下标、作用域和常见编译运行错误。

`float`、`double`、整数与浮点除法仍未学习，因此检查点 B 尚未补齐，也尚未进入最终验收。完成这些内容的学习，再通过七个问题的闭卷口述、变式追问和小程序验证后，才能将状态改为“验收通过”，随后进入检查点 C。
