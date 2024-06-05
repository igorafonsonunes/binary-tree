#include <stdio.h>
#include <stdlib.h>


// Definindo a estrutura da arvore
typedef struct tree {
    int value;
    struct tree* left;
    struct tree* right;
} Tree;

// Função para criar uma arvore
Tree* createTree() {
    return NULL;
}

// Função para inserir um valor na arvore de forma recursiva
Tree* insertTree(Tree** t, int value) {
    if(*t == NULL) {
        *t = (Tree*)malloc(sizeof(Tree)); // Alocando espaco na memoria
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->value = value;
    } else {
        if(value < (*t)->value) {
            insertTree(&((*t)->left), value);
        } 
        
        if(value > (*t)->value) {
            insertTree(&((*t)->right), value);
        }
    }
}

// Função para imprimir a arvore em ordem
void printTree(Tree* tree) {
    if(tree != NULL){
        printTree(tree->left);
        printf("%d", tree->value);
        printTree(tree->right);
    }
}

//Função para buscar um valor na arvore
Tree* searchTree(Tree* tree, int value) {
    if(tree == NULL || tree->value == value) {
        return tree;
    }

    if(value < tree->value) {
        return searchTree(tree->left, value);
    } else {
        return searchTree(tree->right, value);
    }
}

// Função para encontrar o menor valor na árvore
Tree* findMinValue(Tree* tree) {
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

// Função para deletar um valor na árvore
Tree * deleteDataInTree(Tree * tree, int value) {
    if(tree == NULL) {
        return tree;
    }

    if(value < tree->value) {
        tree->left = deleteDataInTree(tree->left, value);
    } else if (value > tree->value) {
        tree->right = deleteDataInTree(tree->right, value);
    } else {
        //Caso o valor tenha um filho ou nenhum filho
        if(tree->left == NULL) {
            Tree * temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            Tree * temp = tree->left;
            free(tree);
            return temp;
        }

        //Caso o valor tenha dois filhos
        Tree* temp = findMinValue(tree->right);
        tree->value = temp->value;
        tree->right = deleteDataInTree(tree->right, temp->value);
    }

    return tree;
}

int main() {
    Tree* tree = createTree();

    printf("INSERINDO DADOS NA ÁRVORE...\n");
    insertTree(&tree, 7);
    insertTree(&tree, 2);
    insertTree(&tree, 1);
    insertTree(&tree, 3);
    insertTree(&tree, 4);
    insertTree(&tree, 5);
    insertTree(&tree, 6);
    insertTree(&tree, 8);
    insertTree(&tree, 9);
    insertTree(&tree, 10);
    insertTree(&tree, 11);

    printTree(tree);
    printf("\nÁRVORE IMPRESSA EM ORDEM...\n");

    printf("REALIZANDO A BUSCA...\n");

    Tree* found = searchTree(tree, 5);
    if(found != NULL) {
        printf("VALOR ENCONTRADO: %d\n", found->value);
    } else {
        printf("NENHUM VALOR ENCONTRADO...\n");
    }

    printf("REALIZANDO A REMOCAO...\n");

    tree = deleteDataInTree(tree, 7);
    printTree(tree);
    printf("\nÁRVORE IMPRESSA EM ORDEM...\n");

    free(tree); 

    return 0;
}

//EXECUÇÃO: gcc -o binary_tree main.c
//EXECUÇÃO: ./binary_tree