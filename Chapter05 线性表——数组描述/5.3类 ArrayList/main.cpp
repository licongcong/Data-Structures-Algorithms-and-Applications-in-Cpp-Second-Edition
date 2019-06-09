#include <iostream>
using namespace std;

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
    explicit ArrayList(int arrayLength); // 构造函数
    ArrayList(const ArrayList<T>& arrayList); // 拷贝构造函数
    virtual ~ArrayList();

    bool empty() const final { return this->m_listSize == 0; }
    int size() const final { return this->m_listSize; }
    T get(int index) const final;
    int indexOf(T x) const final;
    void erase(int index) final;
    void insert(int index, T x) final;
    void output() const final;

private:
    T *m_element;
    int m_arrayLength;
    int m_listSize;

};

template <typename T>
ArrayList<T>::ArrayList(int arrayLength):m_arrayLength(arrayLength){
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

//    for (int i=0; i < this->m_listSize; i++) {
//        if (this->m_element[i] == x) {
//            result = i;
//            break;
//        }
//    }
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

//    for (int i=index; i < this->m_listSize-1; i++) {
//        this->m_element[i] = this->m_element[i+1];
//    }
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
        throw "ArrayList if full";
    }

    copy(this->m_element+index, this->m_element+this->m_listSize, this->m_element+index+1);
//    copy_backward(this->m_element+index, this->m_element+this->m_listSize, this->m_element+index+1);
    this->m_listSize++;
//    for (int i=this->m_listSize; i > index; i--) {
//        this->m_element[i] = this->m_element[i-1];
//    }
    this->m_element[index] = x;
}

template <typename T>
void ArrayList<T>::output() const {
    copy(this->m_element, this->m_element+this->m_listSize, ostream_iterator<T>(cout, " "));
    cout << endl;
}

int main() {

    ArrayList<int> arrayList(10);

    try {
        for (int i=0; i < 11; i++) {
            arrayList.insert(i, i);
            arrayList.output();
        }
    } catch (char const* msg) {
        cout << msg << endl;
    }
    cout << "indexOf(3) = " << arrayList.indexOf(3) << endl;
    cout << "indexOf(11) = " << arrayList.indexOf(11) << endl;

    ArrayList<int> copyArrayList(arrayList);
    copyArrayList.output();
    arrayList.output();

    try {
        for (int i=0; i < 11; i++) {
            arrayList.erase(i);
            arrayList.output();
        }
    } catch (char const* msg) {
        cout << msg << endl;
    }

    return 0;
}