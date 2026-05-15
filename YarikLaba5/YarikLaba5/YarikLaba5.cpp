#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <windows.h>


class Point {
private:
    double x;
    double y;

public:

    Point() : x(0), y(0) {}


    Point(double x, double y) : x(x), y(y) {}


    double getX() const { return x; }
    double getY() const { return y; }


    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }

    // Методы перемещения
    void moveUp(double distance) { y += distance; }
    void moveDown(double distance) { y -= distance; }
    void moveLeft(double distance) { x -= distance; }
    void moveRight(double distance) { x += distance; }


    void print() const {
        std::cout << "Point(" << x << ", " << y << ")";
    }
};


class Fraction {
private:
    int numerator;   
    int denominator; 

    // Вспомогательный метод для нахождения НОД
    int gcd(int a, int b) const {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Приведение знака: знаменатель всегда положительный
    void normalize() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор по умолчанию
    Fraction() : numerator(0), denominator(1) {}

    // Конструктор с одним параметром (десятичная дробь)
    Fraction(double decimal) {
        const double EPS = 1e-10;
        int sign = (decimal < 0) ? -1 : 1;
        decimal = std::abs(decimal);

        int precision = 1000000;
        numerator = static_cast<int>(std::round(decimal * precision));
        denominator = precision;

        // Сокращаем полученную дробь
        int divisor = gcd(numerator, denominator);
        numerator = sign * numerator / divisor;
        denominator /= divisor;
    }

    // Конструктор с 2 параметрами
    Fraction(int num, int den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен 0");
        }
        numerator = num;
        denominator = den;
        normalize();
    }


    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }


    void setNumerator(int num) {
        numerator = num;
        normalize();
    }

    void setDenominator(int den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен 0");
        }
        denominator = den;
        normalize();
    }

    // Показ дроби на экран
    void print() const {
        if (denominator == 1)
            std::cout << numerator;
        else if (numerator == 0)
            std::cout << 0;
        else
            std::cout << numerator << "/" << denominator;
    }

    // Возврат значения типа double
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Сокращение дроби
    void reduce() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
        normalize();
    }

    // Сравнение дробей
    void compare(const Fraction& other) const {
        double val1 = toDouble();
        double val2 = other.toDouble();
        if (val1 < val2) std::cout << "Первое число меньше второго " << val1 << " < " << val2 << "\n";
        if (val1 > val2) std::cout << "Первое число больше второго " << val1 << " > " << val2 << "\n";
    }

    // Арифметические операции
    Fraction add(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction subtract(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction multiply(const Fraction& other) const {
        return Fraction(
            numerator * other.numerator,
            denominator * other.denominator
        );
    }

    Fraction divide(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Деление на ноль");
        }
        return Fraction(
            numerator * other.denominator,
            denominator * other.numerator
        );
    }
};


class MyVector {
private:
    int* data;      
    int size;       
    int capacity;   

    
    void EnsureCapacity(int required) {
        if (required > capacity) {
            int newCapacity = static_cast<int>(capacity * 1.5) + 1;
            if (newCapacity < required) {
                newCapacity = required;
            }

            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

public:
    
    MyVector() : size(0), capacity(10) {
        data = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }
    }

    
    MyVector(int cap) : size(0), capacity(cap) {
        if (cap <= 0) {
            throw std::invalid_argument("Capacity должен быть положительным");
        }
        data = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }
    }

    
    MyVector(const MyVector& other) : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    
    ~MyVector() {
        delete[] data;
    }

    
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }

    
    void Print() const {
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]";
    }

    
    void PushBack(int value) {
        EnsureCapacity(size + 1);
        data[size++] = value;
    }

    
    void PushFront(int value) {
        EnsureCapacity(size + 1);
        for (int i = size; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    
    void Insert(int index, int value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        EnsureCapacity(size + 1);
        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

   
    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    
    void Remove(int value, bool removeAll = true) {
        int newSize = 0;
        for (int i = 0; i < size; i++) {
            if (data[i] != value) {
                data[newSize++] = data[i];
            }
            else if (!removeAll) {
                for (int j = i + 1; j < size; j++) {
                    data[newSize++] = data[j];
                }
                size = newSize;
                return;
            }
        }
        size = newSize;
    }


    void PopFront() {
        if (size == 0) return;
        RemoveAt(0);
    }


    void PopBack() {
        if (size == 0) return;
        size--;
    }


    void Clear() {
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        size = 0;
    }


    bool IsEmpty() const {
        return size == 0;
    }


    void TrimToSize() {
        if (size == capacity) return;

        int* newData = new int[size];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = size;
    }

   
    int IndexOf(int value) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) return i;
        }
        return -1;
    }


    int LastIndexOf(int value) const {
        for (int i = size - 1; i >= 0; i--) {
            if (data[i] == value) return i;
        }
        return -1;
    }

  
    void Reverse() {
        for (int i = 0; i < size / 2; i++) {
            std::swap(data[i], data[size - 1 - i]);
        }
    }

    // Быстрая сортировка (возрастание)
    void SortAsc() {
        std::sort(data, data + size);
    }

    // Быстрая сортировка (убывание)
    void SortDesc() {
        std::sort(data, data + size, std::greater<int>());
    }

    
    void Shuffle() {
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            std::swap(data[i], data[j]);
        }
    }

    
    void RandomFill(int minVal = 0, int maxVal = 100) {
        for (int i = 0; i < size; i++) {
            data[i] = minVal + rand() % (maxVal - minVal + 1);
        }
    }

    
    bool Equals(const MyVector* other) const {
        if (other == nullptr) return false;
        if (size != other->size) return false;

        for (int i = 0; i < size; i++) {
            if (data[i] != other->data[i]) return false;
        }
        return true;
    }


    int GetElementAt(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    // Clone
    MyVector* Clone() const {
        return new MyVector(*this);
    }

    // Перегрузка оператора =
    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // Перегрузка оператора []
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }

    // Перегрузка оператора ==
    bool operator==(const MyVector& other) const {
        return Equals(&other);
    }

    // Дружественные функции для >> и <<
    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec);
    friend std::istream& operator>>(std::istream& is, MyVector& vec);
};

