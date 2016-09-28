// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	int i;
	if (len < 1)
	{
		throw(len);
	}
	BitLen = len;
	MemLen = (len + 31) >> 5;//int имеет 32 бита, но один бит знаковый
	pMem = new TELEM[MemLen]; // выделили память под это кол-во битов
	if (pMem != NULL)
	{
		for (i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else  printf("No Memory");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	int i;
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];


}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen))
	{
		throw(n);
	}
	int k = n >> 5;
	return k;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen))
	{
		throw(n);
	}
		int k = 1 << (n & 31);
		return k;
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw(n);
	}
		int a = GetMemIndex(n);
		int b = GetMemMask(n);
		pMem[a] |= b; // нужно объеденить их
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
	{
		throw(n);
	}
		int a = GetMemIndex(n);
		int b = GetMemMask(n);
		pMem[a] &= ~b;   // нужно объеденить их
	
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	int a;
	int b;
	if ((n < 0) || (n > BitLen))
	{
		throw(n);
	}
		a = GetMemIndex(n);
		 b = GetMemMask(n);
	return (pMem[a] & b);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	int i;
	BitLen = bf.BitLen;
	if (MemLen == bf.MemLen)
	{
		MemLen = bf.MemLen;
		for (i = 0; i<MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	else
	{
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
		{
			for (i = 0; i<MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
		else printf("No Memory");
	}

	return *this;
	

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int log = 1;
	//if (BitLen != bf.BitLen) return  log = 0;
	if (MemLen != bf.MemLen) return log = 0;
	for (int i = 0; i<MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return log = 0;
		}
	}
	return log;
	
	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	
	int log = 1;
	if (BitLen == bf.BitLen) return log = 0;
	if (MemLen == bf.MemLen) return log = 0;
	for (int i = 0; i<MemLen; i++)
	{
		if (pMem[i] == bf.pMem[i])
		{
			log = 0;
		}
	}
	return log;
	
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	TBitField pr;
	int len = BitLen;
	if (BitLen != bf.BitLen)
	{
		len = bf.BitLen;
	}
	// можно было передать len в качетсве аргумента в pr(len), как конструктор инициализатор  
	pr.MemLen = (len + 31) >> 5;
	pr.pMem = new TELEM[pr.MemLen];
	if (pr.pMem != NULL)
	{
		for (i = 0; i < pr.MemLen; i++)
		{
			pr.pMem[i] = pMem[i];
		}
		for (i = 0; i < pr.MemLen; i++)
		{
			pr.pMem[i] |= bf.pMem[i]; // "|=" - битовая операция "или" с присваиванием
		}
	}
	
	else printf("No Memory");
	return pr;
	
	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int len = BitLen;
	if (len != bf.BitLen)
	{
		len = bf.BitLen;
	}
	TBitField pr(len);
	for (i = 0; i<pr.MemLen; i++)
	{
		pr.pMem[i] = pMem[i];
	}
	for (i = 0; i<pr.MemLen; i++)
	{
		pr.pMem[i] &= bf.pMem[i]; // "&=" - битовая операция "и" с присваиванием
	}
	return pr;
}

TBitField TBitField::operator~(void) // отрицание
{
	int i;
	TBitField pr;
	int len = BitLen;
	pr.MemLen=(len + 31) >> 5;
	pr.pMem = new TELEM[pr.MemLen];
	if (pr.pMem != 0)
	{
		for (i = 0; i < pr.MemLen; i++)
		{
			pr.pMem[i] = pMem[i];
		}
		for (i = 0; i < pr.MemLen; i++)
			pr.pMem[i] =~ pMem[i];////побитовая операция "~" отрицание 1->0; 0->1;
		
	}
	return pr;
}

// ввод/вывод
/*
istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++);

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	int i;
	for (i = 0; i < len; i++)
	{
		if (bf.GetBit(i) == 1) cout << 1;
		else cout << 0;
	}
	return ostr;
}
*/