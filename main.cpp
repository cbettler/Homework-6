//
//  main.cpp
//  Homework 6
//
//  Created by Carlee Bettler on 4/21/16.
//  Copyright (c) 2016 Carlee Bettler. All rights reserved.
//

#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Declaring my functions
int* extraction_method(string A[], int arraySize, int ProbeNum);
void writeOutFile(int A[], int size);


int main() {
    string file1name = "/Users/carleebettler/Documents/Comp 271/Unit 3/everybodys_socials.txt" ;
    
    string line, line2;
    
    int input;
    
    int i;
    
    vector<string> SSNums;
    
    
    //Geting input from the file. I push its numbers onto a vector called SSNums
    ifstream file1(file1name);
    
    while(!file1.is_open()){
        cout << "Not able to open file. Please enter another file name: "<< endl;
        
        getline(cin, file1name);
        
        file1.open(file1name);
    }
    
    
    if (file1.is_open())
    {
        while(!file1.eof())
        {
            getline (file1,line);
            
            istringstream ss(line);
            
            while(getline(ss, line2, ',')) {
                SSNums.push_back(line2);
            }
        }
    }
    
    file1.clear();
    
    file1.close();
    
    
    //I add the contents of my vector to a string array called SSoriginal of the vector's size
    string* SSoriginal = new string[SSNums.size()];
    
    for(i = 0; i< SSNums.size(); i++) {
        SSoriginal[i] = SSNums[i];
    }
    
    //I am prompting the user for a number for quadratic probing. Note: This conditional statement freaks out if the user enters a value too big for the while statement to handle... it became infinite, which it didn't do when I changed the parameter for a smaller max number. It also doesn't have a condition for non numerical answers. So I'm assuming my user is smart enough to enter a number, and it is not a number if the billions
    cout<<"Please enter a number between 0 and 450000000 for quadratic probing"<<endl;
    cin >> input;
    
    while(!(input > 0 && input < 450000000)) {
        cout<<"Please enter a number between 0 and 450000000 for quadratic probing"<<endl;
        cin >> input;
    }
    
    
    //Implementing my functions
    int* HashSlingingSlasher = extraction_method(SSoriginal, SSNums.size(), input);
    writeOutFile(HashSlingingSlasher, SSNums.size());
    
    return 0;
}


int* extraction_method(string A[], int arraySize, int ProbeNum) {
    
    //Declaring my variables
    int i, j;
    
    string* keyStrings = new string[arraySize];
    
    int Keys[arraySize];
    
    int SSNumsInts[arraySize];
    
    int HashTable[arraySize];
    
    
    //I am creating an array of keys by parsing an array of SS Number strings
    for(i = 0; i< arraySize; i++) {
        for(j = 0; j< 9; j++) {
            keyStrings[i] = A[i][2];
            keyStrings[i] += A[i][4];
            keyStrings[i] += A[i][6];
            keyStrings[i] += A[i][7];
        }
    }
    
    
    //I am parsing my string arrays of keys and SS numbers into arrays of ints
    for(i = 0; i< arraySize; i++) {
        SSNumsInts[i] = stoi(A[i]);
    }
    
    for(i = 0; i<arraySize; i++){
        Keys[i] = stoi(keyStrings[i]);
    }
    
    //Dealing with collisions
    for(i = 0; i<arraySize; i++){
        //If there is nothing in the hash table at that key value, I set it equal to the SSNum at the same index the array of SS numbers
        if(HashTable[Keys[i]] == 0){
            HashTable[Keys[i]] = SSNumsInts[i];
        }
        else{
            //Otherwise, I create a temp index called index of the key value at that position. While the value in the hash table at the index of index is empty.
            //If not, it reassigns index's value using the quadratic probing formula and the probe number taken in the from the user.
            //If that new index value still isn't empty, it increments the probe number and reassigns the index value using the same quadratic probing formula but a new probe number.
            //If keeps doing this until it finds a space that is not empty and then assigns the a SS number to that new index.
            
            int index=Keys[i];
            
            while(HashTable[index] != 0) {
                
                index=(Keys[i] + ProbeNum*ProbeNum)%arraySize;
                
                if(HashTable[index] != 0) {
                    ProbeNum++;
                }
                else break;
            }
            
            HashTable[index] = SSNumsInts[i];
        }
    }
    
    
    //Printing my hashtable for testing/comparison purposes
    for(i = 0; i<arraySize; i++){
        cout<<"Hashtable result " << HashTable[i]<<endl;
    }
    
    return HashTable;
}


//This function is for writing my hash table to a file
void writeOutFile(int A[], int size){
    ofstream readFile1;
    readFile1.open("hashed_socials.txt");
    
    readFile1<< "Hash Table Results: \n";
    
    for(int i=0; i< size; i++){
        if(i != (size-1)) {
            readFile1<< A[i]<< ",";
        }
        else{
            readFile1<<A[i];
        }
    }
    
}





