#include <iostream>
#include <cmath>
using namespace std;

// 19. 编写一个非递归程序计算 n!。测试你的代码
namespace Factorial {
    unsigned long factorialRecursive(unsigned int n) {
        if (n <= 0) {
            return 1;
        }
        return n * factorialRecursive(n-1);
    }

    unsigned long factorial(unsigned int n) {
        unsigned long result = 1;
        while (n > 0) {
            result *= n;
            n--;
        }
        return result;
    }

    void test() {
        cout << "19. " << endl;
        cout << 10 << "! = " << factorialRecursive(10) << endl;
        cout << 10 << "! = " << factorial(10) << endl;
    }
}

// 20.
// 1. 编写递归函数计算斐波那契数（Fibonacci）Fn。测试你的代码
// 3. 编写非递归函数计算斐波那契数（Fibonacci) Fn。对于每个斐波那契数，你的代码应该只计算一次。
namespace Fibonacci {
    unsigned long  fibonacciRecursive(unsigned int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }

    unsigned long fibonacci(unsigned int n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        unsigned long fn1 = 1;
        unsigned long fn2 = 1;
        unsigned long result;
        for (int i=1; i < n; i++) {
            result = fn1 + fn2;
            fn1 = fn2;
            fn2 = result;
        }
        return result;
    }
    void test() {
        cout << "20. " << endl;
        cout << "1. " << endl;
        cout << "F(7) = " << fibonacciRecursive(7) << endl;
        cout << "F(7) = " << fibonacci(7) << endl;

    }
}

// 21.
// 考查下面公式中定义的函数f，其中 n 是非负整数
// f(n) = n/2, n 为偶数
//        f(3n+1), n 为奇数
// 1. 使用公式手算 f(5) 和 f(7)
// 2. 确定函数的基础部分和递归部分。证明重复应用递归部分可以把长等式左侧的 f 表达式转为基础部分
// 3. 编写一个 C++ 递归函数计算 f(n)。测试你的代码。
// 4. 使用 2) 的证明编写 C++ 非递归函数计算 f(n)。不能使用循环。测试你的代码。
namespace Function {
    // 1.
    // f(5) = f(3 * 5 + 1) = f(16) = 8
    // f(7) = f(3 * 7 + 1) = f(22) = 11

    // 2.
    // 基础部分：当 n 为偶数时
    // 递归部分：当 n 为奇数时
    // 当 n 为奇数时，3n+1 必为偶数，可将 f(n) = f(3n+1) 转化为 f(n) = (3n+1)/2

    // 3.
    unsigned int functionRecursive(unsigned int n) {
        if (n % 2 == 0) {
            return n/2;
        } else {
            return functionRecursive(3 * n + 1);
        }
    }

    // 4.
    unsigned int function(unsigned int n) {
        if (n%2 == 0) {
            return n/2;
        } else {
            return (3 * n + 1) / 2;
        }
    }
    void test() {
        cout << "21. " << endl;
        for (unsigned int i=1; i < 100; i++) {
            cout << functionRecursive(i) << "\t" << function(i) << endl;
        }

    }
}


// 22. 阿克曼函数(Ackermann's function)
namespace Ackermann {
    unsigned long ackermann(unsigned long i, unsigned long j) {

        if (i == 0 || j == 0) {
            throw "i and j should >= 1";
        }
        if (i == 1 && j >= 1) {
            return (unsigned long)pow(2, j);
        }
        if (i >= 2 && j == 1) {
            return ackermann(i-1, 2);
        }
        return ackermann(i-1, ackermann(i, j-1));
    }

    void test() {
        cout << "22. " << endl;
        for (int i=1; i < 3; i++) {
            for (int j=1; j < 4; j++) {
                cout << "Ackermann(" << i << ", " << j << ") = " << ackermann(i, j) << endl;
            }
        }
    }
}

// 23. 最大公约数（Greatest Common Divisor, GCD)
namespace Gcd {
    unsigned int gcd (unsigned int x, unsigned int y) {

        if (y == 0) {
            return x;
        }
        return gcd(y, x%y);
    }

    void test () {
        cout << "23. " << endl;
        cout << "gcd(0, 0) = " << gcd(0, 0) << endl;
        cout << "gcd(10, 0) = " << gcd(10, 0) << endl;
        cout << "gcd(0, 10) = " << gcd(0, 10) << endl;
        cout << "gcd(20, 30) = " << gcd(20, 30) << endl;
        cout << "gcd(112, 42) = " << gcd(112, 42) << endl;
        cout << "gcd(2, 3) = " << gcd(2, 3) << endl;
    }
}

// 24. 编写一个递归模板函数，确定元素 x 是否属于 a[0:n-1]
namespace Contains{
    template <typename T>
    bool contains(T *arr, T x, unsigned int n) {
        if (n == 0) {
            return false;
        }
        if (*arr == x) {
            return true;
        }
        return contains(arr+1, x, n-1);
    }
    void test() {
        cout << "24. " << endl;
        int arr[] = {2, 3, 4, 5, 6, 9, 8};
        cout << "contains(8): " << contains(arr, 8, 7) << endl;
        cout << "contains(7): " << contains(arr, 7, 7) << endl;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
//    Factorial::test();
//    Fibonacci::test();
//    Function::test();
//    Ackermann::test();
//    Gcd::test();
    Contains::test();
    return 0;
}