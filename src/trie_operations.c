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
        TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
        node->depth = 0;
        node->x = 0;
        node->y = 0;
        node->subtree_count = 0;
        for (int i = 0; i < 4; i++) {
                node->child[i] = NULL;
        }
        return node;
}

void insert(TrieNode *root, char *seq, int *k){
        TrieNode *current = root;
        size_t len = strlen(seq);
        if (len > 0 && seq[len-1] == '\n') {
                        seq[--len] = '\0';
                }
        for (size_t i = 0; i < len; i++){
                uint8_t base = encoding[(unsigned char) seq[i]];
                if (current->child[base] == NULL) {
                        current->child[base] = createNode();
                        current->child[base]->depth = i + 1;
                        current->child[base]->base = base;
                        current->child[base]->x = (current->x << 1) | corner_x[base];
                        current->child[base]->y = (current->y << 1) | corner_y[base];
                }
                current = current->child[base];
        }
        current->is_maw = 1;
        if ((current->is_maw) = 1 && (current->depth) > *k){
                *k = (current->depth);
        }
}

uint32_t compute_subtree_count(TrieNode *node){
        if (node == NULL) return 0;

        uint32_t total = 0;
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

