#ifndef TRIE_OPERATIONS_H
#define TRIE_OPERATIONS_H

#include "trie.h"

TrieNode *createNode();
void insert(TrieNode *root, uint64_t idx, int k);
TrieNode *free_helper(TrieNode *root, int k);

#endif
