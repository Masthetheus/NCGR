#ifndef EXPORT_H
#define EXPORT_H

#include "trie.h"
#include <stdio.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
        uint32_t x, y;
        uint32_t subtree_count;
        uint8_t  depth;
        uint8_t  is_maw;
} ExportRecord;

_Static_assert(sizeof(ExportRecord) == 14, "ExportRecord deve ter 14 bytes");

void export_trie(TrieNode *root, int k, const char *out_path);

#endif