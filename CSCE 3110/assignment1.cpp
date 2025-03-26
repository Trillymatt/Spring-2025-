#include <iostream>
#include <string>

using namespace std;  


template <typename T>
T getLarger(const T& a, const T& b) {
    return (a > b) ? a : b;
}

int main() {
    
    int intA = 10, intB = 20;
    cout << "Larger int: " << getLarger(intA, intB) << endl;

    
    float floatA = 5.5, floatB = 2.3;
    cout << "Larger float: " << getLarger(floatA, floatB) << endl;

    
    string strA = "apple", strB = "banana";
    cout << "Larger string: " << getLarger(strA, strB) << endl;

    return 0;
}