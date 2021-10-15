#include <iostream>
#include <utility>
#include "md5.h"

using namespace std;

double antiPlagiarism(string text, string fragment);

string deleteUnions(string text);

string deleteSeparators(string text);

string getShingleHash(string shingle);

string getShingle(string text);

string deleteOneItemFromShingle(string text);

string toLowerCase(string text);

int countWords(string text);

int main() {
    string text = "Lorem ipsum dolor so sit amet, consectetur adipiscing elit. Morbi id lorem eu purus vehicula pellentesque. "
                  "Suspendisse enim augue, dictum nec eros nec, rutrum varius velit. Nam vulputate egestas enim pretium congue. "
                  "Donec a tristique turpis, vestibulum varius tellus. Quisque imperdiet semper fringilla. Proin in vehicula purus. "
                  "Nulla vehicula ut sem eget luctus. Aliquam porta ullamcorper efficitur. Etiam maximus orci ac augue egestas, sit amet commodo magna egestas. "
                  "Duis sagittis auctor felis sed iaculis. Donec vulputate non urna sed finibus. Quisque aliquam convallis ante non mattis. "
                  "Nulla eu libero convallis, vulputate magna id, interdum mi. Etiam sit amet efficitur arcu, ac malesuada est. "
                  "Vivamus facilisis ex quis erat auctor, sit amet dictum metus interdum.";
    string fragment = "Lorem ipsum dolor so sit amet, consectetur adipiscing elit. Donec et tempor odio, vitae condimentum risus. "
                      "Fusce posuere, quam venenatis placerat porttitor, augue nulla porta magna, quis lacinia dolor enim non metus. "
                      "Praesent elementum enim id rutrum volutpat. Duis maximus vitae nisl eu efficitur. Ut dapibus lobortis augue quis porttitor. "
                      "Sed magna risus, varius fringilla ipsum vel, rhoncus bibendum lectus. Donec ut justo pellentesque, fringilla leo maximus, pharetra ipsum. "
                      "Maecenas convallis diam et massa pulvinar auctor. Nam maximus nunc ipsum, sed semper lorem imperdiet eget. "
                      "Donec nisi quam, mattis in maximus a, viverra a libero. Quisque vitae velit eget diam sagittis varius. "
                      "Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. "
                      "Proin vitae libero gravida, vulputate lectus vulputate, dapibus augue. Aliquam tincidunt sed purus mollis pharetra. "
                      "Sed nisi nulla, sollicitudin id urna non, dictum scelerisque lorem. Vivamus ut luctus ante.";

    cout << antiPlagiarism(text, fragment);

    return 0;
}

double antiPlagiarism(string text, string fragment) {
    if (fragment == "" || text == "") {
        cout << "Error!";
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
    cout << text << endl;
    fragment = deleteUnions(toLowerCase(deleteSeparators(fragment)));
    cout << fragment;

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
    return NULL;
}

string deleteUnions(string text) {
    string stringUnions = "an as or then but if till how so because unless until although however whenever";
    string wordText = "";
    string wordUnion = "";
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
    char arraySeparators[] = {" .,!?;:-+{}()[]*@%$^&#`~_=<>/|'\\\"\\\\"};

    for (int i = 0; i < text.length(); ++i) {
        if (strchr(arraySeparators, text[i])) {
            text[i] = ' ';
        }
    }
    return text;
}