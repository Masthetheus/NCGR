#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_parser.h"
#include "trie.h"
#include "trie_operations.h"
#include "export.h"

int main(int argc, char *argv[]){
        if (argc != 3){
                fprintf(stderr, "Usage: %s <nullomer_file> <out_file>\n", argv[0]);
                return 1;
        }

        FILE *f = fopen(argv[1], "rb");
        if (!f){
                perror("Error opening file!");
                return 1;
        }

        char *out = argv[2];

        // gather null set from file
        int k = 0;
        size_t count = 0;
        uint64_t *nullomers = parse_nullomer_file(f, &k, &count);
        
        // load nullomers into trie object
        TrieNode *root = createNode();

        for (int i = 0; i < count; i++){
                insert(root, nullomers[i], k);
        }
        free(nullomers);

        compute_subtree_count(root);
        export_trie(root, k, out);
        root = free_helper(root, k);
        return 0;
}
