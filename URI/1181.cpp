#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    cout << fixed << setprecision(1);
    int L;
    string op;
    float m[12][12], s = 0, med = 0;

    cin >> L;
    cin >> op;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            cin >> m[i][j];

    for (int j = 0; j < 12; j++)
        s += m[L][j];

    if (op[0] == 'S')
        cout << s << endl;
    else if (op[0] == 'M')
        cout << s / 12.0 << endl;

    // system("PAUSE");
    return 0;
}
