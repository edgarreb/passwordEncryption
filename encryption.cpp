#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

bool caesarCipher(string file1, string file2) {

	// a predetermined offset is used for ceaserCipher function call
	const int offset = 13;

	// open a file and read from it
	ifstream inputFile;
	inputFile.open(file1);

	if(inputFile.bad() == true) {

		cout << "ERROR: unable to read file.." << endl;
		inputFile.close();
	}
	else {

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

	return true;
}

bool randomOffset(string originalFile, string encryptedFile, string offsetFile, string positionFile) {

	ifstream originalInput;
	originalInput.open(originalFile);

	if(originalInput.bad() == true) {

		cout << "ERROR: unable to read file.." << endl;
		originalInput.close();
	}
	else {

		// open files to write to
		ofstream encryptedOutput;
		encryptedOutput.open(encryptedFile);

		ofstream offsetOutput;
		offsetOutput.open(offsetFile);

		ofstream positionOutput;
		positionOutput.open(positionFile);

		// stores lines from the original file
		string unencryptedLine;

		// used for math operations to encode a single character
		int encodedPosition;
		int randomOffset;
		int updatedOffset;

		// used to store random values
		int additionalCharacters;
		int hiddenPosition;
		int randomCharacter;

		// used to set ranges
		const int offsetRange = 127;
		const int characterRange = 10;

		while(originalInput.eof() != true) {

			getline(originalInput, unencryptedLine);

			if(originalInput.eof() != true) {

				// write the number of initial chars in a given line
				positionOutput << unencryptedLine.length() << endl;

				if(unencryptedLine.length() > 0) {
					// encryption is done here
					for(int i = 0; i < unencryptedLine.length(); i++) {

						// generate a random offset in range from 0 - 126
						randomOffset = rand() % offsetRange;
						offsetOutput << randomOffset << endl;

						// figure out how much down the table to move
						encodedPosition = static_cast<int>(unencryptedLine[i]) + randomOffset;

						// make sure we are in table range
						while(encodedPosition > 126) {

							updatedOffset = encodedPosition - 126;
							encodedPosition = 32 + updatedOffset;
						}

						string encodedString;

						// generate additional chars and hidden positon (not working test 0)
						additionalCharacters = rand() % characterRange;
						positionOutput << additionalCharacters << " ";

						if(additionalCharacters != 0) {
							hiddenPosition = rand() % additionalCharacters;
						}
						else {
							hiddenPosition = 0;
						}
						positionOutput << hiddenPosition << endl;

						// create a string of random additional chars
						for(int j = 0; j < additionalCharacters; j++) {

							// generate values between 32 - 126 (possible chars from ASCII table)
							randomCharacter = (rand() % 95) + 32;
							encodedString.append(1, static_cast<char>(randomCharacter));
						}

						string encodedChar(1, static_cast<char>(encodedPosition));

						encodedString.insert(hiddenPosition, encodedChar);
						encryptedOutput << encodedString;

					}

					encryptedOutput << endl;
				}
				else {

					// output random garbage
					for(int i = 0; i < (rand() % 50) + 50; i++) {

						encryptedOutput << static_cast<char>( (rand() % 95) + 32);
					}

					encryptedOutput << endl;
				}
			}
		}

		encryptedOutput.close();
		offsetOutput.close();
		positionOutput.close();
	}

	originalInput.close();

	return true;
}
