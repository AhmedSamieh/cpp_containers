#ifndef _BTREE_H_
#define _BTREE_H_
#include "bnode.h"

#include <iostream>
#include <list>
using namespace std;

template <class T, class Node = bnode<T> >

class btree
{
protected:
    Node*  root;
    size_t number_of_nodes;

    Node* const subtree_top(Node* const subtree_root)
    {
        Node* node = subtree_root;
        if (NULL != node)
        {
            for (; NULL != node->get_right(); node = node->get_right());
        }
        return node;
    }
    Node* const subtree_bottom(Node* const subtree_root)
    {
        Node* node = subtree_root;
        if (NULL != node)
        {
            for (; NULL != node->get_left(); node = node->get_left());
        }
        return node;
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
                int shift = (node.first.first->get_val() / 10) ? ((node.first.first->get_val() / 100) ? 2:1):0;
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
                cout << node.first.first->get_val();
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
    btree() : root(NULL), number_of_nodes(0) {}
    virtual ~btree() {}
    virtual Node* const insert(T const& val)
    {
        Node* node = new Node(val);
        if (NULL == root)
        {
            root = node;
        }
        else
        {
            Node* p = root;
            while (true)
            {
                if (val > p->get_val())
                {
                    if (NULL == p->get_right())
                    {
                        node->set_parent(p);
                        p->set_right(node);
                        break;
                    }
                    p = p->get_right();
                }
                else
                {
                    if (NULL == p->get_left())
                    {
                        node->set_parent(p);
                        p->set_left(node);
                        break;
                    }
                    p = p->get_left();
                }
            }
        }
        number_of_nodes++;
        return node;
    }
    Node* const top(void)
    {
        return subtree_top(root);
    }
    Node* const bottom(void)
    {
        return subtree_bottom(root);
    }
    Node* const find(T const& val)
    {
        Node* node = root;
        while (NULL != node)
        {
            if (val == node->get_val())
            {
                break;
            }
            node = val > node->get_val() ? node->get_right() : node->get_left();
        }
        return node;
    }
    virtual void erase(Node* const node)
    {
        Node* parent = node->get_parent();
        Node* right = node->get_right();
        Node* left = node->get_left();
        if (NULL == parent)
        {
            root = (NULL == left) ? right : left;
        }
        else
        {
            if (NULL == left)
            {
                if (node == parent->get_right())
                {
                    parent->set_right(right);
                }
                else
                {
                    parent->set_left(right);
                }
            }
            else
            {
                if (node == parent->get_right())
                {
                    parent->set_right(left);
                }
                else
                {
                    parent->set_left(left);
                }
            }
        }
        if (NULL == left)
        {
            if (NULL != right)
            {
                right->set_parent(parent);
            }
        }
        else
        {
            Node* left_top = subtree_top(left);
            left->set_parent(parent);
            left_top->set_right(right);
            if (NULL != right)
            {
                right->set_parent(left_top);
            }
        }
        delete node;
    }
    size_t erase(T const& val)
    {
        Node* node;
        size_t number_of_erased_nodes = 0;
        while (NULL != (node = find(val)))
        {
            erase(node);
            ++number_of_erased_nodes;
        }
        return number_of_erased_nodes;
    }
    void print(void)
    {
        subtree_print(root);
    }
};

#endif // _BTREE_H_