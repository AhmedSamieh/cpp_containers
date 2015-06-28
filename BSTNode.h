#include <iostream>

using namespace std;

template <class Type>
class BSTNode
{
private:
    BSTNode *parent;
    BSTNode *left;
    BSTNode *right;
    Type     val;
public:
    BSTNode() : parent(NULL), left(NULL), right(NULL)
    {
    }
    BSTNode(Type ival, BSTNode *iparent = NULL) : parent(iparent), left(NULL), right(NULL), val(ival)
    {
    }
    ~BSTNode()
    {
    }
    void set_parent(BSTNode *node)
    {
        parent = node;
    }
    BSTNode *get_parent()
    {
        return parent;
    }
    void set_left(BSTNode *node)
    {
        left = node;
    }
    BSTNode *get_left()
    {
        return left;
    }
    void set_right(BSTNode *node)
    {
        right = node;
    }
    BSTNode *get_right()
    {
        return right;
    }
    void set_val(Type ival)
    {
        val = ival;
    }
    Type get_val()
    {
        return val;
    }
};
