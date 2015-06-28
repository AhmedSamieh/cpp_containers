#include <iostream>
#include "BSTNode.h"
#include <list>

using namespace std;

template <class Type>

class BST
{
private:
    BSTNode<Type> *head;
    size_t number_of_nodes;
    
public:
    BST() : head(NULL), number_of_nodes(0)
    {
    }
    ~BST()
    {
    }
    void insert(Type val)
    {
        if (NULL == head)
        {
            head = new BSTNode<Type>(val);
        }
        else
        {
            BSTNode<Type> *i = head;
            do
            {
                if (val > i->get_val())
                {
                    if (NULL != i->get_right())
                    {
                        i = i->get_right();
                    }
                    else
                    {
                        i->set_right(new BSTNode<Type>(val, i));
                        break;
                    }
                }
                else
                {
                    if (NULL != i->get_left())
                    {
                        i = i->get_left();
                    }
                    else
                    {
                        i->set_left(new BSTNode<Type>(val, i));
                        break;
                    }
                }
            }
            while (true);
        }
        number_of_nodes++;
    }
    BSTNode<Type> *find(Type val)
    {
        BSTNode<Type> *i = head;
        while (NULL != i)
        {
            if (val == i->get_val())
            {
                break;
            }
            else if (val > i->get_val())
            {
                i = i->get_right();
            }
            else
            {
                i = i->get_left();
            }
        }
        return i;
    }
    void erase(Type val)
    {
        /*BSTNode<Type> *i = find(val);
        if (NULL != i)
        {
            if (NULL == i->get_left())
            {
                BSTNode<Type> *p = i->get_parent();
                if (NULL == p)
                {
                    head = i->get_right();
                }
                else
                {
                    
                }
            }
            else if (NULL == i->get_right())
            {
            }
            else
            {
            }
        }*/
    }
    void print()
    {
        list<pair< pair< BSTNode<Type> *, int>, bool> > q;
        q.push_back(make_pair(make_pair(head, 64), true));
        while (!q.empty())
        {
            pair< pair< BSTNode<Type> *, int>, bool> node = q.front();
            q.pop_front();
            for (int i = 0; i < node.first.second/2; i++)
            {
                cout << " ";
            }
            if (NULL != node.first.first)
            {
                if (NULL != node.first.first->get_left())
                {
                    for (int i = 0; i < node.first.second/2; i++)
                    {
                        cout << ".";
                    }
                }
                else
                {
                    for (int i = 0; i < node.first.second/2; i++)
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
};

int main(int argc, char **argv)
{
    BST<int> b;
    b.insert(4);
    b.insert(7);
    b.insert(2);
    b.insert(3);
    b.insert(6);
    b.insert(1);
    b.insert(9);
    b.insert(5);
    b.insert(6);
    b.insert(4);
    b.insert(2);
    b.insert(6);

    b.print();
}
