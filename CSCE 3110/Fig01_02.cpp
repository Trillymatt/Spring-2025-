#include <iostream>

using namespace std;

int f( int x ) {
    if ( x == 0 ){
        return 0;
    }
    else {
        return 2 * f( x - 1 ) + x * x;
    }
}

int main() {
    cout << "f(S) = " << f(5) << endl;
    
    return 0;
}