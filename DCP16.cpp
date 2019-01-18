/*
This problem was asked by Twitter.

You run an e-commerce website and want to record the last N order ids in a log.
Implement a data structure to accomplish this, with the following API:

record(order_id): adds the order_id to the log
get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal to N.
You should be as efficient with time and space as possible.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include<list>
using namespace std;

vector<string> ordinal_suffixes{"th", "st", "nd", "rd", "th"};

template <class T>
struct Last_N_Elements {
    size_t N;
    vector <T> arr;
    size_t insert_at;
    
    Last_N_Elements(size_t N): N{N}, arr(N, T{}), insert_at{0} {}
    
    void record(T x) {
        arr[insert_at++] = x;
        if(insert_at == N)
            insert_at = 0;
    }
    
    T retreive(size_t pos) {
        // 1 <= i <= N
        return arr[(insert_at - pos + N)%N];
    }
};

string get_suffix(size_t x) {
    return ordinal_suffixes[min(x%10,ordinal_suffixes.size()-1)];
}

int main()
{
    Last_N_Elements<int> last_4_elements{4};
    list<int> input{20, 34, -45, 107, 78, -200, 95, 179, 244};
    size_t num_inserted = 0;
    for(int element: input) {
        last_4_elements.record(element);
        ++num_inserted;
        cout<<"Inserting "<<num_inserted<<
        get_suffix(num_inserted)<<
        " element: "<<element<<endl;
        for(int i=1;i<=min(num_inserted, (size_t)4); i++)
            cout<<"retreive("<<i<<") = "<<last_4_elements.retreive(i)<<endl;
    }
    return 0;
}
