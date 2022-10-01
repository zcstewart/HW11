//Homework 11

/*
 *  Filename:           main.cpp
 * 
 *  Purpose:            The purpose of this program is to read in numbers in
 *                      a text file. The program will determine the total
 *                      number of values in the data file, the total number
 *                      of even values, the total number of odd values, the
 *                      total number of zeros, the sum of the numbers, and
 *                      the average of the numbers. 
 * 
 * 
 *  Author:             Zachary Charles Stewart
 *  Student ID:         105903414
 *  Date:               1/30/2017 13:50 PST
 */

#include<iostream>      //<< >>
#include<iomanip>       //get_money/put_money function
#include<cstdlib>       //exit()
#include<fstream>       //ifstream, ofstream

using namespace std;

// Initialize all input variables to 0
void initialize(int &totalCount, int &evenCount, int &oddCount, 
                 int &zeroCount, int &totalSum, double &totalAverage);

// Get the current number from the data file
// Print the number to the screen and the data file 
void getNumber(int &num, ifstream &inputFile, ofstream &outputFile);

// Classify the number as even, odd, and/or zero.
// Keep track of the tally for each number.
void classifyNumber(int num, int &evenCount, int &oddCount, int &zeroCount);

// Print the results of the classification of the numbers
// to the output data file.
void printResults(int totalCount, int evenCount, int oddCount, int zeroCount, 
                  int totalSum, double totalAverage, ofstream &outputFile);


int main(int argc, char** argv)
{
    //Variable Declaration
    int num = 0;
    int num_even, num_odd, num_zero, num_sum, num_total;
    double num_average = 0;

    //fstream variable definition
    ifstream inFile;
    ofstream outFile;
    
    //Initialize variables for use in program
    initialize(num_total, num_even, num_odd, num_zero, num_sum, num_average);
    
    //Open input file
    inFile.open("Numbers.txt");
    //Open output file
    outFile.open("Output.txt");

    //Test for present input file
    if(!inFile)
    {
        cout << "Cannot open input file \'Numbers.txt\'.";
        cout << " Program Terminating." << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << "Processing Data..." << endl;
    cout << "Numbers Read from File" << endl << endl;
    
    //Test for valid data on input file
    if(inFile.eof())
    {
        cout << "No valid input. Please check input file." << endl;
        exit(EXIT_FAILURE);
    }
    
    //While loop to cycle through file
    while(!inFile.eof())
    {
        //Get Number function
        getNumber(num, inFile, outFile);
        
        //Break if last number was EOF
        if(inFile.peek() == EOF)
        {
            break;
        }
        
        //Classify Number function
        classifyNumber(num, num_even, num_odd, num_zero);
        
        //Increment total number of 
        num_total++;
        num_sum += num;
        
        if(num_total % 10 == 0)
        {
            cout << endl;
            outFile << endl;
        }
    }
    //Compute average, static cast as double to avoid integer division
    num_average = static_cast<double>(num_sum) / num_total;
    
    //Print results of number classification
    printResults(num_total, num_even, num_odd, num_zero, num_sum, 
                 num_average, outFile);

    //Close files
    inFile.close();
    outFile.close();
    
    //Terminate program upon successful completion
    exit(EXIT_SUCCESS);
}

//FUNCTION DEFINITIONS

//Initialize all variables to zero
void initialize(int &totalCount, int &evenCount, int &oddCount, 
                 int &zeroCount, int &totalSum, double &totalAverage)
{
    totalCount = 0;
    evenCount = 0;
    oddCount = 0;
    zeroCount = 0;
    totalSum = 0;
    totalAverage = 0;    
}

//Get the current number from the data file
//Print the number to the screen and the data file
void getNumber(int &num, ifstream &inputFile, ofstream &outputFile)
{
    //Read in number
    inputFile >> num;
    
    if(inputFile.peek() != EOF)
    {
        //Output number to screen
        cout << setw(5) << num;
    
        //Write number to file
        outputFile << setw(5) << num;
    }
}

//Classify the number as even, odd, and/or zero
void classifyNumber(int num, int &evenCount, int &oddCount, int &zeroCount)
{
    if(num == 0)
    {
        zeroCount++;
        evenCount++;
    }
    else if((num % 2) == 0)
    {
        evenCount++;
    }
    else
    {
        oddCount++;
    }
}

//
void printResults(int totalCount, int evenCount, int oddCount, int zeroCount, 
                  int totalSum, double totalAverage, ofstream &outputFile)
{
    //Output statements to user
    outputFile << endl << endl;
    outputFile << "Number of values in data file: " << totalCount << endl;
    outputFile << "Total number of evens: " << evenCount << endl;
    outputFile << "Total number of odds: " << oddCount << endl;
    outputFile << "Total number of zeros: " << zeroCount << endl;
    outputFile << "Sum of the numbers: " << totalSum << endl;
    outputFile << "Average of numbers: " << fixed << showpoint;
    outputFile << setprecision(1) << totalAverage << endl;
}