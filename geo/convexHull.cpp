vector<pair<pnt,int>> convexHull(vector<pair<pnt,int>> &points) {
	sort(all(points));
	int n = sz(points);
	vector<pair<pnt,int>> hull;
	for (int i = 0 ; i < n*2 - 1 ; ++i) {
		int j = i < n ? i : (2 * n) - i - 2;
		while(sz(hull) >= 2 && ((points[j].st - (hull.end()[-1]).st) * ((hull.end()[-2]).st - (hull.end()[-1]).st)) < 0)
			hull.pop_back();
		hull.pb(points[j]);
	}
	hull.pop_back();
	return hull;
}