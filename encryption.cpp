// Name: Edgar Martinez
// Date: 01-07-20

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

const int offset = 13;

void caesarCipher (string file1, string file2) {

	// open a file and read from it 
	ifstream inputFile;
	inputFile.open(file1);

	if(inputFile.bad() == true) {
	
		cout << "ERROR: unable to read file.." << endl;
		inputFile.close();
	}
	else {
		
		// open file to write to 
		ofstream outputFile;
		outputFile.open(file2);

		// reset the state flags of inputFile so that we can enter the loop
		inputFile.clear();
		string str;

		while(inputFile.eof() != true) {
			
			getline(inputFile, str);
		
			// convert ASCII to int 
			for(int i = 0; i < str.length(); i++) {
						
				int position = (int) str[i]; 
				int encodedPosition = position + offset;
				
				if(encodedPosition > 126) {
					
					int newOffset = encodedPosition - 126;
					encodedPosition = 32 + newOffset; 
					outputFile << (char) encodedPosition;
				}	
				else {
					
					outputFile << (char) encodedPosition;
				}
			}

			outputFile << endl;
			
		}

		inputFile.close();
		outputFile.close(); 
	}

}

int main() {
	
	string file1, file2; 

	cout << "Input file: ";
		cin >> file1;
	cout << "Name of encrypted file: ";
		cin >> file2;

	caesarCipher(file1, file2);	

	return 0;
}
