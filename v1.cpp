// scores subtask 1,2,4,5
#include <iostream>
using namespace std;

int R, C, N;
bool wall[100][100];
bool Inverted;

int count_contrasts(int i, int j) {
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
                wall[i][j] = true; 
								N--; 
								count += rank;
            }
        }
    }
    return count;
}

int solve() {	// greedy approach
    int count = paint(4);	// first those that add 4
    count += paint(3);	// then those that add 3
    count += paint(2);	// then those that add 2
    count += paint(1);	// then those that add 1
		return count;
}

int main() {
    int i, j;
    cin >> R >> C >> N;
    if (N > (R*C/2)) {
        Inverted = true;
        N = R * C - N;
    }
    solve();
		// add code here to try again but blocking out cell (1,1) for 100 points
    for (i=0; i<R; i++) {
        for (j=0; j<C; j++)
            cout << (wall[i][j] ^ Inverted);
        cout << endl;
    }
    return 0;
}