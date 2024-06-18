#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

struct user{
    int id;
    string name;
    string surname;
    string email;
    string nrTel;
    string address;
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

void updateFile(vector<user> &users){
    fstream file;
    file.open("newfile.txt", ios::out);
    for(int i=0; i<users.size(); i++){
        file << users[i].id << "|";
        file << users[i].name << "|";
        file << users[i].surname << "|";
        file << users[i].email << "|";
        file << users[i].nrTel << "|";
        file << users[i].address << "|"<<endl;
    }
}

void getUsers(vector<user> &users){

    fstream file;
    file.open("newfile.txt", ios::in);
    string line, item;
    int lineNr = 1, pose = 0;

    while(getline(file,line) && line!=""){
        stringstream ss(line);
        user currUser;
        while(getline(ss, item, '|')){
            switch(lineNr){
                case 1: currUser.id = stoi(item); break;
                case 2: currUser.name = item; break;
                case 3: currUser.surname = item; break;
                case 4: currUser.email = item; break;
                case 5: currUser.nrTel = item; break;
                case 6: currUser.address = item; lineNr = 0;
                    users.push_back(currUser);
                    break;
            }
            lineNr++;
        }
        pose++;
    }
    file.close();
}

void addAdresate(vector<user> &users){
    fstream file;
    file.open("newfile.txt", ios::app);
    user newUser;
    int freeId;
    if(users.size() > 0){
        freeId = users.back().id + 1;
    }
    else{
        freeId = 1;
    }
    
    newUser.id = freeId;
    cout << "Enter new friend's name: ";
    cin >> newUser.name;
    cout << "Enter new friend's surname: ";
    cin >> newUser.surname;
    cout << "Enter new friend's email address: ";
    cin >> newUser.email;
    cout << "Enter new friend's telephone number: ";
    cin >> newUser.nrTel;
    cout << "Enter new friend's address: ";
    cin.ignore();
    newUser.address = getAddress();

    users.push_back(newUser);

    file << users.back().id << "|";
    file << users.back().name << "|";
    file << users.back().surname << "|";
    file << users.back().email << "|";
    file << users.back().nrTel << "|";
    file << users.back().address << "|" << endl;


    cout << endl;
    cout << "New friend "<<users.back().name << " has been added." << endl;
    cout << endl;
}

void showFriends(vector<user> &users){
    for(int i=0; i<users.size(); i++){
        cout << "Friend " << users[i].id << ": ";
        cout << users[i].name << " ";
        cout << users[i].surname << ", ";
        cout << users[i].email << ", " << endl;
        cout << users[i].nrTel << ", ";
        cout << users[i].address << endl;
        cout << endl;
    }
}

void searchByName(vector<user> &users){
    string name;
    cout << "Enter a name: ";
    cin >> name;

    for(int i=0; i<users.size(); i++){
        if(transformToLower(name) == transformToLower(users[i].name)){
            cout << "Friend " << users[i].id << ": ";
            cout << users[i].name << " ";
            cout << users[i].surname << ", ";
            cout << users[i].email << ", " << endl;
            cout << users[i].nrTel << ", ";
            cout << users[i].address << endl;
            cout << endl;
        }
    }
}

void searchBySurame(vector<user> &users){
    string surname;
    cout << "Enter a surname: ";
    cin >> surname;

    for(int i=0; i<users.size(); i++){
        if(transformToLower(surname) == transformToLower(users[i].surname)){
            cout << "Friend " << users[i].id << ": ";
            cout << users[i].name << " ";
            cout << users[i].surname << ", ";
            cout << users[i].email << ", " << endl;
            cout << users[i].nrTel << ", ";
            cout << users[i].address << endl;
            cout << endl;
        }
    }
}

void searchFriend(vector<user> &users){
    int choice;
    cout << "Would you like to search by: "<< endl; 
    cout << "1. name" << endl;
    cout << "2. surname" << endl;
    cin >> choice;
    switch(choice){
        case 1: searchByName(users); break;
        case 2: searchBySurame(users); break;
    }
}

void deleteAFriend(vector<user> &users){
    int choice;
    string delName, delSurname;
    showFriends(users);
    cout << "Type id of the friend you would like to delete: " << endl;
    cout << "Enter 0 for exit." << endl;
    cin >> choice;
    if(choice==0) return;
    bool found = false;
    size_t i = 0;
    for(auto a : users){

        if(a.id == choice){
            delName = a.name;
            delSurname = a.surname;
            found = true;
            users.erase(users.begin()+i);
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

    updateFile(users);
    showFriends(users);
    cout << "Friend " << delName << " " << delSurname << " has been deleted." << endl;

}

void editFriend(vector<user> &users){
    showFriends(users);
    int choice, edition;
    cout << "Which friend would you like to edit?" << endl;
    cout << "Enter 0 to exit." << endl;
    cout << "Choice: ";
    cin >> choice;
    if(choice==0) return;
    int i = 0;
    bool found = false;
    for(auto a: users){
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
    cout << "Friend " << users[i].id << ": ";
    cout << users[i].name << " ";
    cout << users[i].surname << ", ";
    cout << users[i].email << ", " << endl;
    cout << users[i].nrTel << ", ";
    cout << users[i].address << endl;
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
        cin >> users[i].name;
        break;
    case 2:
        cout << "Enter new surname: ";
        cin >> users[i].surname;
        break;
    case 3:
        cout << "Enter new email: ";
        cin >> users[i].email;
        break;
    case 4:
        cout << "Enter new telephone number: ";
        cin >> users[i].nrTel;
        break;
    case 5:
        cout << "Enter new address: ";
        users[i].address = getAddress();
        break;  
    default:
        break;
    }
    if(edition>=1 && edition <=5){
        cout << "Data has been changed." << endl;
        updateFile(users);
    }
    else cout << "Data has not been changed" << endl;
}

int main(){
    int choice;
    vector<user> users;
    getUsers(users);
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
                searchFriend(users);
                break;
            case 2: 
                showFriends(users);
                break;
            case 3: 
                addAdresate(users);
                break;
            case 4: 
                deleteAFriend(users);
                break;
            case 5: 
                editFriend(users);
                break;
            case 9: exit(0);
        };
    }
}