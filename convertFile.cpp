#include <iostream>
#include <fstream>

using namespace std;

void convertFile(string fileName, string newFileName){
    fstream file;
    fstream newFile;
    file.open(fileName, ios::in);
    newFile.open(newFileName, ios::out);

    if(file.good() == false || newFile.good() == false){
        cout << "one of the files is unavailable.";
        exit(0);
    }
    string line, newFileLine = "";
    int lineNr = 1;
    while(getline(file, line)){
        switch(lineNr){
            case 1: newFileLine += line + "|"; break;
            case 2: newFileLine += line + "|"; break;
            case 3: newFileLine += line + "|"; break;
            case 4: newFileLine += line + "|"; break;
            case 5: newFileLine += line + "|"; break;
            case 6: newFileLine += line + "|"; 
                newFile << newFileLine << endl;
                newFileLine = "";
                lineNr = 0;
                break;
        }
        lineNr++;
    }
    file.close();
    newFile.close();
}

int main(){
    string fileName;
    string newFileName;
    // cout << "Enter file name to convert: ";
    // getline(cin, fileName);
    // cin.sync();
    // cout << "Enter new file name: ";
    // getline(cin, newFileName);
    fileName = "plik.txt";
    newFileName = "newfile.txt";
    convertFile(fileName, newFileName);
}