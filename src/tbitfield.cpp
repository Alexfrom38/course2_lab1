// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  if (len > -1)
  {
    bitlen = len;
    memlen = (len + 31) >> sizeof(TELEM);
    pMem = new TELEM[MemLen];
    if (pMem != NULL) {
      for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
    }
  }
  else
  {
    throw("exception");
  }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  if (bf.BitLen <= 0)
    throw "the length less than zero";
  else
  {
    bitlen = bf.bitlen;
    pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < bf.MemLen; i++)
    {
      pMem[i] = bf.pMem[i];
    }
    memlen = bf.MemLen;
  }
}

TBitField::~TBitField()
{
  if (pMem != 0) delete[] pMem;
  pMem = 0;
  memlen = 0;
  bitlen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > bitlen)) throw "unexist length";
  else
    return n >> 5; // return pMem[n/32];
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 && n < bitlen) throw "unexist length";
  return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitlen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n > bitlen))
  {
    throw "unexist length";
  }
  else
  {
    int first = GetMemIndex(n);
    int second = GetMemMask(n);
    pMem[First] = pMem[First] | second;
  }
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n > bitlen))
  {
    throw "unexist length";
  }
  else
  {
    int first = GetMemIndex(n);
    int second = GetMemMask(n);
    pMem[First] = pMem[First] & ~second;
  }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n > bitlen))
  {
    throw "unexist length";
  }
  else
  {
    int first = GetMemIndex(n);
    int second = GetMemMask(n);
    return (pMem[First] & second);
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  
    if (this == &bf)
      return *this;
    else
    {
      delete[] pMem;
      memlen = bf.MemLen;
      pMem = new TELEM[MemLen];
      bitlen = bf.bitlen;
      for (int i = 0; i < memlen; i++)
      {
        pMem[i] = bf.pMem[i];
      }
      return *this;
    }
  
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (memlen != bf.MemLen || bitlen != bf.bitlen) return 0;
  else
  {
    for (int i = 0; i < memlen; i++)
    {
      if (pMem[i] != bf.pMem[i])
        return 0;
    }
    return 1;
  }
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int len = BitLen;
  if (bf.bitlen > len)
    len = bf.bitlen;
  TBitField tmp(len);
  for (int i = 0; i < memlen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memlen; i++)
    tmp.pMem[i] |= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int len = bitlen;
  if (bf.bitlen > len)
    len = bf.bitlen;
  TBitField tmp = (len);
  for (int i = 0; i < MemLen; i++)
    tmp.pMem[i] = pMem[i];
  for (int i = 0; i < bf.MemLen; i++)
    tmp.pMem[i] &= bf.pMem[i];
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  {
    TBitField temp(*this);
    for (int i = 0; i < tmp.bitlen; i++)
    {
      if (temp.GetBit(i))
        temp.ClrBit(i);
      else
        temp.SetBit(i);
    }
    return tmp;
  }
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  int temp;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    cin >> temp;
    if (temp == 1)
      bf.SetBit(i);
    else if (temp == 0)
      bf.ClrBit(i);
  }
  return istr;
}

ostream& operator<<(ostream& out, const TBitField& bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
    out << bf.GetBit(i);
  return out;
}
