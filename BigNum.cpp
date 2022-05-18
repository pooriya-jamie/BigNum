/* Writer : Pooriya Jamie */

#include<bits/stdc++.h>
#include "BigNum.h"

using namespace std;

BigNum temp;

BigNum::BigNum(const long long x) // Definition for long long
{
  long long y = x;
  if(y < 0)
  {
    y = y * -1;
    SignOfNumber = false;
  }
  while(y != 0)
  {
    digits.push_back(y % 10); //Take last digit from number
    y /= 10;
  }
}

BigNum::BigNum(const string s)
{
  int n = s.size();
  if (n == 0)
    throw invalid_argument("Number is not valid, Please enter number more than 0.");

  int DigitStartPoint = 0;
  if(s[0] == '+')
  {
    DigitStartPoint = 1;
  }
  else if(s[0] == '-')
  {
    SignOfNumber = false;
    DigitStartPoint = 1;
  }

  for(int i = n - 1; i >= DigitStartPoint; i--)
  {
    if(!isdigit(s[i]))
      throw invalid_argument("invalid number");
    digits.push_back(s[i] - '0'); //This operation change string to number and take it
  }
}

BigNum::BigNum(const BigNum &a)
{
  *this = a;
}

BigNum::BigNum(const char* ch)
{
  string str(ch);
  BigNum t(str);
  this->set(t);
}

vector<unsigned short int> BigNum::getDigits() const
{
  return digits;
}

void BigNum::setDigits(vector<unsigned short int > d)
{
  digits = d;
}

bool BigNum::getSignOfNumber() const
{
  return SignOfNumber;
}

void BigNum::setSignOfNumber(bool positivity)
{
  SignOfNumber = positivity;
}

BigNum& operator+(const BigNum& x, const BigNum& y) // overloading function +
{
  temp = x;
  temp += y;
  return temp;
}

BigNum& operator-(const BigNum& x, const BigNum& y) // overloading function -
{
  temp = x;
  temp -= y;
  return temp;
}

BigNum& operator*(const BigNum& x, const BigNum& y) // overloading function *
{
  temp = x;
  temp *= y;
  return temp;
}

BigNum& operator+=(BigNum &x, const BigNum &y) // overloading function +=
{
  if (x.SignOfNumber == false && y.SignOfNumber == true)
  {
    BigNum temp_x;
    temp_x.SetValue(x.getDigits(), true);
    BigNum temp_y;
    temp_y.set(y);
    temp_y -= temp_x;
    x = temp_y;
    return x;
  }
  else if (x.SignOfNumber == true && y.SignOfNumber == false)
  {
    BigNum temp_y;
    temp_y.SetValue(y.getDigits(), true);
    x -= temp_y;
    return x;
  }

  int TempNum = 0, SumOfNumber;
  bool flag = false;
  if (x.SignOfNumber == false && y.SignOfNumber == false)
  {
    x.setSignOfNumber(true);
    flag = true;
  }

  int x_Size = x.digits.size();
  int y_Size = y.digits.size();

  if(y_Size > x_Size)
  {
    int addition = y_Size - x_Size;
    for (int j = 0; j < addition; j++)
    {
      x.digits.push_back(0);
    }
    x_Size = x.digits.size();
  }

  for (int i = 0; i < x_Size; i++)
  {
    if(i < y_Size)
    {
      SumOfNumber = (x.digits[i] + y.digits[i]) + TempNum;
    }
    else
    {
      SumOfNumber = x.digits[i] + TempNum;
    }
    TempNum = SumOfNumber / 10;
    x.digits[i] = (SumOfNumber % 10);
  }
  if(flag)
    x.SignOfNumber = false;

  if(TempNum)
    x.digits.push_back(TempNum);

  return x;
}

