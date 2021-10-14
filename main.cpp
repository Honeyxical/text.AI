#include <iostream>

using namespace std;

double antiPlagiarism (string text, string fragment); // основной метод

string deleteUnions(string text); // удалить связи

string deleteSeparators(string text); // удалить разделители

int getShingleHash(string text); // получение шингл хэша

int countWordsText(string text); // количество слов в тексте

int main() {
    cout << "Ok";
    return 0;
}
