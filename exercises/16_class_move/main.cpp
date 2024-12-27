#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache; // 动态分配数组，用来缓存 Fibonacci 值
    int cached;    // 当前已经计算到的最大下标（含义：0 ~ cached-1都有效）

public:
    // TODO: 实现动态设置容量的构造器
    // 在此处开辟 capacity 大小的数组，cached 初始设为 2，表示我们先算好 F(0) 和 F(1)
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]), // 仅演示，不存储 capacity
          cached(2)
    {
        cache[0] = 0;
        cache[1] = 1;
    }
    int a = 1; // 这个似乎没实际用途，但原示例里就有，保留即可

    // TODO: 实现移动构造器
    // 移动后把 other.cache 置为 nullptr，以便表示“资源已转移”
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache),
          cached(other.cached)
    {
        other.cache = nullptr; 
        other.cached = 0;      
    }

    // TODO: 实现移动赋值
    // 注意处理“移动到自身”的情况，同时确保移动前释放旧资源
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this == &other) {
            return *this; // 避免自我移动造成的重复释放
        }
        // 释放旧资源
        delete[] cache;

        // 接管 new 出来的数据
        cache = other.cache;
        cached = other.cached;

        // 置空对方
        other.cache = nullptr;
        other.cached = 0;
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    // 如果 i 大于当前已算到的索引 cached-1，就继续往后计算
    size_t operator[](int i) {
        // 只要 cached <= i，就计算下一个 Fibonacci 值
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 测试移动构造
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(),     "Object moved");
    ASSERT(fib_[10] == 55,      "fibonacci(10) should be 55");

    // 测试移动赋值
    DynFibonacci fib0(6);
    DynFibonacci fib1(12);
    fib0 = std::move(fib1); // 移动赋值
    fib0 = std::move(fib0); // 自我移动
    ASSERT(fib0[10] == 55,   "fibonacci(10) should be 55");

    std::cout << "All tests passed!\n";
    return 0;
}