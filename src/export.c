#include "export.h"
#include <stdlib.h>

static void export_traverse(TrieNode *node, FILE *f, uint32_t *node_count){
        if (node == NULL) return;

        ExportRecord rec = { node->x, node->y, node->depth, node->subtree_count };
        fwrite(&rec, sizeof(ExportRecord), 1, f);
        (*node_count)++;

        for (int i = 0; i < 4; i++){
                export_traverse(node->child[i], f, node_count);
        }
}

void export_trie(TrieNode *root, int k, const char *out_path){
        FILE *f = fopen(out_path, "wb");
        if (!f) { perror("fopen"); exit(1); }

        uint32_t header[2] = { (uint32_t)k, 0 };
        fwrite(header, sizeof(uint32_t), 2, f);

        uint32_t node_count = 0;
        export_traverse(root, f, &node_count);

        fseek(f, sizeof(uint32_t), SEEK_SET);
        fwrite(&node_count, sizeof(uint32_t), 1, f);

        fclose(f);
}
