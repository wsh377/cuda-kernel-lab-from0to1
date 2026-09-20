# Day 6：从整体地图到可验证的 CUDA Vector Add

日期：2026-09-21 起

预计用时：必做约 6～8 小时，可拆成 2 个学习日

学习原则：以教材建立整体结构，以小任务立即验证；一次只增加一个 CUDA 步骤；先保证正确，再讨论性能

## 一、Day 6 起点

已经具备：

- CUDA 环境与 `nvcc` 可用；
- 最小 Kernel 已实际运行；
- 初步认识 Grid、Block、Thread 和一维全局线程索引；
- 理解 `if (i < n)` 用于防止越界；
- 学过变量、函数、循环、`std::vector`、引用和指针的基础用法；
- 完成过 CPU Vector Add。

当前需要按新知识学习，而不是当作已经掌握：

- 异构计算、数据并行以及 CPU/GPU 分工的整体图景；
- Host Memory 与 Device Memory 的区别；
- `cudaMalloc`、两种方向的 `cudaMemcpy` 和 `cudaFree`；
- 结果从 GPU 返回 CPU；
- CUDA API、Kernel 启动和执行阶段的错误检查；
- 完整 CUDA Vector Add；
- CPU/GPU 对照测试。

当前没有系统学习过计算机组成原理、数据结构或 GPU 架构。Day 6 不要求先补完这些课程，只学习完成当前程序必需的概念；GPU 架构将在后续结合教材第 4 章系统学习。

## 二、配套主教材与阅读方法

主教材：

```text
resources/大规模并行处理器程序设计（原书第4版）_胡文美（Wen-mei W. Hwu），大卫·B.柯克（David B. Kirk），伊扎特·埃尔·哈吉（Izzat El Hajj）_9787111772767.pdf
```

本计划中的“书本页码”指页面底部印刷的页码，不是 PDF 阅读器显示的文件页码。

| 内容 | 书本页码 | PDF 页码 | 阅读方式 | 对应任务 |
| --- | ---: | ---: | --- | --- |
| 第 1 章 导论 | 1～12 | 30～41 | 浏览，理解整体地图 | 为什么需要并行与异构计算 |
| 2.1 数据并行性 | 14～16 | 43～45 | 认真阅读 | 为什么 Vector Add 可并行 |
| 2.2 CUDA C 程序结构 | 16～17 | 45～46 | 认真阅读 | Host、Device、Kernel 的分工 |
| 2.3 向量加法核 | 17～19 | 46～48 | 认真阅读 | CPU Vector Add 到 CUDA 的映射 |
| 2.4 设备全局存储和数据传输 | 19～22 | 48～51 | 精读并同步编码 | `cudaMalloc`、`cudaMemcpy`、`cudaFree` |
| 2.5 核函数和线程 | 22～25 | 51～54 | 复习并手算 | 线程索引和边界判断 |
| 2.6 调用核函数 | 25～27 | 54～56 | 精读并同步编码 | 启动配置和完整 Vector Add |

阅读规则：

1. 第 1 章读懂六七成即可，不因陌生名词中断主线。
2. 每小节读完后，用自己的话说出一句核心结论。
3. 2.4～2.6 必须边读边写，不能只阅读示例代码。
4. 教材示例用于理解结构；实际程序补上 `n == 0`、完整错误检查和更严格测试。
5. 暂不提前阅读第 4～6 章；完成正确程序后再学习 GPU 架构与性能。

## 三、今日必做目标

1. 通过教材第 1 章和 2.1～2.3 建立 CUDA 程序的整体地图。
2. 能解释数据并行、Host、Device、Kernel 之间的关系。
3. 掌握 `cudaMalloc`、两种 `cudaMemcpy` 方向和 `cudaFree`。
4. 理解 CUDA API 返回的 `cudaError_t`。
5. 为最小 Kernel 加启动与同步错误检查。
6. 创建并运行完整 CUDA Vector Add。
7. 使用 CPU 参考结果逐元素验证 GPU 结果。
8. 完成正常输入和边界输入测试。
9. 能独立口述完整 Host/Device 数据流。

## 四、结束标准

- [ ] 能用自己的话解释为什么 Vector Add 具有数据并行性。
- [ ] 能说明 CPU 主机代码和 GPU Kernel 分别负责什么。
- [ ] 能解释 `cudaMalloc(&p, bytes)` 每个参数。
- [ ] 能区分 HostToDevice 和 DeviceToHost。
- [ ] 能解释为什么 `cudaFree` 必须与 `cudaMalloc` 配对。
- [ ] 能检查每个 CUDA Runtime API 的返回值。
- [ ] 能区分 Kernel 启动错误和执行错误。
- [ ] 能独立写出 Vector Add Kernel。
- [ ] 能正确计算向上取整的 Block 数量。
- [ ] 能处理 `n == 0`，不启动零个 Block。
- [ ] CPU 与 GPU 结果逐元素一致。
- [ ] 至少完成七类测试。
- [ ] 能用自己的话讲出完整数据流。

## 五、阶段 A：建立整体地图（60～90 分钟）

阅读：

```text
第 1 章：书本第 1～12 页（PDF 第 30～41 页）
第 2 章 2.1～2.3：书本第 14～19 页（PDF 第 43～48 页）
```

阅读后不看书回答：

1. 什么是异构计算？
2. 为什么 CPU 与 GPU 要分工？
3. 什么是数据并行性？
4. 为什么向量加法适合交给大量线程？
5. Host、Device 和 Kernel 分别是什么？
6. CUDA 程序为什么同时包含主机代码和设备代码？
7. CPU Vector Add 中的一次循环迭代如何映射到一个 GPU 线程？

