#include "include/tables/sorted_array.h"
#include "include/tables/unsorted_array.h"
#include "include/tables/unsorted_list.h"
#include "include/tables/hashmap_chains.h"
//#include "include/tables/hashmap_open_adressing.h"
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
    //_HashMap_OpenAddressing<kT, T> g;
public:
    TableType active_table{};
};

#endif // CONNECTOR_H
