#include "../exercise.h"

#include <iostream>
#include <cassert>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数，初始化缓存
    Fibonacci() : cached(2) {
        cache[0] = 0;  // F(0)
        cache[1] = 1;  // F(1)
    }

    // 获取第i个斐波那契数，并进行缓存优化
    unsigned long long get(int i) {
        // 如果缓存了该斐波那契数，则直接返回
        if (i < cached) {
            return cache[i];
        }

        // 如果没有缓存该斐波那契数，从已缓存的值开始计算
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存的最大索引
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体
    Fibonacci fib;

    // 验证计算结果是否正确
    assert(fib.get(10) == 55 && "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    return 0;
}
