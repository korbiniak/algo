#include <bits/stdc++.h>
using namespace std;

struct treap
{
    typedef int T;
    treap *left = nullptr, *right = nullptr;
    
    int rank, items = 1;
    bool rev = false;
    T value;
    
    treap(T val = T()) : value(val), rank(rand()) { }
    
    inline void update()
    {
        if(rev)
        {
            swap(left, right);
            if(left) left->rev = !left->rev;
            if(right) right->rev = !right->rev;
            rev = false;
        }
    }
};

inline int items(treap *t) { return t ? t->items : 0; }
inline void recalc(treap *t) { t->items = items(t->left) + items(t->right) + 1; }

pair<treap*, treap*> split(treap *t, int k) //dzieli na prefiks dlugosci k i reszte
{
    if(!t) return make_pair(nullptr, nullptr);
    //t = new treap(*t); //odkomentowac zeby zrobic strukture trwala
    t->update();
    if(items(t->left) < k)
    {
        auto p = split(t->right, k - items(t->left) - 1);
        t->right = p.first;
        recalc(t);
        return make_pair(t, p.second);
    }
    else
    {
        auto p = split(t->left, k);
        t->left = p.second;
        recalc(t);
        return make_pair(p.first, t);
    }
}

treap* merge(treap *a, treap *b)
{
    if(!a) return b;
    if(!b) return a;
    a->update();
    b->update();
    if(a->rank > b->rank)
    {
        //a = new treap(*a); //odkomentowac zeby zrobic strukture trwala
        a->right = merge(a->right, b);
        recalc(a);
        return a;
    }
    else
    {
        //b = new treap(*b); //odkomentowac zeby zrobic strukture trwala
        b->left = merge(a, b->left);
        recalc(b);
        return b;
    }
}

treap::T select(treap *t, int k) //zwraca k-ty element
{
    if(!t) return treap::T();
    t->update();
    int i = items(t->left);
    if(i == k) return t->value;
    if(i > k) return select(t->left, k);
    return select(t->right, k - i - 1);
}

treap* insert(treap *t, treap::T val, int k) //wstaw val na pozycje k (liczac od 0)
{
    auto p = split(t, k);
    return merge(merge(p.first, new treap(val)), p.second);
}

treap* erase(treap *t, int k)
{
    auto p1 = split(t, k);
    auto p2 = split(p1.second, 1);
    return merge(p1.first, p2.second);
}

treap* reverse(treap *t, int a, int b) //odwroc przedzial <a, b)
{
    auto p1 = split(t, b);
    auto p2 = split(p1.first, a);
    if(p2.second) p2.second->rev = !p2.second->rev;
    return merge(merge(p2.first, p2.second), p1.second);
}

void write(treap *t)
{
    if(!t) return;
    t->update();
    write(t->left);
    cout << t->value << " ";
    write(t->right);
}

treap *t = 0;

t = insert(t, k, l);
t = erase(t, k);
cout << select(t, k) << endl;
t = reverse(t, k, l);
write(t);