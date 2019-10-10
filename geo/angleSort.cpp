using namespace std;
typedef long long LL;

bool cmp(Point p1, Point p2) {
	bool t1 = (p1.x > 0 || (p1.x == 0 && p1.y >= 0));
	bool t2 = (p2.x > 0 || (p2.x == 0 && p2.y >= 0));
	if(t1 != t2) return t1;
	return (p1 * p2) < 0;
}

//sortowanie względem pierwszego punktu
sort(t + 1, t + n, [&](const Point &p1, const Point &p2) {
	return cmp(p1 - t[0], p2 - t[0]);
});	
