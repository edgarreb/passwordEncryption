// Name: Edgar Martinez
// Date: 01-09-20

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

void decrypt(string file1, string file2) {

	// offset used to encrypt/decrypt
	const int offset = 13;

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

void randomDecrypt(string encryptedFile, string keyFile, string unencryptedFile) {

	ifstream inputFile;
	inputFile.open(encryptedFile);

	ifstream inputFile2;
	inputFile2.open(keyFile);

	ofstream outputFile;
	outputFile.open(unencryptedFile);

	if( (inputFile.bad() == true) || (inputFile2.bad() == true) ) {

		cout << "ERROR: Unable to read file.." << endl;
	}
	else {

		string line;
		string offsetLine;

		char tempChar;
		int randomOffset;
		int encodedPosition;
		int decodedPosition;

		while(inputFile.eof() != true) {

			getline(inputFile, line);

			for(int i = 0; i < line.length(); i++) {

				getline(inputFile2, offsetLine);

				tempChar = (char) line[i];
				encodedPosition = (int) tempChar;
				randomOffset = stoi(offsetLine);
				cout << randomOffset << endl;

				decodedPosition = encodedPosition - randomOffset;

				while(decodedPosition < 32) {

					if(decodedPosition >= 0) {

						randomOffset = 32 - decodedPosition;
						decodedPosition = 126 - randomOffset;
					}
					else {
						randomOffset = abs(decodedPosition) + 32;
						decodedPosition = 126 - randomOffset;
					}
					/*
					randomOffset = 32 - decodedPosition;
					decodedPosition = 126 - Offset;
					//outputFile << (char) newPosition; */
				}

				outputFile << (char) decodedPosition;
			}

			outputFile << endl;
		}

	}

	inputFile.close();
	inputFile2.close();
	outputFile.close();

}

int main() {

	string file1, file2, file3;

	cout << "Encrypted File: ";
		cin >> file1;
	cout <<	"Key File: ";
		cin >> file2;
	cout << "Unencrypted File: ";
		cin >> file3;

	randomDecrypt(file1, file2, file3);

	return 0;
}
