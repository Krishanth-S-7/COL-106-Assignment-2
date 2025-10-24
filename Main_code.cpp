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

            if(users[user1]->followers.find(user2)!=users[user1]->followers.end()){
                cout<<"User "<<user1<<" and "<<user2<<" are already friends"<<endl;
                continue;
            }
            users[user1]->followers.insert(user2);
            users[user2]->followers.insert(user1);
            cout<<"User "<<user1<<" and "<<user2<<" are now friends"<<endl;
        }
        else if(inp[0]=="LIST_FRIENDS"){
            if(inp[1]==""){
                cout<<"Enter the username"<<endl;
                continue;
            }
            if(inp[2]!=""){
                cout<<"Username can't have spaces"<<endl;
                continue;
            }
            lowercase(inp[1]);

            string username = inp[1];
            if(users.find(username)==users.end()){
                cout<<"User "<<username<<" does not exist"<<endl;
                continue;
            }

            vector<string> friends(users[username]->followers.begin(), users[username]->followers.end());
            sort(friends.begin(), friends.end());
            cout<<"Friends of "<<username<<endl;
            for(const string& friend_name : friends){
                cout<<friend_name<<endl;
            }
        }

        else if(inp[0]=="SUGGEST_FRIENDS"){
            if(inp[1]==""){
                cout<<"Enter the username"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the number of friends to recommend "<<endl;
                continue;
            }
            lowercase(inp[1]);

            string username = inp[1];
            if(users.find(username)==users.end()){
                cout<<"User "<<username<<" does not exist"<<endl;
                continue;
            }
            int n;
            try{
                n = stoi(inp[2]);
            }
            catch(...){
                cout<<"Enter a valid number for friends to recommend"<<endl;
                continue;
            }
            cout<<"Friend suggestions for "<<username<<": "<<endl;
            suggest_friends(username, n, users);


        }
        else if(inp[0]=="DEGREES_OF_SEPERATION"){
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
            int k1 = min_dis(user1 , user2 , users);
            cout << "Degrees of separation between " << user1 << " and " << user2 << ": "  << k1 << endl;

        }
        else if(inp[0]=="ADD_POST"){
            if(inp[1]==""){
                cout<<"Enter the username"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the content of the post"<<endl;
                continue;
            }

            lowercase(inp[1]);

            string username = inp[1];
            string content = inp[2];
            if(users.find(username)==users.end()){
                cout<<"User "<<username<<" does not exist"<<endl;
                continue;
            }

            users[username]->posts.insert(username, content);
            cout<<"Post added for user "<<username<<endl;
        }
        else if(inp[0]=="OUTPUT_POSTS"){
            if(inp[1]==""){
                cout<<"Enter the username"<<endl;
                continue;
            }
            if(inp[2]==""){
                cout<<"Enter the number of posts to be printed"<<endl;
                continue;
            }
            int n;
            try{
                n = stoi(inp[2]);
            }
            catch(...){
                cout<<"Enter a valid number for posts to be printed"<<endl;
                continue;
            }
            if(n<-1){
                cout<<"Enter a valid number for posts to be printed"<<endl;
                continue;
            }
            lowercase(inp[1]);

            string username = inp[1];
            if(users.find(username)==users.end()){
                cout<<"User "<<username<<" does not exist"<<endl;
                continue;
            }

            cout<<"Posts of user "<<username<<":"<<endl;
            users[username]->posts.printnposts(n);
        }
        else{
            cout<<"Invalid command"<<endl;
        }
    }

}