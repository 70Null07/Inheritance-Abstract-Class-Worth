#include "Worth.h"

Gold::Gold()
{
    value = 0;
    weight = 0;
}

Stock::Stock()
{
    value = 0;
    amount = 0;
    issuer_name = "0";
}

Gold::Gold(const Gold& obj)
{
    value = obj.value;
    weight = obj.weight;
}

Stock::Stock(const Stock& obj)
{
    value = obj.value;
    amount = obj.amount;
    issuer_name = obj.issuer_name;
}

void Gold::print(ostream& stream) const
{
    stream << myName() << "\nВес: " << weight << " Стоимость одного грамма: " << value << " Общая стоимость " << conversion_to_rubbles() << endl;
}

void Gold::scan(istream& stream)
{
    cout << "\nВведите вес: ";
    stream >> weight;
    cout << "Введите стоимость одного грамма: ";
    stream >> value;
}

void Stock::print(ostream& stream) const
{
    stream << myName() << "\nНазвание эмитента: " << issuer_name << " Стоимость одной акции: " << value << " Число акций: " << amount << " Общая стоимость " << conversion_to_rubbles() << endl;
}

void Stock::scan(istream& stream)
{
    cout << "\nВведите название эмитента: ";
    stream >> issuer_name;
    cout << "\nВведите стоимость одной акции: ";
    stream >> value;
    cout << "\nВведите количество акций: ";
    stream >> amount;
}

Safe::Safe()
{
    count_elem = 0;
    objptr = NULL;
}

Safe::Safe(int _count_elem)
{
    count_elem = _count_elem;
    objptr = new Worth * [count_elem];
}

Safe::Safe(const Safe& obj)
{
    count_elem = obj.count_elem;
    objptr = new Worth * [count_elem];
    for (int i = 0; i < count_elem; i++)
    {
        objptr[i] = obj.objptr[i];
    }
}

void Safe::scan(istream& stream)
{
    for (int i = 0; i < count_elem; ++i)
    {
        string user_choise;
        cout << "Укажите, что вы хотите ввести (Gold или Stock):\n";
        stream >> user_choise;
        if (user_choise == "Gold")
        {
            Worth* gold = new Gold;
            gold->scan(stream);
            objptr[i] = gold;
        }
        else if (user_choise == "Stock") {
            Worth* stock = new Stock;
            stock->scan(stream);
            objptr[i] = stock;
        }
    }
}

void Safe::print(ostream& stream) const
{
    for (int i = 0; i < count_elem; ++i)
    {
        objptr[i]->print(stream);
    }
}

double Safe::total_amount() const
{
    double temp = 0;
    for (int i = 0; i < count_elem; ++i)
    {
        temp += objptr[i]->conversion_to_rubbles();
    }
    return temp;
}

double Safe::smallest_amount() const
{
    double temp = 0;
    for (int i = 0; i < count_elem; ++i)
    {
        if (i == 0) temp = objptr[i]->conversion_to_rubbles(); else
            if (objptr[i]->conversion_to_rubbles() < temp) temp = objptr[i]->conversion_to_rubbles();
    }
    return temp;
}

tuple<int, double, int, double> Safe::share_of_total_amount() const
{
    double temp_g = 0;
    double temp_s = 0;
    for (int i = 0; i < count_elem; ++i)
    {
        if (objptr[i]->myName() == "Gold")
        {
            temp_g += objptr[i]->conversion_to_rubbles();
        }
        else if (objptr[i]->myName() == "Stock")
        {
            temp_s += objptr[i]->conversion_to_rubbles();
        }
    }
    return make_tuple(temp_g, temp_g / total_amount(), temp_s, temp_s / total_amount());
}

ostream& operator << (ostream& stream, Safe& obj)
{
    obj.print(stream);
    return stream;
}

istream& operator >> (istream& stream, Safe& obj)
{
    obj.scan(stream);
    return stream;
}
