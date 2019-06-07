#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// 15.
// 1. 假设无符号长整型、无符号整型都占用 4 字节（所以这些类型的对象范围是 0~2^31-1），那么在程序 1-13 中，可容许的货币最大和最小值是多少？
// 2. 在程序 1-13 中，假设美元和美分都改为整型，那么可容许的货币的最大和最小值是多少
// 3. 在程序 1-16 的 add 中，为了确保从 Currency 类型转换成 long int 类型时不会发生错误， a1 和 a2 最大可能的值应该是多少？
namespace MaxAndMin{
    // 1-13
    enum SignType {PLUS, MINUS};
    class Currency {
    private:
        SignType m_signType;
        unsigned long m_dollars;
        unsigned int m_cents;
    };
    void test() {
        cout << "15: " << endl;
        cout << "1 : " << endl;
        cout << "max of m_dollars = 2^31 - 1" << endl;
        cout << "max of m_cents = 99" << endl;
        cout << "max of currency = $(2^31 - 1).99" << endl;
        cout << "min of currency = -$(2^31 - 1).99" << endl;

        cout << "2. " << endl;
        cout << "-2^15 <= m_dollar << 2^15 - 1" << endl;
        cout << "max of currency = $(2^15 - 1).99" << endl;
        cout << "min of currency = -$(2^15).99" << endl;

        cout << "3. " << endl;
        cout << "-2^31 <= long int <= 2^31 -1" << endl;
        cout << "a1 + a2 <= 2^31 - 1" << endl;


    }
}

// 16. 扩展程序 1-13 的类 currency，添加下列成员函数
// 1). input() 从标准输入流中读取 currency 的值，然后赋给调用对象
// 2). subtract(x) 从调用对象中减去参数对象 x 的值，然后返回结果
// 3). percent(x) 返回一个 currency 类的对象，它的值是调用对象的 x%。x 的数据类型为 double
// 4). multiply(x) 返回一个 currency 类的对象，它的值是调用对象和 double 型数 x 的乘积
// 5). divide(x) 返回一个 currency 类的对象，它的值是调用对象除以 double 型数 x 的结果
// 1-13
namespace CurrencySpace{
    enum SignType{PLUS, MINUS};
    class Currency {
    public:
        explicit Currency(SignType theSign=PLUS,
                          unsigned long theDollars = 0,
                          unsigned int theCents = 0);
        ~Currency() = default;

        void setValue(SignType theSign, unsigned long theDollars, unsigned int theCents);
        void setValue(double theAmount);

        SignType getSign() const {return m_signType;}
        unsigned long getDollars() const {return m_dollars;}
        unsigned int getCents() const {return m_cents;}

        Currency add(const Currency &currency) const;
        Currency& increment(const Currency& currency);

        void output() const;

        void input();
        Currency subtract(const Currency &currency) const;
        Currency percent(double x) const;
        Currency multiply(double x) const;
        Currency divide(double x) const;

    private:
        SignType m_signType;
        unsigned long m_dollars;
        unsigned int m_cents;
    };

