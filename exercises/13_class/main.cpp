#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // TODO: 实现构造器
    // Fibonacci()
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }
    size_t get(int i) {
        // 简单的边界检查，防止索引越界
        if (i < 0) {
            // 自定义需求：这里也可以抛异常或返回其他值
            return 0;
        }
        if (i >= 16) {
            // 这里也可以抛异常或进行其他处理
            std::cerr << "Index " << i << " out of Fibonacci cache range [0,15]" << std::endl;
            return 0;
        }

        // 如果已经计算过第 i 个斐波那契数，直接返回
        if (i < cached) {
            return cache[i];
        }

        // 否则，从已经缓存的数开始计算到 i
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存到的位置
        
        return cache[i];
    }

};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
