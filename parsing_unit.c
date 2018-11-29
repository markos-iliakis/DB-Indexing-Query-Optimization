#include "parsing_unit.h"


int main() {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;

    fp = fopen("small.work", "r");
    if (fp == NULL)
        return -1;

    queries *root = malloc(sizeof(queries));
    root->num = 0;
    root->next = malloc(sizeof(batch));

    batch *curr = root->head;
    instruction *temp = curr->head;

    while ((getline(&line, &len, fp)) != -1) {
        if (strcmp(line, "F\n") == 0) {
            root->num++;
            curr->next = malloc(sizeof(batch));
            curr = curr->next;

            curr->num = 0;
            curr->head = NULL;
        }
        else {
            temp = malloc(sizeof(instruction));
            temp->next++;
            int i;
            char *token, *token2, *token3;

            token = strtok(line, "|\n");
            for (i = 0; i < 3; i++) {
              if (i == 0) {
                printf("%s\n", token);
                temp->rel = malloc((strlen(token) + 1)*sizeof(char));
                strcpy(temp->rel, token);
                token2 = strtok(NULL, "|\n");
              }
              else if (i == 1) {
                printf("%s\n", token2);
                temp->pred = malloc((strlen(token2) + 1)*sizeof(char));
                strcpy(temp->pred, token2);
                token3 = strtok(NULL, "|\n");
              }
              else {
                printf("%s\n", token3);
                temp->proj = malloc((strlen(token3) + 1)*sizeof(char));
                strcpy(temp->proj, token3);
              }

              // token = strtok(NULL, "|\n");
            }
            // free(token);
            temp = temp->next;
        }
    }

    batch *tmp = root->head;
    while (tmp != NULL) {
        instruction *i = tmp->head;
        while (i != NULL) {
            parsed_instruction *new = malloc(sizeof(parsed_instruction));
            char *token, *token2, *token3, *token4, *storage;
            char *save1, *save2, *save3;
            int i;

            //------------ PARSE RELATIONS TABLES ------------
            storage = malloc(strlen((i->rel)+1)*sizeof(char));
            strcpy(storage, i->rel);

            token = strtok_r(storage, " ", &save1);

            i = 0;
            while (token != NULL) {
              i++;
              token = strtok_r(NULL, " ", &save1);
            }

            new->arrays = malloc(i*sizeof(int));

            save1 = NULL;
            token = strtok_r(i->rel, " ", &save1);
            i = 0;
            while (token != NULL) {
              new->arrays[i] = atoi(token);
              i++;
              token = strtok_r(NULL, " ", &save1);
            }
            free(storage);

            // -------------- PARSE PREDICATES -------------
            new->pl = malloc(sizeof(pred_list));

            save1 = NULL;
            token = strtok_r(i->pred, "&", &save1);
            while (token != NULL) {
              storage = malloc((strlen(token)+1)*sizeof(char));
              strcpy(storage, token);

              //scan token for =, <, > and set op
              int op = -1;
              if (strstr(token, "=") != NULL)
                op = 0;
              else if (strstr(token, "<") != NULL)
                op = 1;
              else if (strstr(token, ">") != NULL)
                op = 2;

              save2 = NULL;
              if (op == 0) {
                new->pl->op = 0;
                token2 = strtok_r(token, "=", &save2);
                token3 = strtok_r(NULL, "=", &save2);

                save3 = NULL;
                new->pl->t1 = malloc(sizeof(data));
                token4 = strtok(token2, ".", &save3);
                new->pl->t1->data->table = atoi(token4);
                token4 = strtok(NULL, ".", &save3);
                new->pl->t1->data->column = atoi(token4);

                save3 = NULL;
                new->pl->t2 = malloc(sizeof(data));
                token4 = strtok(token3, ".", &save3);
                new->pl->t2->data->table = atoi(token4);
                token4 = strtok(NULL, ".", &save3);
                new->pl->t2->data->column = atoi(token4);

                new->pl->next = NULL;
              }
              else if (op == 1) {
                new->pl->op = 1;
                token2 = strtok(token, "<", &save2);
                token3 = strtok(NULL, "<", &save2);

                save3 = NULL;
                new->pl->t1 = malloc(sizeof(data));
                token4 = strtok(token2, ".", &save3);
                new->pl->t1->data->table = atoi(token4);
                token4 = strtok(NULL, ".", &save3);
                new->pl->t1->data->column = atoi(token4);

                save3 = NULL;
                new->pl->t2 = malloc(sizeof(data));
                new->pl->t2->data->table = atoi(token3);
                new->pl->t2->data->column = -1;

                new->pl->next = NULL;
              }
              else if (op == 2) {
                new->pl->op = 2;
                token2 = strtok(token, ">", &save2);
                token3 = strtok(NULL, ">", &save2);

                save3 = NULL;
                new->pl->t1 = malloc(sizeof(data));
                token4 = strtok(token2, ".", &save3);
                new->pl->t1->data->table = atoi(token4);
                token4 = strtok(NULL, ".", &save3);
                new->pl->t1->data->column = atoi(token4);

                save3 = NULL;
                new->pl->t2 = malloc(sizeof(data));
                new->pl->t2->data->table = atoi(token3);
                new->pl->t2->data->column = -1;

                new->pl->next = NULL;
              }
              else {
                //error
              }

              free(storage);
            }

            // -------------- PARSE PROJECTIONS ------------
            new->prl = malloc(sizeof(proj_list));

            save1 = NULL;
            token = strtok(i->proj, " ", &save1);
            while (token != NULL) {


                token = strtok(NULL, " ", &save1);
            }


            i = i->next;
        }

        tmp = tmp->next;
    }

}
