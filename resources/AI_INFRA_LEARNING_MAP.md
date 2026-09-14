# AI Infra 学习资源、知识地图与实习路线

整理日期：2026-09-15

## 一、我的问题与目标

我对未来的 AI Infra 学习有些迷茫，特别是知识体系与概念。我仍然记得最初的目标是寻找相关实习岗位。我阅读了一些网络上的 CUDA 学习路线，也收集了碎片化的 GitHub 仓库、个人博客、课程和书籍。

希望基于这些资料：

1. 建立 AI Infra 的整体知识体系；
2. 理解 CUDA、算子、编译器、推理系统和分布式系统之间的关系；
3. 获得适合当前基础、面向实习的学习路线；
4. 逐渐理解行业中的专业概念；
5. 避免被高级岗位中的大量名词打乱学习节奏。

当前情况：

- 正在从 C++ 基础进入 CUDA；
- 已学习变量、函数、循环、`std::vector`、引用、指针和 CPU Vector Add；
- 已配置 WSL、CUDA Toolkit 与 VS Code；
- 已运行第一个 CUDA Kernel；
- 正在学习 Thread、Block、全局线程索引以及 Host/Device 内存；
- 当前 GPU 为 NVIDIA GeForce GTX 1650 Ti；
- 当前近期目标是完成完整 CUDA Vector Add；
- 长期目标是获得 AI Infra / CUDA 相关实习能力。

## 二、本地书籍

### 1. 当前 CUDA 入门主教材

- `CUDA 编程：基础与实践_樊哲勇.pdf`

建议当前重点阅读：

```text
第2章 CUDA中的线程组织
第3章 简单CUDA程序的基本框架
第4章 CUDA程序的错误检测
第5章 获得GPU加速的关键
```

这本书从线程组织、基本程序框架、错误检测、计时和内存组织逐步推进，与当前水平最匹配。

### 2. CUDA 与并行算法第二主教材

- `大规模并行处理器程序设计（原书第4版）_胡文美（Wen-mei W. Hwu），大卫·B.柯克（David B. Kirk），伊扎特·埃尔·哈吉（Izzat El Hajj）_9787111772767.pdf`
- `programming-massively-parallel-processors-a-hands-on-approach-4th-edition.pdf`

以上两份分别为中文和英文版本，不需要同时逐页阅读。当前对应第2章：

```text
异构数据并行计算
CUDA C程序结构
向量加法Kernel
设备全局内存与数据传输
Kernel与线程
调用Kernel
编译
```

完成 CUDA 基础后重点阅读第3～6章，学习多维网格、GPU 架构、调度、内存层次、数据局部性和性能。

### 3. C++ 查缺补漏教材

- `Accelerated_Cpp_Chinese.pdf`

不暂停 CUDA 从头通读。遇到类型、函数、引用、容器、迭代器、指针、内存管理和工程结构问题时按需查阅。

## 三、网络资源清单

### 官方文档与课程

- NVIDIA CUDA 官方文档：https://docs.nvidia.com/cuda/
- Modern GPU Programming for MLSys（中文）：https://mlc.ai/modern-gpu-programming-for-mlsys/zh/index.html
- GPU Mode Lectures：https://github.com/gpu-mode/lectures
- GPU Mode YouTube：https://www.youtube.com/@GPUMODE/videos
- Bilibili 视频系列：https://space.bilibili.com/218427631/lists/4695308?type=series
- CUDA 相关参考书 PDF：https://www.cse.iitd.ac.in/~rijurekha/col851/necessary_reading/cudabook.pdf

### GEMM、Tensor Core 与高性能 Kernel

- How To Write A Fast Matrix Multiplication From Scratch With Tensor Cores：
  https://alexarmbr.github.io/2024/08/10/How-To-Write-A-Fast-Matrix-Multiplication-From-Scratch-With-Tensor-Cores.html#introduction
- Matrix Multiplication on NVIDIA Blackwell：
  https://www.modular.com/blog/matrix-multiplication-on-nvidias-blackwell-part-1-introduction
- Implementing a Fast Tensor Core Matmul on Ada：
  https://www.spatters.ca/mma-matmul
- Outperforming cuBLAS on H100：
  https://cudaforfun.substack.com/p/outperforming-cublas-on-h100-a-worklog
- Optimising GEMM on NVIDIA H100：
  https://hamzaelshafie.bearblog.dev/worklog-optimising-gemm-on-nvidia-h100-for-cublas-like-performance-wip/
- Inside NVIDIA GPUs: High Performance Matmul Kernels：
  https://www.aleksagordic.com/blog/matmul#cpt1

### FlashAttention 与推理系统

- Flash Attention From Scratch：https://lubits.ch/flash/
- FlashAttention on RTX 5090：https://gau-nernst.github.io/fa-5090/
- vLLM Implementation Details：https://blog.scatterlab.co.kr/vllm-implementation-details/

