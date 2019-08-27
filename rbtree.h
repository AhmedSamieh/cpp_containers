#ifndef _RBTREE_H_
#define _RBTREE_H_
#include "rbnode.h"
#include "btree.h"

/*
 - [OK] Every node is red or black
 - [OK] Root is always black - if it is red we change it to black
 - [OK] New insertions are always red
 - Every path from root to leaf has the same number of black nodes
 - [OK] No path can have tow consecutive red nodes
 - [OK] Nulls are black

 - Black aunt rotate, after rotation we got black parent and red children
 - Red aunt color flip, after flip we got red grand-parent and black parent/aunt
 */
template <class T, class Node = rbnode<T> >
class rbtree : public btree<T, Node>
{
    using parent_class = btree<T, Node>;
protected:
    void balance(Node* node)
    {
        while (true)
        {
            // facts:
            // - node is red
            // - mum is red, not the root, we have a grandma
            // - sister is black
            // - grandma is black, it may be the root
            Node* mum = node->get_parent();
            Node* grandma = mum->get_parent();
            Node* grand_grandma = grandma->get_parent();
            bool  mum_direction = (grandma->get_right() == mum);
            bool  node_direction = (mum->get_right() == node);
            Node* aunt = mum_direction ? grandma->get_left() : grandma->get_right();

            if (NULL == aunt || !aunt->is_red()) // aunt is black : rotate A->B->C
            {
                Node* new_parent;
                if (mum_direction != node_direction)
                {
                    new_parent = node;
                    mum->set_parent(node);
                    if (mum_direction) // && !node_direction
                    {
                        // A<-C->B
                        node->set_left(grandma);
                        node->set_right(mum);
                        grandma->set_right(NULL);
                        mum->set_left(NULL);
                    }
                    else //if (!mum_direction && node_direction)
                    {
                        // B<-C->A
                        node->set_right(grandma);
                        node->set_left(mum);
                        grandma->set_left(NULL);
                        mum->set_right(NULL);
                    }
                }
                else // if (mum_direction == node_direction)
                {
                    new_parent = mum;
                    if (mum_direction)
                    {
                        // A<-B->C
                        grandma->set_right(mum->get_left()); // sister is black
                        mum->set_left(grandma); // same
                    }
                    else
                    {
                        // C<-B->A
                        grandma->set_left(mum->get_right()); // sister is black
                        mum->set_right(grandma); // same
                    }
                }
                if (NULL == grand_grandma)
                {
                    parent_class::root = new_parent;
                }
                else
                {
                    if (grand_grandma->get_right() == grandma)
                    {
                        grand_grandma->set_right(new_parent);
                    }
                    else // if (grand_grandma->get_left() == grandma)
                    {
                        grand_grandma->set_left(new_parent);
                    }
                }
                new_parent->set_parent(grand_grandma);
                new_parent->set_red(false);
                grandma->set_parent(new_parent);
                grandma->set_red(true); // it's ok, parent, right and left are black
            }
            else // if (NULL != aunt && aunt->is_red()) // aunt is red : color flip
            {
                aunt->set_red(false);
                mum->set_red(false);
                if (NULL != grand_grandma)
                {
                    grandma->set_red(true);
                    if (grand_grandma->is_red())
                    {
                        node = grandma;
                        continue;
                    }
                }
            }
            break;
        }
    }
    virtual void subtree_print(Node* const subtree_root)
    {
        list<pair< pair<Node* const, int>, bool> > q;
        q.push_back(make_pair(make_pair(subtree_root, 64), true));
        while (!q.empty())
        {
            auto node = q.front();
            q.pop_front();
            for (int i = 0; i < node.first.second/2; i++)
            {
                cout << " ";
            }
            if (NULL != node.first.first)
            {
                int shift = (node.first.first->get_val() / 10) ? ((node.first.first->get_val() / 100) ? 3:2):1;
                if (NULL != node.first.first->get_left())
                {
                    for (int i = shift; i < node.first.second/2; i++)
                    {
                        cout << ".";
                    }
                }
                else
                {
                    for (int i = shift; i < node.first.second/2; i++)
                    {
                        cout << " ";
                    }
                }
                cout << node.first.first->get_val() << (node.first.first->is_red() ? 'R':'B');
                if (NULL != node.first.first->get_right())
                {
                    for (int i = 1; i < node.first.second/2; i++)
                    {
                        cout << ".";
                    }
                }
                else
                {
                    for (int i = 1; i < node.first.second/2; i++)
                    {
                        cout << " ";
                    }
                }
                for (int i = 0; i < node.first.second/2; i++)
                {
                    cout << " ";
                }
            }
            else
            {
                for (int i = 0; i < node.first.second/2; i++)
                {
                    cout << " ";
                }
                for (int i = 0; i < node.first.second; i++)
                {
                    cout << " ";
                }
            }
            if (node.second)
            {
                cout << endl;
            }
            if (NULL != node.first.first)
            {
                q.push_back(make_pair(make_pair(node.first.first->get_left(), (node.first.second)/2), false));
                q.push_back(make_pair(make_pair(node.first.first->get_right(), (node.first.second)/2), node.second));
            }
            else if (node.first.second > 1)
            {
                q.push_back(make_pair(make_pair(node.first.first, (node.first.second)/2), false));
                q.push_back(make_pair(make_pair(node.first.first, (node.first.second)/2), node.second));
            }
        }
    }
public:
    rbtree() : parent_class() {}
    virtual ~rbtree() {}
    Node* const insert(T const& val)
    {
        Node* node = parent_class::insert(val);
        Node* mum = node->get_parent();
        if (NULL != mum) // if not root
        {
            if (mum->is_red()) // implies not the root node
            {
                balance(node);
            }
        }
        else
        {
            node->set_red(false);
        }
    }
    virtual void erase(Node* const node)
    {
        parent_class::erase(node);
        // Todo ...
    }
};
#endif // _RBTREE_H_