//
// Created by sasha on 04.12.2020.
//
#include <iostream>
#include <set>

int range_query(std::set <int> tree, int start, int finish){
    int count = 0;
    auto first = tree.lower_bound(start);
    auto second = tree.upper_bound(finish);

    while (first != second){
        first++;
        count++;
    }
    return count;
}

int main() {
    int N, nq, elem;
    int query[2];
    std::set <int> tree;

    std::cin >> N;
    for (int i = 0; i < N; i++){
        std::cin >> elem;
        tree.emplace(elem);
    }

    std::cin >> nq;
    for (int i = 0; i < nq; i++) {
        std::cin >> query[0];
        std::cin >> query[1];
        std::cout << range_query(tree, query[0], query[1]) << " ";
    }
    return 0;
}