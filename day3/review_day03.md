# Day 3 - 回忆提纲

今日学习记录：

1. 数值类型与字面量

- `int` 保存整数，`float`、`double` 保存浮点数；
- `23.5` 默认是 `double` 字面量，`23.5f` 是 `float` 字面量；
- `sizeof` 观察类型在当前环境中的字节数，结果不代表所有平台。

2. 数组、`vector` 与 `sizeof`

- `float a[10]`：一个含 10 个 `float` 的数组；
- `std::vector<float> b(10)`：一个 `vector`，管理 10 个 `float`；
- `std::vector<float> c[10]`：一个数组，里面有 10 个 `vector`；
- 数组的数据属于数组本身，`vector` 对象负责管理另一块元素存储；
- `sizeof(vector)` 只计算管理对象本身，不包含它管理的全部元素。

3. 除法与类型转换

- `5 / 2` 得到 `2`，`5.0 / 2.0` 得到 `2.5`；
- `double result = 5 / 2` 仍是 `2.0`；
- `static_cast<double>` 可在运算前主动转换类型。

4. 函数参数与 `void`

- `int value`：复制一份，修改副本不影响原变量；
- `int& value`：引用原变量，可以修改原变量；
- `const int& value`：不复制原对象，只能读取，不能通过引用修改；
- 引用同一个对象不等于共享变量名，函数内部使用自己的参数名；
- `void` 不返回普通值，但可以输出、修改引用参数或提前 `return;`。

5. `vector`、边界与 `struct`

- `size()` 是元素数量，`empty()` 判断元素数量是否为零；
- `[]` 通常不检查范围，`at()` 会检查范围；
- `N` 个元素的合法下标是 `0` 到 `N-1`，越界未必立即崩溃；
- `vector` 把多个相同类型对象放在一起；
- `struct` 把一个对象内部多个不同类型的数据组织在一起；
- `std::vector<Student>` 表示许多个 `Student` 对象。

6. CPU 与 CUDA

- CPU 通过循环依次处理各个元素；
- CUDA Kernel 让许多 GPU 线程分别处理不同元素；
- 两者可以使用相同的计算规则，如 `output[i] = a[i] + b[i]`。

目前以上内容仍以概念理解为主，完整的 `vector` 程序、CPU Vector Add 和指针尚未完成。
