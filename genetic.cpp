#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <map>

using namespace std;

/* best path that i found had a path length of 2471
 */

unsigned int largestDistance;
unsigned int smallestDistance;


/* possible distances from city to city
 * not fully filled in
 */
int distanceArray[27][27] = {
	{0,129,206,569,107,360,284,144,115,162,200,231,288,226,436,272,174,231,297,252,118,146,258,347,121,227,200}, // bakersfield
	{0,0,153,696,236,395,155,139,130,291,329,360,417,123,565,401,71,176,426,381,247,225,387,476,250,356,329}, // Barstow
	{0,0,0,777,315,780,312,82,93,370,406,428,496,116,644,480,827,23,505,460,293,188,466,565,329,435,408}, // Carlsbad
	{0,0,0,0,462,398,797,713,694,407,369,388,291,795,150,314,43,800,272,317,504,609,349,222,544,356,488}, // Eureko
	{0,0,0,0,0,388,408,251,222,55,93,152,181,333,329,185,281,338,190,145,137,242,151,240,82,120,93}, // Fresno
	{0,0,0,0,0,0,466,479,456,194,156,266,195,435,249,107,436,542,192,197,197,492,229,199,335,131,133}, // Lake Tahoe
	{0,0,0,0,0,0,0,314,302,446,484,504,567,276,640,587,228,332,568,524,414,354,524,610,408,510,435}, // las vegas
	{0,0,0,0,0,0,0,0,29,306,344,364,432,112,580,416,68,105,441,396,229,124,402,491,265,371,344}, // Long Beach
	{0,0,0,0,0,0,0,0,0,277,315,335,403,111,551,387,59,116,412,367,200,95,373,462,236,342,315}, // Los Angeles
	{0,0,0,0,0,0,0,0,0,0,37,118,126,388,274,110,336,393,135,114,192,297,118,185,137,65,81}, // Merced
	{0,0,0,0,0,0,0,0,0,0,0,153,88,426,236,72,374,431,97,82,230,335,114,147,175,27,119}, // Modesto
	{0,0,0,0,0,0,0,0,0,0,0,0,111,446,325,185,394,451,116,71,135,240,45,166,234,140,199}, // Monterey
	{0,0,0,0,0,0,0,0,0,0,0,0,0,514,214,87,462,519,9,40,227,332,72,59,263,75,207}, // Oakland
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,682,498,52,139,523,478,311,206,484,573,347,453,426}, // Palm Springs
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,164,610,667,223,254,411,546,286,251,411,209,355}, // Redding
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,446,503,87,114,301,406,146,103,247,45,191}, // sacramento
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,105,471,426,259,254,432,521,295,401,374}, // San Bernardino
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,528,483,316,211,489,578,352,458,431}, // San Diego
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,232,337,77,50,272,84,216}, // San Francisco
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,187,292,32,95,227,69,195}, // San Jose
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,105,180,282,174,256,230}, // San Luis Obispo
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,285,387,287,361,335}, // Santa Barbara
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,233,101,199}, // Santa Cruz
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,322,134,266}, // Santa Rosa
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,202,175}, // Sequoia Park
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,146}, // Yosemite
};

class geneticAlgorithm {
	private:
		const unsigned int populationSize;
		const unsigned int genes = 26;				// # genes in this case cities
		const int maxGen;
		int totalCompetitors;
		
		int** currentGen;
		int** nextGen;
		double* individualPopFitness; 
		
		const double selectionRate = 0.88; 			// percent of fit population selected
		const double crossOverRate = 0.65; 			// percent of genetic material exchanged
		const double mutationRate = 0.017; 			// likelyhood member of pop mutates
		
		int populationFitness; 						// total fitness
		const int start = 0;
		
		void createIndividual(vector<int> cities,int individual);
		double calculateChromosomeFitness(int index);		
	
	public:
		void printPath(int); 						// prints nextGen paths
		void printPathCurrent(int); 				// prints currentGen paths
		void run(); // runs process
		geneticAlgorithm(unsigned int popSize,unsigned int maxGenerations); 
		void generateStartPopulation();				// creates initial random pop
		void printPopulation();						// prints nextGen matrix
		void printPopulation2();					// prints currentGen matrix
		
