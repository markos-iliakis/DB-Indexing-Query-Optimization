BestTree join_enumeration() {
	BestTree bt;
	bt = createJoinTree();

	for (int i = 0; i <=n; i++) {
		bt(r[i]) = r[i];
	}

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


LEO EISAI MPAKLIARAKI SWSTO ME AGAPH -> O XRHSTARAS SOU  !!!];)'
