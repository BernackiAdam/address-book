#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <filesystem>


using namespace std;

struct contact{
    int id;
    int userId;
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

int checkLogin(user& currentUser, string login, bool save = false){
    int lastFreeId =0;
    fstream userFile;
    userFile.open("users.txt", ios::in | ios::app);
    string line, item;
    int lineNr = 1;
    
    if(!save){
        while(getline(userFile,line) && line!=""){
        stringstream ss(line);
        user currUser;
        
        while(getline(ss, item, '|')){
            switch(lineNr){
                case 1: currUser.id = stoi(item); break;
                case 2: currUser.login = item; break;
                case 3: 
                    currUser.passwd = item; 
                    if(currUser.login == login){
                        currentUser = currUser;
                    }
                    lineNr=0;
                    break;
            }
            lineNr++;
            lastFreeId = currentUser.id;
            }
        }
    }
    else{
        userFile << currentUser.id << "|";
        userFile << currentUser.login << "|";
        userFile << currentUser.passwd << "|";
        userFile << endl;
        userFile.close();
        return 0;
    }
    userFile.close();
    return lastFreeId;
}

void rejestration(user& currUser){
    string login, password;
    int lastFreeId;
    while(true){
        cout << "Type 0 for exit" << endl;
        cout << "Enter login: ";
        cin >> login;
        if(login == "0") return;
        lastFreeId = checkLogin(currUser, login);
        if(currUser.login != ""){
            cout << "This login is already taken." << endl;
            cout << endl;
            continue;
        }
        else{
            cout << "Enter password: ";
            cin >> password;
            currUser.id = lastFreeId+1;
            currUser.login = login;
            currUser.passwd = password;
            checkLogin(currUser, login, true);
            cout << endl;
            cout << "Account has been created." << endl;
            cout << endl;
            return;
        }
        
        
    }
}

int login(user &currUser){
    string login, password;
    while(true){
        cout << "Enter your login or type 0 to exit: ";
        cin >> login;
        if(login == "0") break;
        checkLogin(currUser, login);
        if(currUser.login == ""){
            cout << "Such user does not exist, try again." << endl;
            continue; 
        }
        else{
            int incorrectPasswd = 0;
            while(incorrectPasswd < 3){
                cout << "Enter your password: ";
                cin >> password;
                if(password != currUser.passwd){
                    cout << "Incorrect password" << endl;
                    cout << "You have " << 2-incorrectPasswd 
                        << " attepts left." << endl;
                        cout << endl;
                    incorrectPasswd++;
                    continue;
                }
                else{
                    cout << "Welcome!" << endl;
                    return currUser.id;
                }
                if(incorrectPasswd == 2){
                    cout << "You reached limit of trys" << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}
void updateFile(vector<contact> &contacts, int idToCheck){

    fstream userFile;
    fstream tempFile;
    userFile.open("newfile.txt", ios::in);
    tempFile.open("temp.txt", ios::out);
    string line;
    stringstream ss;
    ss << idToCheck;
    char currId;
    ss >> currId;
    while(getline(userFile, line) && line!=""){
        if(currId != line[0]){
            tempFile << line << endl;
        }
        else{
            for(auto a : contacts){
                if(a.id == idToCheck){
                    tempFile << a.id << "|";
                    tempFile << a.userId << "|";
                    tempFile << a.name << "|";
                    tempFile << a.surname << "|";
                    tempFile << a.email << "|";
                    tempFile << a.nrTel << "|";
                    tempFile << a.address << "|"<<endl;
                    break;
                }
            } 
        }
    }

    userFile.close();
    tempFile.close();
    rename("temp.txt", "temp_temp.txt");
    rename("newfile.txt", "temp.txt");
    rename("temp_temp.txt", "newfile.txt");

}

void getcontacts(vector<contact> &contacts, int currUserId, int &lastFreeId){

    fstream file;
    file.open("newfile.txt", ios::in);
    string line, item;
    int lineNr = 1;

    while(getline(file,line) && line!=""){
        stringstream ss(line);
        contact currContact;
        while(getline(ss, item, '|')){  
            switch(lineNr){
                case 1: currContact.id = stoi(item); break;
                case 2: currContact.userId = stoi(item); break;
                case 3: currContact.name = item; break;
                case 4: currContact.surname = item; break;
                case 5: currContact.email = item; break;
                case 6: currContact.nrTel = item; break;
                case 7: currContact.address = item; lineNr = 0;
                    if(currContact.userId == currUserId){
                        contacts.push_back(currContact);
                    }
                    break;
            }    
            lastFreeId = currContact.id;
            lineNr++;
        }
    }
    file.close();
}

void addAdresate(vector<contact> &contacts, int currUserId, int &lastFreeId){
    fstream file;
    file.open("newfile.txt", ios::app);
    contact newcontact;
    
    newcontact.id = lastFreeId+1;
    newcontact.userId = currUserId;
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
    file << contacts.back().userId << "|";
    file << contacts.back().name << "|";
    file << contacts.back().surname << "|";
    file << contacts.back().email << "|";
    file << contacts.back().nrTel << "|";
    file << contacts.back().address << "|" << endl;

    lastFreeId++;
    cout << endl;
    cout << "New friend "<<contacts.back().name << " has been added." << endl;
    cout << endl;
}

void showFriends(vector<contact> &contacts){
    for(int i=0; i<contacts.size(); i++){
        cout << "Friend id. " << contacts[i].id << ": ";
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
            cout << "Friend id " << contacts[i].id << ": ";
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
            cout << "Friend id " << contacts[i].id << ": ";
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

void deleteAFriend(vector<contact> &contacts, int currUserId){
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

    updateFile(contacts, choice);
    showFriends(contacts);
    cout << "Friend " << delName << " " << delSurname << " has been deleted." << endl;

}

void editFriend(vector<contact> &contacts, int currUserId){
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
        cin.ignore();
        contacts[i].address = getAddress();
        break;  
    default:
        break;
    }
    if(edition>=1 && edition <=5){
        cout << "Data has been changed." << endl;
        updateFile(contacts, choice);
    }
    else cout << "Data has not been changed" << endl;
}


int main(){
    int choice, currUserId;
    int lastFreeId;
    vector<contact> contacts;
    user currUser;

    
    while(1){
        if(currUserId==0){
            cout << "Hello, log in or create new account" << endl;
            cout << "1. Log in" << endl;
            cout << "2. Register" << endl;
            cout << "9. Exit" << endl;
            cin >> choice;
            switch(choice){
                case 1:
                    currUserId = login(currUser);
                    if(currUserId!=0){
                        cout << currUserId << endl;
                        getcontacts(contacts, currUserId, lastFreeId);
                    }
                    break;
                case 2: 
                    rejestration(currUser);
                    break;
                case 9:
                    exit(0);
                default:
                    break;
            }
        }
        else{
            cout << currUserId << endl;
            cout << "Your address book." << endl;
            cout << "1. Search your friend" << endl;
            cout << "2. Show all friends" << endl;
            cout << "3. Add a friend" << endl;
            cout << "4. Delete a friend" << endl;
            cout << "5. Edit a friend" << endl;
            cout << "6. Change Password" << endl;
            cout << "7. Logout" << endl;
            cout << "9. Exit" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                searchFriend(contacts);
                break;
            case 2:
                showFriends(contacts);
                break;
            case 3:
                addAdresate(contacts, currUserId, lastFreeId);
                break;
            case 4:
                deleteAFriend(contacts, currUserId);
                break;
            case 5:
                editFriend(contacts, currUserId);
                break;
            case 6:
                break;
            case 7:
                contacts.clear();
                currUserId = 0;
                break;
            case 9:
                exit(0);
            };
        }
    }
}