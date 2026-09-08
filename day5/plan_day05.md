# Day 5：把 CPU Vector Add 映射为第一个 CUDA Kernel

日期：下一次学习日  
预计用时：必做约 4-6 小时；学有余力约 1 小时  
学习原则：先巩固指针，再验证 CUDA 环境；每加入一个 CUDA 步骤都解释它解决的问题，不机械复制完整程序

## 一、Day 5 起点

Day 4 已完成：

- 数值类型、字面量、转换与除法；
- 输入检查和安全除法逻辑；
- 参数传递、`void` 与作用域；
- `vector` 基本操作和范围 `for`；
- CPU Vector Add；
- 指针、数组、指针算术、索引与 `vector.data()`。

Day 4 没有进入 CUDA 线程索引和完整 CUDA Vector Add，因此 Day 5 从这里继续，不把预览当作已掌握。

当前环境检查结果：

```text
GPU：NVIDIA GeForce GTX 1650 Ti
驱动：可被 nvidia-smi 识别
nvcc：当前 PowerShell 无法识别
```

这可能表示 CUDA Toolkit 尚未安装，或已经安装但 `nvcc` 所在目录没有加入环境变量。Day 5 先诊断，不直接假设原因。

## 二、今日必做目标

1. 闭卷重建变量、地址、指针、数组和 `vector.data()` 的关系。
2. 独立完成并运行 `pointer_basics.cpp`。
3. 确认 CUDA Toolkit 与 `nvcc` 状态，使 `.cu` 文件能够编译。
4. 理解 `threadIdx.x`、`blockIdx.x` 和 `blockDim.x`。
5. 理解并计算一维全局线程索引。
6. 编写并运行第一个最小 CUDA Kernel。
7. 将 CPU Vector Add 改写为 CUDA Vector Add。
8. 使用 CPU 结果验证 GPU 结果，而不是只看程序是否运行。

## 三、结束标准

- [ ] 能区分 `p`、`*p`、`&x`、`a[i]`、`a+i` 和 `*(a+i)`。
- [ ] 能解释 `vector.data()` 为什么能连接 `vector` 与指针接口。
- [ ] 能解释为什么 `vector` 扩容后旧元素指针可能失效。
- [ ] 能运行 `nvcc --version`，或明确记录无法运行的实际原因和下一步。
- [ ] 能解释一个 CUDA Kernel 由谁启动、在哪里执行。
- [ ] 能根据块编号、块大小和块内线程编号算出全局索引。
- [ ] 能解释为什么 Kernel 必须检查 `i < n`。
- [ ] 能说出 CUDA Vector Add 的完整数据流。
- [ ] 能编译并运行最小 Kernel；若环境确有阻塞，保留源码和完整诊断记录。
- [ ] 能完成 CUDA Vector Add 并通过 CPU 对照测试；只有实际运行通过后才标记完成。

## 四、阶段 A：指针闭卷热身（20-30 分钟）

不看 Day 4 总结，回答：

1. `float value`、`&value`、`float* p`、`p` 和 `*p` 分别表示什么？
2. `p = &other` 和 `*p = 5.0f` 分别改变什么？
3. 为什么不能解引用 `nullptr`？
4. `const float* input` 与 `float* output` 有什么区别？
5. 为什么 `a[i] == *(a+i)`？
6. `v.data()` 返回什么？是否复制元素？
7. 为什么 `push_back()` 后旧的 `data` 指针可能失效？

创建 `day5/src/11_pointer_basics.cpp`，至少验证：

```cpp
float value = 1.0f;
float* pointer = &value;
*pointer = 5.0f;

float array[3] = {1.0f, 2.0f, 3.0f};
float* array_data = array;

std::vector<float> values = {1.0f, 2.0f, 3.0f};
float* vector_data = values.data();
```

输出并解释变量值、地址、解引用、下标和指针算术的对应关系。不要访问空指针或越界下标。

## 五、阶段 B：CUDA 环境诊断（30-60 分钟）

依次检查：

```powershell
nvidia-smi
nvcc --version
where.exe nvcc
```

若 `nvcc` 不可识别：

1. 检查 CUDA Toolkit 是否已安装；
2. 检查常见 CUDA `bin` 目录是否存在；
3. 区分“有 NVIDIA 驱动”和“已安装 CUDA Toolkit”；
4. 若需要安装或修改环境变量，先确认准确路径和版本；
5. 修改后重新打开 PowerShell，再运行 `nvcc --version`。

