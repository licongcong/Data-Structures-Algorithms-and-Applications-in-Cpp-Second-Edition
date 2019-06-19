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
        bool operator==(const ArrayList<T> &arrayList) const;
        bool operator!=(const ArrayList<T> &arrayList) const;
        bool operator<(const ArrayList<T> &arrayList) const;
        void push_back(T theElement);
        void pop_back();
        void swap(ArrayList<T> &arrayList);
        void reserve(int theCapacity);
        T set(int theIndex, T theElement);
        void clear();
        void removeRange(int start, int end);
        int lastIndexOf(T theElement) const;

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
        this->m_listSize = arrayList.size();
        this->m_arrayLength = arrayList.capacity();
        this->m_element = new T[this->size()];
        copy(arrayList.m_element, arrayList.m_element+arrayList.size(), this->m_element);
    }

    template <typename T>
    ArrayList<T>::~ArrayList() {
        delete [] this->m_element;
    }

    template <typename T>
    T ArrayList<T>::get(int index) const {
        if (index < 0 || index >= this->size()) {
            throw "index of out range";
        }
        return this->m_element[index];
    }

    template <typename T>
    int ArrayList<T>::indexOf(T x) const {
        int result = -1;

        int findResult = find(this->m_element, this->m_element+this->size(), x) - this->m_element;
        if (findResult == this->size()) {
            result = -1;
        } else {
            result = findResult;
        }
        return result;
    }

    template <typename T>
    void ArrayList<T>::erase(int index) {

        if (index < 0 || index >= this->size()) {
            throw "index out of range";
        }

        copy(this->m_element+index+1, this->m_element+this->size(), this->m_element+index);
        this->m_element[this->size()].~T(); // 调用析构函数，防止因为是自定义对象类型元素而造成内在泄露
        this->m_listSize--;
    }

    template <typename T>
    void ArrayList<T>::insert(int index, T x) {
        if (index < 0 || index > this->size()) { // 确认插入位置是否有效, [0, m_listSize] 之间
            throw "index out of range";
        }
        if (this->size() == this->capacity()) {
            int arrayLength = this->size() * this->m_factor;
            T *tempArray = new T[arrayLength];
            copy(this->m_element, this->m_element+this->size(), tempArray);
            delete [] this->m_element;
            this->m_element = tempArray;
            tempArray = nullptr;
            this->m_arrayLength = arrayLength;
        }

        copy(this->m_element+index, this->m_element+this->size(), this->m_element+index+1);
        this->m_listSize++;
        this->m_element[index] = x;
    }

    template <typename T>
    void ArrayList<T>::output() const {
        copy(this->m_element, this->m_element+this->size(), ostream_iterator<T>(cout, " "));
        cout << endl;
    }

    // 5. 编写一个方法 arrayList<T>::trimToSize，它使数组的长度等于max(listSize, 1).
    // 感觉自己没有看懂这题想干什么 -_-//
    template <typename T>
    void ArrayList<T>::trimToSize(int listSize) {
        int size = max(listSize, 1);

        T *tempArray = new T[size];
        int newSize = min(size, this->size());
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

        if (size == this->capacity()) {
            return;
        }

        T *tempElement = new T[size];
        int newSize = min(size, this->size());
        copy(this->m_element, this->m_element+newSize, tempElement);

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
        if (index >= this->size() || index < 0) {
            throw "index out of range";
        }
        return this->m_element[index];
    }
    template <typename T>
    const T& ArrayList<T>::operator[](int index) const {
        if (index >= this->size() || index < 0) {
            throw "index out of range";
        }
        return this->m_element[index];
    }

    // 8. 重载操作符 == ，使得表达式 x==y 返回 true, 当且仅当两个用数组描述的线性表 x 和 y 相等（即对所有的 i, 两个线性表的第 i 的元素相等
    // 是否需要考虑 arrayLength 是否相同？
    template <typename T>
    bool ArrayList<T>::operator==(const ArrayListSpace::ArrayList<T> &arrayList) const {
        if (this->size() != arrayList.size()) {
            return false;
        }
        int index = 0;
        while (index < this->size()) {
            if (this->m_element[index] != arrayList[index]) {
                return false;
            }
            index++;
        }
        return true;

    }

    // 9. 重载操作符 !=，使得表达式 x!=y 返回 true, 当且仅当两个用数组描述的线性表 x 和 y 不相等
    template <typename T>
    bool ArrayList<T>::operator!=(const ArrayListSpace::ArrayList<T> &arrayList) const {
        if (this->size() != arrayList.size()) {
            return true;
        }
        int index = 0;
        while (index < this->size()) {
            if (this->m_element[index] != arrayList[index]) {
                return true;
            }
            index++;
        }
        return false;
    }

    // 10. 重载操作符 <，使得线性表 x < y 返回 true, 当且仅当用数组描述的线性表 x 按字典序小于用数组描述的线性表 y
    template <typename T>
    bool ArrayList<T>::operator<(const ArrayListSpace::ArrayList<T> &arrayList) const {
        if (arrayList.empty()) {
            return false;
        }
        if (this->empty()) {
            return true;
        }

        int index = 0;
        int minLength = min(this->m_listSize, arrayList.m_listSize);
        while (index < minLength) {
            if (this->m_element[index] > arrayList[index]) {
                return false;
            }
            index++;
        }
        if (this->size() < arrayList.size()) {
            return true;
        }
        return false;
    }

    // 11. 编写方法 ArrayList<T>::push_back，它把元素 theElement 插到线性表的右端。不要使用 insert 方法
    template <typename T>
    void ArrayList<T>::push_back(T theElement) {
        if (this->size() == this->capacity()) {
            int newArrayLength = this->capacity() * this->m_factor;
            this->setSize(newArrayLength);
        }
        this->m_element[this->size()] = theElement;
        this->m_listSize++;
    }

    // 12. 编写一个 ArrayList<T>::pop_back，它把线性表右端的元素删除。不要使用 erase 方法
    template <typename T>
    void ArrayList<T>::pop_back() {
        if (this->size() == 0) {
            throw "size = 0, nothing to pop";
        }
        this->m_listSize--;
    }

    // 13. 编写方法 ArrayList<T>::swap(theList)，它交换线性表的元素 *this 和 theList
    template <typename T>
    void ArrayList<T>::swap(ArrayListSpace::ArrayList<T> &arrayList) {
        T *tempElement = this->m_element;
        this->m_element = arrayList.m_element;
        arrayList.m_element = tempElement;

        std::swap(this->m_listSize, arrayList.m_listSize);
        std::swap(this->m_arrayLength, arrayList.m_arrayLength);
        std::swap(this->m_factor, arrayList.m_factor);

    }

    // 14. 编写方法 ArrayList<T>::reserve(theCapacity), 它把数组的容量改变为当前容量和 theCapacity 的较大者
    template <typename T>
    void ArrayList<T>::reserve(int theCapacity) {
        if (theCapacity > this->capacity()) {
            this->setSize(theCapacity);
        }

    }

    // 15. 编写方法 ArrayList<T>::set(theIndex, theElement)，它用元素 theElement 代替索引用 theIndex 的元素.
    //     若索引 theIndex 超出范围，则抛出异常。返回原来索引为 theIndex 的元素。
    template <typename T>
    T ArrayList<T>::set(int theIndex, T theElement) {
        if (theIndex >= this->size() || theIndex < 0) {
            throw "index out of range";
        }
        T result = this->m_element[theIndex];
        this->m_element[theIndex] = theElement;
        return result;
    }

    // 16. 编写方法 ArrayList<T>::clear，它使线性表为空。
    template <typename T>
    void ArrayList<T>::clear() {
        this->m_listSize = 0;
    }

    // 17. 编写方法 ArrayList<T>::removeRange, 它删除指定范围内的所有元素。
    template <typename T>
    void ArrayList<T>::removeRange(int start, int end) {
        if (start > end || start >= this->size() || start < 0 || end < 0 || end >= this->size()) {
            throw "wrong range";
        }

        int removeSize = end - start + 1;
        copy(this->m_element+end+1, this->m_element+this->size(), this->m_element+start);
        this->m_listSize -= removeSize;

    }

    // 18. 编写方法 ArrayList<T>::lastIndexOf, 它的返回值是指定元素最后出现时的索引。如果这样的元素不存在，则返回 -1
    template <typename T>
    int ArrayList<T>::lastIndexOf(T theElement) const {
        if (this->empty()) {
            return -1;
        }

        int index = this->size() - 1;
        while (index >= 0) {
            if (this->m_element[index] == theElement) {
                return index;
            }
            index--;
        }
        return -1;
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
        cout << "9. " << endl;
        cout << (arrayList != newList) << endl;
        newList.erase(2);
        cout << (arrayList != newList) << endl;

        cout << "10. " << endl;
        arrayList.output();
        newList.output();
        cout << (arrayList < newList) << endl;
        newList.insert(2, 3);
        arrayList.output();
        newList.output();
        cout << (arrayList < newList) << endl;

        cout << "11. " << endl;
        for (int i=0; i < 10; i++) {
            newList.push_back(i + 10);
            cout << newList.capacity() << " ";
        }
        newList.push_back(4);
        newList.output();

        cout << "12. " << endl;
        for (int i=0; i < 15; i++) {
            try {
                newList.pop_back();
                newList.output();
            } catch (char const *e) {
                cout << e << endl;
            }

        }

        cout << "13. " << endl;
        for (int i=0; i < 5; i++) {
            newList.push_back(i+1);
        }
        newList.output();
        arrayList.output();
        newList.swap(arrayList);
        newList.output();
        arrayList.output();

        cout << "14. " << endl;
        cout << newList.capacity() << endl;
        newList.reserve(20);
        cout << newList.capacity() << endl;

        cout << "15. " << endl;
        try {
            newList.output();
            cout << newList.set(2, 100) << endl;
            newList.output();
        } catch (char const *error) {
            cout << error << endl;
        }
        newList.set(1, 1111);
        newList.output();

        cout << "16. " << endl;
        newList.clear();
        newList.output();

        cout << "17. " << endl;
        arrayList.output();
        for (int i=0; i < 5; i++) {
            arrayList.push_back(i+10);
        }
        arrayList.output();
        arrayList.removeRange(2, 2);
        arrayList.output();
        arrayList.removeRange(2, 5);
        arrayList.output();
        try {
            arrayList.removeRange(2, 10);
        } catch (char const *error) {
            cout << error << endl;
        }

        cout << "18. " << endl;
        arrayList.insert(3, 1);
        arrayList.output();
        cout << arrayList.lastIndexOf(10) << endl;
        cout << arrayList.lastIndexOf(1) << endl;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    ChangeLength2D::test();
    ArrayListSpace::test();
    return 0;
}