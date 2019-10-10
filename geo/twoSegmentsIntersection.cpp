inline Point interSect(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	LD t = (p1-p2) * (q1-q2);
	LD s = (q2-p2) * (q1-q2);
	LD e = s/t;
	return Point(e*p1.x + (1-e)*p2.x, e*p1.y + (1-e)*p2.y);
} 
