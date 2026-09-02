# Day 1 - 检查点 B：C++ 最小基础（未完成）

状态：学习中，尚未验收通过  
教材进度：用户记录为第 18 页  

## 1. C++ 程序的基本结构

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```

- `#include <iostream>`：引入输入输出相关声明，使编译器认识 `std::cout`、`std::cin` 等名称。
- `int main()`：定义程序入口函数；`int` 表示它返回整数，`()` 是参数列表。
- `{}`：限定函数体范围，函数中的语句写在其中。
- `return 0;`：向操作系统返回整数 `0`，通常表示程序正常结束；它不会自动显示在终端。

## 2. 核心语言、头文件和标准库

- **核心语言**：C++ 本身的语法和机制，例如变量、类型、`if`、`for`、函数和 `return`。
- **标准库**：在核心语言之上提供的通用工具，例如字符串、向量和输入输出。
- **头文件**：提供工具的声明，使编译器知道名称和使用方式。

常见对应关系：

```text
<iostream>  → std::cout、std::cin、std::endl
<string>    → std::string
<vector>    → std::vector
```

`<iostream>` 是头文件，`std` 是命名空间，两者不是同一种东西。

## 3. `std` 命名空间

命名空间用于组织名称并减少重名冲突。

```cpp
std::cout
std::string
```

- `std`：C++ 标准库主要使用的命名空间。
- `::`：作用域解析运算符，可理解为“到这个范围中寻找”。
- `std::cout`：`std` 命名空间中的 `cout`。

`using namespace std;` 可以让代码省略 `std::`，但可能增加名称冲突。学习和正式项目中优先显式写 `std::`。

## 4. 变量、初始化和赋值

基本定义形式：

```cpp
数据类型 变量名;
```

示例：

```cpp
int age;
std::string name;
```

推荐在定义时初始化：

```cpp
int age = 20;
std::string name = "Alice";
```

区别：

- **定义**：创建变量。
- **初始化**：变量创建时获得第一个值。
- **赋值**：变量已经存在，随后修改它的值。

## 5. 标准输入与输出

```cpp
std::cout << "Enter your name: ";
std::cin >> name;
```

- `std::cout`：标准输出对象，通常向终端输出。
- `std::cin`：标准输入对象，通常从终端读取数据。
- `std::cout << value`：把 `value` 送入输出流。
- `std::cin >> variable`：读取输入并保存到变量。

连续输出从左向右理解：

```cpp
std::cout << "Hello, " << name << "!";
```

它会依次输出提示文字、`name` 的值和感叹号。C++ 不会自动添加空格。

`std::cin >> name` 通常读取到空白字符为止；输入 `Zhang San` 时，`name` 通常只得到 `Zhang`。读取整行以后再学习 `std::getline`。

## 6. `std::string`

```cpp
#include <string>

std::string name = "Alice";
```

- `<string>`：头文件。
- `std::string`：标准库提供的字符串类型。
- `name`：字符串变量。

常见操作：

```cpp
name.size();
name[0];
std::string greeting = "Hello, " + name + "!";
```

`std::string` 之间可以用 `+` 拼接，但 `+` 的行为取决于左右两边的数据类型。

## 7. 字符与字符串

```text
'A'                         字符字面量，类型为 char
"A"                         字符串字面量
char letter = 'A';          字符变量
std::string text = "A";     标准库字符串对象
```

重要区别：

- 单引号通常表示一个字符。
- 双引号表示字符串字面量。
- `char + char` 通常进行数值计算，不是字符串拼接。
- `std::string + std::string` 表示字符串拼接。
- 两个字符串字面量不能直接依靠 `+` 完成 `std::string` 拼接。

## 8. `const` 和字符串构造

```cpp
const std::string greeting = "Hello, " + name + "!";
```

`const` 表示变量初始化后不应再被修改。

```cpp
const std::string spaces(greeting.size(), ' ');
```

表示创建一个字符串：字符数量等于 `greeting.size()`，每个字符都是空格 `' '`。

## 9. 当前仍需完成

检查点 B 尚未通过。下次学习需要独立回答：

1. `#include <iostream>` 有什么作用？
2. `main` 为什么返回 `int`？
3. 编译和运行有什么区别？
4. `int`、`float`、`double` 的主要区别是什么？
5. `=` 和 `==` 有什么区别？
6. `for` 循环的三个组成部分是什么？
7. 为什么数组或向量下标通常从 0 开始？

还未系统学习的重点：

- `int`、`float`、`double` 的区别。
- `=` 与 `==`。
- 条件语句和循环。
- 数组或向量下标。
- 输入失败和边界情况。

## 10. 本阶段自评

已初步理解：程序结构、头文件、命名空间、变量、字符串、基本输入输出。  
需要巩固：准确术语、类型区别、运算符、条件、循环和独立书写能力。  
本检查点必须在后续口述验收和小程序验证后，才能标记为完成。