BigNum& operator-=(BigNum& x, const BigNum& y) // overloading function -=
{
  if (x.SignOfNumber == true && y.SignOfNumber == false)
  {
    BigNum temp_y;
    temp_y.SetValue(y.getDigits(), true);
    x += temp_y;
    return x;
  }
  else if (x.SignOfNumber == false && y.SignOfNumber == true)
  {
    BigNum temp_y;
    temp_y.SetValue(y.getDigits(), false);
    x += temp_y;
    return x;
  }

  BigNum temp_y;
  temp_y = y;
  BigNum temp_x;
  temp_x = x;

  int TempNum = 0;
  bool flag = false;
  if (temp_x.SignOfNumber == false && temp_y.SignOfNumber == false){
    temp_x.setSignOfNumber(true);
    temp_y.setSignOfNumber(true);
    flag = true;
  }

  if (temp_x < temp_y)
  {
    swap(temp_x, temp_y);
    flag = !flag;
  }

    int x_Size = temp_x.digits.size();
    int y_Size = temp_y.digits.size();
    int s;

  for(int i = 0; i < x_Size; i++)
  {
    if(i >= y_Size)
    {
        s = temp_x.digits[i] + TempNum;
    }
    else
    {
        s = temp_x.digits[i] - temp_y.digits[i] + TempNum;
    }

    if(s >= 0)
    {
      TempNum = 0;
    }
    else
    {
      s += 10;
      TempNum = -1;
    }
    temp_x.digits[i] = s;
  }

  if(flag == true)
    temp_x.SignOfNumber = !temp_x.SignOfNumber;

  while(x_Size > 1 && temp_x.digits[x_Size - 1] == 0)
  {
    temp_x.digits.pop_back();
    x_Size--;
  }

  x = temp_x;
  return x;
}
BigNum& operator*=(BigNum& x, const BigNum& y) // overloading function -=
{
  if (x.SignOfNumber == true && y.SignOfNumber == false)
  {
    x.SignOfNumber = false;
  }
  else if (x.SignOfNumber == false && y.SignOfNumber == false)
  {
    x.SignOfNumber = true;
  }

  int x_Size = x.digits.size();
  int y_Size = y.digits.size();
  vector<int> vec(x_Size + y_Size, 0);

  for (int i = 0; i < x_Size; i++)
  {
    for (int j = 0; j < y_Size; j++)
    {
      vec[i + j] += x.digits[i] * y.digits[j];
    }
  }
  x_Size += y_Size;
  x.digits.resize(vec.size());
  for (int w, i = 0, z = 0; i < x_Size; i++)
  {
      w = z + vec[i];
      vec[i] = w % 10;
      z = w / 10;
      x.digits[i] = vec[i] ;
  }
  for (int i = x_Size - 1; i >= 1 && !vec[i]; i--)
  {
    x.digits.pop_back();
  }
  return x;
}

BigNum& BigNum::operator=(const BigNum& same) // overloading function -=
{
    this->SignOfNumber = same.SignOfNumber;
    this->digits = same.digits;
    return *this;
}

BigNum& BigNum::operator=(const string same)
{
  BigNum t(same);
  this->set(t);
  return *this;
}

BigNum& BigNum::operator=(const long long same)
{
  BigNum t(same);
  this->set(t);
  return *this;
}

bool BigNum::operator<(const BigNum& same) // overloading function <
{
  int x_Size = digits.size();
  int y_Size = same.digits.size();
  if (SignOfNumber == true && same.SignOfNumber == false) return false;
  if (SignOfNumber == false && same.SignOfNumber == true) return true;
  if(x_Size > y_Size) return SignOfNumber == false;
  if(x_Size < y_Size) return SignOfNumber == true;

  for (int i = x_Size - 1; i >= 0; i--)
  {
    if(digits[i] != same.digits[i])
    {
      bool y = digits[i] < same.digits[i];
      if (SignOfNumber != false)
      {
          return y;
      }
      else
      {
        return !y;
      }
    }
  }
  return false;
}

bool BigNum::operator<=(BigNum& same) // overloading function <=
{
  return !(*this > same);
}

bool BigNum::operator>(BigNum& same) // overloading function >
{
  return same < *this;
}

bool BigNum::operator>=(BigNum& same) // overloading function >=
{
  return !(*this < same);
}

bool BigNum::operator==(BigNum &same) const // overloading function ==
{
  return digits == same.digits;
}

bool BigNum::operator!=(BigNum &same)
{
  return !(*this == same);
}

short int BigNum::operator[](const int index) const // overloading function []
{
  if(index >= digits.size() || index < 0)
        throw("Index in not in a range of an array!");
    return digits[digits.size() - index - 1];
}

ostream& operator<<(std::ostream& output, const BigNum& y) // overloading function <<
{
  if (y.SignOfNumber == false)
    output << "-";
  for (int i = y.digits.size() - 1; i >= 0; i--)
    output << (int)y.digits[i];
  return output;
}

istream& operator>>(std::istream& input, BigNum& y) // overloading function >>
{
  string str;
  cin >> str;
  y.set(BigNum(str));
  return input;
}

void BigNum::set(const BigNum &y)
{
    SignOfNumber = y.SignOfNumber;
    digits = y.digits;
}

void BigNum::SetValue(const vector<unsigned short int> digits, const bool SignOfNumber)
{
  this->digits = digits;
  this->SignOfNumber = SignOfNumber;
}

void BigNum::Delimiter()
{
  if (SignOfNumber == false)
    cout << "-";
  for (int i = digits.size() - 1; i >= 0; i--)
  {
    cout << digits[i];
    if (i != 0 && i % 3 == 0)
      cout << ",";
  }
  cout << endl;
}
