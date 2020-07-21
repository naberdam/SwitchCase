#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **linesInCase;
    int iHaveBreak;
    int lineInCase;
    long numberCase;
} detailsCase;

void arrayOfLinesFree(char **arrayOfLines, int sizeOfArray) {
    int i;
    for (i = 0; i < sizeOfArray; ++i) {
        free(arrayOfLines[i]);
    }
    free(arrayOfLines);
}

void freeArrayStructDetailsCase(detailsCase **details, int howMuchCase) {
    int i;
    for (i = 0; i < howMuchCase; ++i) {
        int j = 0;
        for (; j < details[i]->lineInCase; ++j) {
            /*if (details[i]->linesInCase[j] == NULL) {
                continue;
            }*/
            free(details[i]->linesInCase[j]);
        }
        free(details[i]);
    }
    free(details);
}


void initializeDetailsCases(detailsCase ***details, long numCases) {
    if ((*details) == NULL) {
        (*details) = (detailsCase **) malloc(sizeof(detailsCase *) * numCases);
        if ((*details) == NULL) {
            printf("error in malloc details\n");
            exit(1);
        }
    }
}

void reallocLinesInCase(detailsCase ***details, long whichCase, long howMuchLinesToAdd) {
    char** tempLinesInCase = NULL;
    tempLinesInCase = (char**)realloc((*details)[whichCase]->linesInCase, sizeof(char*) * (howMuchLinesToAdd));
    if (tempLinesInCase == NULL) {
        printf("error in linesInCase details\n");
        exit(1);
    }
    (*details)[whichCase]->linesInCase = tempLinesInCase;
}


void equalWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc((strlen(tempLine) + 1) * sizeof(char));
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void plusEqualWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    //="*p1"
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(tempLine, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "addq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void minusEqualWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    //="*p1"
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "subq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void multEqualWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    //="*p1"
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "imulq %rax,%rbx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "movq %rbx,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void shiftLeftWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    //="*p1"
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "shlq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void shiftRightWrite(char *leftSideEquation, char *rightSideEquation, char ***line, int *lineInCase) {
    char tempLine[50];
    //="*p1"
    if (strstr(leftSideEquation, "*p1")) {
        if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p1")) {
            //maybe we need just to ignore it
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rdi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else if (strstr(leftSideEquation, "*p2")) {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,(%rsi)\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    } else {
        if (strstr(rightSideEquation, "*p1")) {
            strcpy(tempLine, "movq (%rdi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "*p2")) {
            strcpy(tempLine, "movq (%rsi),%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else if (strstr(rightSideEquation, "result")) {
            strcpy(tempLine, "movq %rax,%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        } else {
            strcpy(tempLine, "movq $");
            strcat(tempLine, rightSideEquation);
            strcat(tempLine, ",%rcx\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
            strcpy(tempLine, "sarq %cl,%rax\n");
            (*line)[(*lineInCase)] = (char *) malloc(strlen(tempLine) + 1);
            strcpy((*line)[(*lineInCase)], tempLine);
            ++(*lineInCase);
        }
    }
}

void assemblyCodeForCase(detailsCase ***details, int *indexOfCase, char **arrayOfLines,
                         int *howMuchCase, long biggestNumCase, long numCases) {
    (*details)[(*howMuchCase) - 1]->linesInCase = (char **) malloc(sizeof(char *));
    int lineInEachCase = 0;
    char *numberOfCase = (char *) malloc(strlen(arrayOfLines[(*indexOfCase)]) + 1);
    strcpy(numberOfCase, arrayOfLines[(*indexOfCase)]);
    numberOfCase = strtok(numberOfCase, " ");
    if (strstr(numberOfCase, "case") != NULL) {
        strcpy(numberOfCase, strtok(NULL, ":\n"));
        char *ptr;
        (*details)[(*howMuchCase) - 1]->numberCase = strtol(numberOfCase, &ptr, 10);
    }
    char numLabel[1000];
    sprintf(numLabel, "%d", (*howMuchCase) - 1);
    char tempLine[50];
    strcpy(tempLine, ".L");
    strcat(tempLine, numLabel);
    strcat(tempLine, ":\n");
    (*details)[(*howMuchCase) - 1]->linesInCase[lineInEachCase] = (char *) malloc(strlen(tempLine) + 1);
    strcpy((*details)[(*howMuchCase) - 1]->linesInCase[lineInEachCase], tempLine);
    ++lineInEachCase;
    ++(*indexOfCase);
    (*details)[(*howMuchCase) - 1]->iHaveBreak = -1;
    while (strstr(arrayOfLines[(*indexOfCase)], "case") == NULL &&
           strstr(arrayOfLines[(*indexOfCase)], "default") == NULL &&
           strstr(arrayOfLines[(*indexOfCase)], "}") == NULL) {
        if (strstr(arrayOfLines[(*indexOfCase)], "break") != NULL) {
            char tempLine2[50];
            strcpy(tempLine2, "jmp .L");
            char tempNumCase[50];
            sprintf(tempNumCase, "%ld", numCases);
            strcat(tempLine2, tempNumCase);
            strcat(tempLine2, "\n");
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 1);
            (*details)[(*howMuchCase) - 1]->linesInCase[lineInEachCase] = (char *) malloc(strlen(tempLine2) + 1);
            strcpy((*details)[(*howMuchCase) - 1]->linesInCase[lineInEachCase], tempLine2);
            ++lineInEachCase;
            (*details)[(*howMuchCase) - 1]->iHaveBreak = 1;
            break;
        }
        char *leftSideEquation = strtok(arrayOfLines[(*indexOfCase)], " ");
        char *operatorEquation = strtok(NULL, " ");
        char *rightSideEquation = strtok(NULL, ";");
        if (!strcmp(operatorEquation, "=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 2);
            equalWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                       &lineInEachCase);

        } else if (!strcmp(operatorEquation, "+=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 2);
            plusEqualWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                           &lineInEachCase);
        } else if (!strcmp(operatorEquation, "-=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 2);
            minusEqualWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                            &lineInEachCase);
        } else if (!strcmp(operatorEquation, "*=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 3);
            multEqualWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                           &lineInEachCase);
        } else if (!strcmp(operatorEquation, "<<=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 2);
            shiftLeftWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                           &lineInEachCase);
        } else if (!strcmp(operatorEquation, ">>=")) {
            reallocLinesInCase(details, (*howMuchCase) - 1, lineInEachCase + 2);
            shiftRightWrite(leftSideEquation, rightSideEquation, (&((*details)[(*howMuchCase) - 1]->linesInCase)),
                            &lineInEachCase);
        }
        ++(*indexOfCase);
    }
    if ((*details)[(*howMuchCase) - 1]->iHaveBreak == -1) {
        (*details)[(*howMuchCase) - 1]->iHaveBreak = 0;
    }
    (*details)[(*howMuchCase) - 1]->lineInCase = lineInEachCase;
}

void swap(detailsCase *case1, detailsCase *case2) {
    detailsCase tempCase = *case1;
    *case1 = *case2;
    *case2 = tempCase;
}
detailsCase **bubbleSort(detailsCase **details, int sizeOfDetails) {
    int i, j;
    for (i = 0; i < sizeOfDetails - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < sizeOfDetails - i - 1; j++) {
            if (details[j]->numberCase > details[j + 1]->numberCase)
                swap((details[j]), (details[j + 1]));
        }
    }
    return details;
}

detailsCase **deletePoints(detailsCase **details, int sizeOfDetails) {
    int i = 0;
    for (; i < sizeOfDetails; ++i) {
        char numberOfCase[1000];
        strcpy(numberOfCase, details[i]->linesInCase[0]);
        strcpy(numberOfCase, strtok(numberOfCase, ":"));
        strcpy(details[i]->linesInCase[0], numberOfCase);
    }
    return details;
}

void printToAssembly(detailsCase ***details, char **arrayOfLines, int *howMuchCase, long maxCase, long minCase) {
    FILE *inputTxt = fopen("switch.s", "w+");
    if ((inputTxt) == NULL) {
        printf("error\n");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    fprintf(inputTxt, ".section .text\n");
    fprintf(inputTxt, ".global switch2\n");
    fprintf(inputTxt, "switch2:\n");
    fprintf(inputTxt, "movq $0,%%rax\n");
    fprintf(inputTxt, "subq $%ld,%%rdx\n", minCase);
    long temp = maxCase - minCase;
    fprintf(inputTxt, "cmpq $%ld,%%rdx\n", maxCase - minCase);
    char numberOfCase[1000];
    strcpy(numberOfCase, (*details)[(*howMuchCase) - 1]->linesInCase[0]);
    strcpy(numberOfCase, strtok(numberOfCase, ":"));
    fprintf(inputTxt, "ja %s\n", numberOfCase);
    fprintf(inputTxt, "jmp *.L%d(,%%rdx,8)\n", (*howMuchCase) + 1);
    int i = 0;
    for (; i < (*howMuchCase); ++i) {
        int amountOfLines = (*details)[i]->lineInCase;
        int j = 0;
        for (; j < amountOfLines; ++j) {
            fprintf(inputTxt, "%s", (*details)[i]->linesInCase[j]);
        }
    }
    fprintf(inputTxt, ".L%d:\n", (*howMuchCase));
    fprintf(inputTxt, "ret\n");
    fprintf(inputTxt, ".section .rodata\n");
    fprintf(inputTxt, ".align 8\n");
    fprintf(inputTxt, ".L%d:\n", (*howMuchCase) + 1);

    (*details) = bubbleSort((*details), (*howMuchCase) - 1);
    (*details) = deletePoints((*details), (*howMuchCase));
    long j = (*details)[0]->numberCase;
    int k = 0;
    for (; j <= maxCase; ++j) {
        if (j == (*details)[k]->numberCase) {
            fprintf(inputTxt, "\t.quad %s\n", (*details)[k]->linesInCase[0]);
            k++;
        } else {
            fprintf(inputTxt, "\t.quad %s\n", (*details)[(*howMuchCase) - 1]->linesInCase[0]);
        }
    }
    fclose(inputTxt);
}

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **arrayOfLines = NULL, **tempArrayOfLines = NULL;
    int sizeOfArray = 0, howMuchCase = 0;
    detailsCase **details = NULL;
    int myFirstTimeInCase = 1;
    int indexFirstCase = -1, indexLastCase = -1;
    long tempNumberCase, minCase = 0, maxCase = 0;
    long numCases = 0;

    fp = fopen("switch.c", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        /*printf("Retrieved line of length %zu:\n", read);*/

        if (arrayOfLines == NULL) {
            arrayOfLines = (char **) malloc(sizeof(char *));
            if (arrayOfLines == NULL) {
                printf("error in malloc arrayOfLines\n");
                exit(1);
            }
        } else {
            tempArrayOfLines = NULL;
            tempArrayOfLines = (char **) realloc(arrayOfLines, (sizeOfArray + 1) * sizeof(char *));
            if (tempArrayOfLines == NULL) {
                printf("error in realloc arrayOfLines\n");
                arrayOfLinesFree(arrayOfLines, sizeOfArray);
                exit(1);
            }
            arrayOfLines = tempArrayOfLines;
        }
        ++sizeOfArray;
        arrayOfLines[sizeOfArray - 1] = (char *) malloc(sizeof(char) * (read + 1));
        strcpy(arrayOfLines[sizeOfArray - 1], line);


        if (strstr(line, "default:\n")) {
            indexLastCase = sizeOfArray - 1;
            ++numCases;
        }

        char numberOfCase[1000];
        strcpy(numberOfCase, line);
        strcpy(numberOfCase, strtok(numberOfCase, " "));
        if (strstr(numberOfCase, "case") != NULL) {
            ++numCases;
            strcpy(numberOfCase, strtok(NULL, ":\n"));
            char *ptr;
            tempNumberCase = strtol(numberOfCase, &ptr, 10);
            if (myFirstTimeInCase) {
                indexFirstCase = sizeOfArray - 1;
                minCase = tempNumberCase;
                maxCase = tempNumberCase;
                myFirstTimeInCase = 0;
            } else {
                if (tempNumberCase < minCase) {
                    minCase = tempNumberCase;
                } else if (tempNumberCase > maxCase) {
                    maxCase = tempNumberCase;
                }
            }
        }
        /*printf("%s", arrayOfLines[sizeOfArray - 1]);*/
    }
    fclose(fp);

    /*printf("min %ld\t max %ld\n", minCase, maxCase);
    printf("first %d\t last %d\n", indexFirstCase, indexLastCase);*/
    int i;
    initializeDetailsCases(&details, numCases);
    for (i = indexFirstCase; i <= indexLastCase; ++i) {
        details[howMuchCase] = (detailsCase *) malloc(sizeof(detailsCase));
        ++howMuchCase;
        assemblyCodeForCase(&details, &i, arrayOfLines, &howMuchCase, maxCase, numCases);
        //there were not lines in this case, so we dont want to pass the next case
        if (!details[howMuchCase - 1]->iHaveBreak) {
            --i;
        }
    }

    printToAssembly(&details, arrayOfLines, &howMuchCase, maxCase, minCase);

    freeArrayStructDetailsCase(details, howMuchCase);
    arrayOfLinesFree(arrayOfLines, sizeOfArray);
    if (line) {
        free(line);
    }
    return 0;
}



