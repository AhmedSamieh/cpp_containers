#ifndef _BNODE_H_
#define _BNODE_H_
#include "bnode_base.h"

template <class T>

class bnode : public bnode_base<T, bnode<T> >
{
    using parent_class = bnode_base<T, bnode<T> >;
public:
    bnode() : parent_class() {}
    bnode(T const& ival) : parent_class(ival) {}
    virtual ~bnode() {}
};
#endif // _BNODE_H_