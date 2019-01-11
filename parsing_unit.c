#include "result.h"

int parseInstuctions(indexes_array* indexes) {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;

    fp = fopen("./small.work", "r");
    if (fp == NULL)
        return -1;

    queries *root = malloc(sizeof(queries));
    root->num = 0;
    root->head = malloc(sizeof(batch));

    batch *curr = root->head;
    curr->num = 0;
    curr->head = NULL;

    instruction *temp = NULL;
    while ((getline(&line, &len, fp)) != -1) {

        if (strcmp(line, "F\n") == 0) {
            curr->next = malloc(sizeof(batch));
            curr = curr->next;
            curr->num = 0;
            curr->head = NULL;
            curr->next = NULL;
        }
        else {
            if (curr->head == NULL) {
                curr->head = malloc(sizeof(instruction));
                temp = curr->head;
            }
            else {
                temp->next = malloc(sizeof(instruction));
                temp = temp->next;
                temp->next = NULL;
            }
            curr->num++;

            int i;
            char *token;

            token = strtok(line, "|\n");
            for (i = 0; i < 3; i++) {
                if (i == 0) {
                    // printf("%s\n", token);
                    temp->rel = malloc((strlen(token) + 1)*sizeof(char));
                    strcpy(temp->rel, token);
                }
                else if (i == 1) {
                    // printf("%s\n", token);
                    temp->pred = malloc((strlen(token) + 1)*sizeof(char));
                    strcpy(temp->pred, token);
                }
                else {
                    // printf("%s\n", token);
                    temp->proj = malloc((strlen(token) + 1)*sizeof(char));
                    strcpy(temp->proj, token);
                }

                token = strtok(NULL, "|\n");
            }
            // free(token);
        }
    }

    // print(root);

    parsed_instruction *pi = NULL;
    parsed_instruction *pi_tmp = pi;

    batch *tmp = root->head;
    while (tmp->num != 0) {
        //printf("edw tmp->num : %d\n", tmp->num );
        //getchar();
        instruction *i = tmp->head;
        while (i != NULL) {
            parsed_instruction *new = malloc(sizeof(parsed_instruction));

            char *token, *token2, *token3, *token4, *storage;
            char *save1, *save2, *save3;
            int j;

            //------------ PARSE RELATIONS TABLES ------------

            storage = malloc(strlen((i->rel)+1)*sizeof(char));
            strcpy(storage, i->rel);
            //printf("%s\n", storage);
            token = strtok_r(storage, " ", &save1);

            j = 0;
            while (token != NULL) {
                j++;
                token = strtok_r(NULL, " ", &save1);
            }

            new->arrays = malloc(j*sizeof(int));

            save1 = NULL;
            token = strtok_r(i->rel, " ", &save1);

            j = 0;
            while (token != NULL) {
                new->arrays[j] = atoi(token);
                j++;
                token = strtok_r(NULL, " ", &save1);
            }
            free(storage);

            // -------------- PARSE PREDICATES -------------

            save1 = NULL;
            token = strtok_r(i->pred, "&", &save1);
            pred_list *pl_temp = NULL;
            while (token != NULL) {
                if (new->pl == NULL) {
                    new->pl = malloc(sizeof(pred_list));
                    pl_temp = new->pl;
                    pl_temp->next = NULL;
                }
                else {
                    pl_temp->next = malloc(sizeof(pred_list));
                    pl_temp = pl_temp->next;
                }
                storage = malloc((strlen(token)+1)*sizeof(char));
                strcpy(storage, token);
                //printf("%s\n", storage);

                //scan token for =, <, > and set op
                int op = -1;
                if (strstr(token, "=") != NULL) {
                    char *s = malloc((strlen(token)+1)*sizeof(char));
                    strcpy(s, token);

                    int k;
                    for (k = 0; s[k]; s[k] == '.' ? k++ : *s++);

                    if (k == 2)
                        op = 0;
                    else if (k == 1)
                        op = 3;
                }
                else if (strstr(token, "<") != NULL)
                    op = 1;
                else if (strstr(token, ">") != NULL)
                    op = 2;

                save2 = NULL;


                if (op == 0) {
                    pl_temp->op = 0;
                    token2 = strtok_r(token, "=", &save2);
                    token3 = strtok_r(NULL, "=", &save2);

                    save3 = NULL;
                    pl_temp->t1 = malloc(sizeof(data));
                    token4 = strtok_r(token2, ".", &save3);
                    //an mpei sunarthsh pou diatrexei to pl kai tha koitaei poses fores einai to token4 sth lista
                    pl_temp->t1->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t1->table = new->arrays[atoi(token4)];
                    token4 = strtok_r(NULL, ".", &save3);
                    pl_temp->t1->column = atoi(token4);

                    save3 = NULL;
                    pl_temp->t2 = malloc(sizeof(data));
                    token4 = strtok_r(token3, ".", &save3);
                    pl_temp->t2->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t2->table = new->arrays[atoi(token4)];
                    token4 = strtok_r(NULL, ".", &save3);
                    pl_temp->t2->column = atoi(token4);
                }
                else if (op == 1) {
                    pl_temp->op = 1;
                    token2 = strtok_r(token, "<", &save2);
                    token3 = strtok_r(NULL, "<", &save2);

                    save3 = NULL;
                    pl_temp->t1 = malloc(sizeof(data));
                    token4 = strtok_r(token2, ".", &save3);
                    pl_temp->t1->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t1->table = new->arrays[atoi(token4)];
                    token4 = strtok_r(NULL, ".", &save3);
                    pl_temp->t1->column = atoi(token4);

                    save3 = NULL;
                    pl_temp->t2 = malloc(sizeof(data));
                    pl_temp->t2->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t2->table = atoi(token3);
                    pl_temp->t2->column = -1;
                }
                else if (op == 2) {
                    pl_temp->op = 2;
                    token2 = strtok_r(token, ">", &save2);
                    token3 = strtok_r(NULL, ">", &save2);

                    save3 = NULL;
                    pl_temp->t1 = malloc(sizeof(data));
                    token4 = strtok_r(token2, ".", &save3);
                    pl_temp->t1->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t1->table = new->arrays[atoi(token4)];
                    token4 = strtok_r(NULL, ".", &save3);
                    pl_temp->t1->column = atoi(token4);

                    save3 = NULL;
                    pl_temp->t2 = malloc(sizeof(data));
                    pl_temp->t2->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t2->table = atoi(token3);
                    pl_temp->t2->column = -1;
                }
                else if (op == 3){
                    pl_temp->op = 3;
                    token2 = strtok_r(token, "=", &save2);
                    token3 = strtok_r(NULL, "=", &save2);

                    save3 = NULL;
                    pl_temp->t1 = malloc(sizeof(data));
                    token4 = strtok_r(token2, ".", &save3);
                    pl_temp->t1->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t1->table = new->arrays[atoi(token4)];
                    token4 = strtok_r(NULL, ".", &save3);
                    pl_temp->t1->column = atoi(token4);

                    save3 = NULL;
                    pl_temp->t2 = malloc(sizeof(data));
                    pl_temp->t2->appearance = findAppearances(new->arrays, atoi(token4));
                    pl_temp->t2->table = atoi(token3);
                    pl_temp->t2->column = -1;
                }

                free(storage);
                token = strtok_r(NULL, "&", &save1);
                //printf("token gia operations : %s\n", token);
            }

            // -------------- PARSE PROJECTIONS ------------

            //printf("Koitaw to projection\n");
            //getchar();
            save1 = NULL;
            token = strtok_r(i->proj, " \n", &save1);
            proj_list *pr_temp = NULL;
            while (token != NULL) {
                if (new->prl == NULL) {
                    new->prl = malloc(sizeof(proj_list));
                    pr_temp = new->prl;
                    pr_temp->next = NULL;
                }
                else {
                    pr_temp->next = malloc(sizeof(proj_list));
                    pr_temp = pr_temp->next;
                }
                //printf("%s\n", storage);

                //printf("edw2");
                //getchar();
                save2 = NULL;
                pr_temp->t = malloc(sizeof(data));
                token2 = strtok_r(token, ".", &save2);
                pr_temp->t->appearance = findAppearances(new->arrays, atoi(token2));
                pr_temp->t->table = new->arrays[atoi(token2)];
                token2 = strtok_r(NULL, ".", &save2);
                pr_temp->t->column = atoi(token2);

                token = strtok_r(NULL, " \n", &save1);
                //printf("token : %s\n", token);

            }

            //printf("teleiwsa to parsing\n");
            //getchar();
            if (pi == NULL) {
                pi = new;
                pi_tmp = pi;
            }
            else {
                pi_tmp->next = new;
                pi_tmp = new;
            }

            i = i->next;
            //printf("teleiwsa to parsing 2!!!!\n");
            //getchar();
        }

        //printf("teleiwsa to parsing 3!!!!\n");
        //getchar();

        tmp = tmp->next;
    }

    pi_tmp = pi;
    while (pi_tmp != NULL) {
        int total_j = 0;
        int total_f = 0;
        pred_list *pl_temp =  pi_tmp->pl;

        while (pl_temp != NULL) {
            if (pl_temp->op == 0)
                total_j++;
            else
                total_f++;

            pl_temp = pl_temp->next;
        }

        fprintf(stderr, "\n-------------------------\n");//added

        printQuery(pi_tmp);

        Queue *q = makeInstructionQueue(pi_tmp->pl, total_j, total_f);
        // printQueue(q);
        fprintf(stderr, "\nPriority Queue Created\n\n");

        //run query
        executeQuery(q, indexes, pi_tmp->prl);

        pi_tmp = pi_tmp->next;
    }
    return 1;
}

