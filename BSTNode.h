#include <iostream>

using namespace std;

template <class _KT_, class _VT_>
class BSTNode
{
private:
    BSTNode *parent;
    BSTNode *left;
    BSTNode *right;
    _KT_     key;
    _VT_     val;
public:
    BSTNode() : parent(NULL), left(NULL), right(NULL)
    {
    }
    BSTNode(_KT_ ikey, _VT_ ival) : parent(NULL), left(NULL), right(NULL), key(ikey), val(ival)
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
    void set_key(_KT_ ikey)
    {
        key = ikey;
    }
    _KT_ get_key()
    {
        return key;
    }
    void set_val(_VT_ ival)
    {
        val = ival;
    }
    _VT_ get_val()
    {
        return val;
    }
};
