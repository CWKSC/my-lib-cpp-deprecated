#pragma once

#include <cstdio>

constexpr int maxSize_DistjointSet = 100;

struct DistjointSet {
	int disjointSet[maxSize_DistjointSet]{};
	DistjointSet() {
		for (int i = 0; i < maxSize_DistjointSet; i++) {
			disjointSet[i] = -1;
		}
	}
	int findParent(int id) {
		if (disjointSet[id] == -1) return id;
		int parent = findParent(disjointSet[id]);
		disjointSet[id] = parent;
		return parent;
	}
	void unionSet(int a, int b) {
		int aParent = findParent(a);
		int bParent = findParent(b);
		if (aParent == bParent) return;
		disjointSet[bParent] = aParent;
	}

	static void test() {
		DistjointSet distjointSet;

		distjointSet.unionSet(0, 1);
		printf("%d %d %d %d %d %d\n",
			distjointSet.findParent(0),
			distjointSet.findParent(1),
			distjointSet.findParent(2),
			distjointSet.findParent(3),
			distjointSet.findParent(4),
			distjointSet.findParent(5));

		distjointSet.unionSet(2, 3);
		printf("%d %d %d %d %d %d\n",
			distjointSet.findParent(0),
			distjointSet.findParent(1),
			distjointSet.findParent(2),
			distjointSet.findParent(3),
			distjointSet.findParent(4),
			distjointSet.findParent(5));

		distjointSet.unionSet(5, 3);
		printf("%d %d %d %d %d %d\n",
			distjointSet.findParent(0),
			distjointSet.findParent(1),
			distjointSet.findParent(2),
			distjointSet.findParent(3),
			distjointSet.findParent(4),
			distjointSet.findParent(5));
		distjointSet.unionSet(4, 1);
		printf("%d %d %d %d %d %d\n",
			distjointSet.findParent(0),
			distjointSet.findParent(1),
			distjointSet.findParent(2),
			distjointSet.findParent(3),
			distjointSet.findParent(4),
			distjointSet.findParent(5));

		distjointSet.unionSet(1, 2);
		printf("%d %d %d %d %d %d\n",
			distjointSet.findParent(0),
			distjointSet.findParent(1),
			distjointSet.findParent(2),
			distjointSet.findParent(3),
			distjointSet.findParent(4),
			distjointSet.findParent(5));
	}
};


