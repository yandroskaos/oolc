#ifndef __FUNCTIONAL_H__
#define __FUNCTIONAL_H__

#include <vector>
#include <string>
#include <functional>
using namespace std;

template<typename T>
vector<T> filterT(vector<T> _in, std::function<bool(T)> _predicate)
{
    vector<T> result;
    copy_if(_in.begin(), _in.end(), back_inserter(result), _predicate);
    return result;
}

template<typename T>
bool predicateT(vector<T> _in, std::function<bool(T)> _predicate)
{
    for(auto i : _in)
    {
        if(_predicate(i))
            return true;
    }
    return false;
}

template<typename T>
void forallT(vector<T> _in, std::function<void(T)> _function)
{
    for(auto i : _in)
    {
        _function(i);
    }
}

#endif