    Currency::Currency(CurrencySpace::SignType theSign, unsigned long theDollars, unsigned int theCents):
            m_signType(theSign), m_dollars(theDollars), m_cents(theCents){
    }
    void Currency::setValue(CurrencySpace::SignType theSign, unsigned long theDollars, unsigned int theCents) {

        if (theCents > 99) {
            throw "Cents should be < 100";
        }

        this->m_signType = theSign;
        this->m_dollars = theDollars;
        this->m_cents = theCents;

    }
    void Currency::setValue(double theAmount) {

        if (theAmount < 0) {
            this->m_signType = SignType::MINUS;
            theAmount = -theAmount;
        } else {
            this->m_signType = SignType::PLUS;
        }

        this->m_dollars = (unsigned long) theAmount;

        theAmount += 0.005;  // 四舍五入 // 10.2
        this->m_cents = (unsigned int)((theAmount - this->m_dollars)*100);
    }
    // 这里有一个类型转换问题，如果原始数据比较大，则会产生溢出
    Currency Currency::add(const CurrencySpace::Currency &currency) const {
        long amountThis = this->m_dollars * 100 + this->m_cents;
        long amountCurrency = currency.m_dollars * 100 + currency.m_cents;

        if (this->m_signType == SignType::MINUS) {
            amountThis = -amountThis;
        }
        if (currency.m_signType == SignType::MINUS) {
            amountCurrency = -amountCurrency;
        }

        double sum = double(amountCurrency + amountThis)/100.0;

        Currency result;
        result.setValue(sum);
        return result;
    }
    Currency& Currency::increment(const CurrencySpace::Currency &currency) {
        long amountThis = this->m_dollars * 100 + this->m_cents;
        long amountCurrency = currency.m_dollars * 100 + currency.m_cents;

        if (this->m_signType == SignType::MINUS) {
            amountThis = -amountThis;
        }
        if (currency.m_signType == SignType::MINUS) {
            amountCurrency = -amountCurrency;
        }

        long sum = amountThis + amountCurrency;
        this->setValue(double(sum/100.0));
        return (*this);
    }
    void Currency::output() const {
        if (this->m_signType == MINUS) {
            cout << "-";
        }
        cout << "$";
        cout << this->m_dollars;
        cout << ".";
        if (this->m_cents < 10) {
            cout << 0;
        }
        cout << this->m_cents << endl;
    }
    void Currency::input() {
        string inputCurrency;
        cin >> inputCurrency;

        SignType signType;
        unsigned long dollars = 0;
        unsigned int cents = 0;

        int index;
        if (inputCurrency[0] == '-') {
            signType = SignType::MINUS;
            index = 2;
        } else {
            signType = SignType::PLUS;
            index = 1;
        }

        while (index < inputCurrency.size() && inputCurrency[index] != '.') {
            dollars *= 10;
            dollars += inputCurrency[index] - '0';
            index++;
        }
        index++;
        unsigned long numberSizeAfterDot = inputCurrency.size() - index;
        double tempCents = 0;
        double mask = 0.1;
        while (index < inputCurrency.size()) {
            tempCents += (inputCurrency[index] - '0') * mask;
            mask *= 0.1;
            index++;
        }
        cents = (unsigned int)(tempCents * (100 > pow(10, numberSizeAfterDot) ? 100 : pow(10, numberSizeAfterDot)));

        this->setValue(signType, dollars, cents);

    }
    Currency Currency::subtract(const CurrencySpace::Currency &currency) const {
        long int thisAmount = this->m_dollars * 100 + this->m_cents;
        long int currencyAmount = currency.m_dollars * 100 + currency.m_cents;

        if (this->m_signType == SignType::MINUS) {
            thisAmount = -thisAmount;
        }
        if (currency.m_signType == SignType::MINUS) {
            currencyAmount = -currencyAmount;
        }

        double amount = double(thisAmount - currencyAmount) / 100.0;
        Currency result;
        result.setValue(amount);
        return result;
    }
    Currency Currency::percent(double x) const {
        long int amount = this->m_dollars * 100 + this->m_cents;
        if (this->m_signType == SignType::MINUS) {
            amount = -amount;
        }

        double percentX = amount * (x / 100.0);
        percentX /= 100.0;

        Currency result;
        result.setValue(percentX);
        return result;
    }
    Currency Currency::multiply(double x) const {
        long int amount = this->m_dollars * 100 + this->m_cents;
        if (this->m_signType == SignType::MINUS) {
            amount = -amount;
        }

        double multiplyAmount = amount * x / 100.0;

        Currency result;
        result.setValue(multiplyAmount);
        return result;
    }
    Currency Currency::divide(double x) const {
        long int amount = this->m_dollars * 100 + this->m_cents;
        if (this->m_signType == SignType::MINUS) {
            amount = -amount;
        }

        double dividedAmount = amount / x / 100.0;

        Currency result;
        result.setValue(dividedAmount);
        return result;
    }
    void test() {
        cout << "16. Currency: " << endl;
        Currency currency(MINUS, 10, 29);
        currency.output();

        Currency newCurrency;
        newCurrency.setValue(-100);
        newCurrency.output();

        newCurrency.setValue(PLUS, 20, 30);
        newCurrency.output();

        currency = currency.add(newCurrency);
        currency.output();

        newCurrency.increment(currency);
        newCurrency.output();

        currency.input();
        currency.output();

        currency = currency.subtract(newCurrency);
        currency.output();

        currency = currency.percent(10.0);
        currency.output();

        currency = currency.multiply(2.3);
        currency.output();

        currency = currency.divide(2.3);
        currency.output();

        currency = currency.multiply(10.0);
        currency.output();
    }
}

