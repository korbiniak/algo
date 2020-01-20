#include<bits/stdc++.h>
using namespace std;

typedef char T;
static const int SIZE = 26;

struct Node {
  Node * children[SIZE];
  T val;
  bool is_end;


  Node() {
    is_end = false;
    for (int i = 0; i < SIZE; ++i) children[i] = nullptr;
    val = 0;
  }
};

struct Trie {
  Node * root;

  Trie () { root = new Node(); }
  Trie (Node * node) : root(node) {}

  void insert(T tab[], int sz) {
    Node *crawl = root;

    for (int i = 0; i < sz; ++i) {
      if (!crawl->children[tab[i]]) crawl->children[tab[i]] = new Node();
      crawl = crawl->children[tab[i]];
    }

    crawl->is_end = true;
  }

  bool exists(T tab[], int sz) {
    Node *crawl = root;
    
    for (int i = 0; i < sz; ++i) {
      if (!crawl->children[tab[i]]) return false;
      crawl = crawl->children[tab[i]];
    }

    return crawl->is_end;
  }

};

int main() {}