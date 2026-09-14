# Day 5 - 从 CPU Vector Add 进入第一个 CUDA Kernel

日期：2026-09-11 至 2026-09-15  
状态：完成 CUDA 环境、执行模型和最小 Kernel；完整 CUDA Vector Add 延续到 Day 6

## 一、今天实际完成的内容

1. 复习变量、地址、指针、取地址、解引用、数组和 `vector.data()`。
2. 理解 `vector` 扩容后旧元素指针可能失效。
3. 区分 Windows、Linux、WSL 与 Ubuntu 的关系。
4. 在 WSL Ubuntu 中验证 NVIDIA GPU、CUDA Toolkit 与 `nvcc`。
5. 配置 VS Code，使 `.cpp`、`.cu` 和 `.py` 可以通过统一任务运行。
6. 学习 Bash 中的 `cd`、路径补全、历史命令、编译与运行。
7. 理解 `g++`、`nvcc`、`-o`、源文件、可执行文件和运行命令的关系。
8. 编写并运行第一个 CUDA Kernel，得到 CPU 与 GPU 输出。
9. 理解 Kernel、Grid、Block、Thread 和 Kernel 启动语法。
10. 掌握一维全局线程索引的计算。
11. 理解为什么总线程数可以大于数据量，以及为什么必须检查 `i < n`。
12. 再次复习 CPU Vector Add 和范围 `for` 中值、引用、常量引用的区别。
13. 开始学习 Host Memory、Device Memory、`cudaMalloc` 和 HostToDevice `cudaMemcpy`。

今天关于 AI Infra 知识体系、实习路线、教材和网络资源的讨论属于长期职业规划，已经单独整理到 `resources/AI_INFRA_LEARNING_MAP.md`，不计入 Day 5 CUDA 学习进度。

## 二、CUDA 开发环境

当前采用：

```text
Windows
└── WSL 2
    └── Ubuntu 24.04
        ├── Bash
        ├── g++
        └── nvcc + CUDA Runtime
```

环境已经能够：

- 使用 `g++` 编译和运行普通 C++；
- 使用 `nvcc` 编译 `.cu`；
- 在 WSL 中访问 NVIDIA GeForce GTX 1650 Ti；
- 实际运行 GPU Kernel；
- 在 VS Code WSL 窗口中编辑和构建程序。

统一 VS Code Task 使用当前文件后缀决定工具：

```text
.cpp -> g++编译并运行
.cu  -> nvcc编译并运行
.py  -> python3运行
```

Bash 是命令环境，`g++` 和 `nvcc` 才是编译器。快捷键只是代替人工执行相同的构建命令。

## 三、编译与运行

普通 C++：

```bash
g++ source.cpp -o program
./program
```

CUDA：

```bash
nvcc -arch=sm_75 source.cu -o program
./program
```

`-o` 表示 output，用来指定生成的可执行文件名称或路径。编译成功时通常没有输出；之后仍需运行生成的程序。

减少重复输入的方法：

- 按 `Tab` 补全路径；
- 按 `↑` 取回历史命令；
- 使用 `Ctrl+R` 搜索历史命令；
- 使用 `&&` 连接“编译成功后运行”；
- 使用 VS Code Task 自动执行。

## 四、第一个 CUDA Kernel

当前最小程序的核心：

```cpp
__global__ void hello_from_gpu()
{
    printf("Hello from GPU!\n");
}

hello_from_gpu<<<1, 1>>>();
cudaDeviceSynchronize();
```

关键理解：

- `__global__` 声明一个由 CPU 启动、在 GPU 上执行的 Kernel；
- `<<<blocks, threads_per_block>>>` 配置启动规模；
- 每个被创建的 GPU 线程都会执行一遍 Kernel 函数体；
- Kernel 启动通常是异步的；
- `cudaDeviceSynchronize()` 让 CPU 等待 GPU 工作完成。

程序实际输出过：

```text
Hello from CPU!
Hello from GPU!
```

