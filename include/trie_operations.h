#ifndef TRIE_OPERATIONS_H
#define TRIE_OPERATIONS_H

#include "trie.h"

TrieNode *createNode();
void insert(TrieNode *root, char *seq, int *k);
TrieNode *free_helper(TrieNode *root);
uint32_t compute_subtree_count(TrieNode *node);

#endif
