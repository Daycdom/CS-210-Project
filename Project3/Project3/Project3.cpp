#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;



class ItemTracker {
public:
	ItemTracker() { // constructor
		ifstream input(inputFile); // open input file
		string item;
		if (!input) { // incase input file cant open
			cout << "input could not open";
		}
		while (input >> item) { // write to the map
			itemCount[item]++;
		}
		input.close(); // close the file


		ofstream output(outputFile); // write out to the data file
		output.open(outputFile, ios::app);
		for (auto count = itemCount.begin(); count != itemCount.end(); count++) {
			output << count->first << " " << count->second << endl;
		}
		output.close();
	}

	int GetFrequency(string item) { // get the frequency
		return itemCount[item]; // returns int for frequency
	}

	void printListNumbered() {
		for (auto count = itemCount.begin(); count != itemCount.end(); count++) { // loop from the start to the end
			cout << count->first << " " << count->second << endl; // print the list in a numbered format
		}
	}

	void printListHistogram() {
		for (auto count = itemCount.begin(); count != itemCount.end(); count++) { // loop from the beginning to end again
			cout << count->first << " "; // print the name first
			for (int i = 0; i < count->second; i++) {
				cout << "*"; // then the asterisks
			}
			cout << endl;
		}
	}

private:
	string outputFile = "frequency.dat"; // set the names for the output and input files
	const string inputFile = "CS210_Project_Three_Input_File.txt";
	map<string, int> itemCount; // create the map
};

void PrintMenu() { // make a print menu function to keep everything organizied
	cout << "Menu:" << endl;
	cout << "1. Search for an item" << endl;
	cout << "2. Print item list with frequency by number (i.e. Item: Banana Count: 3)" << endl;
	cout << "3. Print item list with frequency by histogram (i.e. Banana ***)" << endl;
	cout << "4. Exit the program" << endl;
	cout << "Please enter a number (1-4)" << endl;
};

int main() {
	cin.exceptions(ios::failbit); // create an exception mask i believe its called
	ItemTracker groceryItem; // create a new item

	int userInput; // prepare the variable user input
	ofstream outfile("frequency.dat"); 
	do {  // do while loop to end when 4 is chosen
		PrintMenu(); 
		try {  // try catch statement to catch if the variable is an incorrect type
			cin >> userInput;
		}
		catch (ios_base::failure& e) {
			userInput = 0; // set the input to a number that would go into the default case
			cin.clear();
			cin.ignore(100, '\n');
		}
		switch (userInput) {  // use a switch with the input 
		case 1:
		{
			string gItem;
			cout << "Enter the item you want to search for." << endl;
			cin >> gItem;
			int frequency = groceryItem.GetFrequency(gItem);  // get the frequency of gItem
			cout << gItem << " appears " << frequency << " times." << endl;
			break;
		}
		case 2:
		{
			groceryItem.printListNumbered();
			break;
		}
		case 3:
		{
			groceryItem.printListHistogram();
			break;
		}
		case 4:
		{
			cout << "Goodbye." << endl;
			break;
		}
		default:
		{
			cout << "Invalid input, try again." << endl;
			break;
		}
		}

	} while (userInput != 4);
	return 0;
}