#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

struct contact{
    int id;
    string name;
    string surname;
    string email;
    string nrTel;
    string address;
};

struct user{
    int id;
    string login;
    string passwd;
};

string getAddress(){
    string address;
    cin.sync();
    getline(cin, address);
    return address;
}

string transformToLower(string line){
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

void updateFile(vector<contact> &contacts){
    fstream file;
    file.open("newfile.txt", ios::out);
    for(int i=0; i<contacts.size(); i++){
        file << contacts[i].id << "|";
        file << contacts[i].name << "|";
        file << contacts[i].surname << "|";
        file << contacts[i].email << "|";
        file << contacts[i].nrTel << "|";
        file << contacts[i].address << "|"<<endl;
    }
}

void getcontacts(vector<contact> &contacts){

    fstream file;
    file.open("newfile.txt", ios::in);
    string line, item;
    int lineNr = 1, pose = 0;

    while(getline(file,line) && line!=""){
        stringstream ss(line);
        contact currcontact;
        while(getline(ss, item, '|')){
            switch(lineNr){
                case 1: currcontact.id = stoi(item); break;
                case 2: currcontact.name = item; break;
                case 3: currcontact.surname = item; break;
                case 4: currcontact.email = item; break;
                case 5: currcontact.nrTel = item; break;
                case 6: currcontact.address = item; lineNr = 0;
                    contacts.push_back(currcontact);
                    break;
            }
            lineNr++;
        }
        pose++;
    }
    file.close();
}

void addAdresate(vector<contact> &contacts){
    fstream file;
    file.open("newfile.txt", ios::app);
    contact newcontact;
    int freeId;
    if(contacts.size() > 0){
        freeId = contacts.back().id + 1;
    }
    else{
        freeId = 1;
    }
    
    newcontact.id = freeId;
    cout << "Enter new friend's name: ";
    cin >> newcontact.name;
    cout << "Enter new friend's surname: ";
    cin >> newcontact.surname;
    cout << "Enter new friend's email address: ";
    cin >> newcontact.email;
    cout << "Enter new friend's telephone number: ";
    cin >> newcontact.nrTel;
    cout << "Enter new friend's address: ";
    cin.ignore();
    newcontact.address = getAddress();

    contacts.push_back(newcontact);

    file << contacts.back().id << "|";
    file << contacts.back().name << "|";
    file << contacts.back().surname << "|";
    file << contacts.back().email << "|";
    file << contacts.back().nrTel << "|";
    file << contacts.back().address << "|" << endl;


    cout << endl;
    cout << "New friend "<<contacts.back().name << " has been added." << endl;
    cout << endl;
}

void showFriends(vector<contact> &contacts){
    for(int i=0; i<contacts.size(); i++){
        cout << "Friend " << contacts[i].id << ": ";
        cout << contacts[i].name << " ";
        cout << contacts[i].surname << ", ";
        cout << contacts[i].email << ", " << endl;
        cout << contacts[i].nrTel << ", ";
        cout << contacts[i].address << endl;
        cout << endl;
    }
}

void searchByName(vector<contact> &contacts){
    string name;
    cout << "Enter a name: ";
    cin >> name;

    for(int i=0; i<contacts.size(); i++){
        if(transformToLower(name) == transformToLower(contacts[i].name)){
            cout << "Friend " << contacts[i].id << ": ";
            cout << contacts[i].name << " ";
            cout << contacts[i].surname << ", ";
            cout << contacts[i].email << ", " << endl;
            cout << contacts[i].nrTel << ", ";
            cout << contacts[i].address << endl;
            cout << endl;
        }
    }
}

void searchBySurame(vector<contact> &contacts){
    string surname;
    cout << "Enter a surname: ";
    cin >> surname;

    for(int i=0; i<contacts.size(); i++){
        if(transformToLower(surname) == transformToLower(contacts[i].surname)){
            cout << "Friend " << contacts[i].id << ": ";
            cout << contacts[i].name << " ";
            cout << contacts[i].surname << ", ";
            cout << contacts[i].email << ", " << endl;
            cout << contacts[i].nrTel << ", ";
            cout << contacts[i].address << endl;
            cout << endl;
        }
    }
}

void searchFriend(vector<contact> &contacts){
    int choice;
    cout << "Would you like to search by: "<< endl; 
    cout << "1. name" << endl;
    cout << "2. surname" << endl;
    cin >> choice;
    switch(choice){
        case 1: searchByName(contacts); break;
        case 2: searchBySurame(contacts); break;
    }
}

void deleteAFriend(vector<contact> &contacts){
    int choice;
    string delName, delSurname;
    showFriends(contacts);
    cout << "Type id of the friend you would like to delete: " << endl;
    cout << "Enter 0 for exit." << endl;
    cin >> choice;
    if(choice==0) return;
    bool found = false;
    size_t i = 0;
    for(auto a : contacts){

        if(a.id == choice){
            delName = a.name;
            delSurname = a.surname;
            found = true;
            contacts.erase(contacts.begin()+i);
            break;
        }
        i++;
    }
    if(!found){
        cout << endl;
        cout << "Friend has not been found" << endl;
        cout << endl;
        return;
    }

    updateFile(contacts);
    showFriends(contacts);
    cout << "Friend " << delName << " " << delSurname << " has been deleted." << endl;

}

void editFriend(vector<contact> &contacts){
    showFriends(contacts);
    int choice, edition;
    cout << "Which friend would you like to edit?" << endl;
    cout << "Enter 0 to exit." << endl;
    cout << "Choice: ";
    cin >> choice;
    if(choice==0) return;
    int i = 0;
    bool found = false;
    for(auto a: contacts){
        if(a.id == choice){
            found = true;
            break;
        }
        i++;
    }
    if(!found){
        cout << endl;
        cout << "Friend has not been found" << endl;
        cout << endl;
        return;
    }
    cout << endl;
    cout << "Friend " << contacts[i].id << ": ";
    cout << contacts[i].name << " ";
    cout << contacts[i].surname << ", ";
    cout << contacts[i].email << ", " << endl;
    cout << contacts[i].nrTel << ", ";
    cout << contacts[i].address << endl;
    cout << endl;
    cout << "What would you like to change?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Surname" << endl;
    cout << "3. email" <<endl;
    cout << "4. nrTel" << endl;
    cout << "5. address" << endl;
    cout << "6. Exit" << endl;
    cin >> edition;
    switch (edition)
    {
    case 1:
        cout << "Enter new name: ";
        cin >> contacts[i].name;
        break;
    case 2:
        cout << "Enter new surname: ";
        cin >> contacts[i].surname;
        break;
    case 3:
        cout << "Enter new email: ";
        cin >> contacts[i].email;
        break;
    case 4:
        cout << "Enter new telephone number: ";
        cin >> contacts[i].nrTel;
        break;
    case 5:
        cout << "Enter new address: ";
        contacts[i].address = getAddress();
        break;  
    default:
        break;
    }
    if(edition>=1 && edition <=5){
        cout << "Data has been changed." << endl;
        updateFile(contacts);
    }
    else cout << "Data has not been changed" << endl;
}

int main(){
    int choice;
    vector<contact> contacts;
    getcontacts(contacts);
    while(1){
        cout << "Your address book." << endl;
        cout << "1. Search your friend" << endl;
        cout << "2. Show all friends" << endl;
        cout << "3. Add a friend" << endl;
        cout << "4. Delete a friend" << endl;
        cout << "5. Edit a friend" << endl;
        cout << "9. Exit" << endl;
        cin >> choice;
        switch(choice){
            case 1: 
                searchFriend(contacts);
                break;
            case 2: 
                showFriends(contacts);
                break;
            case 3: 
                addAdresate(contacts);
                break;
            case 4: 
                deleteAFriend(contacts);
                break;
            case 5: 
                editFriend(contacts);
                break;
            case 9: exit(0);
        };
    }
}