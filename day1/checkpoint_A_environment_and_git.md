# Day 1 - 检查点 A：环境与 Git

## 1. 开发工具的区别

- **VS Code**：主要用于编辑代码；安装扩展并配置编译器、调试器后，可以作为开发环境使用。
- **编辑器**：负责创建和修改源代码文本。
- **编译器**：检查 C++ 代码，并把它转换成 CPU 可以执行的机器指令。
- **Git**：版本控制工具，负责记录、比较和管理代码版本。
- **GitHub**：在线托管 Git 仓库的平台，用于备份、展示和协作。

## 2. 一条 C++ 程序的基本过程

```text
.cpp 源文件 → C++ 编译器 → .exe 可执行文件 → 操作系统加载 → CPU 执行
```

示例：

```powershell
g++ "01 hello.cpp" -o hello.exe
.\hello.exe
```

- `g++`：运行 C++ 编译器。
- `"01 hello.cpp"`：输入的源文件；文件名含空格，所以使用双引号。
- `-o`：指定输出文件名的选项。
- `hello.exe`：生成的可执行文件。
- `.\hello.exe`：运行当前目录中的程序。

## 3. 命令的组成

命令通常由空格分隔：

```text
程序名  选项  参数
```

例如：

```powershell
g++ --version
```

- `g++`：程序名。
- 空格：分隔程序名和参数。
- `--version`：显示版本信息的长选项。
- `--完整单词` 通常是长选项，`-单个字母` 通常是短选项。

## 4. 目录与分支

- `cd`：切换终端当前所在的文件夹，路径会改变。
- `git switch`：切换同一个仓库中的 Git 分支，路径通常不变，但工作区文件可能改变。

```powershell
cd cpp
git switch main
```

分支可以理解为同一个项目的一份独立开发进度。开发分支中的文件没有被删除；切换到尚未包含相应提交的 `main` 时，只是暂时看不到。

## 5. 本地仓库与远程仓库

```text
本地仓库：位于自己的电脑，由 Git 管理
远程仓库：位于 GitHub 等平台，用于同步、展示和协作
```

Git 不只能连接 GitHub，也可以使用 GitLab、Gitee、公司服务器或其他 Git 仓库。

Git 由 Linus Torvalds 创建，GitHub 是后来建立的 Git 托管平台；Git 不是 GitHub 发明的。

## 6. clone、commit 与 push

```text
git clone：远程仓库 → 本地仓库
git commit：把暂存的改动记录到本地 Git 历史
git push：把本地提交上传到远程仓库
```

`git clone` 得到的不只是当前文件，还包括提交历史、分支信息、Git 管理数据和远程地址。

`Ctrl+S` 只是保存文件，不等于 `git commit`；`git commit` 也不等于 `git push`。

## 7. Day 1 分支

```powershell
git switch -c day01-cpp-vector-ops
```

- `switch`：切换分支。
- `-c`：创建新分支。
- `day01-cpp-vector-ops`：分支名称，表示“第 1 天的 C++ 向量算子学习”。

当前分支检查：

```powershell
git branch
git status
```

`git branch` 输出中的 `*` 表示当前分支。

## 8. 远程仓库

```powershell
git remote -v
```

- `origin`：克隆仓库时建立的远程仓库默认简称。
- `-v`：显示更详细的信息，包括获取和推送地址。

本地创建的分支不会自动出现在 GitHub，需要主动推送：

```powershell
git push -u origin day01-cpp-vector-ops
```

- `push`：推送本地提交。
- `-u`：建立本地分支与远程分支的默认跟踪关系。
- `origin`：远程仓库简称。
- `day01-cpp-vector-ops`：要推送的分支。

## 9. 当前阶段结论

我已经能够：

- 区分 VS Code、编译器、Git 和 GitHub。
- 在终端中切换目录并编译、运行简单 C++ 程序。
- 理解本地仓库和远程仓库的区别。
- 理解分支是一份独立开发进度，而不是新文件夹。
- 创建和检查 Day 1 学习分支。
- 区分 `clone`、`commit` 和 `push`。
