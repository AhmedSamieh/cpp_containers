#include <iostream>
#include <map>
#include <list>

using namespace std;

template <class KeyType, class ValType>
class priority_queue2
{
private:
    map< KeyType, list<ValType> > q;
    typedef typename map< KeyType, list<ValType> >::iterator         map_iterator;
    typedef typename map< KeyType, list<ValType> >::reverse_iterator map_reverse_iterator;
    size_t number_of_nodes;
public:
    priority_queue2() : number_of_nodes(0)
    {
    }
    ~priority_queue2()
    {
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
    ValType top()
    {
        map_reverse_iterator riter = q.rbegin();
        if (riter != q.rend())
        {
            return riter->second.front();
        }
    }
    void push(KeyType key, ValType val)
    {
        map_iterator iter = q.find(key);
        if (iter == q.end())
        {
            iter = q.insert(q.begin(), make_pair(key, list<ValType>()));
        }
        iter->second.push_back(val);
        number_of_nodes++;
    }
    void pop()
    {
        map_reverse_iterator riter = q.rbegin();
        if (riter != q.rend())
        {
            riter->second.pop_front();
            if (riter->second.empty())
            {
                q.erase((++riter).base());
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
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "top : " << pq.top() << endl;
        pq.pop();
    }
    return 0;
}
