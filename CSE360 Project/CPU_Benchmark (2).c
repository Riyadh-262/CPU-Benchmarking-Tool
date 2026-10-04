#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ---------- Cross-platform timing ---------- */
#ifdef _WIN32
#include <windows.h>
typedef LARGE_INTEGER bench_time_t;

void get_time(bench_time_t *t) {
    QueryPerformanceCounter(t);
}

double elapsed_sec(bench_time_t start, bench_time_t end) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
}

#else
#include <time.h>
typedef struct timespec bench_time_t;

void get_time(bench_time_t *t) {
    clock_gettime(CLOCK_MONOTONIC, t);
}

double elapsed_sec(bench_time_t start, bench_time_t end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) * 1e-9;
}
#endif

/* ---------- Constants (reduced for faster run) ---------- */
#define ITER_INT 100000000LL
#define ITER_FP  50000000LL
#define MEM_BYTES (128*1024*1024)
#define MEM_PASSES 2
#define SORT_SIZE 1000000
#define BRANCH_ITER 100000000LL

#define L1_SIZE (32*1024)
#define L2_SIZE (256*1024)
#define L3_SIZE (4*1024*1024)
#define CACHE_STEPS 2000000

/* ---------- Rating ---------- */
const char* rating(double score, double p, double o, double g) {
    if (score >= g) return "Excellent";
    if (score >= o) return "Good";
    if (score >= p) return "Fair";
    return "Poor";
}

/* ---------- 1. Integer ---------- */
double bench_integer() {
    volatile long long a = 3, b = 7, c = 0;
    bench_time_t t0, t1;

    get_time(&t0);
    for (long long i = 0; i < ITER_INT; i++) {
        c += a * b + i;
        a = (c % 97) + 1;
        b = (a + i) & 0xFFFF;
    }
    get_time(&t1);

    return (ITER_INT * 3.0) / elapsed_sec(t0, t1) / 1e6;
}

/* ---------- 2. Floating ---------- */
double bench_float() {
    volatile double x = 1.0, y = 2.0, z = 0.0;
    bench_time_t t0, t1;

    get_time(&t0);
    for (long long i = 0; i < ITER_FP; i++) {
        z = x * y + i * 1e-10;
        x = sqrt(z + 1.0);
        y = z * 0.9 + 1.0;
    }
    get_time(&t1);

    return (ITER_FP * 5.0) / elapsed_sec(t0, t1) / 1e6;
}

/* ---------- 3. Memory ---------- */
double bench_memory() {
    char *buf = malloc(MEM_BYTES);
    if (!buf) return 0;

    memset(buf, 1, MEM_BYTES);

    bench_time_t t0, t1;
    volatile long long sum = 0;

    get_time(&t0);
    for (int p = 0; p < MEM_PASSES; p++) {
        memset(buf, p, MEM_BYTES);
        for (size_t i = 0; i < MEM_BYTES; i += 64)
            sum += buf[i];
    }
    get_time(&t1);

    free(buf);
    double bytes = MEM_BYTES * 2.0 * MEM_PASSES;
    return bytes / elapsed_sec(t0, t1) / 1e9;
}

/* ---------- 4. Branch ---------- */
double bench_branch_predictable() {
    volatile int c = 0;
    bench_time_t t0, t1;

    get_time(&t0);
    for (long long i = 0; i < BRANCH_ITER; i++) {
        if (i & 1) c++;
    }
    get_time(&t1);

    return elapsed_sec(t0, t1);
}

double bench_branch_random() {
    int *arr = malloc(BRANCH_ITER * sizeof(int));
    if (!arr) return 0;

    for (long long i = 0; i < BRANCH_ITER; i++)
        arr[i] = rand() % 2;

    volatile int c = 0;
    bench_time_t t0, t1;

    get_time(&t0);
    for (long long i = 0; i < BRANCH_ITER; i++) {
        if (arr[i]) c++;
    }
    get_time(&t1);

    free(arr);
    return elapsed_sec(t0, t1);
}

/* ---------- 5. Cache ---------- */
typedef struct Node {
    struct Node *next;
} Node;

double walk_cache(size_t size) {
    size_t n = size / sizeof(Node);
    Node *nodes = malloc(n * sizeof(Node));
    if (!nodes) return 0;

    for (size_t i = 0; i < n - 1; i++)
        nodes[i].next = &nodes[i + 1];
    nodes[n - 1].next = &nodes[0];

    Node *p = &nodes[0];

    bench_time_t t0, t1;
    get_time(&t0);
    for (size_t i = 0; i < CACHE_STEPS; i++)
        p = p->next;
    get_time(&t1);

    free(nodes);
    return elapsed_sec(t0, t1) * 1e9 / CACHE_STEPS;
}

/* ---------- 6. Sorting ---------- */
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double bench_sort() {
    int *arr = malloc(SORT_SIZE * sizeof(int));
    if (!arr) return 0;

    for (int i = 0; i < SORT_SIZE; i++)
        arr[i] = rand();

    bench_time_t t0, t1;
    get_time(&t0);
    qsort(arr, SORT_SIZE, sizeof(int), cmp);
    get_time(&t1);

    free(arr);
    return SORT_SIZE / elapsed_sec(t0, t1) / 1e6;
}

/* ---------- MAIN ---------- */
int main(void)
{
    printf("CPU Benchmark Tool\n\n");

    double mips = bench_integer();
    printf("Integer ALU: %.1f MIPS (%s)\n",
           mips, rating(mips, 500, 1500, 3000));

    double mflops = bench_float();
    printf("Floating Point: %.1f MFLOPS (%s)\n",
           mflops, rating(mflops, 100, 500, 1500));

    double gbps = bench_memory();
    if (gbps > 0.0)
        printf("Memory Bandwidth: %.2f GB/s (%s)\n",
               gbps, rating(gbps, 5, 15, 30));
    else
        printf("Memory Bandwidth: Not enough memory\n");

    double t1 = bench_branch_predictable();
    double t2 = bench_branch_random();
    double overhead = ((t2 - t1) / t1) * 100.0;

    printf("Branch Predictor Overhead: %.1f%% (%s)\n",
           overhead,
           overhead < 10 ? "Excellent" :
           overhead < 30 ? "Good" :
           overhead < 70 ? "Fair" : "Weak");

    double l1 = walk_cache(L1_SIZE);
    double l2 = walk_cache(L2_SIZE);
    double l3 = walk_cache(L3_SIZE);

    printf("Cache Latency: L1=%.1f ns, L2=%.1f ns, L3=%.1f ns\n",
           l1, l2, l3);

    double sort = bench_sort();
    if (sort > 0.0)
        printf("Sorting: %.2f M elements/sec (%s)\n",
               sort, rating(sort, 5, 20, 50));
    else
        printf("Sorting: Not enough memory\n");

    return 0;
}