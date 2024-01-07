//
// Created by francesco on 05/01/24.
//

#include "Path.h"

Path::Path(const vector<int> &v) : nodes(v) {}

Path::Path(int size) {
    nodes = vector<int>(size);
    for (int i = 0; i < size; i++) nodes[i] = i;
}

unsigned long Path::size() const {
    return nodes.size();
}

int Path::operator[](int index) const {
    return nodes[(index + size()) % size()];
}

const vector<int> &Path::as_vector() const {
    return nodes;
}

Path Path::reverse_sub_path(int from, int to) const {
    vector<int> res(as_vector());
    for (int i = from; i <= (from + to) / 2; i++) {
        swap(res[i], res[to - (i - from)]);
    }
    return Path(res);
}

string Path::as_string() const {
    string res = "[";
    for (int node: nodes) {
        res += to_string(node) + ", ";
    }
    res.pop_back();
    res.pop_back();
    res += "]";
    return res;
}

bool Path::operator<(const Path &p) const {
    return nodes < p.nodes;
}
