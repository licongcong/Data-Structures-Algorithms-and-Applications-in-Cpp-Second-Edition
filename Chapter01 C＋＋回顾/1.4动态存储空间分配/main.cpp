#include <iostream>
using namespace std;

// 12. 为程序 make2dArray 编写一个通用型算法，它的第三个参数不是整数 numberOfColumns, 而是一维数组 rowSize.
// 它创建一个二维数组，第 i 行的列数是 rowSize[i]
namespace Make2DArray {
    template <typename T>
    void make2dArray(T** &x, int numberOfRows, int rowSize[]) {
        x = new T*[numberOfRows];

        for (int i=0; i < numberOfRows; i++) {
            x[i] = new T[rowSize[i]];
        }
    }

    template <typename T>
    void delete2dArray(T** &x, int numberOfRows, int rowSize[]) {

        for (int i=0; i < numberOfRows; i++) {
            delete [] x[i];
        }

        delete [] x;
        x = nullptr;
    }

    void test() {
        int rowSize[] = {1, 2, 3, 4, 5, 6, 7};
        int **array;
        make2dArray(array, 7, rowSize);

        cout << "12. make2dArray: " << endl;
        for (int i=0; i < 7; i++) {
            for (int j=0; j < rowSize[i]; j++) {
                array[i][j] = j+1;
            }
        }

        for (int i=0; i < 7; i++) {
            for (int j=0; j < rowSize[i]; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        delete2dArray(array, 7, rowSize);
    }
}

// 13. 编写一个模板函数 changeLength1D，它将一个一维数组的长度从 oldLength 变成 newLength
// 函数首先分配一个新的、长度为 newLength 的数组，然后把原数组的前 min{oldLength, newLength} 个元素复制到新数组中，最后释放原数组所占用的空间
namespace ChangeLength1D {
    template <typename T>
    void changeLength1D (T* &array, int oldLength, int newLength) {

        T *temp = new T[newLength];
        for (int i=0; i < newLength; i++) {
            temp[i] = T(0);
        }

        int size = oldLength > newLength ? newLength : oldLength;

        for (int i=0; i < size; i++) {
            temp[i] = array[i];
        }

        delete [] array;
        array = temp;  // 如果不使用传引用的方式，则此赋值无效
        temp = nullptr;

    }

    void test() {
        int oldSize = 10;
        int newSize = 17;

        double *arr = new double[oldSize];

        for (int i=0; i < oldSize; i++) {
            arr[i] = (i+1)*1.01;
        }

        changeLength1D<double>(arr, oldSize, newSize);

        cout << "13. changeLength1D: ";
        for (int i=0; i < newSize; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        delete [] arr;
    }
}

// 14. 编写一个函数 changeLength2D，它改变一个二维数组的大小
namespace ChangeLength2D {
    template <typename T>
    void changeLength2D(T** &arr, int oldRowSize, int oldColumnSize, int newRowSize, int newColumnSize) {

        // 开辟新空间
        T** temp = new T*[newRowSize];

        for (int i=0; i < newRowSize; i++) {
            temp[i] = new T[newColumnSize];
        }
        for (int i=0; i < newRowSize; i++) {
            for (int j=0; j < newColumnSize; j++) {
                temp[i][j] = T(0);
            }
        }

        // 转移元素
        int row = oldRowSize > newRowSize? newRowSize : oldRowSize;
        int column = oldColumnSize > newColumnSize ? newColumnSize : oldColumnSize;

        for (int i=0; i < row; i++) {
            for (int j=0; j < column; j++) {
                temp[i][j] = arr[i][j];
            }
        }

        // 释放旧空间
        for (int i=0; i < oldRowSize; i++) {
            delete [] arr[i];
        }
        delete [] arr;

        arr = temp;
        temp = nullptr;
    }

    void test() {
        int oldRowSize = 4;
        int oldColumnSize = 5;
        int **arr = new int*[4];
        for (int i=0; i < oldRowSize; i++) {
            arr[i] = new int[oldColumnSize];
        }
        for (int i=0; i < oldRowSize; i++) {
            for (int j=0; j < oldColumnSize; j++) {
                arr[i][j] = i+j;
            }
        }

        int newColumnSize = 9;
        int newRowSize = 9;
        changeLength2D(arr, oldRowSize, oldColumnSize, newRowSize, newColumnSize);
        cout << "14. changeLength2D: " << endl;
        for (int i=0; i < newRowSize; i++) {
            for (int j=0; j < newColumnSize; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }

        for (int i=0; i < oldRowSize; i++) {
            delete [] arr[i];
        }
        delete [] arr;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    Make2DArray::test();
    ChangeLength1D::test();
    ChangeLength2D::test();
    return 0;
}