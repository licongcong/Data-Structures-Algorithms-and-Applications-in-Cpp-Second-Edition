#include <iostream>
using namespace std;

// 编写一个函数 changeLength2D, 用以改变一个二维数组的长度。二维数组的每一维的长度都是可以变化的
namespace ChangeLength2D {
    template <typename T>
    void printArray(T** const &arr, unsigned int row, unsigned int col) {
        for (int i=0; i < row; i++) {
            for (int j=0; j < col; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }

    template <typename T>
    void changeLength2D(T ** &arr, unsigned int oldRow, unsigned int oldCol, unsigned int newRow, unsigned int newCol) {
        T** tempArr = new T*[newRow];
        for (int i=0; i < newRow; i++) {
            tempArr[i] = new T[newCol];
        }

        for (int i=0; i < newRow; i++) {
            for (int j=0; j < newCol; j++) {
                tempArr[i][j] = 0;
            }
        }

        unsigned int minRow = min(oldRow, newRow);
        unsigned int minCol = min(oldCol, newCol);
        for (int i=0; i < minRow; i++) {
            copy(*(arr+i), *(arr+i)+minCol, *(tempArr+i));
        }

        for (int i=0; i < oldRow; i++) {
            delete [] arr[i];
        }
        delete [] arr;

        arr = tempArr;
        tempArr = nullptr;
    }

    void test() {
        cout << "3. " << endl;
        int **arr = new int*[4];
        for (int i=0; i < 4; i++) {
            arr[i] = new int[4];
        }
        for (int i=0; i < 4; i++) {
            for (int j=0; j < 4; j++) {
                arr[i][j] = i + j;
            }
        }

        printArray(arr, 4, 4);

        changeLength2D(arr, 4, 4, 3, 7);
        printArray(arr, 3, 7);

        changeLength2D(arr, 3, 7, 2, 2);
        printArray(arr, 2, 2);

        for (int i=0; i < 2; i++) {
            delete [] arr[i];
        }
        delete [] arr;

    }

}
int main() {
    std::cout << "Hello, World!" << std::endl;
    ChangeLength2D::test();
    return 0;
}