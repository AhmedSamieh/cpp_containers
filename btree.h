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
    void extract(Node* const node)
    {
        Node* newChild;
        if (NULL != node->get_left() || NULL != node->get_right())
        {
            if (NULL != node->get_left())
            {
                if (NULL != node->get_right())
                {
                    newChild = subtree_top(node->get_left());
                    if (newChild != node->get_left())
                    {
                        newChild->get_parent()->set_right(newChild->get_left());
                        if (NULL != newChild->get_left())
                        {
                            newChild->get_left()->set_parent(newChild->get_parent());
                        }
                        newChild->set_left(node->get_left());
                        node->get_left()->set_parent(newChild);
                    }
                    newChild->set_right(node->get_right());
                    node->get_right()->set_parent(newChild);
                }
                else
                {
                    newChild = node->get_left();
                }
            }
            else
            {
                newChild = node->get_right();
            }
            newChild->set_parent(node->get_parent());
        }
        else
        {
            newChild = NULL;
        }
        if (NULL == node->get_parent())
        {
            root = newChild;
        }
        else
        {
            if (node == node->get_parent()->get_right())
            {
                node->get_parent()->set_right(newChild);
            }
            else
            {
                node->get_parent()->set_left(newChild);
            }
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
        ++number_of_nodes;
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
            node = (val > node->get_val()) ? node->get_right() : node->get_left();
        }
        return node;
    }
    virtual void erase(Node* const node)
    {
        extract(node);
        delete node;
        --number_of_nodes;
    }
    size_t const erase(T const& val)
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
    size_t const size() const
    {
        return number_of_nodes;
    }
    void print(void)
    {
        subtree_print(root);
    }
};

#endif // _BTREE_H_