#include <iostream>
using namespace std;
// 10. 修改程序1－8，使抛出的异常类型是整型。
// 如果 a、b、c 都小于0，那么抛出的异常值为 1
// 如果 a、b、c 都等于0，那么抛出的异常值为 2
namespace Throw1or2{
    int abc(int a, int b, int c) {
        if (a<0 && b<0 && c<0) {
            throw 1;
        }

        if (a==0 && b==0 && c==0) {
            throw 2;
        }

        return a + b * c;
    }

    void test() {
        int a=-1, b=-1, c=-1;

        cout << "10. throw 1 or 2: ";
        try {
            cout << abc(a, b, c);

        } catch (int e) {
            if (e == 1) {
                cout << "a、b、c　都小于 0" << endl;
            }

            if (e == 2) {
                cout << "a、b、c　都等于 0" << endl;
            }
        }
        cout << endl;
    }
}

// 11. 重做练习2。当n<1 时，抛出类型为 char* 的异常
namespace CountThrowChar{
    const int n = 10;

    template <typename T>
    int count(T a[], T value, int size=n) {
        if (size < 1) {
            throw (char*)"n < 1"; //catch (char * e)
            // throw "n < 1"; // CLion: catch (char const* e)
        }

        int result = 0;
        for (int i=0; i < size; i++) {
            if (a[i] == value) {
                result ++;
            }
        }
        return result;
    }
    void test() {
        int arr[10] = {1, 1, 2, 2, 2, 3, 4, 5, 6, 7};
        cout << "11. Count throw char*: ";
        try{
            cout << count(arr, 2, 0) << endl;
        } catch (char* e) { // Clion: catch (char const* e)

            cout << e << endl;
        }
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    Throw1or2::test();
    CountThrowChar::test();
    return 0;
}