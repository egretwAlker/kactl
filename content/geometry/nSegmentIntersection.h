/**
 * Author: e-maxx.ru
 * Date: 2019-05-07
 * License: CC0
 * Source: cp-algorithms
 * Description: Given  $n$  line segments on the plane. It is required to check whether 
 * at least two of them intersect with each other. If the answer is yes, then print 
 * this pair of intersecting segments; it is enough to choose any of them among several
 *  answers. It returns ids of the segments intersecting. This can be used to find if two polygons intersect for example
 * Time: expected O(n log n)
 * Status: stress-tested
 */
typedef double Sc; 
const Sc EPS = 1E-9;
typedef Point<Sc> P;
struct Segment {
    P p, q; int id;
    Sc get_y(Sc x) const {
        if (abs(p.x - q.x) < EPS) return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};
bool intersect1d(Sc l1, Sc r1, Sc l2, Sc r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}
int vec(const P& a, const P& b, const P& c) {
    Sc s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}
bool intersect(const Segment& a, const Segment& b) {
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
           intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
           vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
           vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}
bool operator<(const Segment& a, const Segment& b) {
    Sc x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}
struct event {
    Sc x; int tp, id;
    // event() {}
    event(Sc x, int tp, int id) : x(x), tp(tp), id(id) {}
    bool operator<(const event& e) const {
        if (abs(x - e.x) > EPS) return x < e.x;
        return tp > e.tp;
    }
};
set<Segment>::iterator prev(set<Segment>::iterator it, set<Segment>& s) { return it == s.begin() ? s.end() : --it; }
set<Segment>::iterator next(set<Segment>::iterator it) { return ++it; }
pair<int, int> n_seg_inter(const vector<Segment>& a) {
    int n = (int)a.size();
    vector<event> e;
    for (int i = 0; i < n; ++i) {
        e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i));
        e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i));
    }
    sort(e.begin(), e.end());

    set<Segment> s;
    s.clear();
    vector<set<Segment>::iterator> where;
    where.resize(a.size());
    for (size_t i = 0; i < e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            set<Segment>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt, s);
            if (nxt != s.end() && intersect(*nxt, a[id]))
                return make_pair(nxt->id, id);
            if (prv != s.end() && intersect(*prv, a[id]))
                return make_pair(prv->id, id);
            where[id] = s.insert(nxt, a[id]);
        } else {
            set<Segment>::iterator nxt = next(where[id]), prv = prev(where[id], s);
            if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
                return make_pair(prv->id, nxt->id);
            s.erase(where[id]);
        }
    }

    return make_pair(-1, -1);
}