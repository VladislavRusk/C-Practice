#include <iostream>
//#include <algorithm>

using namespace std;

void printArray(int* ar,int n) {
	for (int i = 0; i < n; i++) {
		cout << ar[i] << " ";		
	}
	cout << endl;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
int parition(int* ar, int left,int right) {
	int pivot = (right-left)/2 + left;
	cout << endl << endl << "pivot: " << pivot << endl;
	while (left <= right) {
		while (ar[left] < ar[pivot])
			left++;
		while (ar[right] > ar[pivot])
			right--;
		
		if (left <= right) {	
			swap(ar[left],ar[right]);
			left++;
			right--;
		}
		
	}
	return left;
	
}

void quickSort(int* ar,int s,int e) {
	if (s < e) {
		int index = parition(ar,s,e);
		cout << index << endl;
		printArray(ar,6);
		quickSort(ar,s,index-1);
		quickSort(ar,index,e);
	}
}



int main() {
	int ar[6] = {10,7,8,9,1,5};
	quickSort(ar,0,5);
	
	for (int i = 0; i < 6; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
	
	
	return 0;
}
