#include <iostream>
using namespace std;

// 3. 编写一个函数 changeLength2D, 用以改变一个二维数组的长度。二维数组的每一维的长度都是可以变化的
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

namespace ArrayListSpace {
    template <typename T>
    class LinerList {
    public:
        virtual ~LinerList() = default;
        virtual bool empty() const = 0; // 若表为空，返回 true，否则返回 false
        virtual int size() const = 0; // 返回线性表的大小（表中元素个数）
        virtual T get(int index) const = 0; // 返回线性表中索引为 index 的元素
        virtual int indexOf(T x) const = 0; // 返回线性表中第一次出现的 x 的索引，若 x 不存在，则返回 -1
        virtual void erase(int index) = 0; // 删除索引为 index 的元素，索引大于 index 的元素其索引减 1
        virtual void insert(int index, T x) = 0; // 把 x 插入到线性表中索引为 index 的位置上索引值大于等于 index 的元素其索引值加 1
        virtual void output() const = 0; // 从左到右输出表元素

    };

    template <typename T>
    class ArrayList final: public LinerList<T> {
    public:
        //explicit ArrayList(int arrayLength); // 构造函数
        explicit ArrayList(int arrayLength, int factor = 2);
        ArrayList(const ArrayList<T>& arrayList); // 拷贝构造函数
        virtual ~ArrayList();

        bool empty() const final { return this->m_listSize == 0; }
        int size() const final { return this->m_listSize; }
        T get(int index) const final;
        int indexOf(T x) const final;
        void erase(int index) final;
        void insert(int index, T x) final;
        void output() const final;
        int capacity() const {return this->m_arrayLength;}
        void trimToSize(int listSize);
        void setSize(int size);
        T& operator[](int index);
        const T&operator[](int index) const;
        bool operator==(const ArrayList<T> &arraylist) const;
    private:
        T *m_element;
        int m_arrayLength;
        int m_listSize;
        int m_factor;

    };

