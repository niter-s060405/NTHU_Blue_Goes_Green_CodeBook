/*
Tested : https://cses.fi/paste/e6e2c1cedbac71a411e38fd/
AI generated code
*/
// Each operation adds at most (K × ceil(log_2(n))) nodes
// Range update : K = 8, Range query : K = 4
// Only point update : ceil(log_2(n)) + 1
// To optimize K, consider 懶標永久化
struct Persistent_Segment_Tree { // 1-based, [l, r]
	struct Node {
		int lc = 0, rc = 0, sum = 0, tag = 0;
	};
	vector<Node> tr;

	Persistent_Segment_Tree() {
		tr.push_back({}); // Node 0 is null dummy
	}

	void apply(int u, int len, int v) {
		tr[u].sum += v * len;
		tr[u].tag += v;
	}

	void pushup(Node& u) {
		u.sum = tr[u.lc].sum + tr[u.rc].sum;
	}

	Node merge(const Node& a, const Node& b) const {
		return {0, 0, a.sum + b.sum, 0};
	}

	void pushdown(int u, int l, int r) {
		if (!tr[u].tag) return;
		int mid = (l + r) >> 1, tag = tr[u].tag;
		int lc = tr.size(), rc = tr.size() + 1;
		tr.push_back(tr[tr[u].lc]); tr.push_back(tr[tr[u].rc]);
		apply(lc, mid - l + 1, tag); apply(rc, r - mid, tag);
		tr[u].tag = 0; tr[u].lc = lc; tr[u].rc = rc;
	}

	// Must build before use, returns root index
	int build(int l, int r, const vector<int>& a = {}) {
		int u = tr.size(); tr.push_back({});
		if (l == r) {
			tr[u].sum = (a.empty() ? 0 : a[l]);
			return u;
		}
		int mid = (l + r) >> 1;
		int lc = build(l, mid, a), rc = build(mid + 1, r, a);
		tr[u].lc = lc; tr[u].rc = rc;
		pushup(tr[u]);
		return u;
	}

	// Returns root index
	int update(int pre, int l, int r, int ql, int qr, int v) {
		int u = tr.size(); tr.push_back(tr[pre]);
		if (ql <= l && r <= qr) {
			apply(u, r - l + 1, v);
			return u;
		}
		pushdown(u, l, r);
		int mid = (l + r) >> 1, lc = tr[u].lc, rc = tr[u].rc;
		if (ql <= mid) lc = update(lc, l, mid, ql, qr, v);
		if (qr > mid)  rc = update(rc, mid + 1, r, ql, qr, v);
		tr[u].lc = lc; tr[u].rc = rc;
		pushup(tr[u]);
		return u;
	}

	Node query(int u, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return tr[u];
		pushdown(u, l, r);
		int mid = (l + r) >> 1, lc = tr[u].lc, rc = tr[u].rc;
		if (qr <= mid) return query(lc, l, mid, ql, qr);
		if (ql > mid)  return query(rc, mid + 1, r, ql, qr);
		return merge(query(lc, l, mid, ql, qr),
					 query(rc, mid + 1, r, ql, qr));
	}
};