// Перегрузка оператора <<
std::ostream& operator<<(std::ostream& os, const MyVector& vec) {
    os << "[";
    for (int i = 0; i < vec.size; i++) {
        os << vec.data[i];
        if (i < vec.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

// Перегрузка оператора >>
std::istream& operator>>(std::istream& is, MyVector& vec) {
    int value;
    is >> value;
    vec.PushBack(value);
    return is;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(nullptr)));

    // ==================== Point ====================
    std::cout << "==================== Point ====================\n";

    // Конструкторы
    Point p1;                     // по умолчанию
    Point p2(2, 3);              // с параметрами
    std::cout << "p1: "; p1.print(); std::cout << "\n";
    std::cout << "p2: "; p2.print(); std::cout << "\n";

    // getX / getY
    std::cout << "p2.getX() = " << p2.getX() << ", p2.getY() = " << p2.getY() << "\n";

    // setX / setY
    p1.setX(5);
    p1.setY(7);
    std::cout << "p1 после setX(5), setY(7): "; p1.print(); std::cout << "\n";

    // moveUp / moveDown / moveLeft / moveRight
    p2.moveUp(2);
    p2.moveRight(3);
    p2.moveDown(1);
    p2.moveLeft(1);
    std::cout << "p2 после всех перемещений: "; p2.print(); std::cout << "\n";

    // print
    std::cout << "print p1: "; p1.print(); std::cout << "\n\n";

    // ==================== Fraction ====================
    std::cout << "==================== Fraction ====================\n";

    // Конструкторы
    Fraction f1;                  // 0/1
    Fraction f2(3, 4);           // 3/4
    Fraction f3(0.75);           // из double
    std::cout << "f1: "; f1.print(); std::cout << " = " << f1.toDouble() << "\n";
    std::cout << "f2: "; f2.print(); std::cout << " = " << f2.toDouble() << "\n";
    std::cout << "f3 (из 0.75): "; f3.print(); std::cout << " = " << f3.toDouble() << "\n";

    // getNumerator / getDenominator
    std::cout << "f2 числитель = " << f2.getNumerator() << ", знаменатель = " << f2.getDenominator() << "\n";

    // setNumerator / setDenominator
    f1.setNumerator(5);
    f1.setDenominator(8);
    std::cout << "f1 после set: "; f1.print(); std::cout << "\n";

    // toDouble
    std::cout << "f2 как double: " << f2.toDouble() << "\n";

    // reduce
    Fraction f4(8, 12);
    std::cout << "f4 до reduce: "; f4.print();
    f4.reduce();
    std::cout << ", после reduce: "; f4.print(); std::cout << "\n";

    // compare
    std::cout << "Сравнение f2 и f4: "; f2.compare(f4); std::cout << "\n";

    // add / subtract / multiply / divide
    Fraction sum = f2.add(f4);
    Fraction diff = f2.subtract(f4);
    Fraction prod = f2.multiply(f4);
    Fraction quot = f2.divide(f4);
    std::cout << "f2 + f4 = "; sum.print(); std::cout << "\n";
    std::cout << "f2 - f4 = "; diff.print(); std::cout << "\n";
    std::cout << "f2 * f4 = "; prod.print(); std::cout << "\n";
    std::cout << "f2 / f4 = "; quot.print(); std::cout << "\n";

    // print (ещё раз)
    std::cout << "f2: "; f2.print(); std::cout << "\n\n";

    // ==================== MyVector ====================
    std::cout << "==================== MyVector ====================\n";

    // Конструкторы
    MyVector v1;                  // по умолчанию (capacity 10)
    MyVector v2(5);              // с заданной ёмкостью
    MyVector v3(v1);             // копирование
    std::cout << "v1 (пустой): " << v1 << "\n";
    std::cout << "v2 (ёмкость 5): размер " << v2.getSize() << ", ёмкость " << v2.getCapacity() << "\n";
    std::cout << "v3 (копия v1): " << v3 << "\n";

    // getSize / getCapacity
    v1.PushBack(10);
    std::cout << "После PushBack(10): размер v1 = " << v1.getSize() << ", ёмкость = " << v1.getCapacity() << "\n";

    // PushBack / PushFront / Insert
    v1.PushBack(20);
    v1.PushBack(30);
    v1.PushFront(5);
    v1.Insert(2, 15);
    std::cout << "v1 после добавлений: " << v1 << "\n";

    // PopFront / PopBack
    v1.PopFront();
    std::cout << "После PopFront(): " << v1 << "\n";
    v1.PopBack();
    std::cout << "После PopBack(): " << v1 << "\n";

    // RemoveAt
    v1.RemoveAt(1);
    std::cout << "После RemoveAt(1): " << v1 << "\n";

    // Remove (один и все)
    v1.PushBack(15);
    v1.PushBack(15);
    std::cout << "Перед Remove: " << v1 << "\n";
    v1.Remove(15, false);   // удалить только первое вхождение
    std::cout << "После Remove(15, false): " << v1 << "\n";
    v1.Remove(15, true);    // удалить все вхождения
    std::cout << "После Remove(15, true): " << v1 << "\n";

    // Clear / IsEmpty
    v1.Clear();
    std::cout << "После Clear(), IsEmpty? " << (v1.IsEmpty() ? "Да" : "Нет") << "\n";

    // Заполним заново для остальных тестов
    for (int i = 1; i <= 6; i++) v1.PushBack(i * 10); // 10,20,30,40,50,60
    std::cout << "v1 восстановлен: " << v1 << "\n";

    // IndexOf / LastIndexOf
    std::cout << "IndexOf(30) = " << v1.IndexOf(30) << "\n";
    v1.PushBack(30);
    std::cout << "После добавления ещё 30: " << v1 << "\n";
    std::cout << "LastIndexOf(30) = " << v1.LastIndexOf(30) << "\n";

    // Reverse
    v1.Reverse();
    std::cout << "После Reverse: " << v1 << "\n";

    // SortAsc / SortDesc
    v1.SortAsc();
    std::cout << "После SortAsc: " << v1 << "\n";
    v1.SortDesc();
    std::cout << "После SortDesc: " << v1 << "\n";

    // Shuffle
    v1.Shuffle();
    std::cout << "После Shuffle: " << v1 << "\n";

    // RandomFill (нужен предварительный размер)
    MyVector v5(10);
    for (int i = 0; i < 10; i++) v5.PushBack(0);
    v5.RandomFill(10, 99);
    std::cout << "v5 после RandomFill(10,99): " << v5 << "\n";

    // TrimToSize
    std::cout << "v1 до TrimToSize: ёмкость = " << v1.getCapacity() << "\n";
    v1.TrimToSize();
    std::cout << "v1 после TrimToSize: ёмкость = " << v1.getCapacity() << "\n";

    // GetElementAt
    std::cout << "Элемент v1 с индексом 2: " << v1.GetElementAt(2) << "\n";

    // Clone
    MyVector* cloned = v1.Clone();
    std::cout << "Клон v1: " << *cloned << "\n";

    // operator= (уже использовался при создании v3, но покажем явно)
    MyVector v6;
    v6 = v1;
    std::cout << "v6 после operator=: " << v6 << "\n";

    // operator[]
    v1[0] = 999;
    std::cout << "После v1[0] = 999: " << v1 << "\n";
    std::cout << "v1[1] = " << v1[1] << "\n";

    // operator==
    std::cout << "v1 == v6? " << (v1 == v6 ? "Да" : "Нет") << "\n";
    v6 = v1;
    std::cout << "После v6 = v1, v1 == v6? " << (v1 == v6 ? "Да" : "Нет") << "\n";

    // Print (метод, не оператор)
    std::cout << "v1.Print(): "; v1.Print(); std::cout << "\n";

    // operator<< (уже используется везде, но покажем явно)
    std::cout << "operator<<: " << v1 << "\n";

    // operator>> (ввод одного числа)
    MyVector v7;
    std::cout << "Введите число для добавления в v7: ";
    std::cin >> v7;
    std::cout << "v7 после operator>>: " << v7 << "\n";

    // Equals (метод)
    std::cout << "v1.Equals(&v6)? " << (v1.Equals(&v6) ? "Да" : "Нет") << "\n";

    // Чистим клон
    delete cloned;

    std::cout << "\nНажмите Enter, чтобы выйти...";
    std::cin.ignore(1000, '\n');
    std::cin.get();

    return 0;
}