#include<bits/stdc++.h>
using namespace std;

class BigNum {
  friend ostream &operator<<(ostream&, const BigNum&);
  friend istream &operator>>(istream&, BigNum&);
public:
  BigNum(const long long = 0);
  BigNum(const string);
  BigNum(const BigNum&);
  BigNum(const char*);

  bool getSignOfNumber() const;
  void setSignOfNumber(bool);
  vector<unsigned short int> getDigits() const;
  void setDigits(vector<unsigned short>);

  friend BigNum& operator + (const BigNum&, const BigNum&);
  friend BigNum& operator - (const BigNum&, const BigNum&);
  friend BigNum& operator * (const BigNum&, const BigNum&);
  friend BigNum& operator += (BigNum&, const BigNum&);
  friend BigNum& operator -= (BigNum&, const BigNum&);
  friend BigNum& operator *= (BigNum&, const BigNum&);
  BigNum& operator = (const string);
  BigNum& operator = (const BigNum&);
  BigNum& operator = (const long long);
  bool operator > (BigNum&);
  bool operator < (const BigNum&);
  bool operator <= (BigNum&);
  bool operator >= (BigNum&);
  bool operator == (BigNum&) const;
  bool operator != (BigNum&);
  short operator [] (const int) const;
  void set(const BigNum &y);
  void SetValue(const vector<unsigned short int>, const bool);
  void Delimiter();

private:
  vector<unsigned short> digits;
  bool SignOfNumber = true;
};
