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
	int spaceIndex = 0;
	bool spaceFound = false;
	bool firstFound = false;
	bool initialWord = true;
	string textWord;
	statements.open("statements.txt", ios::in);
	while (getline(statements, line)) {
		text.open("the_truman_show_script.txt", ios::in);
		firstFound = false;
		spaceFound = false;
		answer = "";

		cout << line << endl << endl;
		stringstream l(line);

		while (l >> word) {

			for (int i = 0; i < word.length(); i++) {
				if (word[i] == '_') {
					spaceIndex = i;
					spaceFound = true;
					break;
				}
			}

			if (firstFound == false) {
				while (text >> textWord) {

					if (spaceFound == true) {
						//Ilk kelimemiz bosluk ise ->
					}
					else { //word = Truman textWord = THE  //word = God, textWord = ...God,
						if (word != textWord) {  //word.length() < textWord.length()
							if (word.length() < textWord.length()) {
								firstFound = true;
								for (int i = 1; i <= word.length(); i++) {
									if (textWord[textWord.length() - i] != word[word.length() - i]) {
										firstFound = false;
										break;
									}
								}
								if (firstFound == false) {
									continue;
								}
								else {
									break;
								}
							}
						}
						else {
							firstFound = true;
							break;
						}
					}

				}
				if (firstFound == false) {
					cout << "Statement NOT found." << endl;
					break;
				}
			}
			else {
				text >> textWord;
				if (spaceFound == true) {
					if (word == "___") {
						answer = textWord;
						cout << "The answer is : " << answer << endl;
					}
					else if (spaceIndex == 0) {
						//word = ___!...he's textWord=Marilyn!...he's
						int k = word.length() - 3;
						for (int i = 0; i < textWord.length() - k; i++) {
							answer += textWord[i];
						}
						cout << "The answer is : " << answer << endl;
					}
					else if (spaceIndex + 3 == textWord.length()) {
						for (int i = spaceIndex; i < textWord.length(); i++) {
							answer += textWord[i];
						}
						cout << "The answer is : " << answer << endl;
					}
					else {
						string temp;
						for (int i = spaceIndex; i < textWord.length(); i++) {
							temp += textWord[i];
						}
						int k = word.length() - 3 - spaceIndex;
						for (int i = 0; i < temp.length() - k; i++) {
							answer += temp[i];
						}
						cout << "The answer is : " << answer << endl;
					}
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
