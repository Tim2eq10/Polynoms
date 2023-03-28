#include "include/tables/hashmap_chains.h"

template <typename kT, typename T, typename hasher>
void _HashMap_Chains<kT, T, hasher>::rehash(
    size_type _new_capacity,
    Node* new_mem,
    size_t& max_list_len
) {
    for (size_t hs = 0; hs < cap; hs++)
        for (ListNode& el : mem[hs]) {
            auto& new_lst = new_mem[hasher::hash(el.key) % _new_capacity];
            new_lst.insert(new_lst.begin(), el);

            if (new_lst.size() > max_list_len) {
                max_list_len = new_lst.size();
            }

        }
}

template <typename kT, typename T, typename hasher>
void _HashMap_Chains<kT, T, hasher>::reserve(size_type _new_capacity)
{
   if (_new_capacity <= cap) return;

   Node* new_mem = new Node[_new_capacity];

   size_t len = 0;

   try {
       rehash(_new_capacity, new_mem, len);
   }
   catch (std::exception _ex) {
       delete[] new_mem;
       throw _ex;
   }

   delete[] mem;
   max_list_len = len;
   mem = new_mem;
   cap = _new_capacity;
}

template <typename kT, typename T, typename hasher>
ND auto _HashMap_Chains<kT, T, hasher>::__Find(key_type key) {
    auto it = mem[hash(key)].begin();
    auto end = mem[hash(key)].end();
    for (; it != end; it++)
        if (it->key == key)
            return it;
    return it;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_Chains<kT, T, hasher>::insert(
    key_cref key,
    cref value,
    bool replacement
) {
    if (max_list_len > MAX_LIST_LEN_THRESHOLD) {
        if (2 * cap > MAX_ARRAY_SIZE_THRESHOLD) {
            reserve(MAX_ARRAY_SIZE_THRESHOLD);
        }
        else {
            reserve(2 * cap);
        }
    }
    auto place = __Find(key);
    size_t hs = hash(key);
    if (place == mem[hs].end()) {
        mem[hs].insert(place, ListNode(key, value));
        sz++;
        max_list_len = (mem[hs].size() > max_list_len ? mem[hs].size() : max_list_len);
        return 1;
    }
    if (replacement) {
        place->value = value;
    }
    return 0;
}

template <typename kT, typename T, typename hasher>
bool _HashMap_Chains<kT, T, hasher>::remove(key_cref key) {
    auto place = __Find(key);
    if (place == mem[hash(key)].end())
        return 0;

    mem[hash(key)].erase(place);
    sz--;
    return 1;
}

template <typename kT, typename T, typename hasher>
ND bool _HashMap_Chains<kT, T, hasher>::find(key_cref key) {
    return __Find(key) != mem[hash(key)].end();
}

template <typename kT, typename T, typename hasher>
ND typename _HashMap_Chains<kT, T, hasher>::ref
    _HashMap_Chains<kT, T, hasher>::at(key_cref key)
{
    auto place = __Find(key);
    if (place == mem[hash(key)].end())
        throw std::invalid_argument("No key in table");
    return place->value;
}
