#include <iostream>

#include "avl.h"

int main() {
    int N, nq, elem;
    int query[2];
    avl_tree tree;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> elem;
        tree.insert(elem);
    }
    std::cin >> nq;
    for (int i = 0; i < nq; i++) {
        std::cin >> query[0];
        std::cin >> query[1];

        std::cout << tree.range_query(query[0], query[1]) << " ";
    }

    return 0;
}
