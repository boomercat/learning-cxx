#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]),capacity(capacity), cached(2){
        if(capacity > 0) cache[0] = 0;
        if(capacity > 1) cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 简单的边界检查（根据需求决定是否抛异常或其他处理）
        if (i < 0 || i >= capacity) {
            std::cerr << "Index " << i 
                      << " out of Fibonacci cache range [0, " 
                      << (capacity - 1) << "]\n";
            return 0; // 或者抛出异常
        }
                // 如果已经计算过第 i 个斐波那契数，则直接返回
        if (i < cached) {
            return cache[i];
        }

        // 如果没有缓存该值，则从已缓存的部分开始计算
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存到的位置
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
