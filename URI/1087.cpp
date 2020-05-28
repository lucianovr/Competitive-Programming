#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    int x1, y1, x2, y2;

    while (cin >> x1 >> y1 >> x2 >> y2 && (x1 + y1 + x2 + y2)) {
        if (x1 == x2 && y1 == y2)
            cout << "0\n";
        else if (abs(y2 - y1) == abs(x2 - x1))
            cout << "1\n";
        else if (x1 == x2 || y1 == y2)
            cout << "1\n";
        else
            cout << "2\n";
    }
    // system( "PAUSE");
    return 0;
}
