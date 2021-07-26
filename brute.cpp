#include <iostream>
using namespace std;
int R, C, N;
int Max_contrasts = -1;
bool wall[100][100], best_wall[100][100];

void print_wall(bool w[][100]) {
  int i, j;
  for (i = 0; i < R; i++) {
    for (j = 0; j < C; j++) {
      cout << w[i][j];
    }
    cout << endl;
  }
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

void combinations(int k, int offset) {
	int i, j;
	if (k==0) {
		int n_contrasts = count_contrasts();
		if (n_contrasts > Max_contrasts) {
			Max_contrasts = n_contrasts;
      for (i=0; i<R; i++)
        for (j=0; j<C; j++)
          best_wall[i][j] = wall[i][j];
		}
		return;
	}
	for (i=offset; i<R*C; i++) {
    wall[i/C][i%C] = true;
		combinations(k-1, i+1);
    wall[i/C][i%C] = false;
	}
}

int main() {
  cin >> R >> C >> N;
  combinations(N, 0);
  cerr << Max_contrasts << endl;
  print_wall(best_wall);
  return 0;
}