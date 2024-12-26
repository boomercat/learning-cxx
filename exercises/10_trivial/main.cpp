#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;

    FibonacciCache() : cached(2) {
        // 初始化缓存的前两个斐波那契数
        cache[0] = 0;
        cache[1] = 1;
    }
};

// 计算斐波那契数并进行缓存优化
static unsigned long long fibonacci(FibonacciCache &fibCache, int i) {
    if (i < fibCache.cached) {
        // 如果已经缓存了结果，直接返回
        return fibCache.cache[i];
    }
    // 如果结果没有缓存，就从已缓存的值开始计算
    for (int j = fibCache.cached; j <= i; ++j) {
        fibCache.cache[j] = fibCache.cache[j - 1] + fibCache.cache[j - 2];
    }
    fibCache.cached = i + 1; // 更新缓存的最大索引
    return fibCache.cache[i];
}


int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
