static const int M = (1<<17);
static const int N = 1e5 + 10;
static const int K = 18;
 
struct Node {
	Node* left;
	Node* right;
	int val;
 
	Node(Node* _left = nullptr, Node* _right = nullptr, int _val = 0) :
		left(_left), right(_right), val(_val) {}
};
 
Node* ver[N];
 
void upgrade(Node* &prev, Node* &cur, int start, int end, int where, int val) {
	if (start > where || end < where || start > end) 
		return;
 
	if (start == end) {
		cur->val = val;
		return;
	}
 
	int mid = (start + end) / 2;
 
	if (where > mid) {
		cur->left = prev->left;
		cur->right = new Node();
 
		upgrade(prev->right, cur->right, mid + 1, end, where, val);
	}
	else {
		cur->left = new Node();
		cur->right = prev->right;
 
		upgrade(prev->left, cur->left, start, mid, where, val);
	}
 
	cur->val = cur->left->val + cur->right->val;
}
 
int getVal(Node* nodes[]) {
	return nodes[0]->left->val + nodes[1]->left->val - (2 * nodes[2]->left->val);
}
 
int query(Node* nodes[], int add, int start, int end, int k) {
	Node* crawl[] = {nodes[0], nodes[1], nodes[2]};
	while (start != end) {
		int lVal = getVal(crawl);
 
		int mid = (start + end) / 2;
		if (start <= add && add <= mid) lVal++;
 
		if (lVal >= k) {
			FOR (i, 0, 3) {
				crawl[i] = crawl[i]->left;
			}
			end = mid;
		} else {
			k -= lVal;
			FOR (i, 0, 3) {
				crawl[i] = crawl[i]->right;
			}
			start = mid + 1;
		}
	}
 
	return start;
} 
 
void build(Node* &node, int start, int end) {
	node = new Node();
	if(start == end) 
		return;
	int mid = (start + end) / 2;
	build(node->left, start, mid);
	build(node->right, mid + 1, end);
}