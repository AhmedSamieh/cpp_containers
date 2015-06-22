#include <iostream>
#include "BSTNode.h"

using namespace std;

template <class _KT_, class _VT_>
class priority_queue
{
private:
    BSTNode<_KT_, _VT_> *head;
    BSTNode<_KT_, _VT_> *maximum;
    size_t               number_of_nodes;
    BSTNode<_KT_, _VT_> *find_maximum_node(BSTNode<_KT_, _VT_> *root)
    {
        BSTNode<_KT_, _VT_> *node = root;
        if (NULL != node)
        {
            while (NULL != node->get_right())
            {
                node = node->get_right();
            }
        }
        return node;
    }
public:
    priority_queue() : head(NULL), maximum(NULL), number_of_nodes(0)
    {
    }
    ~priority_queue()
    {
        // delete all nodes
        // temp solution
        while (!empty())
        {
            pop();
        }
    }
    bool empty()
    {
        return (0 == number_of_nodes);
    }
    size_t size()
    {
        return number_of_nodes;
    }
    _VT_ top()
    {
        if (NULL != maximum)
        {
            return maximum->get_val();
        }
    }
    void push(_KT_ key, _VT_ val)
    {
        BSTNode<_KT_, _VT_> *new_node = new BSTNode<_KT_, _VT_>(key, val);
        if (NULL == head)
        {
            head = maximum = new_node;
        }
        else if (key > maximum->get_key())
        {
            // insert in the right of the maximum node and make the new node as maximum
            maximum->set_right(new_node);
            new_node->set_parent(maximum);
            maximum = new_node;
        }
        else
        {
            // start from head, insert the new element
            BSTNode<_KT_, _VT_> *parent = head;
            while (true)
            {
                if (key > parent->get_key())
                {
                    if (NULL != parent->get_right())
                    {
                        parent = parent->get_right();
                    }
                    else
                    {
                        parent->set_right(new_node);
                        new_node->set_parent(parent);
                        //cout << "Parent(" << parent->get_key() << ", " << parent->get_val() << ")" << endl;
                        break;
                    }
                }
                else
                {
                    if (NULL != parent->get_left())
                    {
                        parent = parent->get_left();
                    }
                    else
                    {
                        BSTNode<_KT_, _VT_> *grand_parent;
                        parent->set_left(new_node);
                        new_node->set_parent(parent);
                        //cout << "Parent(" << parent->get_key() << ", " << parent->get_val() << ")" << endl;
                        if (NULL == parent->get_right() &&
                            NULL != (grand_parent = parent->get_parent()) &&
                            NULL == grand_parent->get_right())
                        {
                            //cout << "fix (" << new_node->get_val() << ", " << parent->get_val() << ", " << grand_parent->get_val() << ")" << endl;
                            parent->set_right(grand_parent);
                            parent->set_parent(grand_parent->get_parent());
                            grand_parent->set_parent(parent);
                            grand_parent->set_left(NULL);
                            if (NULL == parent->get_parent())
                            {
                                head = parent;
                            }
                            else
                            {
                                if (parent->get_parent()->get_left() == parent->get_right())
                                {
                                    parent->get_parent()->set_left(parent);
                                }
                                else
                                {
                                    parent->get_parent()->set_right(parent);
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        number_of_nodes++;
    }
    void pop()
    {
        // make sure we have nodes to pop
        if (number_of_nodes > 0)
        {
            BSTNode<_KT_, _VT_> *temp_maximum = maximum;
            // check if we will pop from the head
            if (maximum == head)
            {
                head = head->get_left();
                // it was the last node
                if (NULL == head)
                {
                    maximum = NULL;
                }
                else
                {
                    head->set_parent(NULL);
                    maximum = find_maximum_node(head);
                }
            }
            else
            {
                // maximum node should be in the right terminal of it's parent,
                // and it's right terminal = NULL
                //cout << "Parent(" << maximum->get_parent()->get_key() << ", " << maximum->get_parent()->get_val() << ")" << endl;
                maximum->get_parent()->set_right(maximum->get_left());
                if (NULL != maximum->get_left())
                {
                    maximum->get_left()->set_parent(maximum->get_parent());
                }
                maximum = find_maximum_node(maximum->get_parent());
                //cout << "Maximum(" << maximum->get_key() << ", " << maximum->get_val() << ")" << endl;
            }
            delete temp_maximum;
            number_of_nodes--;
        }
    }
    void print()
    {
        priority_queue< int, pair< pair< BSTNode<_KT_, _VT_> *, int>, bool> > q;
        q.push(1, make_pair(make_pair(head, 64), true));
        while (!q.empty())
        {
            pair< pair< BSTNode<_KT_, _VT_> *, int>, bool> node = q.top();
            q.pop();
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
                q.push(1, make_pair(make_pair(node.first.first->get_left(), (node.first.second)/2), false));
                q.push(1, make_pair(make_pair(node.first.first->get_right(), (node.first.second)/2), node.second));
            }
            else if (node.first.second > 1)
            {
                q.push(1, make_pair(make_pair(node.first.first, (node.first.second)/2), false));
                q.push(1, make_pair(make_pair(node.first.first, (node.first.second)/2), node.second));
            }
        }
    }
};

int main(int argc, char **argv)
{
    priority_queue<int, int> pq;

    int input[] = {3, 1, 2, 4, 5, 1, 3, 2, 3, 4, 1, 2, 5, 1, 3, 2, 1, 1};
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "push: " << input[i] << ", " << i + 1 << endl;
        pq.push(input[i], i + 1);
    }
    pq.print();
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "top : " << pq.top() << endl;
        pq.pop();
    }
}
