#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Input files : Truman text,statements text.
//Output : print answers,print complete sentences.
int main() {
	//NOT : linedan wordu dogru aktarma konusunda biraz sikinti var.
	ifstream statements, text;
	string line;
	string word;
	string answer;
	bool firstFound = false;
	bool spaceFound = false;
	string textWord;
	statements.open("statements.txt", ios::in);
	while (getline(statements, line)) {
		answer = "";
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
				int counter = 0 ;//Kelimemizin ilk boşluğunun indexini tutan değişken değer
				for (int i = 0; i < word.length(); i++) {
					if (word[i] == '_') {
						counter = i;
						spaceFound = true;
						break;
					}
				}
				if (spaceFound) {
					if (word == "___") {
						answer = textWord;
						cout << answer << endl;
					}
					else if (counter == 0) {
						//word = ___!...he's textWord=Marilyn!...he's
						int k = word.length() - 3;
						for (int i = 0; i < textWord.length() - k; i++) {
							answer += textWord[i];
						}
						cout << answer << endl;
					}
					else if (counter + 3 == textWord.length()) {
						for (int i = counter; i < textWord.length(); i++) {
							answer += textWord[i];
						}
						cout << answer << endl;
					}
					else {
						string temp = "";
						for (int i = counter; i < textWord.length(); i++) {
							temp += textWord[i];
						}
						int k = word.length() - 3 - counter;
						for (int i = 0; i < temp.length() - k; i++) {
							answer += temp[i];
						}
						cout << answer << endl;
					}
					spaceFound = false;
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