    template <typename T>
    ArrayList<T>::ArrayList(int arrayLength, int factor):m_arrayLength(arrayLength), m_factor(factor) {
        this->m_listSize = 0;
        this->m_element = new T[arrayLength];
    }
    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList<T> &arrayList) {
        this->m_listSize = arrayList.m_listSize;
        this->m_arrayLength = arrayList.m_arrayLength;
        this->m_element = new T[this->m_arrayLength];
        copy(arrayList.m_element, arrayList.m_element+arrayList.m_listSize, this->m_element);
    }

    template <typename T>
    ArrayList<T>::~ArrayList() {
        delete [] this->m_element;
    }

    template <typename T>
    T ArrayList<T>::get(int index) const {
        if (index < 0 || index >= this->m_listSize) {
            throw "index of out range";
        }
        return this->m_element[index];
    }

    template <typename T>
    int ArrayList<T>::indexOf(T x) const {
        int result = -1;

        int findResult = find(this->m_element, this->m_element+this->m_listSize, x) - this->m_element;
        if (findResult == this->m_listSize) {
            result = -1;
        } else {
            result = findResult;
        }
        return result;
    }

    template <typename T>
    void ArrayList<T>::erase(int index) {

        if (index < 0 || index >= this->m_listSize) {
            throw "index out of range";
        }

        copy(this->m_element+index+1, this->m_element+this->m_listSize, this->m_element+index);
        this->m_element[this->m_listSize].~T(); // 调用析构函数，防止因为是自定义对象类型元素而造成内在泄露
        this->m_listSize--;
    }

    template <typename T>
    void ArrayList<T>::insert(int index, T x) {
        if (index < 0 || index > m_listSize) { // 确认插入位置是否有效, [0, m_listSize] 之间
            throw "index out of range";
        }
        if (m_listSize == m_arrayLength) {
            int arrayLength = this->m_arrayLength * this->m_factor;
            T *tempArray = new T[arrayLength];
            copy(this->m_element, this->m_element+this->m_arrayLength, tempArray);
            delete [] this->m_element;
            this->m_element = tempArray;
            tempArray = nullptr;
            this->m_arrayLength = arrayLength;
        }

        copy(this->m_element+index, this->m_element+this->m_listSize, this->m_element+index+1);
        this->m_listSize++;
        this->m_element[index] = x;
    }

    template <typename T>
    void ArrayList<T>::output() const {
        copy(this->m_element, this->m_element+this->m_listSize, ostream_iterator<T>(cout, " "));
        cout << endl;
    }

    // 5. 编写一个方法 arrayList<T>::trimToSize，它使数组的长度等于max(listSize, 1).
    // 感觉自己没有看懂这题想干什么 -_-//
    template <typename T>
    void ArrayList<T>::trimToSize(int listSize) {
        int size = max(listSize, 1);

        T *tempArray = new T[size];
        int newSize = min(size, this->m_listSize);
        copy(this->m_element, this->m_element+newSize, tempArray);
        delete [] this->m_element;
        this->m_element = tempArray;
        tempArray = nullptr;

        this->m_arrayLength = size;
        this->m_listSize = newSize;
    }
    // 6. 编写方法 arrayList<T>::setSize, 它使线性表的大小等于指定的大小。
    // 若线性表开始时的大小小于指定的大小，则不增加元素。
    // 若线性表开始的大小大于指定的大小，则删除多余的元素
    template <typename T>
    void ArrayList<T>::setSize(int size) {
        if (size <= 0) {
            throw "size should > 0";
        }

        if (size == this->m_arrayLength) {
            return;
        }

        T *tempElement = new T[size];
        int newSize = min(size, this->m_listSize);
        copy(this->m_element, this->m_element+this->newSize, tempElement);

        delete [] this->m_element;
        this->m_element = tempElement;
        tempElement = nullptr;

        this->m_listSize = newSize;
        this->m_arrayLength = size;

    }

    // 7. 重载操作符[], 使表达式 x[i]  返回对线性表第 i 个元素的引用
    // 若线性表没有第 i 个元素，则抛出异常。语句 x[i] = y 和　y = x[i] 按预期方式执行
    // 未实现使用 [] 插入元素的功能
    template <typename T>
    T & ArrayList<T>::operator[](int index) {
        if (index >= this->m_listSize || index < 0) {
            throw "index out of range";
        }
        return this->m_element[index];
    }
    template <typename T>
    const T& ArrayList<T>::operator[](int index) const {
        if (index >= this->m_listSize || index < 0) {
            throw "index out of range";
        }
        return this->m_element[index];
    }

    // 8. 重载操作符 == ，使得表达式 x==y 返回 true, 当且仅当两个用数组描述的线性表 x 和 y 相等（即对所有的 i, 两个线性表的第 i 的元素相等
    // 是否需要考虑 arrayLength 是否相同？
    template <typename T>
    bool ArrayList<T>::operator==(const ArrayListSpace::ArrayList<T> &arraylist) const {
        if (this->m_listSize != arraylist.m_listSize) {
            return false;
        }
        int index = 0;
        while (index < this->m_listSize) {
            if (this->m_element[index] != arraylist[index]) {
                return false;
            }
            index++;
        }
        return true;

    }
    void test() {
        ArrayList<int> arrayList(4);
        cout << "4. " << endl;
        for (int i=0; i < 2; i++) {
            arrayList.insert(i, i+1);
//            cout << i << " " << arrayList.capacity() << endl;
        }

        cout << "5. " << endl;
        arrayList.trimToSize(3);
        cout << arrayList.capacity() << endl;
        cout << arrayList.size() << endl;
        arrayList.output();
        cout << "7. " << endl;
        arrayList[1] = 10;
        arrayList.output();
        try {
            arrayList[10] = 10;
        } catch (const char * e) {
            cout << e << endl;
        }
        int y = arrayList[0];
        cout << y << endl;

        cout << "8. " << endl;
        ArrayList<int> newList(3);
//        newList[0] = 1;
//        newList[1] = 10;
        newList.insert(0, 1);
        newList.insert(1, 10);
        arrayList.output();
        newList.output();
        cout << (arrayList == newList) << endl;
//        newList[2] = 3;
        newList.insert(2, 3);
        newList.output();
        cout << (arrayList == newList) << endl;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    ChangeLength2D::test();
    ArrayListSpace::test();
    return 0;
}