#ifndef __LEWZENSERVER_KV_HEAP__
#define __LEWZENSERVER_KV_HEAP__
#include <string>
#include <map>
#include <set>

namespace kv_heap {
    template<class T>
    class KVHeap{
    public:

        KVHeap(){

        }
        KVHeap(std::string Flag){
            cmpFlag = Flag;
        }

        void add(std::string key, T val)
        {            
            M[key] = val;
            mst.insert(val);
        }

        T top()
        {
            if(mst.empty())return 0;
            if(cmpFlag == "<")return *mst.begin();
            else if(cmpFlag == ">")return *mst.rbegin();
        }

        void remove(std::string key){
            if(!M.count(key))return;
            mst.erase(mst.lower_bound(M[key]));
            M.erase(key);
        }
    private:
        std::string cmpFlag;
        std::map<std::string,T>M;
        std::multiset<T>mst;

    };

}
#endif