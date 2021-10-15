#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <vector>

using namespace std;
ifstream input;
ofstream output;

string eraser(string line) {
	auto ending = line.end();

	advance(ending, -1);
	if (!isalpha(*ending))
		line.erase(ending);
	advance(ending, -1);
	if ((*ending) == ')')
		line.erase(ending);

	if (!isalpha(*line.begin()))
		line.erase(line.begin());

	return line;
}


void converter(list <string>& list_of_lists, list <string>& list_of_words) {

	list <string>::iterator it;

	for (it = list_of_lists.begin(); it != list_of_lists.end(); it++) {
		stringstream stream(*it);
		string t;
		while (stream >> t) {
			t = eraser(t);
			list_of_words.push_back(t);
		}
	}
	list_of_words.sort();

}

void printVector(vector < pair < string, unsigned int>>& vect, int result_size) {
	output << "General size: ," << result_size << "\n\n";
	output.precision(3);
	for (const auto& item : vect) {
		output << item.first << " ;"
			<< (double)item.second / result_size << " ;" << (double)item.second / result_size * 100 << "%" << endl;
	}
	output << endl;
}

void counter(list <string>& list_of_words, vector < pair < string, unsigned int>>& dictionary) {
	string buffer = list_of_words.front();
	unsigned int count = 1;

	list <string>::iterator it = list_of_words.begin();
	advance(it, 1);
	for (; it != list_of_words.end(); it++) {
		if (*it == buffer) {
			count++;
		}
		else {
			dictionary.push_back(std::make_pair(buffer, count));
			count = 1;
			buffer = *it;
		}
	}
	int res_size = list_of_words.size();
	sort(dictionary.begin(), dictionary.end(),
		[](const auto& x, const auto& y) { return x.second > y.second; });


	printVector(dictionary, res_size);
}


int main(int argc, char** argv) {

	input.open(argv[1]);
	output.open(argv[2]);

	if (!input)
	{
		cerr << "There is no input file" << endl;
		exit(1);
	}

	list <string> list_of_string;
	string buffer;

	while (getline(input, buffer)) {
		transform(buffer.begin(), buffer.end(), buffer.begin(), tolower); // to lower each symbol
		list_of_string.push_back(buffer);
	}



	list <string> list_of_words;
	converter(list_of_string, list_of_words);

	vector < pair<string, unsigned int> > dict;

	counter(list_of_words, dict);

}
