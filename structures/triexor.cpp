#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
  Node * left, * right;

  Node () {
    left = nullptr;
    right = nullptr;
  }
};

struct Trie {
  Node * root;
  static const int SIZE = 61;

  Trie () {
    root = new Node();
  }

  void insert(ll n) {
    Node *crawl = root;
    for (int i = SIZE-1; i >= 0; --i) {
      ll current_bit = (1LL<<i);

      if (current_bit <= n) {
        n -= current_bit;
        if (!crawl->right) crawl->right = new Node();
        crawl = crawl->right;
      } 
      else {
        if (!crawl->left) crawl->left = new Node();
        crawl = crawl->left;
      }
    }
  }

  ll biggest_xor(ll n) {
    Node *crawl = root;
    ll ans = 0;

    for (int i = SIZE-1; i >= 0; --i) {
      bool is_bit_lit = (n & (1LL<<i));
      if ((is_bit_lit && crawl->left) || !crawl->right) {
        crawl = crawl->left;
      } else {
        ans += (1LL<<i);
        crawl = crawl->right;
      }
    }

    return ans;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  vector<ll> v;
  Trie trie;
  for (int i = 0; i < n; ++i) {
    ll x; scanf("%lld", &x);
    trie.insert(x);
    v.push_back(x);
  }

  ll ans = -1;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, trie.biggest_xor(v[i]) ^ v[i]);
  }

  printf("%lld\n", ans);
}