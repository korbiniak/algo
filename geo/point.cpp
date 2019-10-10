struct Point {
	typedef int T;
	
	T x, y;

	Point(T _x, T _y) : x(_x), y(_y) {}
	Point() {}

	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	} 								

	Point operator + (const Point &p) const {
		return Point(x + p.x, y + p.y);
	}

	T operator * (const Point &p) const {
		return x * p.y - y * p.x;
	}

	T operator ^ (const Point &p) const {
		return x * p.x + y * p.y;
	}
};
