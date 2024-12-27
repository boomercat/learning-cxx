#include "../exercise.h"

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化// 1. 将这个函数“模板化”
template <typename T>
T plus_(T a, T b) {
    return a + b;
}

// 如果要判断浮点数是否“足够接近”，可以用如下辅助宏
#define ASSERT_FLOAT_EQ(a, b, epsilon, msg) do {             \
    if (std::fabs((a) - (b)) > (epsilon)) {                   \
        std::cerr << "Assertion failed: " << (msg) << '\n';  \
        std::exit(EXIT_FAILURE);                             \
    }                                                        \
} while(0)

int main(int argc, char **argv) {
    // 测试整型
    // ASSERT(plus_(1, 2) == 3, "Plus two int");
    // ASSERT(plus_(1u, 2u) == 3u, "Plus two unsigned int");

    // // 测试浮点数（用直接比较 ==，但注意浮点数可能存在表示误差）
    // ASSERT(plus_(1.25f, 2.5f) == 3.75f, "Plus two float");
    // ASSERT(plus_(1.25, 2.5)   == 3.75,  "Plus two double");

    // 2. 修改判断条件使测试通过：这里使用近似比较
    // 因为 0.1 + 0.2 在二进制浮点下不等于 0.3
    // ASSERT_FLOAT_EQ(plus_(0.1, 0.2), 0.3, 1e-12, "How to make this pass?");

    std::cout << "All tests passed!\n";
    return 0;
}