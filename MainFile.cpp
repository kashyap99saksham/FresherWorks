#include<bits/stdc++.h>
using namespace std;

unordered_map<string,pair<int,int>>dict;      // store key-values

bool checkAlpha(string key) {
    for (int i = 0; i < key.length(); i++)
        if(!isalpha(key[i])) return false;
    return true;    
}
// for create operation 
// use syntax "create(key_name,value,timeout_value)" timeout is optional you can continue by passing two arguments without timeout
void create(string key,long long value,int timeout=0) {
    if(dict.find(key) != dict.end())
        cout<<"error: this key already exists\n";
    else    {
        if(checkAlpha(key))   {
            if (dict.size() < (1024*1020*1024) && value <= (16*1024*1024))    { // constraints for file size less than 1GB and Jasonobject value less than 16KB 
                pair<int,int>l;
                if (timeout==0) {
                    l = {value,timeout};
                }
                else    {
                    time_t result = time(nullptr);
                    l = {value,result + timeout};
                }
                if (key.size() <= 32) // constraints for input key_name capped at 32chars
                    dict[key] = l;
            }
            else
                cout<<"error: Memory limit exceeded!!\n";
        }
        else       
            cout<<"error: Invalind key_name!! key_name must contain only alphabets and no special characters or numbers\n";
    }
}


// for read operation
// use syntax "read(key_name)"  
string read(string key)    {
    string stri = "";
    if (dict.find(key) == dict.end())
        return "error: given key does not exist in database. Please enter a valid key\n";
    else    {
        pair<int,int>b = dict[key];
        if (b.second != 0)    {
            time_t result = time(nullptr);
            if (result < b.second ) {        // comparing the present time with expiry time
                stri = key + ":" + to_string(b.first);          // to return the value in the format of JasonObject i.e.,"key_name:value"
                return stri;
            }
            else
                return "error: time-to-live of " + key + "has expired\n"; 
        }
        else    {
            stri = key + ":" + to_string(b.first);
            return stri;
        }
    }
}


// for delete operation
// use syntax "delete(key_name)"

void Delete(string key)    {
    if (dict.find(key) == dict.end())
        cout<<"error: given key does not exist in database. Please enter a valid key\n";
    else    {
        pair<int,int>b = dict[key];
        if (b.second != 0)  {
            time_t result = time(nullptr);
            if (result < b.second) {        // comparing the current time with expiry time
                dict.erase(key);
                cout<<"key is successfully deleted\n";    
            }
            else
                cout<<"error: time-to-live of "<<key<<" has expired\n";
        }
        else    {
            dict.erase(key);
            cout<<"key is successfully deleted\n";
        }
    }
}


int main()  {
    while(1)    {
        cout<<"Press 1 : Create \t Press 2 : Read \t Press 3 : Delete\n";
        int x;  cin>>x;
        string key;
        int val;
        int tim;
        switch (x) 
        { 
            case 1: cout<<"enter key || value\n";
                    cin>>key>>val;
                    cout<<"want to give time ? Press 1\n";
                    int ch; cin>>ch;
                    if(ch)  {
                        cout<<"Enter time\n";
                        cin>>tim;
                        create(key,val,tim);
                    } 
                    else  create(key,val);
                    break; 
            case 2: cout<<"enter key\n";
                    cin>>key;
                    cout<<read(key)<<endl;
                    break; 
            case 3: cout<<"enter key\n";
                    cin>>key;
                    Delete(key);
                    break; 
            default: printf("Choice other than 1, 2 and 3"); 
                        break;   
        } 
    }
}