# Day 6：完成可验证的 CUDA Vector Add

日期：下一次学习日  
预计用时：必做约 4～6 小时  
学习原则：一次只增加一个 CUDA 步骤；先保证正确，再讨论性能

## 一、Day 6 起点

已经具备：

- CUDA 环境与 `nvcc` 可用；
- 最小 Kernel 已实际运行；
- 理解 Grid、Block、Thread；
- 会计算一维全局线程索引；
- 理解 `if (i < n)` 的边界作用；
- 理解 Host/Device Memory 的基本区别；
- 初步认识 `cudaMalloc` 和 HostToDevice `cudaMemcpy`。

尚未完成：

- 结果从 GPU 返回 CPU；
- 设备资源释放；
- 完整错误检查；
- 完整 CUDA Vector Add；
- CPU/GPU 对照测试。

## 二、今日必做目标

1. 闭卷复习 Day 5 核心概念。
2. 掌握 `cudaMalloc`、两种 `cudaMemcpy` 方向和 `cudaFree`。
3. 理解 CUDA API 返回的 `cudaError_t`。
4. 为最小 Kernel 加启动与同步错误检查。
5. 创建并运行完整 CUDA Vector Add。
6. 使用 CPU 参考结果逐元素验证 GPU 结果。
7. 完成正常输入和边界输入测试。
8. 能独立口述完整 Host/Device 数据流。

## 三、结束标准

- [ ] 能解释 `cudaMalloc(&p, bytes)` 每个参数。
- [ ] 能区分 HostToDevice 和 DeviceToHost。
- [ ] 能解释为什么 `cudaFree` 必须与 `cudaMalloc` 配对。
- [ ] 能检查每个 CUDA Runtime API 的返回值。
- [ ] 能区分 Kernel 启动错误和执行错误。
- [ ] 能独立写出 Vector Add Kernel。
- [ ] 能正确计算向上取整的 Block 数量。
- [ ] 能处理 `n=0`，不启动无意义的 Kernel。
- [ ] CPU 与 GPU 结果逐元素一致。
- [ ] 至少完成六类测试。
- [ ] 能用自己的话讲出完整数据流。

## 四、阶段 A：闭卷热身（20～30分钟）

不看总结回答：

1. `__global__` 表示什么？
2. `kernel<<<3, 4>>>()` 启动多少线程？
3. 写出一维全局线程索引公式。
4. 为什么需要 `if (i < n)`？
5. `vector.data()` 返回什么？
6. 10 个 `float` 需要多少字节？
7. `cudaMalloc` 操作哪一侧内存？
8. HostToDevice 表示什么方向？

完成后再对照 `day5/review_day05.md`。

## 五、阶段 B：补齐设备内存生命周期（40～60分钟）

按顺序学习：

```text
声明设备指针
→ 计算字节数
→ cudaMalloc
→ HostToDevice cudaMemcpy
→ Kernel使用设备指针
→ DeviceToHost cudaMemcpy
→ cudaFree
```

需要解释：

- 为什么输出空间也需要 `cudaMalloc`；
- 为什么 Kernel 前不必把空的输出向量复制到 GPU；
- DeviceToHost 时哪个地址是目标、哪个是来源；
- 释放设备内存后为什么不能继续解引用旧设备指针；
- 哪些失败路径也必须释放已经申请的资源。

建议教材：

```text
《CUDA编程：基础与实践》第3章
《大规模并行处理器程序设计》第2.4节
```

## 六、阶段 C：CUDA 错误检查（40～50分钟）

认识：

```cpp
cudaError_t
cudaSuccess
cudaGetErrorString(error)
cudaGetLastError()
cudaDeviceSynchronize()
```

区分：

```text
cudaGetLastError     -> 检查Kernel启动是否有效
cudaDeviceSynchronize -> 等待Kernel并暴露执行阶段错误
```

先为 `day5/src/11_first_kernel.cu` 增加清晰错误信息，再进入 Vector Add。

建议教材：

```text
《CUDA编程：基础与实践》第4章
```

## 七、阶段 D：编写 CUDA Vector Add（90～120分钟）

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
5. 计算 `bytes`；
6. 申请三个设备数组；
7. 复制两个输入到 GPU；
8. 计算 Block 数量；
9. 启动 Kernel；
10. 检查启动错误；
11. 同步并检查执行错误；
12. 把结果复制回 CPU；
13. 释放设备内存；
14. 逐元素比较 CPU/GPU 结果。

线程配置先使用：

```cpp
int threads_per_block = 256;
int blocks = (n + threads_per_block - 1) / threads_per_block;
```

必须先用小数值手算向上取整，再运行代码。

## 八、阶段 E：正确性测试（60～75分钟）

最低测试：

```text
1. {1,2,3} + {4,5,6} -> {5,7,9}
2. 单元素
3. 空输入
4. 包含负数和小数
5. 元素数不是Block大小的整数倍
6. 较大向量
7. 长度不一致（错误路径）
```

验证要求：

- 不能只打印 GPU 结果；
- 为每个元素计算 CPU 参考值；
- 逐元素比较；
- 任一失败时输出下标、期望值和实际值；
- 测试失败时程序返回非零状态。

## 九、阶段 F：可选性能入门（30～45分钟）

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
Kernel时间
HostToDevice时间
DeviceToHost时间
端到端总时间
```

不要因为小向量 GPU 更慢就断言 CUDA 无效；需要考虑启动和传输开销。

## 十、今天暂不进入

- Shared Memory；
- Warp 内函数；
- Reduction；
- Tensor Core；
- GEMM 优化；
- FlashAttention；
- Triton、TileLang、TIRx；
- NCCL 与 RDMA。

这些内容已经进入长期 AI Infra 路线，但不是 Day 6 的当前任务。

## 十一、结束整理

完成后创建：

```text
day6/summary_day06.md
day6/review_day06.md
day7/plan_day07.md
```

总结只记录实际完成内容。若 Vector Add 尚未通过 CPU 对照测试，不能写成已经掌握。

