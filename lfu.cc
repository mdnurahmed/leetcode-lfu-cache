#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
class LFUCache
{
public:
    int cap, nowtime = INT_MIN + 1;
    unordered_map<int, piii> cache; // key - value,freq,time
    map<pii, int> track;            //freq,time - key
    LFUCache(int capacity)
    {
        cap = capacity;
    }
    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;
        update(key);
        return cache[key].ff;
    }
    void put(int key, int value)
    {
        if (cap == 0)
            return;
        if (cache.find(key) == cache.end())
        { //new element
            if (cache.size() == cap)
                evict(); //if overflow then evicting first
            cache[key] = piii(value, pii(0, INT_MIN));
        }
        else
        { //old element
            cache[key].ff = value;
        }
        update(key);
    }
    void update(int key)
    {
        track.erase(cache[key].ss); //error dibe na na thakleo
        cache[key].ss.ff++;
        cache[key].ss.ss = nowtime;
        track[cache[key].ss] = key;
        nowtime++;
    }
    void evict()
    {
        auto it = track.begin();
        cache.erase(it->second);
        track.erase(it);
    }
};