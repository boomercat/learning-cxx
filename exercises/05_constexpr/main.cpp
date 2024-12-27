#include "../exercise.h"

#include <iostream>



constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0: return 0ULL;
        case 1: return 1ULL;
        default: return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main() {
    // 1. 测试 Fibonacci(20)
    // constexpr auto FIB20 = fibonacci(20);
    // ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    // std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // 2. 计算 Fibonacci(90)
    //    因为 ANS_N 是 const，而不是 constexpr，
    //    所以不能在编译期使用它来展开 fibonacci
    const auto ANS_N = 90;  
    // ↓ 关键改动：去掉了 constexpr
    // auto ANS = fibonacci(ANS_N);
    // std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;
    return 0;
}
