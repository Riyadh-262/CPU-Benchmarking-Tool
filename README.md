# CPU Benchmarking Tool

A C-based CPU benchmarking tool designed to evaluate different aspects of computer performance, including processor computation, memory bandwidth, cache latency, branch prediction, and sorting performance.

The project was developed for **CSE360 – Computer Architecture** at **East West University**.

---

## 📌 Project Overview

The **CPU Benchmarking Tool** measures the performance of different components of a computer system through a collection of benchmark tests.

The program evaluates:

* Integer processing performance
* Floating-point performance
* Memory bandwidth
* Branch prediction overhead
* L1, L2, and L3 cache latency
* Sorting performance

Each benchmark uses high-precision timing to measure execution performance. The results are displayed with performance ratings such as **Excellent, Good, Fair, or Poor**.

This project demonstrates important Computer Architecture concepts including **ALU performance, FPU operations, memory hierarchy, cache behavior, branch prediction, and CPU efficiency**.

---

## ✨ Features

### 1. Integer Processing Benchmark

Tests the CPU's **Arithmetic Logic Unit (ALU)** using integer operations such as:

* Addition
* Multiplication
* Modulo
* Bitwise operations

**Output:** MIPS (Million Instructions Per Second)

---

### 2. Floating-Point Benchmark

Evaluates floating-point computation using mathematical operations including multiplication, addition, and `sqrt()`.

**Output:** MFLOPS (Million Floating Point Operations Per Second)

This type of computation is relevant to applications such as:

* AI/ML
* Graphics
* Scientific computing

---

### 3. Memory Bandwidth Benchmark

Measures the speed of data transfer between the CPU and main memory.

The benchmark:

* Allocates a large memory block
* Performs repeated memory writes
* Reads memory at regular intervals
* Calculates the effective bandwidth

**Output:** GB/s (Gigabytes per second)

---

### 4. Branch Prediction Benchmark

Evaluates the performance impact of CPU branch prediction by comparing:

* Predictable branches
* Random branches

The difference between the two execution times is used to calculate **Branch Predictor Overhead (%)**.

Lower overhead indicates better branch prediction performance.

---

### 5. Cache Latency Benchmark

Measures access latency for different cache levels:

* **L1 Cache**
* **L2 Cache**
* **L3 Cache**

A pointer traversal technique is used to measure the average access time.

**Output:** Latency in nanoseconds (ns)

Lower latency indicates faster cache access.

---

### 6. Sorting Benchmark

Tests algorithm execution performance by:

1. Generating random integer data
2. Sorting the data using the C standard library `qsort()`
3. Measuring the execution time

**Output:** Million elements per second

This benchmark provides an additional indication of CPU and memory performance.

---

### 7. Cross-Platform High-Precision Timing

The program supports different operating systems through platform-specific timing methods.

**Windows:**

* `QueryPerformanceCounter()`
* `QueryPerformanceFrequency()`

**Linux/macOS:**

* `clock_gettime()`
* `CLOCK_MONOTONIC`

This allows the benchmark to obtain accurate execution times across supported platforms.

---

### 8. Performance Rating System

Raw benchmark results are converted into simple performance categories:

* 🟢 **Excellent**
* 🔵 **Good**
* 🟡 **Fair**
* 🔴 **Poor**

This makes the benchmark results easier to understand.

---

## 🛠️ Technologies Used

* **C**
* Standard C Library
* Windows API for high-resolution timing
* POSIX `clock_gettime()` for Unix-like systems
* Dynamic Memory Allocation
* Mathematical Functions
* `qsort()`

---

## 📊 Benchmark Metrics

| Benchmark         | Metric         | What It Measures                |
| ----------------- | -------------- | ------------------------------- |
| Integer ALU       | MIPS           | Integer computation performance |
| Floating Point    | MFLOPS         | Floating-point computation      |
| Memory            | GB/s           | Memory bandwidth                |
| Branch Prediction | % Overhead     | Branch prediction efficiency    |
| L1 Cache          | ns             | L1 cache latency                |
| L2 Cache          | ns             | L2 cache latency                |
| L3 Cache          | ns             | L3 cache latency                |
| Sorting           | M elements/sec | Sorting performance             |

---

## ⚙️ Benchmark Configuration

The program uses predefined workloads for each benchmark:

```c
#define ITER_INT 100000000LL
#define ITER_FP 50000000LL
#define MEM_BYTES (128*1024*1024)
#define MEM_PASSES 2
#define SORT_SIZE 1000000
#define BRANCH_ITER 100000000LL
```

Cache tests use:

```c
#define L1_SIZE (32*1024)
#define L2_SIZE (256*1024)
#define L3_SIZE (4*1024*1024)
#define CACHE_STEPS 2000000
```

These workloads are designed to provide measurable execution times while keeping the benchmark practical to run.

---