		void calculateFitness(); 					// calculates individual fitness values, and total fitness
		void printFitness();
		
		void selectBest(); 							// selects population that goes on to next gen based on selectionRate
		
		void tournamentSelect(); 					// select members to recombinate
		void recombinate(int,int,int); 				// based on crossover rate combine genetics
		void possiblyMutate(int); 					// mutate based on mutation percentage
		void superMutate(int); 						// different kind of mutation
		void deleteHalf(); 							// removes half (for testing purpose)
};


void geneticAlgorithm::run() {
	int gen = 0; // generation
	while (gen < maxGen) { 
		cout << "generation: " << gen << endl;
		calculateFitness();
		selectBest();
		tournamentSelect();
		int** temp = currentGen;
		currentGen = nextGen;			
		nextGen = temp;
		gen++;
	}
	
}


/* prints value at index in nextGen
 * @param index
 * @return none
 */
void geneticAlgorithm::printPath(int index) {
	cout << "0 ";
	for (int i = 0; i < genes; i++) {
		cout << nextGen[index][i] << " ";
	}
	cout << "0" << endl;
	
}

/* prints value at index in currentGen
 * @param index
 * @return none
 */
void geneticAlgorithm::printPathCurrent(int index) {
	cout << "0 ";
	for (int i = 0; i < genes; i++) {
		cout << currentGen[index][i] << " ";
	}
	cout << "0" << endl;
	
}


/* selects two random 
 * @param none
 * @return no return
 */
void geneticAlgorithm::tournamentSelect() {
//	srand(time(0));
	totalCompetitors = 3;
	int start = (populationSize*(1 - selectionRate));
	
	if (start % 2 != 0) {
		start--;
	}
	for (int i = start; i < populationSize; i = i + 2) {
		map<int, int> tournamentMap;		
		for (int j = 0; j < (2*totalCompetitors); j++) { // fill best array
			int indiv = rand() % populationSize;
			tournamentMap.insert(pair<int, int>(individualPopFitness[indiv],indiv));
		}
		map<int,int>::iterator it = ++tournamentMap.begin();
		if (i < populationSize) {
			recombinate(tournamentMap.begin()->second, it->second, i);	
			possiblyMutate(i);	
		}	
	}
	
}

/* randomly mutates values, switching 2 genes randomly
 * @param index of mutatated path
 * @return none
 */
void geneticAlgorithm::possiblyMutate(int index) {
	if (10000*mutationRate/4 > (rand() % 10000)) {
		superMutate(index);
	} else if (10000*mutationRate > (rand() % 10000)) {
//		cout << "MUTATE" << endl;
		int gene1 = rand() % genes;
		int gene2 = rand() % genes;
		int temp = nextGen[index][gene1];
		nextGen[index][gene1] = nextGen[index][gene2];
		nextGen[index][gene2] = temp;
	}
	
	
}

/* mutates worst values in array, more rare then regular mutation
 * @param none
 * @return none
 */
void geneticAlgorithm::superMutate(int index) {
	int first = 0;
	int second = 0;
	int third = 0;
	for (int i = 0; i < genes - 1; i++) {
		int x = nextGen[index][i];
		int y = nextGen[index][i+1];
		if (distanceArray[x][y] > first) {
			first = i;
		} else if (distanceArray[x][y] > second) {
			second = i;
		} else if (distanceArray[x][y] > third) {
			third = i;
		}
	}
	int one = rand() % (genes - 1);
	int two = rand() % (genes - 1);
	int three = rand() % (genes - 1);
	int temp = nextGen[index][first];
	nextGen[index][first] = nextGen[index][one];
	nextGen[index][one] = temp;	
	temp = nextGen[index][second];
	nextGen[index][second] = nextGen[index][two];
	nextGen[index][two] = temp;
	temp = nextGen[index][third];
	nextGen[index][third] = nextGen[index][three];
	nextGen[index][third] = temp;				
	
}

/* @param chromosome1 and chromosome2 from current generation array
 * and index for position where there offspring will be placed in nextgen
 * array
 * @return will put completed recombinated chromosomes in index and index+1
 * in nextGen array
 * PMX, takes a portion of chromosome1 and chromosome 2 and switches the 
 * portions, properly modifying path
 */
