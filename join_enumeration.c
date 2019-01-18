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

BestTree createJoinTree() {

}

BestTree createBestTree() {

}

void insert(char* buffer) {
    // try to instantiate node for number
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL)
    {
        return;
    }

    // make a new ponter
    newptr->name = buffer;
    newptr->next = NULL;

    // check for empty list
    if (first == NULL)
    {
        first = newptr;
    }
    // check for insertion at tail
    else
    {
        // keep track of the previous spot in list
        node* predptr = first;

        // because we don't know how long this list is
        // we must induce a forever loop until we find the end
        while (true)
        {
            // check if it is the end of the list
            if (predptr->next == NULL)
            {
                // add new node to end of list
                predptr->next = newptr;

                // break out of forever loop
                break;
            }

            // update pointer
            predptr = predptr->next;
        }
    }
}
