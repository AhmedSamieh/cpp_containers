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
            cout << "TOP(" << maximum->get_key() << ", " << maximum->get_val() << ")" << endl;
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
            BSTNode<_KT_, _VT_> *i = head;
            while (true)
            {
                if (new_node->get_key() > i->get_key())
                {
                    if (NULL != i->get_right())
                    {
                        i = i->get_right();
                    }
                    else
                    {
                        i->set_right(new_node);
                        new_node->set_parent(i);
                        //cout << "Parent(" << i->get_key() << ", " << i->get_val() << ")" << endl;
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
                        i->set_left(new_node);
                        new_node->set_parent(i);
                        //cout << "Parent(" << i->get_key() << ", " << i->get_val() << ")" << endl;
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
};

int main(int argc, char **argv)
{
    priority_queue<int, int> pq;

    int input[] = {1, 1, 2, 4, 5, 1, 3, 2, 3, 4};
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        pq.push(input[i], i + 1);
    }
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        //cout << "top : " << pq.top() << endl;
        pq.top();
        pq.pop();
    }
}