本阶段只建立整体结构，不要求记忆 GPU 微架构名词。

## 六、阶段 B：回忆已有 CUDA 基础（15～25 分钟）

先回答，再对照 `day5/review_day05.md` 和教材 2.5～2.6：

1. `__global__` 表示什么？
2. `kernel<<<3, 4>>>()` 启动多少线程？
3. 写出一维全局线程索引公式。
4. 为什么需要 `if (i < n)`？
5. `vector.data()` 返回什么？
6. 10 个 `float` 通常需要多少字节？

本阶段不再把 `cudaMalloc` 和 `cudaMemcpy` 当作闭卷复习题，它们属于下一阶段的新课。

## 七、阶段 C：设备内存生命周期（60～90 分钟）

精读教材 2.4：书本第 19～22 页（PDF 第 48～51 页），重点看图 2.8。

按顺序学习并逐步写代码：

```text
声明设备指针
→ 计算字节数
→ cudaMalloc
→ HostToDevice cudaMemcpy
→ Kernel 使用设备指针
→ DeviceToHost cudaMemcpy
→ cudaFree
```

需要解释：

- 为什么输出空间也需要 `cudaMalloc`；
- 为什么 Kernel 前不必把空的输出向量复制到 GPU；
- `cudaMemcpy` 的参数顺序为什么是目标、来源、字节数、方向；
- DeviceToHost 时哪个地址是目标、哪个是来源；
- 释放设备内存后为什么不能继续使用旧设备指针；
- 哪些失败路径也必须释放已经申请的资源。

辅助教材：

```text
《CUDA编程：基础与实践》第3章
```

## 八、阶段 D：CUDA 错误检查（40～50 分钟）

先阅读教材第 2 章第 22 页的“CUDA 中的错误检测与处理”方框，再认识：

```cpp
cudaError_t
cudaSuccess
cudaGetErrorString(error)
cudaGetLastError()
cudaDeviceSynchronize()
```

区分：

```text
cudaGetLastError       -> 检查 Kernel 启动配置等启动阶段错误
cudaDeviceSynchronize -> 等待 Kernel，并暴露执行阶段错误
```

教材为了简洁省略了部分错误检查，实际代码必须检查每个 CUDA Runtime API。先为 `day5/src/11_first_kernel.cu` 增加清晰错误信息，再进入 Vector Add。

辅助教材：

```text
《CUDA编程：基础与实践》第4章
```

## 九、阶段 E：编写 CUDA Vector Add（90～120 分钟）

精读教材 2.5～2.6：书本第 22～27 页（PDF 第 51～56 页），重点看图 2.10 和图 2.13。

创建：

```text
day6/src/13_vector_add_cuda.cu
```

Kernel 接口：

```cpp
__global__ void vector_add_kernel(
    const float* a,
    const float* b,
    float* output,
    int n)
```

先独立完成 Kernel，再逐步完成 Host 端：

1. 创建输入向量；
2. 检查长度；
3. 创建 CPU 参考结果；
4. 调整输出向量长度；
5. 对 `n == 0` 提前返回；
6. 计算 `bytes`；
7. 申请三个设备数组；
8. 复制两个输入到 GPU；
9. 计算 Block 数量；
10. 启动 Kernel；
11. 检查启动错误；
12. 同步并检查执行错误；
13. 把结果复制回 CPU；
14. 释放设备内存；
15. 逐元素比较 CPU/GPU 结果。

线程配置先使用：

```cpp
int threads_per_block = 256;
int blocks = (n + threads_per_block - 1) / threads_per_block;
```

教材使用 `ceil(n / 256.0)` 讲解向上取整；实际练习使用上面的整数公式。必须先用小数值手算，再运行代码。

## 十、阶段 F：正确性测试（60～75 分钟）

最低测试：

```text
1. {1,2,3} + {4,5,6} -> {5,7,9}
2. 单元素
3. 空输入
4. 包含负数和小数
5. 元素数不是 Block 大小的整数倍
6. 较大向量
7. 长度不一致（错误路径）
```

验证要求：

- 不能只打印 GPU 结果；
- 为每个元素计算 CPU 参考值；
- 逐元素比较；
- 任一失败时输出下标、期望值和实际值；
- 测试失败时程序返回非零状态。

## 十一、阶段 G：可选性能入门（30～45 分钟）

只有正确性测试全部通过后，才学习 CUDA Event：

```cpp
cudaEventCreate
cudaEventRecord
cudaEventSynchronize
cudaEventElapsedTime
cudaEventDestroy
```

先区分：

```text
Kernel 时间
HostToDevice 时间
DeviceToHost 时间
端到端总时间
```

不要因为小向量 GPU 更慢就断言 CUDA 无效；需要考虑启动和传输开销。

## 十二、今天暂不进入

- 第 4 章 GPU 架构和调度；
- Shared Memory；
- Warp 内函数；
- Reduction；
- Tensor Core；
- GEMM 优化；
- FlashAttention；
- Triton、TileLang、TIRx；
- NCCL 与 RDMA。

这些内容属于长期 AI Infra 路线，但不是 Day 6 的当前任务。完成 Vector Add 后，再按教材顺序进入二维网格、GPU 架构、内存层次和 GEMM。

## 十三、结束整理

完成后创建：

```text
day6/summary_day06.md
day6/review_day06.md
day7/plan_day07.md
```

总结只记录实际完成内容。若 Vector Add 尚未通过 CPU 对照测试，不能写成已经掌握。
