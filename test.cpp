#include <iostream>
#include "btree.h"

using namespace std;

int main(int argc, char **argv)
{
    btree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(6);
    tree.insert(3);
    tree.insert(1);
    tree.insert(9);
    tree.insert(8);
    tree.insert(4);
    tree.insert(6);
    tree.insert(2);
    tree.insert(5);
    tree.insert(7);
    tree.insert(1);
    tree.insert(10);
    tree.print();
    cout << "remove 2" << endl;
    tree.erase(2);
    tree.print();
    return 0;
}