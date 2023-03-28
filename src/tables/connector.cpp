#include "include/tables/connector.h"

template <typename kT, typename T>
void all_tables<kT,T>::insert(const kT& key, const T& value) {
    a.insert(key, value, true);
    b.insert(key, value, true);
    c.insert(key, value, true);
    //d.insert(key, value, true);
    //e.insert(key, value, true);
    //f.insert(key, value, true);
    //g.insert(key, value, true);
}

template <typename kT, typename T>
void all_tables<kT,T>::remove(const kT& key) {
    a.remove(key);
    b.remove(key);
    c.remove(key);
    //d.remove(key);
    //e.remove(key);
    //f.remove(key);
    //g.remove(key);
}

template <typename kT, typename T>
ND T& all_tables<kT,T>::at(const kT& key) {
    switch (active_table)
    {
    case UNSORTED_ARRAY:
        return a.at(key);
    case UNSORTED_LIST:
        return b.at(key);
    case SORTED_ARRAY:
        return c.at(key);
    case RB_TREE:
        break;
        //return d.at(key);
    case AVL_TREE:
        break;
        //return e.at(key);
    case HASHMAP_CHAINS:
        break;
        //return f.at(key);
    case HASHMAP_OPENADRESSING:
        break;
        //return g.at(key);
    };
}

template <typename kT, typename T>
ND bool all_tables<kT,T>::find(const kT& key) {
    switch (active_table)
    {
    case UNSORTED_ARRAY:
        return a.find(key);
    case UNSORTED_LIST:
        return b.find(key);
    case SORTED_ARRAY:
        return c.find(key);
    case RB_TREE:
        break;
        //return d.find(key);
    case AVL_TREE:
        break;
        //return e.find(key);
    case HASHMAP_CHAINS:
        break;
        //return f.find(key);
    case HASHMAP_OPENADRESSING:
        break;
        //return g.find(key);
    };
}

template <typename kT, typename T>
ND size_t all_tables<kT,T>::size() const noexcept {
    switch (active_table)
    {
    case UNSORTED_ARRAY:
        return a.size();
    case UNSORTED_LIST:
        return b.size();
    case SORTED_ARRAY:
        return c.size();
    case RB_TREE:
        break;
        //return d.size();
    case AVL_TREE:
        break;
        //return e.size();
    case HASHMAP_CHAINS:
        break;
        //return f.size();
    case HASHMAP_OPENADRESSING:
        break;
        //return g.size();
    };
}
