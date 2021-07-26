// try 2 ways: normal way and alternate way (where (1,1) is banned)
// that would score 100 pts and work for even odd R
#include <iostream>
using namespace std;

int R, C, N;
bool wall[100][100];
bool Inverted, Alt;

int count_borders(int i, int j) {
    if (Alt && i==1 && j==1)
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
    int i, j, count = 0;
    for (i=0; i<R; i++) {
        for (j=0; j<C; j++) {
            if (N==0) 
                return count;
            if (count_borders(i, j) == rank) {
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

int solve() {
    bool backup_wall[100][100];
    int pairs1, pairs2, i, j, n2 = N;
    pairs1 = helper();
    for (i=0; i<R; i++)
        for (j=0; j<C; j++)
            wall[i][j] = false;

    Alt = true;
    N = n2;
    pairs2 = helper();
    return max(pairs1, pairs2);
}

// count the number of contrasts in the boolean 2D array wall
int count_contrasts() {
	int i, j, ans = 0;
  for (i = 0; i < R; i++) {
    for (j = 0; j < C; j++) {
      if ((j != C-1) && (wall[i][j] != wall[i][j+1])) {
        ans++;
      }

      if ((i != R-1) && (wall[i][j] != wall[i+1][j])) {
        ans++;
      }
    }
  }
	return ans;
}

bool verify(int max_contrasts) {
  string wall2[100];
  int i, j;
  for (i=0; i<R; i++) {
    cin >> wall2[i];
    for (j=0; j<C; j++)
      wall[i][j] = (wall2[i][j] == '1');
  }
  return count_contrasts() == max_contrasts;
}

int main() {
    int i, j;
    cin >> R >> C >> N;
    if (N > (R*C/2)) {
        Inverted = true;
        N = R * C - N;
    }
    if (!verify(solve()))
      return -1;
    return 0;
}