#include "include/tables/sorted_array.h"
#include "include/tables/unsorted_array.h"
#include "include/tables/unsorted_list.h"
#include "include/tables/hashmap_chains.h"
#include "include/tables/hashmap_openadressing.h"
//#include "include/tables/AVL_tree.h"
//#include "include/tables/RB_tree.h"

#ifndef CONNECTOR_H
#define CONNECTOR_H

#define ND [[nodiscard]]

enum TableType {
    UNSORTED_ARRAY = 0,
    UNSORTED_LIST,
    SORTED_ARRAY,
    RB_TREE,
    AVL_TREE,
    HASHMAP_CHAINS,
    HASHMAP_OPENADRESSING
};

template <typename kT, typename T>
class all_tables {
public:
    all_tables() = default;
    all_tables(const all_tables&) = delete;
    all_tables(const all_tables&&) = delete;
    void set_active_table(TableType active) noexcept { active_table = active; }

    void insert(const kT& key, const T& value);
    void remove(const kT& key);
    ND T& at(const kT& key);
    ND bool find(const kT& key);
    ND size_t size() const noexcept;
    ND bool empty() const noexcept { return size() == 0; }
private:
    _Table_unsorted_array<kT, T> a;
    _Table_unsorted_list<kT, T> b;
    _Table_sorted_array<kT, T> c;
    //_Map_RB_Tree<kT, T> d;
    //_Map_AVL_Tree<kT, T> e;
    _HashMap_Chains<kT, T> f;
    _HashMap_OpenAddressing<kT, T> g;
public:
    TableType active_table{};
};



template <typename kT, typename T>
void all_tables<kT,T>::insert(const kT& key, const T& value) {
    a.insert(key, value, true);
    b.insert(key, value, true);
    c.insert(key, value, true);
    //d.insert(key, value, true);
    //e.insert(key, value, true);
    f.insert(key, value, true);
    g.insert(key, value, true);
}

template <typename kT, typename T>
void all_tables<kT,T>::remove(const kT& key) {
    a.remove(key);
    b.remove(key);
    c.remove(key);
    //d.remove(key);
    //e.remove(key);
    f.remove(key);
    g.remove(key);
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
        return f.at(key);
    case HASHMAP_OPENADRESSING:
        return g.at(key);
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
        return f.find(key);
    case HASHMAP_OPENADRESSING:
        return g.find(key);
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
        return f.size();
    case HASHMAP_OPENADRESSING:
        return g.size();
    };
}

#endif // CONNECTOR_H
