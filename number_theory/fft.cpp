#include<bits/stdc++.h>
using namespace std;
using cd = complex<double>;
typedef long long ll;

double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len/2; ++j) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd &x: a) 
            x /= n;
    }
}

vector<ll> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; ++i)
        result[i] = (ll)round(fa[i].real());
    return result;
}

int n;
vector<int> a, b;

void solve() {
    cin >> n;
    ++n;
    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    auto res = multiply(a, b);
    for (int i = 0; i < n*2-1; ++i) cout << res[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
   // cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}