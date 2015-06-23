#include <iostream>
#include <map>
#include <list>

using namespace std;

template <class _KT_, class _VT_>
class priority_queue2
{
private:
    map< _KT_, list<_VT_> > q;
    typedef typename map< _KT_, list<_VT_> >::iterator         map_iterator;
    typedef typename map< _KT_, list<_VT_> >::reverse_iterator map_reverse_iterator;
    size_t number_of_nodes;
public:
    priority_queue2() : number_of_nodes(0)
    {
    }
    ~priority_queue2()
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
        if (0 != number_of_nodes)
        {
            for (map_reverse_iterator riter = q.rbegin();
                 riter != q.rend();
                 riter++)
            {
                if (!riter->second.empty())
                {
                    return riter->second.front();
                }
            }
        }
    }
    void push(_KT_ key, _VT_ val)
    {
        map_iterator iter = q.find(key);
        if (iter == q.end())
        {
            iter = q.insert(q.begin(), make_pair(key, list<_VT_>()));
        }
        iter->second.push_back(val);
        number_of_nodes++;
    }
    void pop()
    {
        if (0 != number_of_nodes)
        {
            for (map_reverse_iterator riter = q.rbegin();
                 riter != q.rend();
                 riter++)
            {
                if (!riter->second.empty())
                {
                    riter->second.pop_front();
                    break;
                }
            }
            number_of_nodes--;
        }
    }
};

int main(int argc, char **argv)
{
    priority_queue2<int, int> pq;

    int input[] = {3, 1, 2, 4, 5, 1, 3, 2, 3, 4, 1, 2, 5, 1, 3, 2, 1, 1};
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "push: " << input[i] << ", " << i + 1 << endl;
        pq.push(input[i], i + 1);
    }
    //pq.print();
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "top : " << pq.top() << endl;
        pq.pop();
    }
    return 0;
}