// 17. 使用程序1-19 完成练习16
// 1-19
namespace CurrencySpace2{
    enum SignType{PLUS, MINUS};
    class Currency {
    public:
        explicit Currency(SignType signType = SignType::PLUS,
                          unsigned long dollars = 0,
                          unsigned int cents = 0);
        ~Currency() = default;
        void setValue(SignType signType, unsigned long dollars, unsigned int cents);
        void setValue(double amount);
        SignType getSign() const;
        unsigned long getDollars() const;
        unsigned int getCents() const;
        Currency add(const Currency &currency) const;
        Currency& increment(const Currency &currency);
        void output() const;

        void input();
        Currency subtract(const Currency &currency) const;
        Currency percent(double x) const;
        Currency multiply(double x) const;
        Currency divide(double x) const;

    private:
        long m_amount;
    };
    Currency::Currency(CurrencySpace2::SignType signType, unsigned long dollars, unsigned int cents) {
        this->setValue(signType, dollars, cents);
    }
    void Currency::setValue(CurrencySpace2::SignType signType, unsigned long dollars, unsigned int cents) {
        if (cents > 99) {
            throw "cents should < 99";
        }

        this->m_amount = dollars * 100 + cents;
        if (signType == SignType::MINUS) {
            this->m_amount = - this->m_amount;
        }
    }
    void Currency::setValue(double amount) {
        if (amount < 0) {
            amount -= 0.005;
        } else {
            amount += 0.005;
        }
        this->m_amount = long (amount * 100);
    }
    SignType Currency::getSign() const {
        if (this->m_amount < 0) {
            return SignType::MINUS;
        }
        return SignType::PLUS;
    }
    unsigned long Currency::getDollars() const {
        unsigned long amount;
        if (this->m_amount < 0) {
            amount = - this->m_amount;
        } else {
            amount = this->m_amount;
        }
        return amount / 100;
    }
    unsigned int Currency::getCents() const {
        unsigned long amount;
        if (this->m_amount < 0) {
            amount = -this->m_amount;
        } else {
            amount = this->m_amount;
        }
        return amount % 100;
    }
    Currency Currency::add(const CurrencySpace2::Currency &currency) const {

        double sum = double(this->m_amount + currency.m_amount) / 100.0;
        Currency result;
        result.setValue(sum);
        return result;

    }
    Currency& Currency::increment(const CurrencySpace2::Currency &currency) {

        long amount = this->m_amount + currency.m_amount;
        this->setValue(double(amount) / 100.0);
        return *this;
    }
    void Currency::output() const {
        if (this->getSign() == SignType::MINUS) {
            cout << "-";
        }
        cout << "$";
        cout << this->getDollars();
        cout << ".";
        if (this->getCents() < 10) {
            cout << "0";
        }
        cout << this->getCents() << endl;
    }

    void Currency::input() {
        string amountString;
        cin >> amountString;

        SignType signType;
        unsigned long dollars = 0;
        unsigned int cents = 0;

        int index;
        if (amountString[0] == '-') {
            signType = SignType::MINUS;
            index = 2;
        } else {
            signType = SignType::PLUS;
            index = 1;
        }

        while (index < amountString.size() && amountString[index] != '.') {
            dollars *= 10;
            dollars += amountString[index] - '0';
            index++;
        }
        index++;
        unsigned long numberSizeAfterDot = amountString.size() - index;
        double tempCents = 0;
        double mask = 0.1;
        while (index < amountString.size()) {
            tempCents += (amountString[index] - '0') * mask;
            mask *= 0.1;
            index++;
        }
        cents = (unsigned int)(tempCents * (100 > pow(10, numberSizeAfterDot) ? 100 : pow(10, numberSizeAfterDot)));
        cout << cents;
        this->setValue(signType, dollars, cents);
    }
    Currency Currency::subtract(const CurrencySpace2::Currency &currency) const {

        long amount = this->m_amount - currency.m_amount;

        Currency result;
        result.setValue(double(amount) / 100.0);
        return result;
    }
    Currency Currency::percent(double x) const {

        double percentX = this->m_amount * x / 100.0;

        Currency result;
        result.setValue(percentX / 100.0);
        return result;
    }

