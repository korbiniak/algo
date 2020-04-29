#include<iostream>
#include<cstdio>
#include<algorithm>

class AVL {
private:
  struct node {
    int value, height, balance;
    node *left, *right, *parent;

    node(int _value=0, node *_parent=nullptr, node *_left=nullptr, node *_right=nullptr):
      value(_value), left(_left), right(_right), parent(_parent) {
        height = 1;
        balance = 0;
      }
  
    int compute() {
      int lh = 0, rh = 0;
      if (left) lh = left->height;
      if (right) rh = right->height;
      height = std::max(lh, rh) + 1;
      balance = lh - rh;
      return balance;
    }
  };
  
  node * root;
  
  void print(node *p) {
    if (p) {
      std::cout << p->value << ", parent: " << (p->parent ? p->parent->value : -1) 
                << ", address: " << p << ", sons adresses " << p->left << " " << p->right << "\n";
      print(p->left);
      print(p->right);
    }
  }

  void clear(node *p) {
    if (p) {
      clear(p->left);
      clear(p->right);
      delete p;
      p = nullptr;
    }
  }

  void rotr(node *p) {
    node *q = p->left;
    node *a = q->right;
    if (p->parent) {
      if (p->parent->left == p) p->parent->left = q;
      else p->parent->right = q;
    }
    q->parent = p->parent;
    p->parent = q;
    q->right = p;
    if (a) {
      a->parent = p;
    }
    p->left = a;

    p->compute();
    q->compute();
    if (q->parent)
      q->parent->compute();
    else root = q;
  }

  void rotl(node *p) {
    node *q = p->right;
    node *a = q->left;

    if (p->parent) {
      if (p->parent->left == p) p->parent->left = q;
      else p->parent->right = q;
    }
    q->parent = p->parent;
    p->parent = q;
    q->left = p;
    if (a) {
      a->parent = p;
    }
    p->right = a;

    p->compute();
    q->compute();
    if (q->parent)
      q->parent->compute();
    else root = q;
  }

  void rebalance(node *&p) {
    if (!p) return;
    p->compute();
    if (p->balance == -2) {
      if (p->right->left && p->right->left->height == p->height - 2) {
        rotr(p->right);
      }
      rotl(p);
    }
    else if (p->balance == 2) {
      if (p->left->right && p->left->right->height == p->height - 2) {
        rotl(p->left);
      }
      rotr(p);
    }
  }

  node* insert(int x, node *&p, node *parent=nullptr) {
    if (!p) {
      p = new node(x, parent);
      return p;
    }

    if (p->value > x) p->left = insert(x, p->left, p);
    if (p->value < x) p->right = insert(x, p->right, p);
    rebalance(p);
    return p;
  }

  bool find(int x, node *&p) {
    if (!p) return false; 
    if (p->value > x) return find(x, p->left);
    if (p->value < x) return find(x, p->right);
    return true;
  }

  void emplace_node(node *p, node *&q) {
    if (p->parent) {
      q->parent = p->parent;
      if (p->parent->left == p) p->parent->left = q;
      else p->parent->right = q;
    }
  }

  int get_rightest(node *&p) {
    if (!p->right) {
      if (p->left) emplace_node(p, p->left);
      int ret = p->value;
      rebalance(p->left);
      delete p;
      p = nullptr;
      return ret;
    }
    else return get_rightest(p->right);
  }

  int get_leftest(node *&p) {
    if (!p->left) {
      if (p->right) emplace_node(p, p->right);
      int ret = p->value;
      rebalance(p->right);
      delete p;
      p = nullptr;
      return ret;
    }
    else return get_leftest(p->left);
  }

  void erase(int x, node *&p) {
    if (!p) return;
    if (p->value > x) {
      erase(x, p->left); 
      rebalance(p);
      return;
    }
    if (p->value < x) {
      erase(x, p->right); 
      rebalance(p);
      return;
    }
    if (p->left) {
      if (!p->left->right) {
        p->value = p->left->value;
        node *temp = p->left->left;
        delete p->left;
        p->left = temp;
        if (temp) temp->parent = p;
        rebalance(p);
      }
      else {
        p->value = get_rightest(p->left);
      }
    }
    else if (p->right) {
      if (!p->right->left) {
        p->value = p->right->value;
        node *temp = p->right->right;
        delete p->right;
        p->right = temp;
        if (temp) temp->parent = p;
        rebalance(p);
      }
      else {
        p->value = get_leftest(p->right);
      }
    }
    else {
      if (p->parent) {
        if (p == p->parent->left) p->parent->left = nullptr;
        else p->parent->right = nullptr;
      }
      delete p;
      p = nullptr;
    }
  }

public:
  AVL() {
    root = nullptr;
  }

  void clear() {
    clear(root);
  }

  ~AVL() {
    clear();
  }

  void insert(int x) {
    insert(x, root);
  }

  bool find(int x) {
    return find(x, root);
  }

  void erase(int x) {
    erase(x, root);
  }

  void print() {
    print(root);
  }
};

int main() {
  int n;
  scanf("%d", &n);
  AVL s;
  for (int i = 0; i < n; ++i) {
    int x;
    char t;
    scanf(" %c%d", &t, &x);
    if (t == 'i') s.insert(x);
    else if (t == 'e') s.erase(x);
    else printf((s.find(x) ? "TAK\n" : "NIE\n"));
  }
}