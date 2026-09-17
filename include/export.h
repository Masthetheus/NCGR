#ifndef EXPORT_H
#define EXPORT_H

#include "trie.h"
#include <stdio.h>

typedef struct {
        uint32_t x, y;
        uint8_t depth;
        uint32_t subtree_count;
} ExportRecord;

void export_trie(TrieNode *root, int k, const char *out_path);

#endif
