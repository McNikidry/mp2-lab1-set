// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
TSet::TSet(int mp) :BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) :BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{

	TBitField res(BitField);
	return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int elmn = BitField.GetBit(Elem);
	return elmn;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField != s.BitField) return 0;
	return 1;

}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField == s.BitField) return 0;
	 return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet pr(BitField | s.BitField);
	return pr;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem<0) || (Elem>MaxPower))
	{
		throw(Elem);
	}
	TBitField res(MaxPower);
	res.SetBit(Elem);
	TSet pr(BitField | res);
	return pr;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem<0) || (Elem>MaxPower))
	{
		throw(Elem);
	}
	TBitField res(MaxPower);
	res.SetBit(Elem);
	TSet pr(BitField & res);
	return pr;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet pr(BitField & s.BitField);
	return pr;

}

TSet TSet::operator~(void) // дополнение
{
	TSet pr(~BitField);
	return pr;
}

// перегрузка ввода/вывода

istream &operator >> (istream &istr, TSet &s) // ввод
{
	char k;
	int i = 0;
	for (i = 0; i < s.MaxPower; i++)
	{
		cin >> k;
		if (k == '1') s.InsElem(i);
		else s.DelElem(i);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i = 0;
	for (i = 0; i < s.MaxPower; i++)
		cout<< ' ' << s.IsMember(i);
	return ostr;
}

