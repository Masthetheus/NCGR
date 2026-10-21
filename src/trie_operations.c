#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

static const uint8_t corner_x[4] = {0, 0, 1, 1};
static const uint8_t corner_y[4] = {0, 1, 0, 1};
static const uint8_t encoding[256] = { 
        ['A'] = 0, ['C'] = 1, ['G'] = 3, ['T'] = 2
};

TrieNode *createNode() {
        TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));  // zera is_maw, base, x, y, filhos
        if (!node) { perror("calloc"); exit(1); }
        return node;
}

void insert(TrieNode *root, char *seq, int *k){
        TrieNode *current = root;
        size_t len = strlen(seq);
        while (len > 0 && (seq[len-1] == '\n' || seq[len-1] == '\r')) {
                seq[--len] = '\0';
        }
        if (len == 0) return;

        for (size_t i = 0; i < len; i++){
                uint8_t base = encoding[(unsigned char) seq[i]];
                if (current->child[base] == NULL) {
                        TrieNode *n = createNode();
                        n->depth = i + 1;
                        n->base  = base;
                        // base nova entra no bit MAIS ALTO (posicao i); primeira base fica no bit 0
                        n->x = current->x | ((uint32_t)corner_x[base] << i);
                        n->y = current->y | ((uint32_t)corner_y[base] << i);
                        current->child[base] = n;
                }
                current = current->child[base];
        }
        current->is_maw = 1;
        if (current->depth > *k) *k = current->depth;
}

uint32_t compute_subtree_count(TrieNode *node){
        if (node == NULL) return 0;

        uint32_t total = node->is_maw ? 1 : 0;   // o proprio no conta
        for (int i = 0; i < 4; i++){
                total += compute_subtree_count(node->child[i]);
        }
        node->subtree_count = total;
        return total;
}

TrieNode *free_helper(TrieNode *root){
        if (root == NULL) {
                return NULL;
        }

        for (uint8_t i = 0; i < 4; i++){
               if (root->child[i] != NULL){
                       free_helper(root->child[i]);
               }
        }
        free(root);
        return NULL;
}

