#include <iostream>
#include <set>

using namespace std;

template <class Type>
class priority_queue
{
private:
    multiset<Type> ms;
public:
    priority_queue()
    {
    }
    ~priority_queue()
    {
        ms.clear();
    }
    bool empty()
    {
        return ms.empty();
    }
    size_t size()
    {
        return ms.size();
    }
    const Type& top()
    {
        auto criter = ms.crbegin();
        if (criter != ms.crend())
        {
            return *criter;
        }
    }
    void push(const Type &val)
    {
        ms.insert(val);
    }
    void pop()
    {
        if (ms.begin() != ms.end())
        {
            ms.erase(prev(ms.end()));
        }
    }
};

int main(int argc, char **argv)
{
    priority_queue<int> pq;

    int input[] = {3, 1, 2, 4, 5, 1, 3, 2, 3, 4, 1, 2, 5, 1, 3, 2, 1, 1};
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "push: " << input[i] << endl;
        pq.push(input[i]);
    }
    for (int i = 0; i < sizeof(input)/sizeof(int); i++)
    {
        cout << "top : " << pq.top() << endl;
        pq.pop();
    }
    return 0;
}

