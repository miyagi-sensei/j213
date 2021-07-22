#include <iostream>
#include <vector>
using namespace std;
int R, C, N;
vector< pair<int, int> > comb, best_comb;
int Max_contrasts = -1;

void print_wall() {
  bool wall[100][100] = {false};
  int i, j;
  for (i=0; i<best_comb.size(); i++) {
    int r = best_comb[i].first;
    int c = best_comb[i].second;
    wall[r][c] = true;
  }
  for (i = 0; i < R; i++) {
    for (j = 0; j < C; j++) {
      cout << wall[i][j];
    }
    cout << endl;
  }
}

int count_contrasts() {
  int i, j, ans = 0;
  bool map[100][100] = {false};

  for (int i = 0; i < comb.size(); i++) {
    map[comb[i].first][comb[i].second] = true;
  }

  for (i = 0; i < R; i++) {
    for (j = 0; j < C; j++) {
      if ((j != C-1) && (map[i][j] != map[i][j+1])) {
        ans++;
      }

      if ((i != R-1) && (map[i][j] != map[i+1][j])) {
        ans++;
      }
    }
  }
	return ans;
}

void combinations(int k, int offset) {
  int i;
  if (k==0) {
    // print out that combination stored in comb vector
    // for (i=0; i<comb.size(); i++)
    // 	printf("(%d, %d) ", comb[i].first, comb[i].second);
    // cout << endl;
    int n_contrasts = count_contrasts();
    if (n_contrasts > Max_contrasts) {
      Max_contrasts = n_contrasts;
      best_comb = comb;
    }
    return;
  }
  for (i=offset; i<R*C; i++) {
    comb.push_back({i / C, i % C});
    combinations(k-1, i+1);
    comb.pop_back();
  }
}

int main() {
  cin >> R >> C >> N;
  combinations(N, 0);
  cerr << Max_contrasts << endl;
  print_wall();
  return 0;
}
