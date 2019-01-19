//dedomena eisodou:
// - ta join tis priorityQueue
// - N! twn sxesewn -- arithmos sindiasmwn

BestTree join_enumeration() {
	BestTree bt;
	bt = createBestTree();
	int* costs;

	//initialize bt to single relation
	//initialize costs

	for (int i = 0; i < n; i++) {
		while (r[i] != NULL) {
			for (int j = 0; j < n; j++) {
				if (r[j] != r[i]) {
					if (!connected(r[i], r[j])) {
						continue;
					}
					else {
						BestTree ct = createJoinTree(bt(r[i]), r[j]);
						// s' = s u r[j]
						if (bt)
					}
				}
			}
		}
	}

	return bt;
}


//MALLON JOINTREE KAI BESTTREE IDIA SINARTISI, MPOREI KAI OXI, PROXWRAME

BestTree createJoinTree(int relNum) {
	node* root[relNum+1] = {NULL};


}

// BestTree createBestTree() {
//
// }

void insert(int key, const char* buffer)
{
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


2 6 8 10 57 89           thesi:57?


h(57) = 4;







array[h(57)] = 57;
