#ifndef CLASSES_HPP
#define CLASSES_HPP

#include<iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include<unordered_map>
#include <cctype>

using namespace std;

// pose node

struct post{
    string username;
    string content;
    time_t timestamp;
    post(string user, string cont, time_t time){
        username = user;
        content = cont;
        timestamp = time;
    }
};

//graph node

struct graph_node{
    string username;
    // AVLTree* friends;
    graph_node(string user = "") : username(user) {}
};



struct post_node{
    post* p;
    post_node* left;
    post_node* right;
    post_node* parent;
    int height;
    post_node(post* postptr): p(postptr), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
};



int height(post_node *node){
    if (!node)
        return -1;
    return node->height;
}

int getBalance(post_node *node){
    if(!node)
        return 0;
    return height(node->left) - height(node->right);
}

post_node* rightRotate(post_node* y){
    post_node* x = y-> left;
    post_node* tre = x->right;

    x->right = y;
    y->parent = x;
    y->left = tre;
    if(tre)
        tre->parent = y;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

post_node* leftRotate(post_node* y){
    post_node* x = y->right;
    post_node* tre = x->left;

    x->left = y;
    y->parent = x;
    y->right = tre;
    if(tre)
        tre->parent = y;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

class AVLTree{
    private:
        void deleteTree(post_node *node){
            if (node){
                deleteTree(node->left);
                deleteTree(node->right);
                delete node->p;
                delete node;
            }
        }

        post_node* insertRec(post_node* root, post* p){
            if(root ==NULL){
                return new post_node(p);
            }
            if(p->timestamp < root->p->timestamp){
                root->left = insertRec(root->left, p);
                if(root->left) root->left->parent = root;
            } else if (p->timestamp > root->p->timestamp){
                root->right = insertRec(root->right, p);
                if(root->right) root->right->parent = root;
            } else {
                delete p;
                return root; 
            }
            root->height = 1 + max(height(root->left), height(root->right));

            int balance = getBalance(root);
            if(balance > 1 && p->timestamp < root->left->p->timestamp){
                return rightRotate(root);
            }
            if(balance < -1 && p->timestamp > root->right->p->timestamp){
                return leftRotate(root);
            }
            if(balance > 1 && p->timestamp > root->left->p->timestamp){
                root->left = leftRotate(root->left);
                if(root->left) root->left->parent = root;
                return rightRotate(root);
            }
            if(balance < -1 && p->timestamp < root->right->p->timestamp){
                root->right = rightRotate(root->right);
                if(root->right) root->right->parent = root;
                return leftRotate(root);
            }
            return root;
        }

        public : post_node *root;
        AVLTree(): root(nullptr) {}
        ~AVLTree(){
            deleteTree(root);
        }
        void insert(string username, string content){
            time_t now = time(0);
            post* p = new post(username, content, now);
            root = insertRec(root,p);
        }
};




// process input command

vector<string> process(string command){
    vector<string> result(3, "") ;
    int i = 0;
    while (i < (int)command.size() && command[i] != ' '){
        result[0] += command[i];
        i++;
    }
    while (i < (int)command.size() && command[i] == ' '){
        i++;
    }
    while (i < (int)command.size() && command[i] != ' '){
        result[1] += command[i];
        i++;
    }
    i++;
    while (i < (int)command.size()){
        result[2] += command[i];
        i++;
    }
    return result;
}

void lowercase(string &s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

#endif
