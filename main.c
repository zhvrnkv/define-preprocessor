//
//  main.c
//  TableLookup
//
//  Created by Vlad Zhavoronkov on 7/15/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "zvf.h"
#include "getword.h"
#include "nlist.h"
#include <string.h>

#define define "#define"
#define defineLength 7

#define INTEGER int*

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        printf("Incorrect arguments");
        return argc;
    }

    char *sentence = zvread(argv[1]);
    int pointer = 0;
    char *word;
    while (sentence[pointer] && (word = getword(sentence, &pointer))) {
        int isDefine = (strcmp(word, define) == 0);
        if (isDefine) {
            char *name = getword(sentence, &pointer);
            char *value = getword(sentence, &pointer);
            install(name, value);
        }
    }

    int lineToDelete;
    while((lineToDelete = getFirstLineThatContain(sentence, define)) != -1) {
        sentence = removeLine(sentence, lineToDelete);
    }
    printf("%s\n", sentence);

    for (int i = 0; i < HASHTABSIZE; i++) {
        struct nlist *np = get(i);
        if (np) {
            sentence = replaceWord(sentence, np->name, np->defn);
        }
    }
    printf("%s\n", sentence);
    return 0;
}