### 补充 PDF

- Generative AI C++：https://www.aussieai.com/pdf/BOOK-Generative-AI-CPP-Spuler-2024.pdf
- C++ Low Latency：https://www.aussieai.com/pdf/CPP-Low%20Latency-Spuler-2025.pdf
- CUDA C++ Optimization：https://www.aussieai.com/pdf/CUDA-CPP-Optimization-Book-Spuler-2024.pdf
- CUDA C++ Debugging：https://www.aussieai.com/pdf/CUDA-CPP-Debugginb-Book-Spuler-2024.pdf

## 四、对这批资料的总体判断

这些资料质量总体较高，但至少一半属于高级 Kernel 工程内容。现在直接学习 H100、RTX 5090、Blackwell、Tensor Core GEMM 或 FlashAttention，容易出现“见过很多名词，但还不能独立写完整 CUDA 程序”的情况。

学习方向没有选错，关键是重新排序：

```text
先成为能独立写对CUDA程序的人
→ 再成为能测量、解释并优化Kernel的人
→ 最后形成真实AI Infra工程能力
```

## 五、资料的学习层级

### 第一层：现在学习

- 《CUDA 编程：基础与实践》第2～5章；
- 《大规模并行处理器程序设计》第2章；
- NVIDIA 文档中当前正在使用的 CUDA API；
- CUDA Vector Add、错误检查、内存复制和结果验证。

当前主线：

```text
CPU准备数据
→ cudaMalloc申请GPU内存
→ cudaMemcpy复制到GPU
→ 启动Kernel
→ 同步并检查错误
→ 复制结果回CPU
→ 与CPU结果比较
→ cudaFree释放GPU内存
```

### 第二层：完成基础 CUDA 后学习

- Warp 与 SIMT；
- 全局内存合并访问；
- Shared Memory；
- `__syncthreads()`；
- Occupancy；
- 分支发散；
- Reduction；
- 矩阵转置；
- 普通 CUDA Core GEMM；
- CUDA Event 与 Nsight。

主要对应：

```text
《CUDA编程：基础与实践》第6～10章
《大规模并行处理器程序设计》第3～6章、第10章
GPU Mode的基础课程
```

### 第三层：高性能 GEMM 专题

相关资料涉及：

```text
分层Tiling
寄存器分块
共享内存分块
向量化读写
Bank Conflict
Double Buffering
Tensor Core
MMA / WMMA
PTX
Roofline
流水线
Warp Specialization
```

应当在完成普通矩阵乘法、共享内存 GEMM 和基础性能分析后再精读。

这批文章分别面向 T4、Ada、H100、RTX 5090 或 Blackwell。GTX 1650 Ti 足以练习基础 CUDA、内存访问、Reduction、转置和普通矩阵乘法，但不能假定高级架构指令和示例可以原样运行。

### 第四层：FlashAttention 与推理系统

FlashAttention 组合了：

```text
矩阵乘法
+ Softmax
+ 分块
+ 数据复用
+ 数值稳定性
+ 在线归一化
+ Kernel融合
```

vLLM 则进入推理系统层，关注：

```text
请求调度
KV Cache
PagedAttention
Continuous Batching
GPU任务调度
张量并行
吞吐与延迟
```

这部分应在掌握基础算子并了解 Transformer 推理后学习。

### 第五层：Blackwell 与编译器 DSL

Modern GPU Programming for MLSys 主要围绕：

- Blackwell GPU；
- TIRx Python DSL；
- TMA；
- TMEM；
- `tcgen05.mma`；
- Warp Specialization；
- CTA Cluster；
- SOTA GEMM；
- FlashAttention 4。

其中部分示例要求 Blackwell `sm_100a`（例如 B200）。当前可以浏览“GPU执行模型”建立远景，但暂时不安装 TIRx，也不把 TMA、TMEM 和 `tcgen05` 加入当前学习任务。

## 六、AI Infra 的分层知识体系

```text
6. 大规模集群与分布式系统
   NCCL、RDMA、TP、PP、DP、EP

5. 训练框架与推理系统
   PyTorch、vLLM、SGLang、Megatron、DeepSpeed

4. ML编译器与Kernel DSL
   Triton、TileLang、TVM、MLIR、LLVM

3. 高性能算子与算法
   GEMM、Reduction、Softmax、LayerNorm、Attention

2. GPU编程模型与性能
   CUDA、Thread、Warp、Memory、Synchronization、Profiling

1. 系统与编程基础
   C++、Python、Linux/Bash、Git、CMake、数据结构
```

当前处在第1层到第2层的交界处。

高级 AI Infra 岗位往往横跨第2～6层，这是团队级、高阶能力集合，不应逐条当作 CUDA 初学者的入门清单。

