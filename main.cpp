#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Input files : Truman text,statements text.
//Output : print answers,print complete sentences.
int main() {
	//NOT : linedan wordu dogru aktarma konusunda biraz sikinti var.
	ifstream statements,text;
	string line;
	string word;
	string answer;
	bool firstFound = false;
	string textWord;
	statements.open("statements.txt",ios::in);
	while (getline(statements, line)) {
		text.open("the_truman_show_script.txt", ios::in);

		cout << line << endl << endl;
		stringstream l(line);

		while (l >> word) {

			if (firstFound == false) {
				while (text >> textWord) {
					if (word != textWord) {
						continue;
					}
					else {
						firstFound = true;
						//text >> textWord;
						break;
					}
				}
				if (firstFound == false) {
					cout << "Statement NOT found." << endl;
					break;
				}
			}
			else {
			text >> textWord;
			if (word == "___") {
				answer = textWord;
				cout << "The answer is : " << answer << endl;
				break;
			}
			else if (word == textWord) {
			continue;
			}
			else {
			l.clear();
			l.seekg(0, ios::beg);
			firstFound = false;
			}
			}

		}
		cout << endl;

		text.close();

	}

	statements.close();

	return 0;
}