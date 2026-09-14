# Day 5 - 回忆提纲

日期：2026-09-15

## 1. 环境与工具

- Windows 提供宿主系统，WSL 运行 Linux 环境，Ubuntu 是当前 Linux 发行版。
- Bash 接收命令；`g++` 编译 C++；`nvcc` 编译 CUDA。
- `-o` 指定输出文件；编译和运行是两个阶段。
- VS Code Task 是对实际编译和运行命令的自动化。

## 2. Kernel

- Kernel 由 CPU 启动，在 GPU 上执行。
- `__global__` 用于声明可从 Host 启动的 GPU Kernel。
- `kernel<<<blocks, threads_per_block>>>()` 配置执行规模。
- Kernel 启动后需要在合适位置同步和检查错误。

## 3. 线程索引

- `threadIdx.x`：块内线程编号。
- `blockIdx.x`：线程块编号。
- `blockDim.x`：每块线程数。
- `i = blockIdx.x * blockDim.x + threadIdx.x`。
- 总线程数为 `blocks * threads_per_block`，编号从 0 开始。
- `if (i < n)` 防止多余线程越界。

## 4. CPU 与 GPU 的任务映射

- CPU Vector Add：一个循环依次处理所有 `i`。
- CUDA Vector Add：每个线程处理一个 `i`。
- 数学公式相同，任务分配方法不同。

## 5. Host 与 Device 内存

- `vector.data()` 是 Host 端连续元素指针，不复制数据。
- Device Memory 需要通过 `cudaMalloc` 申请。
- `bytes = n * sizeof(float)`。
- `cudaMalloc(&device_pointer, bytes)` 修改设备指针保存的地址。
- `cudaMemcpyHostToDevice` 表示 CPU 到 GPU。
- 结果返回应使用 `cudaMemcpyDeviceToHost`，Day 6 继续验证。

## 6. 范围 `for`

- `for (float value : result)`：复制当前元素。
- `for (float& value : result)`：引用并可修改原元素。
- `for (const float& value : result)`：只读引用。
- 冒号可读作“遍历 result 中的元素”。

## 7. 尚未完成

- 完整 CUDA Vector Add；
- DeviceToHost；
- 完整错误检查；
- CPU/GPU 对照验证；
- 边界测试；
- CUDA Event 计时。

## 8. 闭卷自测

1. Kernel 由谁启动，在哪里执行？
2. `<<<3, 4>>>` 创建几个线程，索引范围是什么？
3. 为什么 Block 内线程编号会重复，但全局索引不会？
4. 为什么总线程数可以超过 `n`？
5. `cudaMalloc` 为什么接收 `&device_pointer`？
6. 10 个 `float` 通常需要申请多少字节？
7. HostToDevice 与 DeviceToHost 的目标和来源分别是什么？
8. 为什么普通 `vector.data()` 不能直接作为独立显卡的设备内存使用？
9. CUDA Vector Add 的完整数据流是什么？