    Currency Currency::multiply(double x) const {
        Currency currency;
        currency.setValue(this->m_amount * x / 100); //类内可以直接访问私有成员变量
        return currency;
    }

    Currency Currency::divide(double x) const {
        Currency currency;
        currency.setValue(this->m_amount / x / 100);
        return currency;
    }
    void test() {
        cout << "17. Currency2: " << endl;
        Currency currency(MINUS, 10, 29);
        currency.output();

        Currency newCurrency;
        newCurrency.setValue(-100);
        newCurrency.output();

        newCurrency.setValue(PLUS, 20, 30);
        newCurrency.output();

        currency = currency.add(newCurrency);
        currency.output();

        newCurrency.increment(currency);
        newCurrency.output();

        currency.input();
        currency.output();

        currency = currency.subtract(newCurrency);
        currency.output();

        currency = currency.percent(10.0);
        currency.output();

        currency = currency.multiply(2.3);
        currency.output();

        currency = currency.divide(2.3);
        currency.output();

        currency = currency.multiply(10.0);
        currency.output();
    }
}

// 18.
// 1. 使用程序 1-22 完成练习 16。重载 >>、-、%、* 和 \。当重载 >> 时，将其声明为友员函数，不要定义公有输入函数来支持输入操作
// 2. 重载赋值操作符 = 来替代成员函数 setValue。
//    形式为 operator=(int x) 的重载，它替代了具有三个参数的成员函数 setValue，x 把符号、美元和美分都集中在一个整数里。
//    形式为 operator=(double x) 的重载，替代的是仅有一个参数的成员函数 setValue.
namespace CurrencyOverloading {
    enum SignType {PLUS, MINUS};
    class Currency {
    public:
        explicit Currency (SignType theSign = SignType::PLUS,
                 unsigned long theDollars = 0,
                 unsigned int theCents = 0);
        ~ Currency() = default;
        void setValue(SignType theSign, unsigned long theDollars, unsigned int theCents);
        void setValue(double amount);
        SignType getSign() const;
        unsigned long getDollars() const;
        unsigned int getCents() const;
        Currency operator+(const Currency &currency) const;
        Currency& operator+=(const Currency &currency);
        void output() const;

        Currency operator-(const Currency& currency) const;
        Currency operator*(double x) const;
        Currency operator/(double x) const;
        Currency operator%(double x) const;
        Currency& operator=(int x);
        Currency& operator=(double x);

        friend istream& operator>>(istream &in, Currency& currency);
        friend ostream& operator<<(ostream &out, const Currency& currency);

    private:
        long m_amount;
    };
    Currency::Currency(CurrencyOverloading::SignType theSign, unsigned long theDollars, unsigned int theCents) {
        this->setValue(theSign, theDollars, theCents);
    }
    void Currency::setValue(CurrencyOverloading::SignType theSign, unsigned long theDollars, unsigned int theCents) {
        if (theCents > 99) {
            throw "cents > 99";
        }
        long amount = (long)theDollars * 100 + theCents;
        if (theSign == SignType::MINUS) {
            amount = -amount;
        }
        this->m_amount = amount;
    }
    void Currency::setValue(double amount) {

        if (amount < 0) {
            amount -= 0.005;
        } else {
            amount += 0.005;
        }

        this->m_amount = long(amount * 100);
    }
    SignType Currency::getSign() const {
        if (m_amount < 0) {
            return SignType::MINUS;
        }
        return SignType::PLUS;
    }
    unsigned long Currency::getDollars() const {
        unsigned long amount;
        if (this->m_amount < 0) {
            amount = -this->m_amount;
        } else {
            amount = this->m_amount;
        }

        return amount / 100;
    }
    unsigned int Currency::getCents() const {
        unsigned long amount;
        if (this->m_amount < 0) {
            amount = -this->m_amount;
        } else {
            amount = this->m_amount;
        }
        return amount - this->getDollars() * 100;
    }
    Currency Currency::operator+(const CurrencyOverloading::Currency &currency) const {

        long amount = this->m_amount + currency.m_amount;

        Currency result;
        result.setValue(amount / 100.0);
        return result;
    }
    Currency& Currency::operator+=(const CurrencyOverloading::Currency &currency) {
        this->m_amount += currency.m_amount;
        return (*this);
    }
    void Currency::output() const {
        if (this->getSign() == SignType::MINUS) {
            cout << "-";
        }
        cout << "$";
        cout << this->getDollars();
        cout << ".";
        if (this->getCents() < 10) {
            cout << "0";
        }
        cout << this->getCents();
        cout << endl;
    }

