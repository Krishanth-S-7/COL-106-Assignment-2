#include "classes.hpp"
using namespace std;

int main(){
    unordered_map<string, graph_node*> users;
    while(true){
        cout << "> ";
        string command;
        getline(cin,command);
        if (command == "EXIT") break;
        if (command.size() == 0) continue;
        vector<string> inp = process(command);
        if (inp[0] == "") continue;
        if(inp[0]=="ADD_USER"){
            if(inp[1]==""){
                cout<<"Enter the username"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Username cannot contain spaces"<<endl;
                continue;
            }

            lowercase(inp[1]);

            string username = inp[1];
            if(users.find(username)!=users.end()){
                cout<<"User "<<username<<" already exists"<<endl;
                continue;
            }

            graph_node* newUser = new graph_node(username);
            users[username] = newUser;
            cout<<"User "<<username<<" added successfully"<<endl;
        }
        else if(inp[0]=="ADD_FRIEND"){
            if(inp[1]==""){
                cout<<"Enter usernames"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"need 2 usernames"<<endl;
                continue;
            }

            lowercase(inp[1]);
            lowercase(inp[2]);
            
            string user1 = inp[1];
            string user2 = inp[2];
            if(users.find(user1)==users.end()&& users.find(user2)==users.end()){
                cout<<"User "<<user1<<" & "<<user2<<" does not exist"<<endl;
                continue;
            }
            if(users.find(user1)==users.end()){
                cout<<"User "<<user1<<" does not exist"<<endl;
                continue;
            }
            if(users.find(user2)==users.end()){
                cout<<"User "<<user2<<" does not exist"<<endl;
                continue;
            }

            // Check if they are already friends
            // For simplicity, we will not implement a full AVL tree here
            // Just a placeholder for adding friends
            // cout<<"User "<<username<<" and "<<friendname<<" are now friends"<<endl;
        }
    }

}