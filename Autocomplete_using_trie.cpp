#include <iostream>
#include <string>
#include <vector>

using namespace std;

class trie{    
    class node{
    public:
    node* arr[26];
    int count;
    char val;    
    node(char val){
        this->val = val;
        this->count = 0;
        for(int i=0;i<26;i++){
            arr[i] = nullptr;
        }
    }
    };

    node* root;  

    void pprint(node* root ,string s){             
        if(root->val != '-') s+=root->val;
        if(root->count > 0 ) cout<<s<<endl;
        for(int i=0;i<26;i++)
        {
            if(root->arr[i] != nullptr) 
                pprint(root->arr[i],s);
        }
        return;
    }

    public:

    trie(){
        root = new node('-');
    }

    void print()        
    {
        pprint(root,"");        
        return;
    }            

    void insert(string s){

        // empty string 

        try{
            if(s.size() == 0)throw "emtpty string can't be added!";
        }
        catch (const char* e) {
            cerr << e << endl;
            return;
        }

        // non empty string
        node* curr = root;
        for(int i=0;i<s.size();i++){
            // not present            
            if(curr->arr[s[i] - 'a'] == nullptr)
            {
                node *temp = new node(s[i]);
                curr->arr[s[i] - 'a'] = temp;                
                curr = temp;                               
            }
            // present
            else{
                curr = curr->arr[s[i] - 'a'];
                
            }
            if(i == s.size() - 1)curr->count +=1;
            
        }
    }
    
    int find(string s){
        node* curr = root;
        int ret = 0;
        for(int i=0;i<s.size();i++){
            if(curr->arr[s[i] - 'a'] == nullptr) return 0;
            curr = curr->arr[s[i] - 'a'];            
            ret = curr->count;             
        }
        return ret;
    }

    void deleteWord(string s){
        node* curr = root;
        try
        {
            if (s.size() == 0)
            {
                throw "Empty string cannot be deleted!";
            }
            
            else{
                for(int i=0;i<s.size();i++){
            if(curr->arr[s[i] - 'a'] == nullptr){
                throw "The given string doesn't exist!";
                break;
            } 
            curr = curr->arr[s[i] - 'a'];
            if(i == s.size() - 1) curr->count -=1;
                }
            }
        }
        catch(const char* e)
        {
            cout << e << '\n';
        }
        
        return;
    }    

    void solve(node *root,string temp,int lim,vector<string>&ans){
        if(ans.size() >= lim)
            return;

        temp.push_back(root->val);

        if(root->count > 0)
        {
            ans.push_back(temp);
        }                

        for(int i=0;i<26;i++){
            if(root->arr[i]){
                solve(root->arr[i],temp,lim,ans);
            }
        }

        return;
    }

    vector<string> autocomplete(string s,int max_limit){
        try
        {
            if(s.size() == 0){
                throw "Empty String";
            }
            else{                
                node* curr = root;
                vector<string>ans;
                for(int i=0; i<s.size();i++){
                    if(curr->arr[s[i] - 'a'] == nullptr)
                        return ans;
                curr = curr->arr[s[i] - 'a'];            
        }        
                string temp = s;    
                temp.pop_back();
                solve(curr,temp,max_limit,ans);
                return ans;
            }
        }
        catch(const char* e)
        {
            cout << e << '\n';
        }                        
    } 

};
