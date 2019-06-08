#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

// 程序 1-32 不论初始序列如何，都能输出全排列
// 程序 1-35 不输出按字典顺序比初始序列小的排列。
// 练习要求修改程序 1-35, 使它能够输出所有排列
namespace Permutation{
    int arr[] = {3, 2, 1, 4};
    // 1-32
    template <typename T>
    void permutations(T arr[], int curr, int n) {

        T *arrPermutations = new T[n];
        copy(arr, arr+n, arrPermutations);

        if (curr == n) {
            copy(arrPermutations, arrPermutations+n, ostream_iterator<T>(cout, " "));
            cout << endl;
            return;
        }

        for (int i=curr; i<n; i++) {
            swap(arrPermutations[i], arrPermutations[curr]);
            permutations(arrPermutations, curr+1, n);
            swap(arrPermutations[i], arrPermutations[curr]);
        }
    }

    // 1-35
    template <typename T>
    void nextPermutations(T arr[], int n) {

        T *arrNextPermutations = new T[n];
        copy(arr, arr+n, arrNextPermutations);

        do {
            copy(arrNextPermutations, arrNextPermutations+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        } while (next_permutation(arrNextPermutations, arrNextPermutations+n));
    }

    // 修改 1
    // 在进行排列前先将 arr 进行从小到大排序即可
    // 当有重复元素时，会去掉重复序列
    template <typename T>
    void nextPermutationsSorted(T arr[], int n) {

        T *arrSorted = new T[n];
        copy(arr, arr+n, arrSorted);

        sort(arrSorted, arrSorted+n);

        do {
            copy(arrSorted, arrSorted+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        }while (next_permutation(arrSorted, arrSorted+n));
    }

    // 修改 2
    // 增加一个 compare 函数，进行两次全排序
    // 第一次排列出大于字典序的序列
    // 第二次排列出小于字典序的序列
    template <typename T>
    void nextPermutationsCompare(T arr[], int n) {

        T *arrLess = new T[n];    // 两次排列使用不同的数组可以保证第一次排列的结果不会影响第二次排列
        copy(arr, arr+n, arrLess);
        T *arrGreater = new T[n];
        copy(arr, arr+n, arrGreater);

        do {
            copy(arrLess, arrLess+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        } while (next_permutation(arrLess, arrLess+n));

        while (next_permutation(arrGreater, arrGreater+n, greater<T>())) {
            copy(arrGreater, arrGreater+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        }

    }
    void test() {
        cout << "修改练习 1-35: " << endl;
        cout << "程序 1-32 的排列结果： " << endl;
        permutations(arr, 0, 4);
        cout << "程序 1-35 的排列结果： " << endl;
        nextPermutations(arr, 4);
        cout << "增加 compare 函数的排序结果：" << endl;
        nextPermutationsCompare(arr, 4);
        cout << "先进行从小到大排序，再进行排列的排列结果：" << endl;
        nextPermutationsSorted(arr, 4);

    }
}

// 27. 编写 C＋＋ 代码，实现三个参数的模板函数 accumulate
namespace Accumulate {
    template <typename T>
    T accumulate(T *start, T *end, T initialValue) {
        T result = initialValue;
        while (start != end){
            result += *start;
            start++;
        }
        return result;
    }

    void test() {
        int arr[] = {1, 2, 3, 4};
        cout << "27. " << endl;
        cout << "Accumulate::accumulate: " << Accumulate::accumulate(arr, arr+4, 0) << endl;
        cout << "std::accumulate: " << std::accumulate(arr, arr+4, 0) << endl;
    }
}

// 28. 编写 C＋＋ 代码，实现四个参数的模板函数 accumulate
namespace AccumulateOperation {
    int function(int a, int b) {
        return 3 * a + b;
    }
    template <typename T>
    T accumulate(T *start, T *end, T initialValue, T (*operation)(T , T )) {

        T result = initialValue;

        while (start != end) {
            result = operation(result, (*start));
            start++;
        }

        return result;
    }

    void test() {
        int arr[] = {1, 2, 3, 4};

        cout << "28. " << endl;
        cout << "AccumulateOperation::accumulate: " << AccumulateOperation::accumulate(arr, arr+4, 0, function) << endl;
        cout << "std::accumulate: " << std::accumulate(arr, arr+4, 0, function) << endl;
    }
}

// 29. 编写 C＋＋ 代码，实现模板函数 copy
namespace Copy {
    template <typename T>
    void copy(T *start, T *end, T* to) {

        unsigned long index = end - start;

        end--;
        index--;

        while (end >= start) {
            *(to+index) = *end;
            index--;
            end--;
        }
    }

    void test() {
        int arr[] = {1, 2, 3, 4, 5};
        int *des = new int[5];
        cout << "29. " << endl;
        Copy::copy(arr, arr+5, des);
        for (int i=0; i < 5; i++) {
            cout << des[i] << " ";
        }
        cout << endl;
    }
}

// 30. 修改程序 1-35，输出所有不同元素的所有排列。
// 在生成排列之前，把表元素按升序排列。
namespace PermutationSorted {
    template <typename T>
    void permutation(T *arr, int n) {
        std::sort(arr, arr+n);

        do {
            copy(arr, arr+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        } while (next_permutation(arr, arr+n));
    }

    void test() {
        int arr[] = {3, 2, 1, 4};
        cout << "30. " << endl;
        permutation(arr, 4);
    }
}

// 31. 修改程序 1-35, 输出所有不同元素的所有排列
// 先使用 STL 算法 next_permutation 生成比初始序列大的排列
// 再使用 STL 算法 prev_permutation 生成比初始序列小的排列
namespace PermutationNextPrev {
    template <typename T>
    void permutation(T *arr, int n) {

        T *arrNext = new T[n];
        copy(arr, arr+n, arrNext);
        T *arrPrev = new T[n];
        copy(arr, arr+n, arrPrev);

        do {
            copy(arrNext, arrNext+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        } while (next_permutation(arrNext, arrNext+n));

        while (prev_permutation(arrPrev, arrPrev+n)) {
            copy(arrPrev, arrPrev+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        }
    }

    void test() {
        int arr[] = {3, 1, 2, 4};
        cout << "31. " << endl;
        permutation(arr, 4);
    }
}

// 32. 修改程序 1-35, 输出所有不同元素的所有排列
// 注意：当 next_permutation 的返回值是 false 时，序列 [start, end) 是最小序列。
// 因此，调用 next_permutation 可得到剩余的排列。
namespace PermutationFalse {
    template <typename T>
    void permutation(T *arr, int n) {
        while (next_permutation(arr, arr+n)) {
            copy(arr, arr+n, ostream_iterator<T>(cout, " "));
            cout << endl;
        }
    }

    void test() {
        int arr[] = {3, 1, 2, 4};
        cout << "32. 没理解题意 -_-//" << endl;
        permutation(arr, 4);
    }
}

// 33. 使用 STL 算法 count 做练习 2
namespace Count{
    template <typename T>
    int count(T *arr, int n, T value) {
        return std::count(arr, arr+n, value);
    }

    void test() {
        cout << "33. " << endl;
        int arr[] = {1, 2, 3, 1, 1, 4, 2};
        cout << Count::count(arr, 7, 2) << endl;
    }
}

// 34. 使用 STL 算法 fill 做练习3
namespace Fill {
    template <typename T>
    void fill(T *arr, int n, T value) {
        std::fill(arr, arr+n, value);
    }

    void test() {
        cout << "34. " << endl;
        int *arr = new int[10];
        Fill::fill(arr, 10, -1);
        for (int i=0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

// 35. 使用 STL 算法 inner_product 做练习 4
namespace InnerProduct {

    template <typename T>
    T innerProduct(T *a, T *b, int n) {
        return std::inner_product(a, a+n, b, 0);
    }

    void test() {
        int a[] = {1, 2, 3, 4};
        int b[] = {1, 2, 3, 4};
        cout << "35. " << endl;
        cout << innerProduct(a, b, 4) << endl;
    }
}

// 36. 使用 STL 算法 iota 做练习 5
namespace Iota {
    template <typename T>
    void iota(T *arr, int n, T value) {
        std::iota(arr, arr+n, value);
    }
    void test() {
        cout << "36. " << endl;
        int *arr = new int[10];
        Iota::iota(arr, 10, 10);
        for (int i=0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

// 37. 使用 STL 算法 is_sorted 做练习 6
namespace IsSorted {
    template <typename T>
    bool isSorted(T *arr, int size) {
        return std::is_sorted(arr, arr+size);
    }
    void test() {
        int arr[] = {2, 3, 4, 1, 5};
        cout << "37. " << endl;
        cout << isSorted(arr, 5) << endl;
    }
}

// 38. 使用 STL 算法 mismatch 做练习 7
namespace Mismatch {
    // 当两个数组完全相同时，返回数组大小
    template <typename T>
    int mismatch(T *a, T *b, int n) {
        std::pair<T *, T *> result = std::mismatch(a, a+n, b);
        return int(result.first - a);
    }
    void test() {
        int a[] = {1, 2, 3, 4};
        int b[] = {1, 3, 3, 4};
        cout << "38. " << endl;
        cout << mismatch(a, b, 4) << endl;
    }
}

// 39. 编写 C＋＋ 代码，实现练习 33 的 STL 模板函数 count
namespace CountSTL {
    template <typename T>
    int count(T *start, T *end, T value) {
        int result = 0;
        while (start != end) {
            if (*start == value) {
                result++;
            }
            ++start;
        }
        return result;
    }

    void test() {
        int arr[] = {2, 1, 2, 2, 4, 5, 7};
        cout << "39. " << endl;
        cout << CountSTL::count(arr, arr+7, 2) << endl;
    }
}

// 40. 编写 C＋＋ 代码，实现练习 34 的 STL 模板函数 fill
namespace FillSTL {
    template <typename T>
    void fill(T *start, T *end, T value) {
        while (start != end) {
            *start = value;
            ++start;
        }
    }

    void test() {
        cout << "40. " << endl;
        int *arr = new int[10];
        FillSTL::fill(arr, arr+10, 23);
        for (int i=0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

// 41. 编写 C＋＋ 代码，实现练习 34 的 STL 模板函数 inner_product
namespace InnerProductSTL {
    template <typename T>
    T innerProduct(T *firstStart, T *firstEnd, T *secondStart, T initialValue) {
        T result = initialValue;

        while (firstStart != firstEnd) {
            result += (*firstStart) * (*secondStart);
            ++firstStart;
            ++secondStart;
        }

        return result;
    }

    void test() {
        cout << "41. " << endl;
        int a[] = {1, 2, 3, 4};
        int b[] = {1, 2, 3, 4};
        cout << InnerProductSTL::innerProduct(a, a+4, b, 0) << endl;
    }
}
// 42. 编写 C＋＋ 代码，实现练习 34 的 STL 模板函数 iota
namespace IotaSTL {
    template <typename T>
    void iota(T *start, T *end, T value) {
        T *originalStart = start;
        while (start != end) {
            *start = value + (start - originalStart);
            ++start;
        }
    }

    void test() {
        cout << "42. " << endl;
        int *arr = new int[10];
        IotaSTL::iota(arr, arr+10, 10);
        for (int i=0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}
// 43. 编写 C＋＋ 代码，实现练习 34 的 STL 模板函数 is_sorted
namespace IsSortedSLT {
    template <typename T>
    bool isSorted(T *start, T *end) {
        while (start < end-1) {
            if (*start > *(start+1)) {
                return false;
            }
            ++start;
        }
        return true;
    }

    void test() {
        int arr[] = {2, 3, 4, 5};
        cout << "43. " << endl;
        cout << IsSortedSLT::isSorted(arr, arr+5) << endl;
    }
}

// 44. 编写 C＋＋ 代码，实现练习 34 的 STL 模板函数 mismatch
namespace MismatchSTL {
    template <typename T>
    std::pair<T *, T *> mismatch(T *firstStart, T *firstEnd, T *secondStart) {
        while (*firstStart == *secondStart & firstStart < firstEnd) {
            ++firstStart;
            ++secondStart;
        }
        return std::make_pair(firstStart, secondStart);
    }

    void test() {
        cout << "44. " << endl;
        int a[] = {1, 2, 3, 4};
        int b[] = {1, 2, 3, 4};
        cout << MismatchSTL::mismatch(a, a+4, b).first - a << endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Permutation::test();
    Accumulate::test();
    AccumulateOperation::test();
    Copy::test();
    PermutationSorted::test();
    PermutationNextPrev::test();
    PermutationFalse::test();
    Count::test();
    Fill::test();
    InnerProduct::test();
    Iota::test();
    IsSorted::test();
    Mismatch::test();
    CountSTL::test();
    FillSTL::test();
    InnerProductSTL::test();
    IotaSTL::test();
    IsSortedSLT::test();
    MismatchSTL::test();
    return 0;
}