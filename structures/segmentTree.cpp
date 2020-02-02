#include<bits/stdc++.h>
using namespace std;

const int M = (1<<18); //Rozmiar drzewa, M >= rozmiar którego potrzebujesz
int tree[M * 2 + 10];

// DRZEWO PUNKT-PRZEDZIAL

void update(int where, int val) {
    where += M;
    tree[where] += val;
    while (where > 1) {
        where /= 2;
        tree[where] = max(tree[where*2], tree[where*2 + 1]);
    }
}

int query(int l, int r) {
    if (l > r) return;
    l += M; r += M;
    int ans = max(tree[l], tree[r]);

    /* Jesli robilbys dodaj na przedziale - suma na przedziale:
     * int ans = tree[l];
     * if (l != r) ans += tree[r] */

    while (l/2 != r/2) {
        if (l % 2 == 0) ans += tree[l+1];
        if (r % 2 == 1) ans += tree[r-1];
        l /= 2; r /= 2;
    }

    return ans;
}


// DRZEWO PRZEDZIAL-PUNKT

void update(int l, int r, int val) {
    l += M; r += M;
    tree[l] += val;
    if (l != r) tree[r] += val;
    
    while (l/2 != r/2) {
        if (l % 2 == 0) tree[l+1] += val;
        if (r % 2 == 1) tree[r-1] += val;
        l /= 2;
        r /= 2;
    }
}

int query(int where) {
    where += M;
    int ans = 0;

    while (where > 0) {
        ans += tree[where];
        where /= 2;
    }

    return ans;
}
