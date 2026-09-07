# cuda-kernel-lab-from0to1
CUDA kernel learning and optimization lab

## Project layout

```text
dayN/
├── plan_dayN.md
├── summary_dayN.md
├── review_dayN.md
└── src/
    └── exercise.cpp

build/dayN/   compiled programs, ignored by Git
resources/    local reference material; PDFs are ignored by Git
```

C++ source files and Markdown learning notes are committed to Git. Generated executables and local textbook PDFs remain on the local machine.

Example compilation:

```powershell
g++ -std=c++17 -Wall -Wextra -O0 day4/src/example.cpp -o build/day4/example.exe
```
