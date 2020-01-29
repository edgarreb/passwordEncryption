// Name: Edgar Martinez
// Date: 01-09-20

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

bool decrypt(string file1, string file2) {

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

	return true;
}

bool randomDecrypt(std::string encryptedFile, std::string unencryptedFile, std::string offsetFile, std::string positionFile) {

	// open the files to read from
	ifstream encryptedInput;
	encryptedInput.open(encryptedFile);

	ifstream offsetInput;
	offsetInput.open(offsetFile);

	ifstream positionInput;
	positionInput.open(positionFile);

	if( (encryptedInput.bad() == true) || (offsetInput.bad() == true) || (positionInput.bad() == true) ) {

		cout << "ERROR: Unable to read from files.." << endl;
	}
	else {

		ofstream decryptedOutput;
		decryptedOutput.open(unencryptedFile);

		string encodedLine;
		string offsetKey;
		string charactersPerLine;
		string hiddenPosition;
		string additionalCharacters;
		string key;

		int randomOffset;
		int encodedPosition;
		int decodedPosition;

		while(encryptedInput.eof() != true) {

			getline(encryptedInput, encodedLine);

			if(encryptedInput.eof() != true) {

				// get the number of characters on our current line that we already read
				getline(positionInput, charactersPerLine);

				if(stoi(charactersPerLine) == 0) {
					decryptedOutput << endl;
				}
				//if(stoi(charactersPerLine) != 0) {
				else {

					string* entriesPointer = new string[stoi(charactersPerLine)];

					int breakPoint = 0;

					for(int i = 0; i < stoi(charactersPerLine); i++) {

						// grab the offset value
						getline(offsetInput, offsetKey);
						randomOffset = stoi(offsetKey);

						// store additional character and hidden position pair of values
						getline(positionInput, key);
						additionalCharacters = key.substr(0, key.find(" "));
						hiddenPosition = key.substr(key.find(" ") + 1);

						// extract encoded character from the additional random characters
						entriesPointer[i] = encodedLine.substr(breakPoint + stoi(hiddenPosition), 1);

						// optimize later
						char testChar = static_cast<char>(entriesPointer[i][0]);
						encodedPosition = static_cast<int>(testChar);

						// decoding done here
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

		                }

						// update breakpoint
						breakPoint = breakPoint + stoi(additionalCharacters) + 1;

						decryptedOutput << static_cast<char>(decodedPosition);
					}

					decryptedOutput << endl;
		            delete[] entriesPointer;
				}
			}
		}

		decryptedOutput.close();
	}

	encryptedInput.close();
	offsetInput.close();
	positionInput.close();

	return true;
}
