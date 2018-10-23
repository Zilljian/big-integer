#include "BigInteger.h"

BigInteger::BigInteger() :  number(), length(0), sign(false) {
}

BigInteger::BigInteger(std::string initString) :  number(), length(0), sign(false) {
    sign = initString[0] == '-' ? true: false;
    initString.erase(0,1);
    toStringVar = initString;
    initBigInteger(initString);
    initStack();
}

BigInteger::BigInteger(std::vector<int> initVector) : number(), length(0), sign(false) {
    number.insert(number.begin(), initVector.begin(), initVector.end());
    length = number.size();
    initStack();
}

BigInteger::BigInteger(std::vector<int> initVector, bool sign) : number(), length(0), sign(false) {
    this->sign = sign;
    number.insert(number.begin(), initVector.begin(), initVector.end());
    length = number.size();
    initStack();
}


BigInteger BigInteger::operator + (BigInteger addend) {
    int remain = 0;
    std::vector<int> sum;

    if (!sign && addend.isNegative()) return *(this) - BigInteger(addend.getVector(), false);
    if (sign && !addend.isNegative()) return addend - BigInteger(number, false);

    for (auto item : addend.getVector()) buffer2.push(item);

    while (!buffer1.empty() && !buffer2.empty()) {
        if (buffer1.top() + buffer2.top() >= 10) {
            sum.push_back(buffer1.top() + buffer2.top() % 10 + remain);
            remain = buffer1.top() + buffer2.top() / 10;
        } else {
            sum.push_back(buffer1.top() + buffer2.top() + remain);
            remain = 0;
        }
        buffer2.pop();
        buffer1.pop();
    }

    if (buffer2.empty()) {
        while (!buffer1.empty()) {
            sum.push_back(buffer1.top() + remain);
            remain = 0;
            buffer1.pop();
        }
    } else {
        while (!buffer2.empty()) {
            sum.push_back(buffer2.top() + remain);
            remain = 0;
            buffer2.pop();
        }
    }

    std::reverse(sum.begin(), sum.end());

    return BigInteger(sum, sign);
}

BigInteger BigInteger::operator - (BigInteger subtrahend) {
    std::vector<int> subtraction;
    int tempNumber1, tempNumber2;

    if (sign && !subtrahend.isNegative()) return BigInteger(subtrahend.getVector(), true) + *(this); // -a - b = -(a + b) = -a + (-b)
    if (!sign && subtrahend.isNegative()) return BigInteger(subtrahend.getVector(), false) + *(this); // a - (-b) = a + b
    if (sign && subtrahend.isNegative()) return BigInteger(subtrahend.getVector(), false) + *(this);  // -a - (-b) = b - a

    if (*(this) < subtrahend) return BigInteger((subtrahend - *(this)).getVector(), true);
    if (*(this) == subtrahend) return BigInteger(std::vector<int>(0), false);

    for (auto item : subtrahend.getVector()) buffer2.push(item);

    while (!buffer1.empty() && !buffer2.empty()) {
        tempNumber1 = buffer1.top();
        tempNumber2 = buffer2.top();
        buffer2.pop();
        buffer1.pop();
        if (tempNumber1 - tempNumber2 >= 0) {
            subtraction.push_back(tempNumber1 - tempNumber2);
        } else {
            int counter = 0;
            int temp;
            while(true) {
                if (buffer1.top() == 0) {
                    buffer1.pop();
                    counter++;
                }
                else {
                    temp = buffer1.top();
                    buffer1.pop();
                    tempNumber1 = tempNumber1 + 10;
                    buffer1.push(temp - 1);
                    while( counter > 0){
                        buffer1.push(9);
                        counter--;
                    }
                    break;
                }
            }
            subtraction.push_back(tempNumber1 - tempNumber2);
        }
    }

    if (buffer2.empty()){
        while(!buffer1.empty()) {
            subtraction.push_back(buffer1.top());
            buffer1.pop();
        }
    }

    while(!subtraction.empty()){
        if (subtraction.back() == 0) subtraction.pop_back();
        else break;
    }

    std::reverse(subtraction.begin(), subtraction.end());

    if (subtraction.empty()) subtraction.push_back(0);

    return BigInteger (subtraction);
}

bool BigInteger::operator < (BigInteger &rightExpr){
    if (length == rightExpr.getVector().size()) {
        if(!rightExpr.isNegative() && !sign) {
            for (int i = 1; i < length; i++) {
                if (rightExpr.getVector()[i] > number[i]) return true;
            }
            return false;
        } else if (rightExpr.isNegative() && sign) {
            for (int i = 1; i < length; i++) {
                if (rightExpr.getVector()[i] > number[i]) return false;
            }
            return true;
        } else return sign;
    } else {
        if (!rightExpr.isNegative() && !sign) {
            return length < rightExpr.getVector().size();
        } else if (rightExpr.isNegative() && sign) {
            return length >= rightExpr.getVector().size();
        }
        else return sign;
    }
}

bool BigInteger::operator > (BigInteger &rightExpr){
    if (length == rightExpr.getVector().size()) {
        if(!rightExpr.isNegative() && !sign) {
            for (int i = 1; i < length; i++) {
                if (rightExpr.getVector()[i] > number[i]) return false;
            }
            return true;
        } else if (rightExpr.isNegative() && sign) {
            for (int i = 1; i < length; i++) {
                if (rightExpr.getVector()[i] > number[i]) return true;
            }
            return false;
        } else return !sign;
    } else {
        if (!rightExpr.isNegative() && !sign) {
            return length > rightExpr.getVector().size();
        } else if (rightExpr.isNegative() && sign) {
            return length <= rightExpr.getVector().size();
        }
        else return !sign;
    }
}

bool BigInteger::operator == (BigInteger &rightExpr) {
    if (length == rightExpr.getVector().size() && ((rightExpr.isNegative() && sign) || (!rightExpr.isNegative() && !sign)) ){
        for (int i = 1; i < length; i++) {
            if (rightExpr.getVector()[i] != number[i]) return false;
        }
        return true;
    } else return false;
}

bool BigInteger::operator != (BigInteger &rightExpr){
    if (length == rightExpr.getVector().size() && ((rightExpr.isNegative() && sign) || (!rightExpr.isNegative() && !sign)) ){
        for (int i = 1; i < length; i++) {
            if (rightExpr.getVector()[i] != number[i]) return true;
        }
        return false;
    } else return true;
}

std::vector<int> BigInteger::getVector(){
    return number;
}

std::string BigInteger::toString() {
    stringBuilder();
    return toStringVar;
}

bool BigInteger::isNegative() {
    return sign;
}


void BigInteger::initBigInteger(std::string initString) {
    while(initString[0] == '0' && (initString.size() > 1)) initString.erase(0,1);

    for (int i = 0; initString[i] != '\0'; i++) {
        if (initString[i] != '-') number.push_back(int(initString[i]) - 48);
    }
    length = number.size();
}

void BigInteger::stringBuilder() {
    toStringVar = sign ? "-" : "";

    for (int i = 0; i < length; i++) {
        toStringVar += std::to_string(number[i]);
    }
}

void BigInteger::initStack() {
    for (auto item : number) buffer1.push(item);
}
