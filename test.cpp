#include <iostream>
#include <vector>
#include "rbtree.h"

using namespace std;

int main(int argc, char **argv)
{
    //btree<int> tree;
    //tree.insert(5);
    //tree.insert(7);
    //tree.insert(2);
    //tree.insert(6);
    //tree.insert(3);
    //tree.insert(1);
    //tree.insert(9);
    //tree.insert(8);
    //tree.insert(4);
    //tree.insert(6);
    //tree.insert(2);
    //tree.insert(5);
    //tree.insert(7);
    //tree.insert(1);
    //tree.insert(10);
    //tree.print();
    //cout << "remove 2" << endl;
    //tree.erase(2);
    //tree.print();
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