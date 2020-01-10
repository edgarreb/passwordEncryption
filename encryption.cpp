// Name: Edgar Martinez
// Date: 01-07-20

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void caesarCipher (string file1, string file2, string file3) {

	// open a file and read from it 
	ifstream inputFile;
	inputFile.open(file1);

	if(inputFile.bad() == true) {
	
		cout << "ERROR: unable to read file.." << endl;
		inputFile.close();
	}
	else {
		
		// open filse to write to 
		ofstream outputFile;
		outputFile.open(file2);

		ofstream outputFile2;
		outputFile2.open(file3);

		// reset the state flags of inputFile so that we can enter the loop
		inputFile.clear();
		string str;
		string hexData;

		while(inputFile.eof() != true) {
			getline(inputFile, str);
			cout << "ASCII: " << str << endl;
		
			// convert ASCII to Hex
			ostringstream os;

    			for (int i=0; i<str.length() ; i++) {
        			os << hex << uppercase << (int) str[i];
			}

    			hexData = os.str();
			//cout << "Hex: " << hexData << endl;
			outputFile << hexData << endl;
	
			// convert the hex string and store it in an array 
			int sizeOfArray = hexData.length() / 2;
			//cout << "size of array: " << sizeOfArray << endl;
			
			int shiftedPosition;
			int offset = 13;
			int* ptr = NULL;
			ptr = new int[sizeOfArray];
			
			for(int i = 0; i < hexData.length(); i += 2) {
			
				string hexParse = hexData.substr(i,2);
				//cout << "Parse: " << hexParse << endl;
				
				ptr[i/2] = stoi(hexParse, 0, 16);
				//cout << "int value: " <<  ptr[i/2] << endl;
				
				shiftedPosition= ptr[i/2] += offset;
				
				if(shiftedPosition > 126) {
				
					int newOffset = shiftedPosition - 126;
					ptr[i/2] = 32 + newOffset;
				}
				else {
			
					ptr[i/2] = shiftedPosition;
				}
				
				//cout << "shift: " << ptr[i/2] << endl;
			}

			for(int j = 0; j < sizeOfArray; j++) {
				
				outputFile2 << (char)ptr[j];
			}
			
			outputFile2 << endl;
			delete[] ptr;	
	
		}

		inputFile.close();
		outputFile.close(); 
		outputFile2.close();
	}
}

int main() {
	
	string file1, file2, file3; 

	cout << "Input file: ";
		cin >> file1;
	cout << "Hex file name: ";
		cin >> file2;
	cout << "Output file: ";
		cin >> file3;

	caesarCipher(file1, file2, file3);	

	return 0;
}
