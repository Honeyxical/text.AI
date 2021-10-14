#include <iostream>

using namespace std;

double antiPlagiarism(string text, string fragment); // основной метод

string deleteUnions(string text); // удалить союз

int getShingleHash(string text); // получение шингл хэша

int countWordsText(string text); // количество слов в тексте

string deleteSeparators(string text);

bool isSeparator(char symbol);

int main() {
    string testText = "Hello, World!";

    cout << countWordsText(testText);

    return 0;
}

int countWordsText(string text) {
    int countWords = 0;

    deleteSeparators(text);

    for (int i = 0; i < text.length(); ++i) {
        if (isSeparator(text[i])) {
            countWords++;
        }
    }
    if (isSeparator(text[text.length() - 1])) {
        return countWords - 1;
    }
    return countWords;
}

string deleteSeparators(string text) {
    for (int i = 0; i < text.length(); ++i) {
        if (isSeparator(text[i])) {
            text[i] = ' ';
        }
    }
    return text;
}

bool isSeparator(char symbol) {
    char arraySeparators[] = {" .,:;!?-+{}()[]*@%$^&#`~№_=<>'/|"};

    for (int i = 0; arraySeparators[i] != '\0'; ++i) {
        if (arraySeparators[i] == symbol) {
            return true;
        }
    }
    return false;
}
