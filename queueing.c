#include "queue.h"

Queue* makeInstructionQueue(pred_list* ls, int tot_j, int tot_f){ 
    
    int marked_j[tot_j][2];
    int marked_f[tot_f];
    pred_list* temp = ls;
    Queue* q = createQueue(tot_f+tot_j);

    // run list of instruction and mark joins and filters
    int i=0, j=0;
    while(temp != NULL){
        // if its a join
        if(ls->op == 0){
            marked_j[i][0] = temp->t1->table;
            marked_j[i][1] = temp->t2->table;
            i++;
        }
        // if its a filter
        else{
            marked_f[i][0] = temp->t1->table;
            j++;
        }
        temp = temp->next;
    }

    // search for tables that take part in both join and filter
    // for every filter
    for(int j=0; j < tot_f; j++){
        for(int i=0; i<tot_j; i++){
            if(marked_f[j] == marked_j[i][0]){

            }
            else if(marked_f[j] == marked_j[i][1]){

            }
            else{
                
            }
        }
    }
}
