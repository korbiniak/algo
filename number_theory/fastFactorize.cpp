const int FACTORS_THRESHOLD = 8000000;
const int NAIVE_PRIMES_TRIES = 4000;

LL FastPow(LL a, LL b, LL m) {
  LL ca = a, r = 1LL;
  while (b > 0LL) {
    if (b & 1LL) r = RussianMultiply(r, ca, m);
    ca = RussianMultiply(ca, ca, m);
    b >>= 1;
  }
  return r;
}

LL Abs(LL x) {
  return (x >= 0) ? x : -x;
}

void Sieve(int n, vector<int>* primes, vector<int>* factors) {
  factors->resize(n+1);
  for (int i = 2; i*i <= n; i++) {
    if ((*factors)[i] != 0) continue;
    for (int j = 2*i; j <= n; j += i)
      if ((*factors)[j] == 0) (*factors)[j] = i;
  }
  (*factors)[1] = 1;
  for (int i = 2; i <= n; i++)
    if ((*factors)[i] == 0) {
      (*factors)[i] = i;
      primes->push_back(i);
    }
}

LL PollardRho(LL n) {
  bool succeed = false;
  LL g;
  while (!succeed) {
    succeed = true;
    LL b0 = rand() % n, b1 = b0;
    LL dod = rand() % n;
    b1 = (RussianMultiply(b1, b1, n) + dod) % n;
    g = Gcd(Abs(b0 - b1), n);
    while (g == 1) {
      b0 = (RussianMultiply(b0, b0, n) + dod) % n;
      b1 = (RussianMultiply(b1, b1, n) + dod) % n;
      b1 = (RussianMultiply(b1, b1, n) + dod) % n;
      g = Gcd(Abs(b0 - b1), n);
      if (g == n) {
        succeed = false;
        break;
      }
    }
  }
  return g;
}

LL Ferma(LL n) {
  LL x = sqrt(n), y = 0, r = x*x - n;
  while (true) {
    if (r == 0) return x != y ? x-y : x+y;
    if (r > 0) { r -= y+y+1LL, y++; }
    else { r += x+x+1LL; x++; }
  }
}

int SmallestFactor(LL n, const vector<int>& primes, const vector<int>& factors) {
  if (n <= FACTORS_THRESHOLD) {
    if (factors[n] == n) return 1;
    return factors[n];
  }
  else {
    for (int i = 0; i < primes.size() && i < NAIVE_PRIMES_TRIES; i++)
      if (n % primes[i] == 0)
        return primes[i];
    return 1;
  }
}

bool MillerRabin(LL n, const vector<int>& primes, const vector<int>& factors) {
  int div = SmallestFactor(n, primes, factors);
  if (div != 1) return false;
  if (n <= FACTORS_THRESHOLD) return true;
  LL s = 1, d = n-1LL;
  while ((d & 1LL) == 0LL) {
    s <<= 1;
    d >>= 1;
  }
  const int b[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  for (int i = 0; i < 7; i++) {
    bool ok = false;
    LL x = FastPow(b[i], d, n);
    if (x == 1 || x == n-1) continue;
    for (int i = 0; i < s; i++) {
      x = RussianMultiply(x, x, n);
      if (x == 1) return false;
      if (x == n-1) { ok = true; break; }
    }
    if (ok) continue;
    return false;
  }
  return true;
}

void Factorize(LL n, const vector<int>& primes, const vector<int>& factors,
               unordered_map<LL,int>* factorization) {
  if (n == 1) return;
  if (MillerRabin(n, primes, factors)) { (*factorization)[n]++; return; }
  LL d = 1;
  if (d == 1) d = SmallestFactor(n, primes, factors);
  if (d == 1) d = PollardRho(n);
  if (d == 1) d = Ferma(n);
  Factorize(d, primes, factors, factorization);
  Factorize(n / d, primes, factors, factorization);
}

unordered_map<LL,int> Factorize(LL n,
                                const vector<int>& primes,
                                const vector<int>& factors) {
  unordered_map<LL,int> factorization;
  Factorize(n, primes, factors, &factorization);
  return factorization;
}

void Divisors(const unordered_map<LL,int>& factorization,
              unordered_map<LL,int>::iterator it,
              LL divisor,
              LL min_div,
              vector<LL>* result) {
  if (it == factorization.end()) {
    result->push_back(divisor);
    return;
  }
  for (int i = 0; i <= it->second; i++) {
    Divisors(factorization, next(it), divisor, min_div, result);
    if (i < it->second)
        divisor *= it->first;
  }
}

vector<LL> Divisors(LL n,
                    const vector<int>& primes,
                    const vector<int>& factors,
                    int min_div) {
  unordered_map<LL,int> factorization = Factorize(n, primes, factors);
  vector<LL> divisors;
  Divisors(factorization, factorization.begin(), 1LL, min_div, &divisors);
  return divisors;
}