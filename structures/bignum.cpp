using namespace std;
typedef long long LL;

struct bigint { 
	vector<int> z;
	static const int base = 1e9;
	static const int base_digit = 9;
	int sign;

	bigint() : sign(1) {}
	bigint(const LL &v) {
		*this = v;
	} 
	
	bigint(const string &s) {
		read(s);
	}

	bigint &operator=(LL v) {
		sign = v < 0 ? -1 : 1;
		v *= sign;
		z.clear();
		while(v > 0) {
			z.pb(int(v%base));
			v /= base;
		}
		return *this;
	}

	void trim() {
		while(!z.empty() && z.back() == 0) z.pop_back();
		if(z.empty()) sign = 1;
	}

	void read(const string &s) {
		z.clear();
		sign = 1;
		int in = 0;
		while(in < sz(s) && (s[in] == '-' || s[in] == '+')) {
			if(s[in] == '-') sign = -sign;
			++in;
		}
		for(int i = sz(s) - 1; i >= in ; i -= base_digit) {
			int x = 0;
			for(int j = max(in, i - base_digit + 1) ; j <= i ; ++j) 
				x = x*10 + s[j] - '0';
			z.pb(x);
		}
		trim();
	}

	bool operator<(const bigint &b) const {
		if(sign != b.sign)
			return sign < b.sign;
		if(sz(z) != sz(b.z)) 
			return sz(z) * sign < sz(b.z) * b.sign;
		for(int i = sz(z) - 1 ; i >= 0 ; --i) 
			if(z[i] != b.z[i]) 
				return z[i] * sign < b.z[i] * sign;
		return false;
	}

	bool operator>(const bigint &b) const {
		return b < *this;
	}

	bool operator<=(const bigint &b) const {
		return !(*this > b);
	}

	bool operator>=(const bigint &b) const {
		return !(*this < b);
	}

	bool operator==(const bigint &b) const {
		return !(*this < b) && !(*this > b);
	}

	bool operator!=(const bigint &b) const {
		return (*this < b) || (*this > b);
	}

	friend bigint operator-(bigint v) {
		if(sz(v.z) > 0) v.sign = -v.sign;
		return v;
	}

	bool isZero() const{
		return !sz(z);
	}

	bigint &operator+=(const bigint &b) {
		if(sign == b.sign) {
			for(int i = 0, carry = 0 ; i < sz(b.z) || carry ; ++i) {
				if(i == sz(z)) z.pb(0);
				z[i] += carry + (i < sz(b.z) ? b.z[i] : 0);
				carry = z[i] >= base;
				if(carry) z[i] -= base;   
			}
		}else if(b != 0) {
			*this -= -b;
		}
		return *this;
	}

	friend bigint operator+(bigint a, const bigint &b) {
		return a += b;
	}

	bigint &operator-=(const bigint &b) {
		if(sign == b.sign) {
			if((sign == 1 && *this >= b) || (sign == -1 && *this <= b)) {
				for(int i = 0, carry = 0; i < sz(b.z) || carry ; ++i) {
					z[i] -= carry + (i < sz(b.z) ? b.z[i] : 0);
					carry = z[i] < 0;
					if(carry) z[i] += base;
				} 
				trim();
			}else {
				*this = b - *this;
				this->sign = -this->sign;
			}
		}else {
			*this += -b;
		}
		return *this;
	}

	friend bigint operator - (bigint a, const bigint &b) {
		return a -= b;
	}
	
	bigint &operator*=(int v) {
		if(v < 0) {
			sign = -sign;
			v = -v;
		}
		for(int i = 0 , carry = 0 ; i < sz(z) || carry ; ++i) {
			if(i == sz(z))
				z.pb(0);
			LL cur = (LL)((LL)z[i] * (LL)v + (LL)carry);
			carry = int(cur / base);
			z[i] = int(cur % base);
		} 
		trim();
		return *this;
	}

	bigint operator*(int v) const {
		return bigint(*this) *= v;
	}

	bigint &operator/=(int v) {
		if(v < 0) {
			v = -v;
			sign = -sign;
		}
		for(int i = sz(z) - 1, rem = 0; i >= 0 ; --i) {
			LL cur = (LL)((LL)rem * (LL)base + (LL)z[i]);
			z[i] = int(cur / v);
			rem = int(cur % v);
		}
		trim();
		return *this;
	}

	bigint operator/(int v) const {
		return bigint(*this) /= v;
	}

	int operator%(int v) {
		if(v < 0) v = -v;
		int m = 0;
		for(int i = sz(z) - 1 ; i >= 0 ; --i) {
			m = int((LL)((LL)z[i] + (LL)m*(LL)base) % v);
		}
		return m * sign;
	}


	friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
		int norm = base / (sz(b1.z) + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.z.resize(sz(a.z));

		for(int i = sz(a.z) - 1; i >= 0 ; --i) {
			r *= base;
			r += a.z[i];
			int s1 = sz(b.z) < sz(r.z) ? r.z[sz(b.z)] : 0;
			int s2 = sz(b.z) - 1 < sz(r.z) ? r.z[sz(b.z) - 1] : 0;
			int d = int((LL)((LL)s1 * (LL)base + (LL)s2) / b.z.back());
			r -= b * d;
			while(r < 0) {
				r += b;
				--d;
			}
			q.z[i] = d;
		}
		
		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return {q, r/norm};
	}

	bigint operator/(const bigint &v) const {
		return divmod(*this, v).st;
	}

	bigint operator%(const bigint &v) const {
		return divmod(*this, v).nd;
	}

	bigint abs() const {
		return sign == 1 ? *this : -*this;
	} 

	static vector<int> convert_base(const vector<int> &a, int oldD, int newD) {
		vector<LL> p(max(oldD, newD) + 1);
		p[0] = 1;
		for(int i = 1 ; i < sz(p); ++i) {
			p[i] = p[i-1] * 10;
		}	
		vector<int> res;
		LL cur = 0;
		int curD = 0;
		for(int v : a) {
			cur += (LL)v * (LL)p[curD];
			curD += oldD;
			while(curD >= newD) {
				res.pb(int(cur % p[newD]));
				cur /= p[newD];
				curD -= newD;
			} 
		}
		res.pb(int(cur));
		while(!res.empty() && res.back() == 0) res.pop_back();
		return res;
	}

	static vector<LL> karatsuba(const vector<LL> &a, const vector<LL> &b) {
		int n = sz(a);
		vector<LL> res(n+n);
		if(n <= 32) {
			for(int i = 0 ; i < n ; ++i)
				for(int j = 0 ; j < n ; ++j)
					res[i+j] += a[i] * b[j];
			return res;
		}
	
		int k = n >> 1;

		vector<LL> a1(a.begin(), a.begin() + k);
		vector<LL> a2(a.begin() + k, a.end());
		vector<LL> b1(b.begin(), b.begin() + k);
		vector<LL> b2(b.begin() + k, b.end());

		vector<LL> a1b1 = karatsuba(a1,b1);
		vector<LL> a2b2 = karatsuba(a2,b2);

		for(int i = 0 ; i < k ; ++i)
			a2[i] += a1[i];
		for(int i = 0 ; i < k ; ++i)
			b2[i] += b1[i];

		vector<LL> r = karatsuba(a2, b2);

		for(int i = 0 ; i < sz(a1b1) ; ++i)
			r[i] -= a1b1[i];
		for(int i = 0 ; i < sz(a2b2) ; ++i)
			r[i] -= a2b2[i];

		for(int i = 0 ; i < sz(r) ; ++i) 
			res[i + k] += r[i];
		for(int i = 0 ; i < sz(a1b1) ; ++i)
			res[i] += a1b1[i];
		for(int i = 0 ; i < sz(a2b2) ; ++i)
			res[i + n] += a2b2[i];

		return res;
	}

	bigint operator*(const bigint &v) const {
		vector<int> a6 = convert_base(this->z, base_digit, 6);
		vector<int> b6 = convert_base(v.z, base_digit, 6);
		vector<LL> a(all(a6)), b(all(b6));
		while(sz(a) < sz(b))
			a.pb(0);
		while(sz(b) < sz(a))
			b.pb(0);
		while(sz(a) & (sz(a) - 1)) {
			a.pb(0);
			b.pb(0);
		} 
		vector<LL> c = karatsuba(a,b);
		bigint res;
		res.sign = sign * v.sign;
		for(int i = 0 , carry = 0 ; i < sz(c); ++i) {
			LL cur = c[i] + carry;
			res.z.pb(int(cur % 1000000LL));
			carry = int(cur/1000000LL);
		}
		res.z = convert_base(res.z, 6, base_digit);
		res.trim();
		return res;
	}

	bigint &operator*=(const bigint &v) {
		*this = *this * v;
		return *this;
	}

	friend istream &operator>>(istream &stream, bigint &v) {
		string s;
		stream >> s;
		v.read(s);
		// cout << sz(v.z) << "\n";
		return stream;
	} 

	friend ostream &operator<<(ostream &stream, const bigint &v) {
		if(v.sign == -1)
			stream << '-';
		stream << (sz(v.z) ? v.z.back() : 0);
		for(int i = sz(v.z) - 2 ; i >= 0 ; --i)
			stream << setw(base_digit) << setfill('0') << v.z[i];
		return stream; 
	}

	friend bigint gcd(bigint a, bigint b) {
		return b.isZero() ? a : gcd(b, a % b);
	}
};