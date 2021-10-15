#include <iostream>

using namespace std;

double antiPlagiarism(string text, string fragment); // основной метод

string deleteUnions(string text); // удалить союз

string deleteSeparators(string text); // удалить разделители

int getShingleHash(string text); // получение шингл хэша

int countWordsText(string text); // количество слов в тексте

bool isSeparator(char symbol);

bool isSymbol(char symbol);

int main() {

    string testText = "   Lorem Ipsum comes from sections   gg g 'g!g  1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC.***";

    cout << countWordsText(testText);

    return 0;
}

int countWordsText(string text) {
    int countWords = 0;

    deleteSeparators(text);

    for (int i = 0; i < text.length(); ++i) {
        if (isSymbol(text[i]) && isSeparator(text[i + 1])) {
            countWords++;
        }
        if (isSymbol(text[i]) && text[i + 1] == '\0') {
            countWords++;
        }
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
    char arraySeparators[] = {" .,!?;:-+{}()[]*@%$^&#`~_=<>/|'\\\"\\\\"};

    for (int i = 0; arraySeparators[i] != '\0'; ++i) {
        if (arraySeparators[i] == symbol) {
            return true;
        }
    }
    return false;
}

bool isSymbol(char symbol) {
    if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9')) {
        return true;
    }
    return false;
}