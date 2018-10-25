#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <iostream>
#ifndef BIG_INTEGER_BIGINTEGER_H
#define BIG_INTEGER_BIGINTEGER_H


class BigInteger {

public:
    BigInteger();
    BigInteger(std::string);
    BigInteger(std::vector<int>);
    BigInteger(std::vector<int>, bool);


    BigInteger operator + (BigInteger);
    BigInteger operator - (BigInteger);
    BigInteger operator * (BigInteger);
    BigInteger operator ^ (BigInteger);
    BigInteger operator / (BigInteger);
    BigInteger operator % (BigInteger);
    bool operator < (BigInteger&);
    bool operator > (BigInteger&);
    bool operator == (BigInteger&);
    bool operator != (BigInteger&);
    friend std::ostream& operator << (std::ostream&,const BigInteger&);
    friend std::istream& operator >> (std::istream&,BigInteger&);
    std::string toString();
    std::vector<int> getVector();
    bool isNegative ();

private:
    void initBigInteger(std::string);
    void stringBuilder();
    void initStack();

    std::vector<int> number;
    std::stack<int> buffer1;
    std::stack<int> buffer2;
    long length;
    std::string toStringVar;
    bool sign;
};


#endif //BIG_INTEGER_BIGINTEGER_H
