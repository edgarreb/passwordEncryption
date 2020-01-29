// Name: Edgar Martinez
// Date: 01-07-20

#include <iostream>
#include <string>
#include "encryption.h"
#include "decryption.h"

using namespace std;

int main() {

	// initialize random number generator
	srand(time(0));

	string flag;

	cout << "Type \"E\" to encrypt a file, or \"D\" to decrypt a file." << endl;
	cout << "(Encrypt/Decrypt): ";
		cin >> flag;

	if (flag == "E") {

		string file1, file2, file3, file4;

		cout << "Enter the name of the file to encrypt. " << endl;
		cout << "Filename: ";
			cin >> file1;
		cout << "Enter the name of the file where you would like to store the encrypted data." << endl;
		cout << "Filename: ";
			cin >> file2;

		file3 = "offsetFile.txt";
		file4 = "positionFile.txt";

		if(randomOffset(file1, file2, file3, file4) == true) {

				cout << "Encryption completed successfully." << endl;
		}
		else {

			cout << "ERROR: unable to encrypt file" << endl;
		}
	}
	else if (flag == "D") {

		string file1, file2, file3, file4;

		cout << "Enter the name of the file to decrypt." << endl;
		cout << "Filename: ";
			cin >> file1;
		cout << "Enter the name of the file where you would like to store the decrypted data." << endl;
		cout << "Filename: ";
			cin >> file2;

		file3 = "offsetFile.txt";
		file4 = "positionFile.txt";

		if(randomDecrypt(file1, file2, file3, file4) == true) {
			
			cout << "Decryption completed successfully." << endl;
		}
		else {

			cout << "ERROR: unable to encrypt file" << endl;
		}
	}
	else {

		cout << "ERROR: " << "\"" << flag << "\" " << "command not found" << endl;
	}

	return 0;
}
