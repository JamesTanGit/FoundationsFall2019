#include <iostream>
#include <vector>
#include <string>
using namespace std;

string GenerateNthString(vector<char> alphabet, int number) {
	int numberOfChars = 1, answer = alphabet.size(), rowIndex = 1, exponent = 1;
	string stringOverAlphabet;
	if (number == 0) {
		return " ";
	}
	while (number > rowIndex + answer - 1) {
		numberOfChars++;
		rowIndex += answer;
		answer = pow(alphabet.size(), numberOfChars);
	}
	for (int i = 0; i < numberOfChars; i++) {
		int j = 0;
		while ((rowIndex + pow(alphabet.size(), numberOfChars - exponent)) <= number) {
			rowIndex += pow(alphabet.size(), numberOfChars - exponent);
			j++;
		}
		exponent++;
		stringOverAlphabet += alphabet.at(j);
	}
	return stringOverAlphabet;
}

int main() {
	vector<char> alphabet;
	alphabet.push_back('a');
	alphabet.push_back('b');
	alphabet.push_back('c');
	char symbol;
	int number;
	cout << "Enter a number: ";
	cin >> number;
	string stringOverAlphabet = GenerateNthString(alphabet, number);
	cout << "\"" << stringOverAlphabet << "\"" << endl;
	return 0;
}
