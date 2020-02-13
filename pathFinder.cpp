#include <iostream>

using namespace std;

struct Node {
	int val;
	int node;
	int index;
	int prev;
};

class minHeap {
	private:
		Node** arr;
		Node** arr2; // stores node lowest values
		int size;
		int end;
		void insert(int v, int i);
		void moveDown(Node* curr, int i); // fixes top value (moves it down)
		void moveUp(Node* curr, int i); // moves node to correct position when its updated
//		void replace(int vPrev, int vNew, int p, int i);		
				
	public:
		minHeap(int s);		
		void upDate(int vNew,int prev, int p);	// update node value				
		void insert(int v,int previous, int p);		// adding a new lowest value
		Node* removeSmallest(); 		// removes smallest value and fixes heap
		bool inCloud(int p);
		void printHeap();
		void printHeapNode();
		void printHeapIndex();				
};

void minHeap::upDate(int vNew,int prev, int p) {
	if (arr2[p] != nullptr) {
		if (arr2[p]->val > vNew) {
			arr2[p]->val = vNew; 
			arr2[p]->prev = prev;
			moveUp(arr[arr2[p]->index],arr2[p]->index);
		}
	}	
}

bool minHeap::inCloud(int p) {
	if (arr2[p] != nullptr)
		return true;
	return false;
}

void minHeap::moveUp(Node* curr, int i) {
	int parent = (i + 1)/2 - 1;
	if (parent >= 0 && curr->val < arr[parent]->val) {
		Node* temp = arr[i];
		arr[i] = arr[parent];
		arr[i]->index = i;
		arr[parent] = temp;
		arr[parent]->index = parent;
		moveUp(curr,parent);
	}	
	
}


Node* minHeap::removeSmallest() {
	Node* temp = nullptr;
	if (end > 0) {
		temp = arr[0];
		end--;
		arr[0] = arr[end];
		arr[0]->index = 0;
		moveDown(arr[0],0);
	}
	return temp;
}

void minHeap::moveDown(Node* curr,int i) {
	int left = (i+1)*2 - 1;
	int right = (i+1)*2;
	if (right < end) {
		if (arr[left]->val > arr[right]->val)
			left = right;
	}
	if (left < end && curr->val > arr[left]->val) {
		Node* temp = arr[i];
		arr[i] = arr[left];
		arr[i]->index = i;
		arr[left] = temp;
		arr[left]->index = left;
		moveDown(curr,left);
	} 
	
	
}


void minHeap::printHeap() {
	for (int i = 0; i < end; i++) {
		cout << arr[i]->val << " ";
	}
	cout << endl;
	
}

void minHeap::printHeapIndex() {
	for (int i = 0; i < end; i++) {
		cout << arr[i]->index << " ";
	}
	cout << endl;
	
}

void minHeap::printHeapNode() {
	for (int i = 0; i < end; i++) {
		cout << arr[i]->node << " ";
	}
	cout << endl;
	
}

minHeap::minHeap(int s) {
	arr = new Node*[s];
	arr2 = new Node*[s];
	size = s;
	end = 0;
}

void minHeap::insert(int v,int previous, int p) {
	if (!inCloud(p)) {
		arr[end] = new Node();
		arr[end]->val = v;
		arr[end]->node = p;
		arr[end]->index = end;
		arr[end]->prev = previous;
		arr2[p] = arr[end];	
		end++;
		if (end > 1) {
			insert(v, end - 1);
		}
	} else {
		upDate(v,previous,p);
	}
}

void minHeap::insert(int v, int i) {
	int parent = (i + 1)/2 - 1;
	if (parent >= 0 && v < arr[parent]->val) {
		Node* temp = arr[i];
		arr[i] = arr[parent];
		arr[i]->index = i;
		arr[parent] = temp;
		arr[parent]->index = parent;
		insert(v,parent);
	}
}



int** makeAjacencyMatrix(const int numVerticies, int numConnections, int (*connections)[3]) {
	int x, y, path, total;
	int** arr = new int*[numVerticies];
	
	for (int i = 0; i < numVerticies; i++) {
		arr[i] = new int[numVerticies];
		for (int j = 0; j < numVerticies; j++) {
			if (i != j)
				arr[i][j] = 9999;
			else
				arr[i][j] = 0;
		}
	}
	for (int j = 0; j < numConnections; j++) {
		x = connections[j][0];
		y = connections[j][1];
		path = connections[j][2]; 
		arr[x][y] = path;
		arr[y][x] = path;
		total += path;
	}
	return arr;
}

void printArray(int** arr, int numVerticies) {
	for (int i = 0; i < numVerticies; i++) {
		for (int j = 0; j < numVerticies; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	
}

//**********************************************************************
/* This is the function that calculates the path
 */
void findShortestPath(int** arr, int numVerticies, int start) {
	int numInPath = 0;
	int vertIns;
	int cloud[numVerticies] = {0};
	Node* shortestPaths[numVerticies];
	
	cloud[start] = 0;
	int addedNode = start;
	
	minHeap minH(numVerticies);
	
	minH.insert(0,start,start);
	shortestPaths[start] = minH.removeSmallest();
		
	while (numInPath != numVerticies) {	
		for (int i = 0; i < numVerticies; i++) {			
			if (arr[addedNode][i] != 9999 && i != addedNode && cloud[i] == 0) {			
				int curr = arr[addedNode][i] + cloud[addedNode];
				if (cloud[i] == 0 && i != start)
					minH.insert(curr,addedNode,i);
				else if (cloud[i] > curr)			
					minH.upDate(curr,addedNode, i);
			}
		}
		numInPath++;
		Node* temp = minH.removeSmallest();
		if (temp != nullptr) {		
			shortestPaths[temp->node] = temp;
			cout << temp->prev << " -> " << temp->node <<" (path length: " << temp->val <<")\n";
//			minH.printHeap();			
			cloud[temp->node] = temp->val;
			addedNode = temp->node;		
		}
	}
	cout << endl;
}
//**********************************************************************
int main() {
	int b[14][3] = {{0,1,4},{0,7,8},{1,2,7},{1,7,5},{7,8,6},{7,6,8},{2,8,4},{2,3,3},{2,5,7},{8,6,2},{6,5,3},{3,5,2},{5,4,10},{3,4,11}};
	int** arr = makeAjacencyMatrix(9,14,b);
	findShortestPath(arr,9,0);
	return 0;
}
