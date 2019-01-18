BestTree join_enumeration() {
	BestTree bt;
	bt = createBestTree()

	for (int i = 0; i <=n; i++) {
		bt(r[i]) = r[i];
	}

	for (int i = 0; i < n; i++) {
		while (r[i] != NULL) {
			for (int j = 0; j < n; j++) {
				if (r[j] != r[i]) {
					if (NoCrossProducts && !connected(r[i], r[j])) {
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

int hashing() {

}