void geneticAlgorithm::recombinate(int chromosome1, int chromosome2, int index) {
	int random = rand() % (int)((1 - crossOverRate)*1.5*genes);
	int numberMoved = random + ((1 - crossOverRate)*genes*(1/4));
	int start = rand() % (genes - numberMoved);
	vector<int> replace1;
	vector<int> dontReplace;
	vector<int> replace2;
	for (int i = start; i < start + numberMoved; i++) {
		bool inside = false;
		nextGen[index][i] = currentGen[chromosome1][i];
		nextGen[index + 1][i] = currentGen[chromosome2][i];
	
		for (int j = start; j < start + numberMoved; j++) {
			if (currentGen[chromosome1][i] == currentGen[chromosome2][j]) {
				inside = true;
				dontReplace.push_back(currentGen[chromosome1][i]);
				break;
			}
		}
		if (!inside) {
			replace1.push_back(currentGen[chromosome1][i]);
		}
	}
	for (int i = start; i < start + numberMoved; i++) {
		bool inside = false;
		for (int j = 0; j < dontReplace.size(); j++) {
			if (currentGen[chromosome2][i] == dontReplace[j]) {
				inside = true;
				break;
			}
		}
		if (!inside) {
			replace2.push_back(currentGen[chromosome2][i]);
		} 
	}

	int r1 = 0;
	int r2 = 0;
	for (int i = 0; i < genes; i++) {
		if (i == start) {
			i = start+numberMoved;
		}
		if (i >= genes) {
			break;
		}
		bool inside1 = false;
		bool inside2 = false;
		for (int j = 0; j < replace1.size(); j++) {
			if (replace1.size() > 0 && currentGen[chromosome2][i] == replace1[j]) {
				inside1 = true;
				nextGen[index][i] = replace2[r1];
				r1++;			
			}
			if (replace2.size() > 0 && currentGen[chromosome1][i] == replace2[j]) {
				inside2 = true;
				nextGen[index+1][i] = replace1[r2];
				r2++;			
			}					
		}
		if (!inside1) {
			nextGen[index][i] = currentGen[chromosome2][i]; 
		}
		if (!inside2) {
			nextGen[index+1][i] = currentGen[chromosome1][i]; 
		}		
		
		
	}
}


/* selects best percent of population based on selection rate and stores them
 * in the nextgeneration array for the nextGen.
 * @param none
 * @return none
 */
void geneticAlgorithm::selectBest() {
	int numberOfBest = populationSize*(1 - selectionRate);
	if (numberOfBest % 2 != 0) {
		numberOfBest--;
	}

	
	map<int,int> bestArray;
	int index = 0;
	for (int i = 0; bestArray.size() < numberOfBest && i < populationSize; i++, index++) { // fill best array
		if (bestArray.count(individualPopFitness[i]) == 0) {
			bestArray.insert(pair<int, int>(individualPopFitness[i],i));
		}
	}
	
	map<int,int>::iterator itr = --bestArray.end();	
	/* go through all values in fitness
	 * 
	 */
	for (int i = numberOfBest; i < populationSize; i++) {
		if (individualPopFitness[i] < itr->first && bestArray.count(individualPopFitness[i]) == 0) {
			bestArray.erase(itr);
			bestArray.insert(pair<int, int>(individualPopFitness[i],i));
			itr = --bestArray.end();			
		}
	}
	
	int i = 0;
	for (auto it = bestArray.begin(); it != bestArray.end(); ++it) {
		for (int j = 0; j < genes; j++) {
			nextGen[i][j] = currentGen[it->second][j];
		}
		if (i == 0) { // prints best result
			cout << "Best path distance: " << it->first << endl;
			cout << "Path: "; 
			printPath(it->second);
			cout << endl;
		}		
		
		i++;
	}
	
}

/* @param popSize, size of population
 * @return none
 */
geneticAlgorithm::geneticAlgorithm(unsigned int popSize,unsigned int maxGenerations)
	: populationSize(popSize), maxGen(maxGenerations) {
	srand(time(0));
			
	currentGen = new int*[populationSize];
	nextGen = new int*[populationSize];
	individualPopFitness = new double[populationSize];
	
	for (int i = 0; i < populationSize; i++) {
		currentGen[i] = new int[genes];
		nextGen[i] = new int[genes];
	}
	
	generateStartPopulation();
}

