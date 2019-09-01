#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "rbtree.h"

template <class T, class Compare = std::greater<T> >

class priority_queue : protected rbtree<T, Compare>
{
    using parent_class = rbtree<T, Compare>;
public:
    priority_queue()
    {
    }
    virtual ~priority_queue()
    {
        this->clear();
    }
    bool empty()
    {
        return parent_class::empty();
    }
    size_t size()
    {
        return parent_class::size();
    }
    const T &top()
    {
        auto ptr = parent_class::top();
        if (NULL != ptr)
        {
            return ptr->get_val();
        }
    }
    void push(const T &val)
    {
        parent_class::insert(val);
    }
    void pop()
    {
        if (!this->empty())
        {
            parent_class::erase(parent_class::top());
        }
    }
};

#endif // _PRIORITY_QUEUE_H_