## 七、专业概念词典

### Tiling

把大问题切成小块，使数据能够进入更快、更小的内存并被重复利用：

```text
大矩阵
→ Thread Block负责一个Tile
→ Warp负责更小的Tile
→ 每个线程负责更小的一组元素
```

### Memory Wall

现代处理器的计算能力增长得比内存传输能力快。很多程序不是算得慢，而是数据无法及时送到计算单元。

### Arithmetic Intensity

```text
算术强度 = FLOP数量 / 数据搬运字节数
```

Vector Add 算术强度低，通常受显存带宽限制；GEMM 可以通过数据复用获得高算术强度。

### Memory-bound 与 Compute-bound

- Memory-bound：主要时间花在搬运数据；
- Compute-bound：主要时间花在执行计算。

优化前要先确认瓶颈类型。

### Roofline Model

使用峰值计算吞吐和内存带宽估计性能上限：

```text
可达到的性能
= min(峰值计算能力, 内存带宽 × 算术强度)
```

### GEMM

通用矩阵乘法：

```text
D = αAB + βC
```

它是线性层、Attention 和大量深度学习计算的基础。

### Tensor Core 与 MMA

Tensor Core 是执行小块矩阵乘加的专用硬件。MMA 表示 Matrix Multiply-Accumulate：

```text
D = A × B + C
```

### cuBLAS

NVIDIA 提供的高性能线性代数库。学习时自己写 GEMM 是为了理解原理，实际工程通常优先使用成熟库。

### FlashAttention

不改变 Attention 的数学定义，而是重组计算和内存访问，避免将大型中间矩阵反复写入和读出显存。

### PagedAttention

借鉴操作系统分页思想管理 KV Cache，减少显存碎片和浪费，是 vLLM 的代表性设计之一。

### DSL

Domain-Specific Language，领域专用语言。Triton、TileLang 和 TIRx 使用更高层的表示描述 GPU Kernel，再由编译器生成底层代码。

## 八、面向实习的阶段路线

### 阶段 A：当前至未来约3周

- 完成 CUDA Vector Add；
- 掌握 `cudaMalloc`、`cudaMemcpy`、`cudaFree`；
- 建立 CUDA 错误检查；
- 使用 CPU 结果验证 GPU；
- 学习 CUDA Event 计时；
- 实现 Vector Scale、SAXPY、ReLU。

### 阶段 B：约第4～8周

- 二维 Grid/Block；
- 图像和矩阵操作；
- Naive GEMM；
- Shared Memory；
- Tiled GEMM；
- Matrix Transpose；
- Reduction；
- Nsight Systems/Compute。

### 阶段 C：约第9～14周

- PyTorch 基础；
- Softmax 和 LayerNorm；
- PyTorch CUDA Extension；
- 与 PyTorch 结果对比；
- Benchmark；
- Roofline 与瓶颈分析；
- 阅读一个中等难度 GPU Mode 课程。

### 阶段 D：约第15～24周

根据兴趣选择一条主线：

```text
算子路线：
GEMM → Tensor Core → CUTLASS/Triton → FlashAttention

推理路线：
Transformer推理 → KV Cache → PagedAttention
→ Continuous Batching → 阅读vLLM
```

另一条路线先建立概念，不同时深入。

## 九、面向实习的项目仓库

目标项目结构：

```text
cuda-kernel-lab-from0to1
├── Vector Add
├── SAXPY / ReLU
├── Reduction
├── Matrix Transpose
├── Naive GEMM
├── Shared-memory GEMM
├── Softmax或LayerNorm
└── PyTorch CUDA Extension
```

每个算子至少包含：

- CPU 参考实现；
- CUDA 实现；
- 边界测试；
- 错误检查；
- 性能测量；
- 优化前后对比；
- README 原理说明。

一个可复现、有测试和性能数据的项目，比只听说过大量术语更能证明实习能力。

## 十、最终阅读建议

### 现在精读

1. 《CUDA编程：基础与实践》第2～4章；
2. 《大规模并行处理器程序设计》第2章；
3. NVIDIA 文档中当前正在使用的 API。

### 现在只浏览概念

1. MLC 的 GPU 执行模型；
2. GPU Mode 入门视频；
3. GEMM 文章中的 Memory Wall、Roofline 与 Tiling。

### 暂缓动手

1. H100、RTX 5090 和 Blackwell GEMM；
2. Tensor Core PTX；
3. FlashAttention CUDA 实现；
4. TIRx、TMEM、TMA；
5. vLLM 源码级分析；
6. RDMA 与 NCCL 底层实现。

这些资料不是被丢弃，而是放到具备相应前置能力后再学习。近期最重要的里程碑仍然是：

> 不看参考代码，独立完成带内存分配、数据复制、Kernel、错误检查、结果验证和资源释放的 CUDA Vector Add。

