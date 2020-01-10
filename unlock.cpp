// Name: Edgar Martinez
// Date: 01-09-20

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

// offset used to encrypt/decrypt
const int offset = 13;

void decrypt(string file1, string file2) {

	ifstream inputFile;
	inputFile.open(file1);

	ofstream outputFile;
	outputFile.open(file2);

	if(inputFile.bad() == true) {
		
		cout << "ERROR: Unable to read file.." << endl;
	}
	else {
	
		string line;
		
		while(inputFile.eof() != true) {
			
			getline(inputFile, line);
	
			for(int i = 0; i < line.length(); i++) {
				
				char tempChar = (char) line[i];
				int temp = (int) tempChar;
				
				int decodedPosition = temp - offset;

				if(decodedPosition < 32) {
					
					int newOffset = 32 - decodedPosition;
					int newPosition = 126 - newOffset;
					outputFile << (char) newPosition;
				}
				else {

					outputFile << (char) decodedPosition;
				}
			}
			
			outputFile << endl; 
		}	

	}

	inputFile.close();
	outputFile.close();

}

int main() {

	string file1, file2;
	cout << "Input File: "; 
		cin >> file1;
	cout <<	"Output File: ";
		cin >> file2;

	decrypt(file1, file2);

	return 0;
}
