#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"


BSTree * tree_read_points_from_file(FILE * pf);


int main (int argc, char *argv[]){
    FILE *f = NULL;
    BSTree *tree = NULL;
    Point *min = NULL, *max = NULL;

    if (argc < 2){
        fprintf(stdout,"Arguments missing\n");
        return EXIT_FAILURE;
    } else if (argc > 2){
        fprintf(stdout,"Too many arguments\n");
        return EXIT_FAILURE;
    }

    if ((f = fopen(argv[1], "r")) == NULL){   /* Argumento en posicion 1, nombre del fichero de texto */
        fprintf(stdout,"Opening file failed\n");
        return EXIT_FAILURE;
    }

    tree = tree_read_points_from_file(f);
    if (!tree){
        fclose(f);
        return EXIT_FAILURE;
    }

    fclose(f);

    min = tree_find_min(tree);
    max = tree_find_max(tree);

    if (!min || !max){
        fprintf(stdout, "Run failed\n");
        tree_destroy(tree);
        return EXIT_FAILURE;
    }

    fprintf(stdout,"Minimun of the tree: ");
    point_print(stdout, min);
    fprintf(stdout,"\n");

    fprintf(stdout,"Maximun of the tree: ");
    point_print(stdout, max);
    fprintf(stdout,"\n");
    

    tree_destroy(tree);

    return EXIT_SUCCESS;
}


BSTree * tree_read_points_from_file(FILE * pf){
    BSTree * t;
    int nnodes=0, i;
    Status st = OK;
    int x, y;
    char symbol;
    Point * p;

    if (!pf){
        return NULL;
    }

    /* Read number of nodes */
    if (fscanf(pf, "%d\n", &nnodes) != 1) return NULL;

    /* Create tree */
    t = tree_init(point_print, point_cmpEuDistance);
    if(!t) return NULL;

    /* Read nodes */
    for (i=0; i<nnodes && st==OK ;i++){
        if(fscanf(pf, "%d %d %c", &x, &y, &symbol)!=3){
            return NULL;
        }
        p = point_new(x, y, symbol);
        if(!p){
            tree_destroy(t);
            return NULL;
        }

        st=tree_insert(t, p); 
        if(st==ERROR){
            tree_destroy(t);
            point_free(p);
            return NULL;      
        }

    }

    return t;
}

Status points_free_rec (BSTree *tree){
    BSTree *left = NULL, *right = NULL;
    if (!tree) return ERROR;

    left


}