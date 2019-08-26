#include <iostream>
#include <vector>
#include "rbtree.h"

using namespace std;

int main(int argc, char **argv)
{
    vector<int> data = {3, 1, 5, 7, 6, 8, 9, 10};
    //vector<int> data = {10, 11, 12, 13, 14, 15, 9, 8, 7, 6, 5, 16, 17, 18, 19, 4, 3, 2, 1};
    rbtree<int> tree;
    for (auto i : data)
    {
        tree.insert(i);
        tree.print();
    }
    //tree.erase(5);
    return 0;
}