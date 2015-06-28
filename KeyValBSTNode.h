#include <iostream>

using namespace std;

template <class KeyType, class ValType>
class KeyValBSTNode
{
private:
    KeyValBSTNode *parent;
    KeyValBSTNode *left;
    KeyValBSTNode *right;
    KeyType        key;
    ValType        val;
public:
    KeyValBSTNode() : parent(NULL), left(NULL), right(NULL)
    {
    }
    KeyValBSTNode(KeyType ikey, ValType ival) : parent(NULL), left(NULL), right(NULL), key(ikey), val(ival)
    {
    }
    ~KeyValBSTNode()
    {
    }
    void set_parent(KeyValBSTNode *node)
    {
        parent = node;
    }
    KeyValBSTNode *get_parent()
    {
        return parent;
    }
    void set_left(KeyValBSTNode *node)
    {
        left = node;
    }
    KeyValBSTNode *get_left()
    {
        return left;
    }
    void set_right(KeyValBSTNode *node)
    {
        right = node;
    }
    KeyValBSTNode *get_right()
    {
        return right;
    }
    void set_key(KeyType ikey)
    {
        key = ikey;
    }
    KeyType get_key()
    {
        return key;
    }
    void set_val(ValType ival)
    {
        val = ival;
    }
    ValType get_val()
    {
        return val;
    }
};
