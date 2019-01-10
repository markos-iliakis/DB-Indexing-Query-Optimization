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