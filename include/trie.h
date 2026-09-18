#ifndef TRIE_H
#define TRIE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct TrieNode {
        struct TrieNode *child[4];
        uint8_t base;
        uint32_t x, y;
        uint8_t depth;
        uint32_t subtree_count;
        bool is_maw;
} TrieNode;


#endif
