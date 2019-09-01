#ifndef _RBTREE_H_
#define _RBTREE_H_
#include "rbnode.h"
#include "btree.h"

#include <iostream>
#include <list>
#include <functional>

using namespace std;
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
template <class T, class Compare = std::greater<T>, class Node = rbnode<T> >
class rbtree : public btree<T, Compare, Node>
{
    using parent_class = btree<T, Compare, Node>;
protected:
    void rotate_right(Node *const head)
    {
        // In  : parent
        //       head
        //       x<-
        //       ->y
        // Out : parent
        //       x
        //       ->head
        //       y<-

        Node *const x = head->get_left();

        // y<-head
        head->set_left(x->get_right());
        if (NULL != x->get_right())
        {
            x->get_right()->set_parent(head);
        }

        // parent:x
        x->set_parent(head->get_parent());
        if (head == this->get_root())
        {
            this->set_root(x);
        }
        else if (head == head->get_parent()->get_right())
        {
            head->get_parent()->set_right(x);
        }
        else
        {
            head->get_parent()->set_left(x);
        }

        //x->head
        x->set_right(head);
        head->set_parent(x);
    }
    void rotate_left(Node *const head)
    {
        // In  : parent
        //       head
        //       ->x
        //       y<-
        // Out : parent
        //       x
        //       head<-
        //       ->y

        Node *const x = head->get_right();

        // head->y
        head->set_right(x->get_left());
        if (NULL != x->get_left())
        {
            x->get_left()->set_parent(head);
        }

        // parent:x
        x->set_parent(head->get_parent());
        if (head == this->get_root())
        {
            this->set_root(x);
        }
        else if (head == head->get_parent()->get_left())
        {
            head->get_parent()->set_left(x);
        }
        else
        {
            head->get_parent()->set_right(x);
        }

        // head<-x
        x->set_left(head);
        head->set_parent(x);
    }
    virtual void extract(Node *const node)
    {
        Node *to_be_deleted = node;
        Node *replacement = NULL;
        Node *replacement_parent = NULL;

        if (NULL == node->get_left())        // node has at most one non-null child.
        {
            replacement = node->get_right(); // replacement might be null.
        }
        else if (NULL == node->get_right())  // node has exactly one non-null child.
        {
            replacement = node->get_left();  // replacement is not null.
        }
        else
        {
            // node has two non-null children.  Set to_be_deleted to
            // node's successor.  replacement might be null.
            to_be_deleted = this->subtree_bottom(node->get_right());
            replacement = to_be_deleted->get_right();
        }
        if (to_be_deleted != node)
        {
            // relink to_be_deleted in place of node.  to_be_deleted is node's successor
            node->get_left()->set_parent(to_be_deleted);
            to_be_deleted->set_left(node->get_left());
            if (to_be_deleted != node->get_right())
            {
                replacement_parent = to_be_deleted->get_parent();
                if (NULL != replacement)
                {
                    replacement->set_parent(to_be_deleted->get_parent());
                }
                to_be_deleted->get_parent()->set_left(replacement);   // to_be_deleted must be a child of get_left()
                to_be_deleted->set_right(node->get_right());
                node->get_right()->set_parent(to_be_deleted);
            }
            else
            {
                replacement_parent = to_be_deleted;
            }
            if (this->get_root() == node)
            {
                this->set_root(to_be_deleted);
            }
            else if (node->get_parent()->get_left() == node)
            {
                node->get_parent()->set_left(to_be_deleted);
            }
            else
            {
                node->get_parent()->set_right(to_be_deleted);
            }
            to_be_deleted->set_parent(node->get_parent());
            bool to_be_deleted_is_red = to_be_deleted->is_red();
            to_be_deleted->set_red(node->is_red());
            node->set_red(to_be_deleted_is_red);
            to_be_deleted = node;
            // to_be_deleted now points to node to be actually deleted
        }
        else
        {
            // to_be_deleted == node
            replacement_parent = node->get_parent();
            if (NULL != replacement)
            {
                replacement->set_parent(node->get_parent());
            }
            if (this->get_root() == node)
            {
                this->set_root(replacement);
            }
            else if (node->get_parent()->get_left() == node)
            {
                node->get_parent()->set_left(replacement);
            }
            else
            {
                node->get_parent()->set_right(replacement);
            }
        }
        if (!to_be_deleted->is_red())
        {
            while (replacement != this->get_root() && (NULL == replacement || !replacement->is_red()))
            {
                if (replacement == replacement_parent->get_left())
                {
                    Node *replacement_sister = replacement_parent->get_right();
                    if (replacement_sister->is_red())
                    {
                        replacement_sister->set_red(false);
                        replacement_parent->set_red(true);
                        rotate_left(replacement_parent);
                        replacement_sister = replacement_parent->get_right();
                    }
                    if ((NULL == replacement_sister->get_left() || !replacement_sister->get_left()->is_red()) &&
                            (NULL == replacement_sister->get_right() || !replacement_sister->get_right()->is_red()))
                    {
                        replacement_sister->set_red(true);
                        replacement = replacement_parent;
                        replacement_parent = replacement_parent->get_parent();
                    }
                    else
                    {
                        if (NULL == replacement_sister->get_right() || !replacement_sister->get_right()->is_red())
                        {
                            replacement_sister->get_left()->set_red(false);
                            replacement_sister->set_red(true);
                            rotate_right(replacement_sister);
                            replacement_sister = replacement_parent->get_right();
                        }
                        replacement_sister->set_red(replacement_parent->is_red());
                        replacement_parent->set_red(false);
                        if (NULL != replacement_sister->get_right())
                        {
                            replacement_sister->get_right()->set_red(false);
                        }
                        rotate_left(replacement_parent);
                        break;
                    }
                }
                else
                {
                    // same as above, with get_right() <-> get_left().
                    Node *replacement_sister = replacement_parent->get_left();
                    if (replacement_sister->is_red())
                    {
                        replacement_sister->set_red(false);
                        replacement_parent->set_red(true);
                        rotate_right(replacement_parent);
                        replacement_sister = replacement_parent->get_left();
                    }
                    if ((NULL == replacement_sister->get_right() || !replacement_sister->get_right()->is_red()) &&
                            (NULL == replacement_sister->get_left() || !replacement_sister->get_left()->is_red()))
                    {
                        replacement_sister->set_red(true);
                        replacement = replacement_parent;
                        replacement_parent = replacement_parent->get_parent();
                    }
                    else
                    {
                        if (NULL == replacement_sister->get_left() || !replacement_sister->get_left()->is_red())
                        {
                            replacement_sister->get_right()->set_red(false);
                            replacement_sister->set_red(true);
                            rotate_left(replacement_sister);
                            replacement_sister = replacement_parent->get_left();
                        }
                        replacement_sister->set_red(replacement_parent->is_red());
                        replacement_parent->set_red(false);
                        if (NULL != replacement_sister->get_left())
                        {
                            replacement_sister->get_left()->set_red(false);
                        }
                        rotate_right(replacement_parent);
                        break;
                    }
                }
            }
            if (NULL != replacement)
            {
                replacement->set_red(false);
            }
        }
    }
    void balance(Node *node)
    {
        while (true)
        {
            // facts:
            // - node is red
            // - mum is red, not the root, we have a grandma
            // - sister is black
            // - grandma is black, it may be the root
            Node *mum = node->get_parent();
            Node *grandma = mum->get_parent();
            Node *grand_grandma = grandma->get_parent();
            bool  mum_direction = (grandma->get_right() == mum);
            bool  node_direction = (mum->get_right() == node);
            Node *aunt = mum_direction ? grandma->get_left() : grandma->get_right();

            if (NULL == aunt || !aunt->is_red()) // aunt is black : rotate mum:x(node):y
            {
                Node *new_parent;
                if (mum_direction != node_direction)
                {
                    new_parent = node;
                    mum->set_parent(node);
                    if (mum_direction) // && !node_direction
                    {
                        // In  : grandma
                        //       mum
                        //       ->x(node)
                        //       y<-
                        // Out : grandma
                        //       y
                        //       mum<-y->x

                        // mum<-y->x
                        grandma->set_right(node->get_left());
                        if (NULL != node->get_left())
                        {
                            node->get_left()->set_parent(grandma);
                        }
                        node->set_left(grandma);
                        mum->set_left(node->get_right());
                        if (NULL != node->get_right())
                        {
                            node->get_right()->set_parent(mum);
                        }
                        node->set_right(mum);
                    }
                    else //if (!mum_direction && node_direction)
                    {
                        // In  : grandma
                        //       mum
                        //       x<-
                        //       ->y
                        // Out : grandma
                        //       x
                        //       y<-x->mum

                        // y<-x->mum
                        mum->set_right(node->get_left());
                        if (NULL != node->get_left())
                        {
                            node->get_left()->set_parent(mum);
                        }
                        node->set_left(mum);
                        grandma->set_left(node->get_right());
                        if (NULL != node->get_right())
                        {
                            node->get_right()->set_parent(grandma);
                        }
                        node->set_right(grandma);
                    }
                }
                else // if (mum_direction == node_direction)
                {
                    new_parent = mum;
                    if (mum_direction)
                    {
                        // In  : grandma
                        //       mum
                        //       ->x
                        //       ->y
                        // Out : grandma
                        //       x
                        //       mum<-x->y

                        // mum<-x->y
                        grandma->set_right(mum->get_left()); // sister is black
                        if (NULL != mum->get_left())
                        {
                            mum->get_left()->set_parent(grandma);
                        }
                        mum->set_left(grandma); // same
                    }
                    else
                    {
                        // In  : grandma
                        //       mum
                        //       x<-
                        //       y<-
                        // Out : grandma
                        //       x
                        //       y<-x->mum

                        // y<-x->mum
                        grandma->set_left(mum->get_right()); // sister is black
                        if (NULL != mum->get_right())
                        {
                            mum->get_right()->set_parent(grandma);
                        }
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
    /*virtual void subtree_print(Node *const subtree_root)
    {
        list<pair< pair<Node *const, int>, bool> > q;
        q.push_back(make_pair(make_pair(subtree_root, 64), true));
        while (!q.empty())
        {
            auto node = q.front();
            q.pop_front();
            for (int i = 0; i < node.first.second / 2; i++)
            {
                cout << " ";
            }
            if (NULL != node.first.first)
            {
                int shift = (node.first.first->get_val() / 10) ? ((node.first.first->get_val() / 100) ? 3 : 2) : 1;
                if (NULL != node.first.first->get_left())
                {
                    for (int i = shift; i < node.first.second / 2; i++)
                    {
                        cout << ".";
                    }
                }
                else
                {
                    for (int i = shift; i < node.first.second / 2; i++)
                    {
                        cout << " ";
                    }
                }
                cout << node.first.first->get_val() << (node.first.first->is_red() ? 'R' : 'B');
                if (NULL != node.first.first->get_right())
                {
                    for (int i = 1; i < node.first.second / 2; i++)
                    {
                        cout << ".";
                    }
                }
                else
                {
                    for (int i = 1; i < node.first.second / 2; i++)
                    {
                        cout << " ";
                    }
                }
                for (int i = 0; i < node.first.second / 2; i++)
                {
                    cout << " ";
                }
            }
            else
            {
                for (int i = 0; i < node.first.second / 2; i++)
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
                q.push_back(make_pair(make_pair(node.first.first->get_left(), (node.first.second) / 2), false));
                q.push_back(make_pair(make_pair(node.first.first->get_right(), (node.first.second) / 2), node.second));
            }
            else if (node.first.second > 1)
            {
                q.push_back(make_pair(make_pair(node.first.first, (node.first.second) / 2), false));
                q.push_back(make_pair(make_pair(node.first.first, (node.first.second) / 2), node.second));
            }
        }
    }*/
public:
    rbtree() : parent_class() {}
    virtual ~rbtree() {}
    Node *const insert(T const &val)
    {
        Node *node = parent_class::insert(val);
        Node *mum = node->get_parent();
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
};
#endif // _RBTREE_H_