不要因为 `nvidia-smi` 能运行就断言 `nvcc` 一定存在。前者证明驱动能识别 GPU，后者属于 CUDA 开发工具链。

## 六、阶段 C：CUDA 执行模型（40-60 分钟）

先理解三个一维索引量：

```text
threadIdx.x -> 线程在线程块内部的编号
blockIdx.x  -> 线程块在网格中的编号
blockDim.x  -> 每个线程块包含的线程数
```

一维全局线程索引：

```cpp
int i = blockIdx.x * blockDim.x + threadIdx.x;
```

至少手算以下组合：

```text
blockIdx.x=0, blockDim.x=4, threadIdx.x=0
blockIdx.x=0, blockDim.x=4, threadIdx.x=3
blockIdx.x=1, blockDim.x=4, threadIdx.x=0
blockIdx.x=2, blockDim.x=4, threadIdx.x=1
```

目标不是背公式，而是理解每个线程块的编号区间为什么不会重叠。

## 七、阶段 D：第一个最小 Kernel（45-75 分钟）

创建：

```text
day5/src/12_first_kernel.cu
```

认识：

```cpp
__global__ void kernel_name()
```

以及 Kernel 启动语法：

```cpp
kernel_name<<<blocks, threads_per_block>>>();
```

最小验收：

1. `.cu` 文件能够由 `nvcc` 编译；
2. CPU 端成功启动 Kernel；
3. 使用 `cudaDeviceSynchronize()` 等待执行完成；
4. 检查 Kernel 启动和同步错误；
5. 能说明 `__global__` 函数由 CPU 发起、在 GPU 上执行。

## 八、阶段 E：CUDA Vector Add 的数据流（30-45 分钟）

先闭卷排列完整流程：

```text
CPU 准备 a、b 和 CPU 对照结果
-> GPU 申请 a、b、output 空间
-> a、b 从 CPU 复制到 GPU
-> 启动 Vector Add Kernel
-> 同步并检查错误
-> output 从 GPU 复制回 CPU
-> 与 CPU 结果逐元素比较
-> 释放 GPU 资源
```

对应 API 只逐个引入：

```text
cudaMalloc
cudaMemcpy
Kernel<<<...>>>
cudaGetLastError
cudaDeviceSynchronize
cudaFree
```

每学一个 API，都回答：它操作 CPU 内存还是 GPU 内存，它在流程中解决什么问题，失败时如何发现。

## 九、阶段 F：实现 CUDA Vector Add（90-120 分钟）

创建：

```text
day5/src/13_vector_add_cuda.cu
```

Kernel 核心：

```cpp
__global__ void vector_add_kernel(
    const float* a,
    const float* b,
    float* output,
    int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        output[i] = a[i] + b[i];
    }
}
```

重点解释：

- `a`、`b` 为什么是 `const float*`；
- `output` 为什么是 `float*`；
- 为什么每个线程只处理一个 `i`；
- 为什么总线程数可以大于 `n`；
- 为什么必须用 `if (i < n)` 防止越界；
- CPU 端的 `vector.data()` 与 CUDA 指针参数有什么联系，又为什么不能把普通 CPU 指针直接当作设备指针使用。

线程块数量使用向上取整：

```cpp
int blocks = (n + threads_per_block - 1) / threads_per_block;
```

先用小数据手算，再运行程序。

## 十、最低测试要求

至少测试：

```text
{1, 2, 3} + {4, 5, 6} -> {5, 7, 9}
单元素输入
空输入
包含负数和小数
元素数量不是线程块大小整数倍
较大向量
```

验证时为每个元素比较 CPU 与 GPU 结果。浮点结果后续可引入误差容限；当前简单加法仍应理解浮点数是有限精度近似表示。

## 十一、学有余力

只有在必做目标实际完成后，再学习：

- `cudaError_t` 与统一错误检查函数；
- 使用 CUDA Event 计时；
- 区分 Kernel 时间与数据传输时间；
- 初步认识 grid-stride loop；
- 比较 `size()` 与 `capacity()`，观察 `vector.data()` 地址何时变化。

暂不进入共享内存、线程同步、归约、多维网格和性能优化。

## 十二、结束整理

学习结束后创建：

```text
day5/summary_day05.md
day5/review_day05.md
day6/plan_day06.md
```

总结必须按实际完成情况记录。若 CUDA Toolkit 配置占用了主要时间，应如实记录环境诊断与解决结果，不把未运行的 Kernel 写成已掌握。

