#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
  int _fixedNum;
  static const int _bits = 8;

public:
  Fixed();
  ~Fixed();
  // copy constructor
  Fixed(Fixed &t);
  // assignment operator overloading
  Fixed &operator=(const Fixed &C);
  int getRawBits(void) const;
  void setRawBits(int const raw);
};

#endif // !FIXED_HPP
