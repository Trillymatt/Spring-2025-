#include <iostream>

using namespace std;

bool isEven (int n) {
    return n % 2 == 0;;
}

long long pow (long long x, int n){
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (isEven(n))
        return pow(x * x, n / 2);
    else 
        return pow(x * x, n / 2) * x;
}

int main() {
    cout << "3^14 = " << pow(3, 14) << endl;
    cout << "2^4 = " << pow(2, 4) << endl;

    return 0;
}