## 🚀 How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/CPU-Benchmarking-Tool.git
cd CPU-Benchmarking-Tool
```

### 2. Compile

#### Windows — MinGW/GCC

```bash
gcc "CPU_Benchmark.c" -o cpu_benchmark -lm
```

Run:

```bash
./cpu_benchmark
```

On Windows, you can also run:

```bash
cpu_benchmark.exe
```

#### Linux/macOS

```bash
gcc CPU_Benchmark.c -o cpu_benchmark -lm
```

Run:

```bash
./cpu_benchmark
```

---

## 💻 Example Output

```text
CPU Benchmark Tool

Integer ALU: XXXX.X MIPS (Good)
Floating Point: XXXX.X MFLOPS (Excellent)
Memory Bandwidth: XX.XX GB/s (Good)
Branch Predictor Overhead: XX.X% (Good)
Cache Latency: L1=X.X ns, L2=X.X ns, L3=X.X ns
Sorting: XX.XX M elements/sec (Good)
```

> The actual values depend on the processor, RAM, operating system, compiler, background processes, and system configuration.

---

## 🧠 How the Benchmark Works

The program follows this general process:

```text
Start
  │
  ▼
Initialize Benchmark
  │
  ├──► Integer ALU Test
  │
  ├──► Floating-Point Test
  │
  ├──► Memory Bandwidth Test
  │
  ├──► Branch Prediction Test
  │
  ├──► Cache Latency Test
  │      ├── L1
  │      ├── L2
  │      └── L3
  │
  └──► Sorting Test
          │
          ▼
     Calculate Results
          │
          ▼
     Performance Rating
          │
          ▼
        Output
```

---

## 📐 Performance Rating

The benchmark uses predefined thresholds to classify some benchmark results.

### Integer ALU

|       Score | Rating    |
| ----------: | --------- |
| ≥ 3000 MIPS | Excellent |
| ≥ 1500 MIPS | Good      |
|  ≥ 500 MIPS | Fair      |
|  < 500 MIPS | Poor      |

### Floating Point

|         Score | Rating    |
| ------------: | --------- |
| ≥ 1500 MFLOPS | Excellent |
|  ≥ 500 MFLOPS | Good      |
|  ≥ 100 MFLOPS | Fair      |
|  < 100 MFLOPS | Poor      |

### Memory Bandwidth

|     Score | Rating    |
| --------: | --------- |
| ≥ 30 GB/s | Excellent |
| ≥ 15 GB/s | Good      |
|  ≥ 5 GB/s | Fair      |
|  < 5 GB/s | Poor      |

### Sorting

|               Score | Rating    |
| ------------------: | --------- |
| ≥ 50 M elements/sec | Excellent |
| ≥ 20 M elements/sec | Good      |
|  ≥ 5 M elements/sec | Fair      |
|  < 5 M elements/sec | Poor      |

---

## 📁 Project Structure

```text
CPU-Benchmarking-Tool/
│
├── CPU_Benchmark.c
├── README.md
└── CSE360_Final_Project_Report.docx
```

---

## 🎯 Project Objectives

The main objectives of this project are to:

* Measure CPU integer computation performance
* Evaluate floating-point performance
* Measure memory bandwidth
* Analyze cache efficiency
* Compare L1, L2, and L3 cache latency
* Evaluate branch prediction behavior
* Measure sorting performance
* Demonstrate Computer Architecture concepts through practical benchmarking

---

## 🎓 Course Information

**Course:** Computer Architecture
**Course Code:** CSE360
**Section:** 07
**Group:** 09
**Institution:** East West University
**Department:** Computer Science & Engineering

### Team Members

* Sumaiya Rahaman
* Fahim Raja
* Riyadh Hossain
* Efajul Islam Seyam
* Tabassum Salsabil Ishpa

---

## 📚 Concepts Demonstrated

This project provides practical implementation of several Computer Architecture concepts:

* Arithmetic Logic Unit (ALU)
* Floating Point Unit (FPU)
* CPU execution performance
* Memory hierarchy
* Cache memory
* Cache latency
* Branch prediction
* CPU pipeline behavior
* Memory bandwidth
* Algorithm performance
* High-resolution timing
* Dynamic memory management

---

## ⚠️ Benchmark Considerations

Benchmark results can vary depending on:

* CPU model and architecture
* CPU temperature
* Background applications
* Operating system
* Compiler and optimization settings
* RAM configuration
* Power/performance mode
* System load

Therefore, benchmark results should primarily be used for **performance comparison under similar conditions**.

---

## 🔮 Future Improvements

Possible future improvements include:

* Multi-threaded CPU benchmarking
* CPU core and thread detection
* Automatic CPU information detection
* More cache sizes and memory access patterns
* SIMD/AVX benchmarking
* File-based result logging
* CSV result export
* Graphical user interface
* Benchmark score aggregation
* Repeated runs with average and standard deviation
* Comparison between multiple CPUs

---

## 📌 Conclusion

The **CPU Benchmarking Tool** provides a practical way to evaluate processor and system performance across computation, memory access, cache efficiency, branch prediction, and algorithm execution.

By combining multiple benchmark tests with high-precision timing, the project demonstrates how Computer Architecture concepts can be measured and analyzed using a C program.

---

## 👨‍💻 Author

**Riyadh Hossain**
Computer Science & Engineering
East West University

GitHub: `github.com/Riyadh-262`
