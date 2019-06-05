#include <iostream>
using namespace std;

// 1. 解释为什么程序 1-7 的交换函数没有把形参 x 和 y 所对应的实参的值交换。如何修改代码，使实参的值得到交换。
namespace Swap {

    namespace Wrong {
        // 1-7
        void swap(int x, int y) {
            int temp = x;
            x = y;
            y = temp;
        }
    }


    // 使用值传递的方式，传递的是实参的副本。 swap 内对实参副本的修改并不会影响实参本身。
    // 可以考虑使用传递引用或地址的方式。
    namespace Reference {
        // 1. 传递引用
        void swap(int &x, int &y) {
            int temp = x;
            x = y;
            y = temp;
        }
    }

    namespace Address{
        // 2. 传递地址
        void swap(int *x, int *y) {
            int temp = *x;
            *x = *y;
            *y = temp;
        }
    }

    void test() {
        int x = 2;
        int y = 3;
        cout << "1. swap: " << endl;
        cout << "1-7 swap: " << endl;
        cout << "x: " << x << " y: " << y << endl;
        Wrong::swap(x, y);
        cout << "x: " << x << " y: " << y << endl;

        cout << "传递引用 swap: " << endl;
        cout << "x: " << x << " y: " << y << endl;
        Reference::swap(x, y);
        cout << "x: " << x << " y: " << y << endl;

        cout << "传递地址 swap: " << endl;
        cout << "x: " << x << " y: " << y << endl;
        Address::swap(&x, &y);
        cout << "x: " << x << " y: " << y << endl;
    }

}

// 2. 编写一个模板函数 count, 返回值是数组 a[0:n-1] 中 value 出现的次数
namespace Count{
    const int n=10;
    template <typename T>
    int count(T arr[], T value, int size = n) {
        int result = 0;

        for (int i=0; i < size; i++) {
            if (arr[i] == value) {
                result++;
            }
        }
        return result;
    }
    void test() {
        int arr[10] = {1, 2, 2, 3, 1, 2, 4, 5, 3, 2};
        cout << "2. count: ";
        cout << Count::count<int>(arr, 2, 10) << endl;
    }
}

// 3. 编写一个模板函数 fill, 给数组 a[start:end-1] 赋值 value
namespace Fill{

    const int n=10;

    template <typename T>
    void fill(T a[], int start, int end, T value, int size=n) {
        for (int i=start; i < end; i++) {
            a[i] = value;
        }
    }

    void test() {
        double arr[10] = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0};

        fill<double>(arr, 3, 7, 10);

        cout << "3. fill: ";
        for (int i=0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

// 4. 编写一个模板函数 inner_product, 返回值是 i=0->n-1, sum(a[i]*b[i])
namespace InnerProduct{
    const int n=10;

    template <typename T>
    T inner_product(T a[], T b[], int size=n) {
        T result=0;
        for (int i=0; i < size; i++) {
            result += a[i]*b[i];
        }
        return result;
    }
    void test() {
        double a[4] = {1.1, 2.2, 3.3, 4.4};
        double b[4] = {1.0, 1.0, 1.0, 1.0};
        cout << "4. inner_product: ";
        cout << inner_product<double>(a, b, 4);
        cout << endl;
    }
}

// 5. 编写一个模版函数 iota，使 a[i]=value+i，0<=i<n
namespace Iota{
    const int n=10;

    template <typename T>
    void iota(T a[], T value, int size=n) {
        for (int i=0; i < size; i++) {
            a[i] = value + i;
        }
    }

    void test() {
        int a[10];
        iota<int>(a, 2, 10);

        cout << "5. iota: ";
        for (int i=0; i < 10; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
}

// 6. 编写一个模版函数 is_sorted，当且仅当 a[0:n-1] 为有序时，返回值是 true
namespace IsSorted{

    const int n=10;

    template <typename T>
    bool is_sorted(T arr[], int size=n) {
        bool result = true;

        for (int i=0; i<size-1; i++) {
            if (arr[i] > arr[i+1]) {
                result = false;
                break;
            }
        }
        return result;
    }

    void test() {
        int arr[5] = {1, 2, 3, 7, 5};
        cout << "6. is_sorted: ";
        cout << is_sorted<int>(arr, 5);
        cout << endl;
    }
}

// 7. 编写一个模板函数 mismatch，返回值是使不等式 a[i] != b[i] 成立的最小索引，　0<=i<n
// 自定义：当 a==b 时，返回 -1
namespace Mismatch{

    const int n=10;

    template <typename T>
    int mismatch(T a[], T b[], int size=n) {
        int result = -1;
        for (int i=0; i < size; i++) {
            if (a[i] != b[i]) {
                result = i;
                break;
            }
        }
        return result;
    }

    void test() {
        int a[5] = {1, 2, 2, 3, 4};
        int b[5] = {1, 2, 3, 3, 4};

        cout << "7. mismatch: ";
        cout << mismatch(a, b, 5);
        cout << endl;
    }
}


// 8. 下面的函数是具有不同签名的函数么？为什么
// 具有相同的签名
namespace Signature {
//    int abc(int a, int b, int c); -> (int, int, int)
//    float abc(int a, int b, int c); -> (int, int, int);
// 一个函数的签名由这个函数的形参类型以及形参个数确定。
}

// 9. 假设有一个程序包含了程序 1-1 和程序 1-2 的 abc 函数，下面的语句分别调用了哪一个版本的函数？哪一条语句会出现编译错误，为什么？
namespace AbcSignature {
    // 1-1
    int abc(int a, int b, int c) {
        cout << "1-1 abc(), Signature:(int, int, int)" << endl;
        return a + b * c;
    }
    // 1-2
    float abc(float a, float b, float c) {
        cout << "1-2 abc(), Signature:(float, float, float)" << endl;
        return a + b * c;
    }

    void test() {
        cout << "9. AbcSignature: " << endl;
        cout << abc(1, 2,3) << endl; // 调用的函数签名为(int, int, int)，与 1-1 的 abc 函数签名匹配
        cout << abc(1.0F, 2.0F, 3.0F) << endl; // 调用的函数签名为 (float, float, float), 与 1-2 的 abc 函数签名匹配
//        cout << abc(1, 2, 3.0F) << endl;     // 错误，调用的函数签名为 (int, int, float), 无匹配项
//        cout << abc(1.0, 2.0, 3.0) << endl;  // 错误，调用的函数签名为 (double, double, double),无匹配项
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Swap::test();
    Count::test();
    Fill::test();
    InnerProduct::test();
    Iota::test();
    IsSorted::test();
    Mismatch::test();
    AbcSignature::test();
    return 0;
}