#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>
#include <ctime>
using namespace std;



//Global Bank of possible / valid gene mutations
//vector<string> bank = {"ABA", "ABC", "CBA", "CCC"}; //results in 2 gene mutations with start: AAA, end: ABC
vector<string> bank = {"ABAAAAAA", "ABAAGAAC", "ABAAAAAC", "ABATGAAC","ABGTGAAC","ABGGGGGG" };// 5 gene mutations start: AAAAAAAA, end ABGTGAAC

// check how many characters are different between two strings
//Must have only one character different to be valid
int countDifference(const string &str1, const string &str2) {
    int count = 0;  // counter 
    for(int i = 0; i < str1.length(); i++) {
        if(str1[i] != str2[i]) { //different gene strings
            ++count;
            if(count > 1) { //return if count is > 1 to stop function (geneString not what we want)
                return count;
            }
        }
    }
    return count;
}
int minMutation(string start, string end) {
    // 		awe use pair<string, int> :
    //     string: the gene string we push into queue
    //     int: minimal gene mutation number we pair to each string
    queue<pair<string,int>> geneQue; // Enque our queue called geneQue
    geneQue.push({start, 0}); // with start string and min gene mutation of 0
    
    const int bankSize = bank.size(); // declare a constant int variable that holds the size of our gene bank
    vector<bool> isUsed(bankSize, false); //Initialize a vector of booleans to keep track of which elements in banks have been used
    
    //Our BFS algorithm
    while(!geneQue.empty()) {
        const string gene = geneQue.front().first; //Have a string that contains first string in geneQue
        const int min = geneQue.front().second;	//Have this int gather our min Gene value  
        //> find ans
        //if(end.compare(gene) == 0) { //if the gene string we are comparing right now = end string, end program
        if(gene == end){  
            return min; //return minGene number
        }
        
        //>> put all posibile string into queue
        for(int i = 0; i < bankSize; i++) {
            if(!isUsed[i] && countDifference(gene, bank[i]) == 1) { // check if there is only one char difference
                geneQue.push({bank[i], min+1}); //If valid, push new into stack after increasing our min value
                isUsed[i] = true; //Set our boolean vector from beginning to set to as used (True)
            }
        }
        geneQue.pop(); //pop off the visited gene string (node)
    }
    //End of BFS algorithm
    return -1; //Something went wrong
}

//Calls the minMutation function given start and end strings of DNA
//Has a timer of runtime that calculates the average time of minMutation function 
int main(int argc, const char * argv[]) {
	cout << endl;
	int mutation;
	double value = 0.0; //calculate the total time it takes to run minmutation 100 times
	string startGene, endGene;
	startGene = argv[1];
	endGene = argv[2];

	for(int i = 0; i < 100; i++){ //Run 100 times to get average time in ms
		int start = clock();
		mutation = minMutation(startGene, endGene);
		int stop = clock();
		value += (stop-start)/double(CLOCKS_PER_SEC)*1000;	 // sum all the time values
	}	

	cout << "Start Gene: " << startGene << endl; //print start gene
	cout << "End Gene: " << endGene << endl;	//print end gene
	cout << "==================== " << endl;

	cout << "Bank" << endl;	//Printing all the elements in the bank below		
	int counter = 1;	
	for(auto i : bank) {cout << "Element number: "<< counter << " || "<< "Gene: " << i << endl; counter++;}

	cout << "==================== \n" << endl;
	cout << "Minimum Gene Mutation: " << mutation << endl; //print min gene number
	cout << "Number of gene strings in bank: " << bank.size() << endl; //print number of genes in bank
	cout << "Average Runtime in ms: " << value / 100 << endl;	//print the calculated average runtime in ms

}
