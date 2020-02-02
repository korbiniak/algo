#include<bits/stdc++.h>
using namespace std;

// Implementacja drzewa przedzial-przedzial, operacje dodaj na przedziale - suma na przedziale

const int M = (1<<18);
int tree[M*2 + 10], lazy[M*2 + 10];

// W kazdej kolejnej funkcji zmiennie node, start i end oznaczają to samo
// Node to numer węzła w którym teraz jesteśmy
// Start i end to przedział, który obejmuje ten węzeł.
// Oczywiście node*2 oraz node*2 + 1 to numery synów węzła node.
// Niech mid := (start+end)/2. Wtedy przedziały obejmowane przez synów node
// to odpowiednio [start, mid], [mid+1, end].
// W tree[node] mamy informacje o tym jaka jest dokładna suma na przedziale
// węzła node. Stąd w propagate i w update to mnożenie przez (end - start + 1)


void propagate(int node, int start, int end) {
    tree[node] += (end - start + 1) * lazy[node];
    if (start != end) {
        lazy[node*2] += lazy[node];
        lazy[node*2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int l, int r, int val, int node = 1, int start = 0, int end = M-1) {
    propagate(node, start, end);
    if (l > r || l > end || start > r) return;

    if (start <= l && r <= end) {
        tree[node] += (end - start + 1) * val;
        if (start != end) {
            lazy[node*2] += val;
            lazy[node*2 + 1] += val;
        }
        return;
    }

    int mid = (start + end)/2;
    update(l, r, val, node*2, start, mid);
    update(l, r, val, node*2 + 1, mid+1, end);

    tree[node] = tree[node*2] + tree[node*2 + 1];
}

int query(int l, int r, int node = 1, int start = 0, int end = M-1) {
    propagate(node, start, end);
    if (l > r || l > end || start > r) return 0;

    if (start <= l && r <= end) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    int p1 = query(l, r, node*2, start, mid);
    int p2 = query(l, r, node*2 + 1, mid+1, end);

    return p1 + p2;
}