void printQuery(parsed_instruction* p_i){
    proj_list* prl = p_i->prl;
    pred_list* pl = p_i->pl;

    fprintf(stderr, "\nSelect ");
    while(prl != NULL){
        fprintf(stderr, "sum(%d.%d) ", prl->t->table, prl->t->column);
        prl = prl->next;
    }
    fprintf(stderr, "Where ");
    while(pl != NULL){
        if(pl->op == 0) fprintf(stderr, "%d.%d = %d.%d", pl->t1->table, pl->t1->column, pl->t2->table, pl->t2->column);
        else {
            fprintf(stderr, "%d.%d", pl->t1->table, pl->t1->column);

            if(pl->op == 1) fprintf(stderr, " < ");
            else if(pl->op == 2) fprintf(stderr, " > ");
            else fprintf(stderr, " = ");

            fprintf(stderr, "%d", pl->t2->table);
        }
        pl = pl->next;
        if(pl != NULL) fprintf(stderr, " and ");
    }
    fprintf(stderr, "\n\n");
}

void print(queries *root) {
    batch *curr = root->head;
    while (curr != NULL) {

        instruction *temp = curr->head;

        while (temp != NULL) {
            printf("%s %s %s\n", temp->rel, temp->pred, temp->proj);

            temp = temp->next;
            // break;//added
        }
        break;//added
        if (curr->next->num == 0)
            break;
        else
            curr = curr->next;
    }
}


int findAppearances(int *arrays, int array_num){
    int appearances = 0;
    // printf("array[num]-->%d \n", arrays[array_num]);
    for(int i = 0; i<= array_num; i++){
        // printf("arr[%d]-->%d\n", i, arrays[i]);
        if(arrays[i] == arrays[array_num])
            appearances++;
    }
    // printf("appearances : %d\n", appearances);
    return appearances;
}
