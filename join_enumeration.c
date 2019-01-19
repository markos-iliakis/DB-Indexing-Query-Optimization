//dedomena eisodou:
// - ta join tis priorityQueue
// - stat_holder sh
//

BestTree join_enumeration(Queue *q, stat_holder* sh) {
	BestTree bt;
	bt = createBestTree();
	int* costs;

	//initialize bt to single relation
	//initialize costs



	return bt;
}


//MALLON JOINTREE KAI BESTTREE IDIA SINARTISI, MPOREI KAI OXI, PROXWRAME

BestTree createJoinTree(int relNum) {
	node* root[relNum+1] = {NULL};


}

// BestTree createBestTree() {
//
// }

void insert(int key, const char* buffer) {
    // try to instantiate node to insert word
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL)
    {
        return;
    }

    // make a new pointer
    strcpy(newptr->word, buffer);
    newptr->next = NULL;

    // check for empty list
    if (first[key] == NULL)
    {
       first[key] = newptr;
    }
    // check for insertion at tail
    else
    {
        node* predptr = first[key];
        while (true)
        {
            // insert at tail
            if (predptr->next == NULL)
            {
                predptr->next = newptr;
                break;
            }

            // update pointer
            predptr = predptr->next;
        }
    }
}

int hashing(int ) {

}



int cost(stat_holder* sh) {
    int c = 0;

    if (same table) {

    }
    else if (different table) {

    }

    return c;
}


// 2 6 8 10 57 89           thesi:57?
//
//
// h(57) = 4;







array[h(57)] = 57;
