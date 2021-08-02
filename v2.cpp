// try 2 ways: normal way and alternate way (where (1,1) is banned)
// that would score 100 pts and work for even odd R
#include <iostream>
using namespace std;

int R, C, N;
bool wall[100][100];
bool Inverted, Alt;

int count_contrasts(int i, int j) {
    if (Alt && i==1 && j==1)    // bar painting (1,1) if Alt is true
        return 0;
    int count = 0;
    if (i > 0)
        count += (wall[i-1][j] ? -1 : 1);
    if (j > 0)
        count += (wall[i][j-1] ? -1 : 1);
    if (i < (R-1))
        count += (wall[i+1][j] ? -1 : 1);
    if (j < (C-1))
        count += (wall[i][j+1] ? -1 : 1);
    return count;
}

int paint(int rank) {
// paint all cells that add <rank> contrasts
    int i, j, count = 0;
    for (i=0; i<R; i++) {
        for (j=0; j<C; j++) {
            if (N==0) 
                return count;
            if (count_contrasts(i, j) == rank) {
                wall[i][j] = true; N--; count += rank;
            }
        }
    }
    return count;
}

int helper() {
    int count = paint(4);
    count += paint(3);
    count += paint(2);
    count += paint(1);
    return count;
}

void solve() {
    bool backup_wall[100][100];
    int pairs1, pairs2, i, j, n2 = N;
    pairs1 = helper();
    for (i=0; i<R; i++)
        for (j=0; j<C; j++) {
            backup_wall[i][j] = wall[i][j];
            wall[i][j] = false;
        }
    Alt = true;
    N = n2;
    pairs2 = helper();
    if (pairs2 < pairs1) {
        for (i=0; i<R; i++)
            for (j=0; j<C; j++)
                wall[i][j] = backup_wall[i][j];
    }
}

int main() {
    int i, j;
    cin >> R >> C >> N;
    if (N > (R*C/2)) {
        Inverted = true;
        N = R * C - N;
    }
    solve();
    for (i=0; i<R; i++) {
        for (j=0; j<C; j++)
            cout << (wall[i][j] ^ Inverted);
        cout << endl;
    }
    return 0;
}