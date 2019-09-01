#include <iostream>
#include <vector>
#include "rbtree.h"

using namespace std;

int main(int argc, char **argv)
{
    vector<int> data = {50, 40, 41, 42, 49, 45, 30, 20, 35, 75, 80, 70, 65, 60, 55, 69};
    //vector<int> data = {3, 1, 5, 7, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    //vector<int> data = {10, 11, 12, 13, 14, 15, 9, 8, 7, 6, 5, 16, 17, 18, 19, 4, 3, 2, 1};
    rbtree<int> tree;
    for (auto i : data)
    {
        tree.insert(i);
    }
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    cout << "erase 49 " << endl;
    tree.erase(49);
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    cout << "erase 50 " << endl;
    tree.erase(50);
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    cout << "erase 41 " << endl;
    tree.erase(41);
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    cout << "erase 42 " << endl;
    tree.erase(42);
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    cout << "erase 65 " << endl;
    tree.erase(65);
    tree.print();
    cout << "tree size : " << tree.size() << endl;
    return 0;
}