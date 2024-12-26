#include "../exercise.h"
#include <iostream>
#include <cassert>

// 定义 ASSERT 宏，如果你没有定义它，可以使用标准的 assert
#ifndef ASSERT
#include <cassert>
#define ASSERT(cond, msg) assert((cond) && msg)
#endif

struct Fibonacci {
    int numbers[11];

    // 修改方法签名，使其成为 constexpr 和 const
    constexpr int get(int i) const {
        // 可选：添加边界检查
        // 如果索引超出范围，可以选择返回 -1 或抛出异常
        // 这里简单地假设索引是有效的
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // 使用 constexpr 初始化 Fibonacci 对象
    constexpr Fibonacci FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};

    // 使用 static_assert 进行编译时检查
    static_assert(FIB.get(10) == 55, "fibonacci(10) should be 55");

    // 运行时输出结果
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;

    return 0;
}
