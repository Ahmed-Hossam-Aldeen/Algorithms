#include <bits/stdc++.h>
using namespace std;

//--------------------------------------QuickSort--------------------//
// last element is taken as pivot
int Partition(vector<int>& v, int start, int end) {

	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (v[i] < v[pivot]) {
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;
}
void Quicksort(vector<int>& v, int start, int end) {
	if (start < end) {
		int p = Partition(v, start, end);
		Quicksort(v, start, p - 1);
		Quicksort(v, p + 1, end);
	}
}