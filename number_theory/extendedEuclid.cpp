pii ExtendedEuclid(int a, int b) {
    if (b == 0) return {1, 0};
    pii p = ExtendedEuclid(b, a % b);
    int x = p.st, y = p.nd;
    return {y, x - (a / b) * y};
}