当前最小程序尚未完整检查 Kernel 启动错误和同步错误，因此只能算最小运行版本。

## 五、Grid、Block 与 Thread

一维 CUDA 中：

```text
threadIdx.x -> 当前线程在Block内部的编号
blockIdx.x  -> 当前Block在Grid中的编号
blockDim.x  -> 每个Block包含的线程数
```

全局线程索引：

```cpp
int i = blockIdx.x * blockDim.x + threadIdx.x;
```

例如：

```cpp
kernel<<<3, 4>>>();
```

表示 3 个 Block，每个 Block 4 个线程，总共 12 个线程，全局索引为 `0` 到 `11`。

```text
Block 0 -> i = 0, 1, 2, 3
Block 1 -> i = 4, 5, 6, 7
Block 2 -> i = 8, 9, 10, 11
```

当数据只有 `n=10` 个元素时，线程 `i=10` 和 `i=11` 必须停止：

```cpp
if (i < n)
{
    output[i] = a[i] + b[i];
}
```

否则会访问数组边界以外的地址。

线程块数量采用向上取整：

```cpp
int blocks = (n + threads_per_block - 1) / threads_per_block;
```

## 六、CPU Vector Add 到 CUDA 的映射

CPU 版本通过一个循环依次计算：

```cpp
for (std::size_t i = 0; i < a.size(); ++i)
{
    output[i] = a[i] + b[i];
}
```

CUDA 版本把不同下标分配给不同线程：

```text
线程0 -> output[0] = a[0] + b[0]
线程1 -> output[1] = a[1] + b[1]
线程2 -> output[2] = a[2] + b[2]
```

数学规则没有改变，改变的是任务分配方式。

Kernel 核心已经理解但尚未形成完整程序：

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

## 七、范围 `for` 的补充复习

```cpp
for (float value : result)        // 每次复制当前元素
for (float& value : result)       // 引用原元素，可以修改
for (const float& value : result) // 只读引用，不复制
```

冒号可以读作“来自”或“遍历”。例如：

```cpp
for (float value : result)
```

表示依次取出 `result` 的每个元素，并把当前复制品命名为 `value`。对于只输出的 `float`，按值写法简单且足够。

## 八、Host Memory 与 Device Memory

CPU 端的：

```cpp
std::vector<float> a = {1.0f, 2.0f, 3.0f};
a.data();
```

位于 Host Memory。普通独立显卡上的 Kernel 通常需要使用 Device Memory，不能把普通 CPU 指针直接当作设备指针使用。

在 GPU 上申请空间：

```cpp
float* device_a = nullptr;
std::size_t bytes = n * sizeof(float);
cudaMalloc(&device_a, bytes);
```

`cudaMalloc` 的大小单位是字节。10 个 `float` 通常需要：

```text
10 * 4 = 40字节
```

`cudaMalloc` 需要修改 `device_a` 保存的地址，所以传入 `&device_a`。

把输入从 CPU 复制到 GPU：

```cpp
cudaMemcpy(
    device_a,
    a.data(),
    bytes,
    cudaMemcpyHostToDevice
);
```

四个参数依次是：目标地址、来源地址、字节数、复制方向。

## 九、尚未完成

以下内容进入 Day 6，不能标记为已经掌握：

- DeviceToHost 结果复制；
- `cudaFree` 的完整资源生命周期；
- `cudaGetLastError()` 与同步错误检查；
- 完整 CUDA Vector Add 主机端代码；
- CPU 与 GPU 逐元素结果验证；
- 空输入、单元素、负数、小数、非整块长度和较大向量测试；
- CUDA Event 性能计时。

## 十、Day 5 结论

Day 5 完成了从 CPU 程序进入 CUDA 编程模型的关键跨越：环境已经可用，最小 Kernel 已实际运行，能够计算一维全局线程索引，并开始理解 Host/Device 两套内存空间。

下一步不是进入高级性能优化，而是先把一次完整 CUDA 程序的生命周期写对、检查对、验证对。