    Currency Currency::operator-(const CurrencyOverloading::Currency &currency) const {
        long amount = this->m_amount - currency.m_amount;

        Currency result;
        result.setValue(amount / 100.0);
        return result;
    }
    Currency Currency::operator*(double x) const {
        double amount = this->m_amount * x;

        Currency result;
        result.setValue(amount);
        return result;
    }
    Currency Currency::operator/(double x) const {
        double amount = this->m_amount / x;

        Currency result;
        result.setValue(amount);
        return result;
    }
    Currency Currency::operator%(double x) const {
        double amount = this->m_amount * x;

        Currency result;
        result.setValue(amount);
        return result;
    }
    Currency& Currency::operator=(int x) {
        this->m_amount = x * 100;
        return *this;
    }
    Currency& Currency::operator=(double x) {
        this->m_amount = long(x * 100);
        return *this;
    }
    istream& operator>>(istream &in, Currency &currency) {
        string amount;
        in >> amount;

        SignType signType = SignType::PLUS;
        unsigned long dollars = 0;
        unsigned int cents = 0;

        int index = 0;
        if (amount[index] == '-') {
            signType = SignType::MINUS;
            index = 2;
        } else {
            signType = SignType::PLUS;
            index = 1;
        }

        while (index < amount.size() && amount[index] != '.') {
            dollars *= 10;
            dollars += amount[index] - '0';
            index++;
        }
        index++;
        unsigned long numberSizeAfterDot = amount.size() - index;
        double tempCents = 0;
        double mask = 0.1;
        while (index < amount.size()) {
            tempCents += (amount[index] - '0') * mask;
            mask *= 0.1;
            index++;
        }
        tempCents += 0.005;
        cents = (unsigned int)(tempCents * (100 > pow(10, numberSizeAfterDot) ? 100 : pow(10, numberSizeAfterDot)));

        currency.setValue(signType, dollars, cents); // 假设输入为 1.0234，仍然会出现 cents > 99 的情况
        return in;
    }
    ostream& operator<<(ostream &out, const Currency &currency) {
        if (currency.getSign() == SignType::MINUS) {
            out << "-";
        }
        out << "$";
        out << currency.getDollars();
        out << ".";
        if (currency.getCents() < 10) {
            out << "0";
        }
        out << currency.getCents();
        out << endl;
        return out;
    }
    void test() {
        cout << "18. " << endl;
        Currency currency;
        currency.output();

        currency.setValue(100.01);
        currency.output();

        currency.setValue(SignType::MINUS, 20, 12);
        currency.output();

        Currency currency1(SignType::PLUS, 13, 32);
        Currency sum = currency + currency1;
        sum.output();

        currency += currency1;
        currency.output();

//        try {
//            currency.setValue(SignType::MINUS, 20, 123);
//        } catch (char const * e) {
//            cout << e << endl;
//        }

        cin >> currency;
        cout << currency;

        currency = 10;
        cout << currency;

        currency = -20.1;
        cout << currency;

    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    MaxAndMin::test();
    CurrencySpace::test();
    CurrencySpace2::test();
    CurrencyOverloading::test();
    return 0;
}