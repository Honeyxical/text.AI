#include <iostream>
#include <utility>
#include "md5.h"

using namespace std;

double antiPlagiarism(string text, string fragment);

bool validateArguments(string text, string fragment);

string deleteUnions(string text);

string deleteSeparators(string text);

string getShingleHash(string shingle);

string getShingle(string text);

string deleteOneItemFromShingle(string text);

string toLowerCase(string text);

int countWords(string text);

int main() {
    string fragment = "Lorem ipsum dolor so sit amet, consectetur adipiscing elit.";
    string text = "Lorem ipsum dolor so sit amet, consectetur adipiscing elit. Donec et tempor odio, vitae condimentum risus.";

    cout << antiPlagiarism(text, fragment);

    return 0;
}

double antiPlagiarism(string text, string fragment) {

    if (!validateArguments(text, fragment)) {
        return -1;
    }

    double countEquals = 0;
    double countFragmentShingles = 0;
    double countTextShingles = 0;
    string bufferText;
    string shingleFragment;
    string shingleFragmentHash;
    string shingleText;
    string shingleTextHash;

    text = deleteUnions(toLowerCase(deleteSeparators(text)));
    fragment = deleteUnions(toLowerCase(deleteSeparators(fragment)));

    for (int i = 0; countWords(fragment) >= 3; i++) {
        bufferText = text;
        shingleFragmentHash = getShingleHash(getShingle(fragment));
        countFragmentShingles++;
        fragment = deleteOneItemFromShingle(fragment);
        for (int j = 0; countWords(bufferText) >= 3; j++) {
            shingleTextHash = getShingleHash(getShingle(bufferText));
            countTextShingles++;
            bufferText = deleteOneItemFromShingle(bufferText);
            if (shingleFragmentHash == shingleTextHash) {
                countEquals++;
            }
        }
    }
    return (countEquals / countFragmentShingles) * 100.0;
}

string deleteOneItemFromShingle(string text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ') {
            while (text[i] != ' ') {
                text[i] = ' ';
                i++;
            }
            return text;
        }
    }
}


string getShingleHash(string shingle) {
    return md5(std::move(shingle));
}

string getShingle(string text) {
    string shingle;
    int wordsCount = 0;

    if (countWords(text) >= 3) {
        for (int i = 0; text[i] != '\0'; i++) {
            if (text[i] != ' ' && text[i] != '\0') {
                while (text[i] != ' ' && text[i] != '\0') {
                    shingle += text[i];
                    i++;
                }
                shingle += " ";
                wordsCount++;
                if (wordsCount == 3) {
                    return shingle;
                }
            }
        }
    }
    return nullptr;
}

string deleteUnions(string text) {
    string stringUnions = "an as or then but if till how so because unless until although however whenever";
    string wordText;
    string wordUnion;
    int position;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ' && text[i] != '\0') {
            position = i;
            while (text[i] != ' ' && text[i] != '\0') {
                wordText += text[i];
                i++;
            }
        }
        for (int j = 0; stringUnions[j] != '\0'; ++j) {
            if (stringUnions[j] != ' ' && stringUnions[j] != '\0') {
                while (stringUnions[j] != ' ' && stringUnions[j] != '\0') {
                    wordUnion += stringUnions[j];
                    j++;
                }
            }
            if (wordText == wordUnion) {
                for (int k = position; k <= i; ++k) {
                    text[k] = ' ';
                }
            }
            wordUnion = "";
        }
        wordText = "";
        position = 0;
    }
    return text;
}

int countWords(string text) {
    int countWords = 0;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] != ' ' && text[i] != '\0') {
            while (text[i] != ' ' && text[i] != '\0') {
                i++;
            }
            countWords++;
        }
    }
    return countWords;
}

string toLowerCase(string text) {
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] += 32;
        }
    }
    return text;
}

string deleteSeparators(string text) {
    char arraySeparators[] = {R"( .,!?;:-+{}()[]*@%$^&#`~_=<>/|'\"\\)"};

    for (int i = 0; i < text.length(); ++i) {
        if (strchr(arraySeparators, text[i])) {
            text[i] = ' ';
        }
    }
    return text;
}

bool validateArguments(string text, string fragment) {
    int check = 0;
    if (!fragment.empty() && !text.empty()) {
        check++;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ' && text[i] != '\0') {
            check++;
            break;
        }
    }
    for (int i = 0; fragment[i] != '\0'; i++) {
        if (fragment[i] != ' ' && fragment[i] != '\0') {
            check++;
            break;
        }
    }

    if (countWords(text) >= 3 && countWords(fragment) >= 3) {
        check++;
    }
    if (check == 4) {
        return true;
    }
    return false;
}