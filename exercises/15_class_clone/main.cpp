#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;  // 指向堆上分配的数组，用来缓存 Fibonacci 值
    int capacity;   // 缓存数组大小，防止越界
    int cached;     // 表示已经计算到的最大下标（含义可灵活定义）

public:
    // TODO: 实现动态设置容量的构造器
    // 我们在构造时开辟指定大小的数组，并初始化前两个斐波那契数
    // cached = 2，表示已经计算好 cache[0] 和 cache[1]
    DynFibonacci(int cap)
        : cache(new size_t[cap]), capacity(cap), cached(2)
    {
        // 初始化前两个 Fibonacci 值
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现复制构造器（深拷贝）
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]),
          capacity(other.capacity),
          cached(other.cached)
    {
        // 拷贝已经计算的所有值
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache; // 释放数组
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    // 如果 i 超过目前已经缓存的范围，就循环计算并填充
    size_t get(int i) {
        // 先做一个越界判断，防止访问到 cache[capacity] 之外
        ASSERT(i < capacity, "i out of range in get(int)");

        // 如果还没算到 i，就继续往后计算
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // 这是 const 版本的 get，用于在 const 对象上调用
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range in get(int) const");
        // 为了防止编译器警告，这里可加个返回
        return 0; 
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
