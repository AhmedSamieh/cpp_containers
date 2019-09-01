#ifndef _BNODE_BASE_H_
#define _BNODE_BASE_H_

template <class T, class Node>
class bnode_base
{
private:
    Node *parent;
    Node *left;
    Node *right;
    T     val;
protected:
    bnode_base() : parent(NULL), left(NULL), right(NULL) {}
    bnode_base(T const &ival) : parent(NULL), left(NULL), right(NULL), val(ival) {}
    virtual ~bnode_base() {}
public:
    void set_parent(Node *const node)
    {
        parent = node;
    }
    Node *const get_parent(void)
    {
        return parent;
    }
    void set_left(Node *const node)
    {
        left = node;
    }
    Node *const get_left(void)
    {
        return left;
    }
    void set_right(Node *const node)
    {
        right = node;
    }
    Node *const get_right(void)
    {
        return right;
    }
    void set_val(T const &ival)
    {
        val = ival;
    }
    T const &get_val(void)
    {
        return val;
    }
};

#endif // _BNODE__BASE_H_
