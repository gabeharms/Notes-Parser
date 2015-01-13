#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<Windows.h>
#include<vector>

using namespace std;

void printOutput ( string output );

#define file_name "Notes.txt"

int file_size;

int main () 
{
	int index = 0;			//For copying cstring into lowercase
	string data , input_string;
	const char * cstring2;	//Holds lower case of input and is added to lowercase
	bool first_read = true;


	ifstream file ( file_name, ios::binary | ios::ate );
	file_size = file.tellg();
	file.close();



	//Set up file stream
	ifstream input(file_name);

	//Make sure file opened
	if ( !input.is_open() ) { 
		cout << "Failed to open: " << file_name << "\n";
		system("pause");
		return 1;
	}


	cout <<"Welcome. Lets find your information";

	vector <string>normal;
	vector <string>lower;

	while ( 1 > 0 ) {

		char * normal_copy = (char*)calloc ( file_size, sizeof(char) );
		char * lowercase_copy = (char*)calloc( file_size, sizeof(char) );
		char * cstring1 = (char*)calloc ( file_size, sizeof(char) );
		string *output = new string;
		string *word = new string;
		string *word_temp = new string;

		cout << "\n\n-------------------------------------------------------\n----------------------------------------------------\nWhat are you Looking for: ";
		getline( cin, *word_temp );

		if ( (*word_temp).length() == 0)
			return 1;

		cout << "Results:\n";

		//Get lower case version of search word
		for ( int i = 0; i < (*word_temp).length(); i++ )
			*word += tolower((*word_temp)[i]);

		//Gather data from input file
		if ( first_read ) {
			do
			{

				input >> input_string;

				strcpy ( cstring1, input_string.c_str() );

				std::transform( input_string.begin(), input_string.end(), input_string.begin(), ::tolower );
				cstring2 = input_string.c_str();

				for ( int i = 0; i < input_string.length(); i++ ) {
					normal_copy[index] = cstring1[i];
					lowercase_copy[index] = cstring2[i];
					index++;
				}
				normal_copy[index] = '\n';
				lowercase_copy[index] = '\n';
				index++;

			} while ( !input.eof() );
		

		//Tokenize lowercase. if a string contains the search 
		//word, then it is added to the output string.
	
		char *temp = strtok( normal_copy, "&" ); 
		while ( temp != NULL ) {
			normal.push_back(temp);
			temp = strtok( NULL, "&" );
		}

		temp = strtok( lowercase_copy, "&" ); 
		while ( temp != NULL ) {
			lower.push_back(temp);
			temp = strtok( NULL, "&" );
		}

		}
		first_read = false;

		for ( int i = 0; i < lower.size(); i++ ) {
			if ( lower[i].find(*word) != string::npos ) 
				*output += normal[i] + "\n";
		}

		if ( (*output).length() != 0 ) 
			printOutput( *output );
		else 
			cout <<"\nNo Results Matched '" << *word_temp << "'\n\n";

		free ( cstring1 );
		free ( lowercase_copy );
		free ( normal_copy );
		free ( output );
		free ( word );
		free ( word_temp );

	}

	system("pause");
	return 1;
}

void printOutput ( string output ) {

	CONSOLE_SCREEN_BUFFER_INFO console;

	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &console );
	int columns = console.srWindow.Right - console.srWindow.Left + 1;

	int current_width = 0;
	cout << "\n";

	bool firstLine = true;
	bool secondLine = false;

	for ( int i = 0; i < output.length(); i++ ) {

		if ( i > 1 ) {
			if ( output[i] == '\n' && output[i-1] == '\n' && output[i-2] == '\n' ) {
				firstLine = true;
				cout << "\n";
				for ( int i = 0; i < ( columns -15 ); i ++ )
					cout << "-";
				cout << "\n";
				
			}				
		}
		
		
		if ( current_width > (columns - 15) && !firstLine && output[i] == 10 ) {
			cout << "\n\t";
			current_width = 0;
		}
		else if ( current_width > (columns - 15) && output[i] != '\n' && firstLine ) {
			cout << "\n";
			current_width = 0;
		}

	

		if ( output[i] != '\n' && !secondLine )
			cout << output[i];
		else if ( output[i] == '\n' && !secondLine )
			cout << " ";
		else if ( output[i] == '\n' && secondLine ) {
			cout << output[i];
			secondLine = false;
		}

		if ( i >1 ) {
			if ( i !=0 && i !=1 && output[i-2] != '\n' && output[i]== '\n' && firstLine ) {
				firstLine = false;
				secondLine = true;
				cout << "\n\t";
				current_width = 0;
			}
		}
		
		current_width++;
	}
	cout << "\n";
}