#ifndef ATCODER_PERSISTENTSEGTREE_HPP
#define ATCODER_PERSISTENTSEGTREE 1

template<class S, S (*op)(S, S), S (*e)()>
struct PersistentSegmentTree {
    struct Node {
        Node *l, *r;
        S x;
        Node() : l(nullptr), r(nullptr) {}
    };

    const int sz;

    explicit PersistentSegmentTree(int n) : sz(n) {}

    Node* build() const {
        return _build(0, sz);
    }

    Node* set(Node* root, int pos, const S& x) const {
        assert(0 <= pos and pos < sz);
        return _set(root, pos, x, 0, sz);
    }

    S prod(Node* root, int a, int b) const {
        assert(0 <= a and a <= b and b <= sz);
        return _prod(root, a, b, 0, sz);
    }

    S get(Node* root, int pos) const {
        assert(0 <= pos and pos < sz);
        return prod(root, pos, pos + 1);
    }

private:
    Node* _new(const S& x) const {
        auto t = new Node();
        t->x = x;
        return t;
    }

    Node* _new(Node* l, Node* r) const {
        auto t = new Node();
        t->l = l, t->r = r, t->x = op(l->x, r->x);
        return t;
    }

    Node* _build(int l, int r) const {
        assert(l < r);
        if (l+1 == r) return _new(e());
        return _new(_build(l, (l+r)>>1), _build((l+r)>>1, r));
    }
    Node* _set(Node* t, int pos, const S& x, int l, int r) const {
        assert(l < r);
        if (pos == l and pos+1 == r) return _new(x);
        if (r <= pos or pos < l) return t;
        return _new(_set(t->l, pos, x, l, (l+r)>>1),
                    _set(t->r, pos, x, (l+r)>>1, r));
    }

    S _prod(Node* t, int a, int b, int l, int r) const {
        assert(l < r);
        if (r <= a or b <= l) return e();
        if (a <= l and r <= b) return t->x;
        return op(_prod(t->l, a, b, l, (l+r)>>1),
                  _prod(t->r, a, b, (l+r)>>1, r));
    }
};

#endif  // ATCODER_PERSISTENTSEGTREE_HPP
