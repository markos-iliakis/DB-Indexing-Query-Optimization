struct new_stats;

typedef struct new_stats {
    int l;
    int u;
    int f;
    int d;
    bool* d_array;
    data* t;
    struct new_stats* next;
} new_stats;

//create new stats for preds in q
new_stats *new_s = NULL;
new_stats *curr = NULL;

for (int i = q->front; i < q->size; i++) {
    if (curr == NULL) {
        new_s = malloc(sizeof(new_stats));

        new_s->l = sh->stats[q->array[i]->t1->table]->l[q->array[i]->t1->column];
        new_s->u = sh->stats[q->array[i]->t1->table]->u[q->array[i]->t1->column];
        new_s->f = sh->stats[q->array[i]->t1->table]->f[q->array[i]->t1->column];
        new_s->d = sh->stats[q->array[i]->t1->table]->d[q->array[i]->t1->column];
        new_s->d_array = sh->stats[q->array[i]->t1->table]->d_array[q->array[i]->t1->column];
        new_s->t = q->array[i]->t1;
        new_s->next = NULL;

        if (q->array[i]->op == 0) {
            new_s->next = malloc(sizeof(new_stats));

            new_s->l = sh->stats[q->array[i]->t2->table]->l[q->array[i]->t2->column];
            new_s->u = sh->stats[q->array[i]->t2->table]->u[q->array[i]->t2->column];
            new_s->f = sh->stats[q->array[i]->t2->table]->f[q->array[i]->t2->column];
            new_s->d = sh->stats[q->array[i]->t2->table]->d[q->array[i]->t2->column];
            new_s->d_array = sh->stats[q->array[i]->t2->table]->d_array[q->array[i]->t2->column];
            new_s->t = q->array[i]->t2;
            new_s->next = NULL;
        }

        curr = new_s->next;
    }
    else {
        //check if t1 stats are copied
        new_stats* tmp = new_s;
        while (tmp != NULL) {
            if (tmp->t->table == q->array[i]->t1->table) {
                break;
            }
            else if (tmp->t->column == q->array[i]->t1->column) {
                break;
            }
            tmp = tmp->next;
        }

        if (tmp == NULL) {
            curr->next = malloc(sizeof(new_stats));

            curr->next->l = sh->stats[q->array[i]->t1->table]->l[q->array[i]->t1->column];
            curr->next->u = sh->stats[q->array[i]->t1->table]->u[q->array[i]->t1->column];
            curr->next->f = sh->stats[q->array[i]->t1->table]->f[q->array[i]->t1->column];
            curr->next->d = sh->stats[q->array[i]->t1->table]->d[q->array[i]->t1->column];
            curr->next->d_array = sh->stats[q->array[i]->t1->table]->d_array[q->array[i]->t1->column];
            curr->next->t = q->array[i]->t1;
            curr->next->next = NULL;
            curr = curr->next;
        }

        //check if t2 stats are copied
        tmp = new_s;
        while (tmp != NULL) {
            if (tmp->t->table == q->array[i]->t2->table) {
                break;
            }
            else if (tmp->t->column == q->array[i]->t2->column) {
                break;
            }
            tmp = tmp->next;
        }

        if (tmp == NULL) {
            curr->next = malloc(sizeof(new_stats));

            curr->next->l = sh->stats[q->array[i]->t2->table]->l[q->array[i]->t2->column];
            curr->next->u = sh->stats[q->array[i]->t2->table]->u[q->array[i]->t2->column];
            curr->next->f = sh->stats[q->array[i]->t2->table]->f[q->array[i]->t2->column];
            curr->next->d = sh->stats[q->array[i]->t2->table]->d[q->array[i]->t2->column];
            curr->next->d_array = sh->stats[q->array[i]->t2->table]->d_array[q->array[i]->t2->column];
            curr->next->t = q->array[i]->t2;
            curr->next->next = NULL;
            curr = curr->next;
        }
    }
}

//for each pred with filter
int f_preds = 0; //num of filter preds
for (int i = q->front; i < q->size; i++) {
    if (q->array[i]->op != 0) {
        f_preds++;
        //find stats for that pred
        new_stats* curr = new_s;
        while (curr != NULL) {

        }

        //call cost to update stats
        cost(q->array[i]->op, q->array[i]->t1, q->array[i]->t2, curr, NULL);
    }
}

//call join enum for rest joins
join_enumeration(q, new_s, f_preds);

//update q order
