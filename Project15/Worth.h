#pragma once

#include "Configuration.h"

// Абстрактный класс "Ценность" с чистыми виртуальными полями
class Worth
{
protected:
    double value;
public:

    virtual double conversion_to_rubbles() const = 0;
    virtual ~Worth() {};

    // Методы ввода/вывода полей для дочерних классов
    virtual void print(ostream& stream) const = 0;
    virtual void scan(istream& stream) = 0;

    // Метод для вывода названия класса
    virtual string myName() const = 0;
};

class Gold : public Worth
{
private:
    double weight;
public:
    Gold();
    Gold(const Gold& obj);

    double conversion_to_rubbles() const { return value * weight; }
    string myName() const { return "Gold"; }

    void print(ostream& stream) const;
    void scan(istream& stream);
};

class Stock : public Worth
{
private:
    int amount;
    string issuer_name;
public:
    Stock();
    Stock(const Stock& obj);

    double conversion_to_rubbles() const { return value * amount; }

    string myName() const { return "Stock"; }

    void print(ostream& stream) const;
    void scan(istream& stream);
};

class Safe
{
private:
    int count_elem;
    Worth** objptr;
public:
    // Конструкторы
    // Конструктор по умолчанию
    Safe();

    // Конструктор с параметрами
    Safe(int _count_elem);

    // Конструктор копирования
    Safe(const Safe& obj);

    string myName() const { return "Safe"; }

    void scan(istream& stream);
    void print(ostream& stream) const;

    double total_amount() const;
    double smallest_amount() const;

    tuple<int, double, int, double> share_of_total_amount() const;

    friend ostream& operator << (ostream& stream, Safe& obj);
    friend istream& operator >> (istream& stream, Safe& obj);
};
