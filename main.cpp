#include <iostream>

using namespace std;

double antiPlagiarism(string text, string fragment); // основной метод

string deleteUnions(string text); // удалить союз

string deleteSeparators(string text); // удалить разделители +

int getShingleHash(string text); // получение шингл хэша

string getShingle(string text); // +

string deleteOneItemFromShingle(string text); // +

string toLowerCase(string text); // +

int countWordsText(string text); // количество слов в тексте +

bool isSeparator(char symbol); // +

bool isSymbol(char symbol); // +

int main() {

    string testText = "   Lorem Ipsum comes from sections h u i  gg g 'g!g  1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC.***";

    return 0;
}

string deleteOneItemFromShingle(string text){
    for(int i = 0; text[i] != '0'; i++){
        if(text[i] != ' '){
            while(text[i] != ' '){
                text[i] = ' ';
                i++;
            }
            return text;
        }
    }
}


string getShingle(string text){
    string shingle = "";
    int wordsCount = 0;

    for(int i = 0; text[i] != 0; i++){
        if(text[i] != ' '){
            while(text[i] != ' '){
                shingle += text[i];
                i++;
            }
            shingle += " ";
            wordsCount++;
            if(wordsCount == 3){
                return shingle;
            }
        }
    }
    return NULL;
}

int countWordsText(string text) {
    int countWords = 0;
    for (int i = 0; i < text.length(); ++i) {
        if(text[i] != ' '){
            while(text[i] != ' '){
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