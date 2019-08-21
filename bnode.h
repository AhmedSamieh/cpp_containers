#ifndef _BNODE_H_
#define _BNODE_H_
#include "bnode_base.h"

template <class T>

class bnode : public bnode_base<T, bnode<T> >
{
public:
    bnode() : bnode_base<T, bnode<T>>() {}
    bnode(T const& ival) : bnode_base<T, bnode<T> >(ival) {}
};
#endif // _BNODE_H_