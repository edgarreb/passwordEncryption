// Name: Edgar Martinez
// Date: 01-07-20

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

// a predetermined offset is used for ceaserCipher function call
const int offset = 13;

const int additionalChars = 3;

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

void randomOffset(string originalFile, string encryptedFile, string keyFile) {

	// open a file and read from it
	ifstream inputFile;
	inputFile.open(originalFile);

	if(inputFile.bad() == true) {

		cout << "ERROR: unable to read file.." << endl;
		inputFile.close();
	}
	else {

		// open file to write to
		ofstream outputFile;
		outputFile.open(encryptedFile);

		ofstream outputFile2;
		outputFile2.open(keyFile);

		// reset the state flags of inputFile so that we can enter the loop
		inputFile.clear();
		string tempString;

		int newOffset;
		int randomOffset;
		int position;
		int encodedPosition;

		while(inputFile.eof() != true) {

			getline(inputFile, tempString);

			// convert ASCII to int
			for(int i = 0; i < tempString.length(); i++) {

				// will generate values from 0 - 126
				randomOffset = rand() % 127;

				position = (int) tempString[i];
				encodedPosition = position + randomOffset;

				// write the random offset to the keyFile
				outputFile2 << randomOffset << endl;

				while(encodedPosition > 126) {

					newOffset = encodedPosition - 126;
					encodedPosition = 32 + newOffset;
					//outputFile << (char) encodedPosition;
				}

				outputFile << (char) encodedPosition;

				}

				outputFile << endl;
			}

			outputFile.close();
			outputFile2.close();

		}

		inputFile.close();

}

int main() {

	// initialize random number generator
	srand(time(0));

	string file1, file2, file3;

	cout << "Original File: ";
		cin >> file1;
	cout << "Encrypted File: ";
		cin >> file2;
	cout << "Key File: ";
		cin >> file3;

	randomOffset(file1, file2, file3);

	return 0;
}
