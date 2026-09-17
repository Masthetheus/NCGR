#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "trie.h"

TrieNode *createNode() {
        TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
        node->depth = 0;
        for (int i = 0; i < 4; i++) {
                node->child[i] = NULL;
        }
        return node;
}

void insert(TrieNode *root, uint64_t idx, int k){
        TrieNode *current = root;
        for (int i = 0; i < k; i++){
                uint8_t base = (idx >> ((k-i-1)*2)) & 3;
                if (current->child[base] == NULL) {
                        current->child[base] = createNode();
                        current->child[base]->depth = i + 1;
                }
                current = current->child[base];
        }
}

TrieNode *free_helper(TrieNode *root, int k){
        if (root == NULL) {
                return NULL;
        }

        for (uint8_t i = 0; i < 4; i++){
               if (root->child[i] != NULL){
                       free_helper(root->child[i], k);
               }
        }
        free(root);
        return NULL;
}
