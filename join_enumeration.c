BestTree join_enumeration(Queue *q, new_stats* new_s, int* q_tables, int n_tables) {
	BestTree* bt;
	int t_n = factorial(n_tables+1);
	bt = malloc(t_n*sizeof(BestTree));

	//initialize bt to single relation
	for (int i = 0; i < n_tables; i++) {
		bt[hashing(q_tables[i])].jeT = malloc(sizeof(int));
		bt[hashing(q_tables[i])].jeT[0] = q_tables[i];
	}

	//initialize costs
	for (int i = 0; i < t_n; i++)
		bt[i].cost = 0;

	for (int i = 0; i < n_tables; i++) {
		new_stats* tmp = new_s;
		int c;

		while (tmp != NULL) {
			if (tmp->t->table == q_tables[i]) {
				c = tmp->f;
				break;
			}
			else
				tmp = tmp->next;
		}

		bt[hashing(q_tables[i])].cost = c;
	}


	//increasing length of relations to check
	for (int i = 1; i < n_tables; i++) {
		//take i rel(s) from pred_list
		int* s_rels = malloc(i*sizeof(int));
		int r_rels;

		for (int j = 0; j < n_tables; j++) {
			for (int k = 0; k < i; k++) {
				s_rels[k] = ;
			}

			for (int m = 0; m < n_tables; m++) {
				r_rels = q_tables[m];
				if (!connected(q, s_rels, i, r_rels) || (r_in_s(s_rels, i, r_rels)))
					continue;
				else {
					int *new_s_rels = malloc((i+1)*sizeof(int));

					//create union S'
					for (int l = 0; l < i; l++)
						new_s_rels[l] = s_rels[l];
					new_s_rels[i+1] = r_rels;

					int nh = hashing(new_s_rels, i+1);

					//if BestTree(union) == null or cost(BestTree(union)) > cost(currTree)
						//BestTree(union) = currTree

					if () {
						bt[nh] ;
					}
				}
			}
		}
	}

	return bt;
}

int hashing(int* pred_int, int l) {
	int h = 0;

	for (int i = 0; i < l; i++) {
		pred_int[i]++;

		pred_int[i] = factorial(pred_int[i]);

		h += pred_int[i];
	}

	return h;
}

int factorial(int n) {
	if (n == 0)
		return 1;
	else
		return n * factorial(n-1);
}

int cost(int op, data* t1, data* t2, new_stats* st1, new_stats* st2) {
    int c = 0;
	int nl, nu, nf, nd;

	if (op == 3) {
		int dim = st1->u - st1->l + 1;
		if (dim > N)
			dim = N;

		nl = t2->table;
		nu = t2->table;

		//search if k is in d_table
		if (dim > t2->table) {
			if (st1->d_table[t2->table]) {
				nf = st1->f/st1->d;
				nd = 1;
			}
		}
		else {
			nf = 0;
			nd = 0;
		}

		//change stats of other columns
		for(int i= 0; i < t_a->tb[t1->table]->colNum; i++) {
			if (i != t1->column) {
				sh->stats[t1->table]->d[i] = sh->stats[t1->table]->d[i] * (1 - pow(1-(nf/st1->f), sh->stats[t1->table]->f[i]/sh->stats[t1->table]->d[i]));
				sh->stats[t1->table]->f[i] = nf;
			}
		}

		st1->l = nl;
		st1->u = nu;
		st1->f = nf;
		st1->d = nd;
	}
	else if (op == 1 || op == 2) {
		int k1 = st1->l;
		int k2 = st2->table;

		// lA < A < k
		if (op == 1) {
			if (k2 > st1->u)
				k2 = st1->u;

			nl = k1;
			nu = k2;
			nf = ((k2-k1)/(st1->u-st1-l)) * st1->f;
			nd = ((k2-k1)/(st1->u-st1-l)) * st1->d;
		}
		// k < A < uA
		else if (op == 2) {
			if (k1 < st1->l)
				k1 = st1->l;

			nl = k1;
			nu = k2;
			nf = ((k2-k1)/(st1->u-st1-l)) * st1->f;
			nd = ((k2-k1)/(st1->u-st1-l)) * st1->d;
		}

		//change stats of other columns
		for(int i= 0; i < t_a->tb[t1->table]->colNum; i++) {
			if (i != t1->column) {
				sh->stats[t1->table]->d[i] = sh->stats[t1->table]->d[i] * (1 - pow(1-(nf/st1->f), sh->stats[t1->table]->f[i]/sh->stats[t1->table]->d[i]));
				sh->stats[t1->table]->f[i] = nf;
			}
		}

		st1->l = nl;
		st1->u = nu;
		st1->f = nf;
		st1->d = nd;
	}
    else if (op == 0) {
		if (same table) {

	    }
	    else if (different table) {

	    }
		else if (same column same table) {

		}
	}

    return c;
}

int connected(Queue* q, int* s, int l, int r) {
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < q->size; j++) {
			if (q->array[j]->table->t1 == s[i] || q->array[j]->table->t2 == s[i])
				if (q->array[j]->table->t1 == r || q->array[j]->table->t2 == r)
					return 1; 
		}
	}

	return 0;
}

int r_in_s(int* s, int l, int r) {
	for (int i = 0; i < l; ++i) {
		if (s[i] == r)
			return 1;
	}

	return 0;
}

int* get_subsets(){

}

int* permutations() {
	
}
