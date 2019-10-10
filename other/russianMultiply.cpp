#include <bits/stdc++.h>
using namespace std;

typedef long long int LL;

LL RussianMultiply(LL a, LL b, LL c) {
	if (b == 0) return 0;
	LL h = (RussianMultiply(a, b/2, c) * 2) % c;
	if (b % 2 == 0) return h;
	return (h + a) % c;
}