#include <iostream>
#include <string>
#include "BigInteger.h"

int main() {
    BigInteger newInt = BigInteger("-20");
    BigInteger newInt2 = BigInteger("-100");
    BigInteger newIntSum = newInt + newInt2;
    BigInteger newIntSub = newInt2 - newInt;
    std::cout << newIntSum.toString() << std::endl;
    std::cout << newIntSub.toString() << std::endl;
}