/* @param none
 * @return none
 * calculates fitness values from 1 to 100 for population and stores
 * those values in individualPopFitness array
 */
void geneticAlgorithm::calculateFitness() {
	int total = 0;
	for (int i = 0; i < populationSize; i++) {
		double chromosomeFitness = calculateChromosomeFitness(i);
		individualPopFitness[i] = chromosomeFitness;
		total += chromosomeFitness;
	}
	
	populationFitness = total;
}

/* calculates fitness level of individual at index
 * @param excepts index to get values from currentGen array 
 * @returns chromosome fitness of that individual
 */
double geneticAlgorithm::calculateChromosomeFitness(int index) {
	double indivFitness = distanceArray[0][currentGen[index][0]];
	for (int i = 0; i < genes - 1; i++) {
		int start = currentGen[index][i];
		int end = currentGen[index][i+1];
		indivFitness += distanceArray[start][end];
	}
	
	indivFitness += distanceArray[currentGen[index][genes-1]][0];
	
	return indivFitness;
}

/*
 * @param none
 * @return none
 */
void geneticAlgorithm::printFitness() {
	for (int i = 0; i < populationSize; i++) {
		cout << individualPopFitness[i] << endl;
	}
	cout << endl;
}

/* creates initial population
 * using the createIndividual function
 * puts all individuals into currentGen
 * @param none
 * @return none
 */
void geneticAlgorithm::generateStartPopulation() {
	vector<int> cities;
	
	for (int i = 1; i < genes + 1; i++) {
		cities.push_back(i);
	}	
	
	for (int i = 0; i < populationSize; i++) {
		createIndividual(cities,i);
	}
}

/* @param excepts a vector of cities and integer for location in currentGen
 * @return none
 * will put that vector at specific location
 */
void geneticAlgorithm::createIndividual(vector<int> cities, int individual) {
	for (int i = 0; i < genes; i++) {
		int val = rand() % cities.size();
		currentGen[individual][i] = cities[val];
		cities.erase(cities.begin() + val);		
	}
}

/* prints all possible paths in currentGen
 * @param none
 * @return none
 */
void geneticAlgorithm::printPopulation() {
	for (int i = 0; i < populationSize; i++) {
		for (int j = 0; j < genes; j++) {
			cout << currentGen[i][j] << " ";
		}
		cout << endl;
	}
}

/* prints all possible paths in nextGen
 * @param none
 * @return none
 */
void geneticAlgorithm::printPopulation2() {
	for (int i = 0; i < populationSize; i++) {
		for (int j = 0; j < genes; j++) {
			cout << nextGen[i][j] << " ";
		}
		cout << endl;
	}
}

/* testing purposes
 * @param none
 * @return none
 */
void geneticAlgorithm::deleteHalf() {
	vector<int> cities;
	
	for (int i = 1; i < genes + 1; i++) {
		cities.push_back(i);
	}	
	
	
	for (int i = 500; i < 10000; i++) {
		createIndividual(cities,i);
		
	}
	
	
}


/* Fills in paths ie: (x,y) = (y,x) for global distanceArray variable
 * @param none 
 * @return none
 */
void finishDistanceMatrix() {	
	largestDistance = 0;
	smallestDistance = 1000;
	for (int i = 0; i < 26; i++) {
		for (int j = i + 1; j < 27; j++) {
			if (i != j) {
				largestDistance = (distanceArray[i][j] > largestDistance) ? distanceArray[i][j] : largestDistance;
				smallestDistance = (smallestDistance > distanceArray[i][j]) ? distanceArray[i][j] : smallestDistance;
			}
			distanceArray[j][i] = distanceArray[i][j];
		}
	}
}

/* prints distance array testing purposes
 * @param none
 * @return none
 */
void printDistanceArray() {
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			cout << distanceArray[i][j] << " ";
		}
		cout << endl;
	}	
}




int main() {
	finishDistanceMatrix();
	
	geneticAlgorithm* test = new geneticAlgorithm(25000,200);
	test->run();
	
	return 0;
}
