#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<chrono>

using namespace std;

//Input files : Truman text,statements text.
//Output : print answers,print complete sentences.
int main() {

	//NOT : Butun kelimeleri kontrol etme eklendi.

	chrono::steady_clock sc;
	auto start = sc.now();

	ifstream statements, text;
	string line;
	string word;
	string answer;
	int spaceIndex = 0;
	bool spaceFound = false;
	bool firstFound = false;
	bool answerFound = false;
	bool firstBlank = false;

	string textWord;
	statements.open("statements.txt", ios::in);
	while (getline(statements, line)) {
		text.open("the_truman_show_script.txt", ios::in);
		firstFound = false;
		spaceFound = false;
		answerFound = false;
		firstBlank = false;
		answer = "";
		cout << line << endl << endl;
		int blanks = 0;
		int wordCounter = 0;
		//int counter = line.length() - 1;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ' ') {
				blanks++;
			}
		}
		// atahan sezgin asim bayraktar
		//Bir for dongusu ile linedaki toplam bosluk sayisini bulup oradan kac kelime oldugunu ceksek
		/*for (int i = counter + 1, j = 0; i < line.length(); i++, j++) {
			if (line[i] != textWord[j]) {
				//break;
			}
		}
		*/
		stringstream l(line);

		while (l >> word) {
			wordCounter++;
			for (int i = 0; i < word.length(); i++) {
				if (word[i] == '_') {
					spaceIndex = i;
					spaceFound = true;
					break;
				}
			}

			if (firstFound == false) {

				if (firstBlank == true) {
					answer = textWord;
					answerFound = true;
					firstFound = true;
					spaceFound = false;
				}
				else {

					while (text >> textWord) {

						if (spaceFound == true && firstBlank == false) {
							answer = textWord;
							answerFound = true;
							firstFound = true;
							spaceFound = false;
							firstBlank = true;
							break;
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
				}
				if (firstFound == false) {
					//cout << "Statement NOT found." << endl;
					break;
				}
			}
			else {
				text >> textWord;
			
				if (spaceFound == true) {
					if (word == "___") {
						answer = textWord;
						//cout << "The answer is : " << answer << endl;
					}
					else if (spaceIndex == 0) {
						//word = ___!...he's textWord=Marilyn!...he's
						int k = word.length() - 3;
						for (int i = 0; i < textWord.length() - k; i++) {
							answer += textWord[i];
						}
						//cout << "The answer is : " << answer << endl;
					}
					else if (spaceIndex + 3 == textWord.length()) {
						for (int i = spaceIndex; i < textWord.length(); i++) {
							answer += textWord[i];
						}
						//cout << "The answer is : " << answer << endl;
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
						//cout << "The answer is : " << answer << endl;
					}
					answerFound = true;
					spaceFound = false;
					//break;
				}
				else if (word == textWord) {
					continue;
				}
				else if (blanks + 1 == wordCounter) {
					if (word.length() < textWord.length()) {
						for (int i = 0; i < word.length(); i++) {
							if (word[i] != textWord[i]) {
								l.clear();
								l.seekg(0, ios::beg);
								firstFound = false;
								answerFound = false;
								wordCounter = 0;
								break;
							}
						}
					}
					else {
						l.clear();
						l.seekg(0, ios::beg);
						firstFound = false;
						answerFound = false;
						wordCounter = 0;
					}
				}
				else {
					l.clear();
					l.seekg(0, ios::beg);
					firstFound = false;
					answerFound = false;
					wordCounter = 0;
				}
			}

		}
		if (answerFound) {
			cout << "The answer is : " << answer << endl;
		}
		else {
			cout << "Statement NOT found." << endl;
		}
		cout << endl;

		text.close();

	}

	statements.close();

	auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
	cout << "Operation took: " << time_span.count() << " seconds !!!";

	return 0;
}
