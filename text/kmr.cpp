#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int LOGN = 17;
int n;
string s;
int KMR[LOGN][N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie();
  cout.tie();

  cin >> n >> s;
  int cnt = 0;
  vector<pair<char, int>> letter_positions;
  for (int i = 0; i < n; ++i) 
    letter_positions.push_back({s[i], i});
  sort(letter_positions.begin(), letter_positions.end());
  for (int i = 0; i < n; ++i) {
    if (i == 0 || letter_positions[i].first != letter_positions[i-1].first) cnt++;
    KMR[0][letter_positions[i].second] = cnt;
  }
  
  for (int k = 1; (1<<k) <= n; ++k) {
    cnt = 0;
    vector<pair<pair<int,int>, int>> pair_position;
    for (int i = 0; i + (1<<k) <= n; ++i) 
      pair_position.push_back({{KMR[k-1][i], KMR[k-1][i + (1<<(k-1))]}, i});
    sort(pair_position.begin(), pair_position.end());
    for (int i = 0; i + (1<<(k)) <= n; ++i) {
      if (i == 0 || pair_position[i].first != pair_position[i-1].first)
        cnt++;
      KMR[k][pair_position[i].second] = cnt;
    }
  }
}