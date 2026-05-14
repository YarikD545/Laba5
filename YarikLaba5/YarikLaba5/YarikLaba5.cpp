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
    int compare(const Fraction& other) const {
        double val1 = toDouble();
        double val2 = other.toDouble();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
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

   
    std::cout << "=== Тестирование Point ===\n";
    Point p1(2, 3);
    Point p2;

    p1.print();
    std::cout << "\n";
    p2.print();
    std::cout << "\n";

    p1.moveUp(5);
    p1.moveRight(3);
    std::cout << "После перемещения: ";
    p1.print();
    std::cout << "\n\n";

    
    std::cout << "=== Тестирование Fraction ===\n";
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    Fraction f3(0.75);

    std::cout << "f1 = ";
    f1.print();
    std::cout << " = " << f1.toDouble() << "\n";

    std::cout << "f2 = ";
    f2.print();
    std::cout << "\n";

    std::cout << "f3 = ";
    f3.print();
    std::cout << "\n";

    Fraction sum = f1.add(f2);
    std::cout << "f1 + f2 = ";
    sum.print();
    std::cout << "\n";

    std::cout << "Сравнение f1 и f2: " << f1.compare(f2) << "\n\n";

    
    std::cout << "=== Тестирование MyVector ===\n";
    MyVector vec;

    std::cout << "Добавляем элементы: ";
    vec.PushBack(10);
    vec.PushBack(20);
    vec.PushBack(30);
    vec.PushFront(5);
    std::cout << vec << "\n";

    vec.Insert(2, 15);
    std::cout << "После вставки 15 на позицию 2: " << vec << "\n";

    vec.RemoveAt(3);
    std::cout << "После удаления элемента с индексом 3: " << vec << "\n";

    vec.SortAsc();
    std::cout << "После сортировки по возрастанию: " << vec << "\n";

    vec.Reverse();
    std::cout << "После реверса: " << vec << "\n";

    std::cout << "Индекс элемента 15: " << vec.IndexOf(15) << "\n";
    std::cout << "Размер: " << vec.getSize() << ", Емкость: " << vec.getCapacity() << "\n";

    vec.TrimToSize();
    std::cout << "После TrimToSize - Емкость: " << vec.getCapacity() << "\n";

    MyVector vec2 = vec; 
    std::cout << "Копия вектора: " << vec2 << "\n";
    std::cout << "Векторы равны? " << (vec == vec2 ? "Да" : "Нет") << "\n";

    
    std::cout << "\n=== Тестирование MyVector: Remove ===\n";
    vec.PushBack(15);
    vec.PushBack(15);
    std::cout << "Вектор перед удалением 15: " << vec << "\n";

    vec.Remove(15, true); 
    std::cout << "После Remove(15, true):    " << vec << "\n";

   
    std::cout << "\n=== Тестирование MyVector: Clone ===\n";
    
    MyVector* clonedVec = vec.Clone();

    std::cout << "Клонированный вектор:      ";
    clonedVec->Print();
    std::cout << "\n";

    // Проверка, что это глубокая копия (меняем оригинал, клон не меняется)
    vec.PushBack(999);
    std::cout << "Оригинал после PushBack:   " << vec << "\n";
    std::cout << "Клон остался прежним:      ";
    clonedVec->Print();
    std::cout << "\n";

   
    delete clonedVec;

    std::cout << "\nНажмите Enter, чтобы выйти...";
    std::cin.ignore(1000, '\n');
    std::cin.get(); 

    return 0;
}