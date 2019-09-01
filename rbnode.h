#ifndef _RBNODE_H_
#define _RBNODE_H_
#include "bnode_base.h"

template <class T>

class rbnode : public bnode_base<T, rbnode<T> >
{
    using parent_class = bnode_base<T, rbnode<T> >;

    bool red;

public:
    rbnode() : parent_class(), red(true) {}
    rbnode(T const &ival) : parent_class(ival), red(true) {}
    virtual ~rbnode() {}
    void set_red(bool const is_red)
    {
        red = is_red;
    }
    bool const is_red(void)
    {
        return red;
    }
};
#endif // _RBNODE_H_