//
//  hashtable.h
//  spellchecking
//
//  Created by Aakash Anand Mishra on 11/17/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef spellchecking_hashtable_h
#define spellchecking_hashtable_h
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
using namespace std;


class hashtable{
    public:
    unsigned int tablesize = 69997;
    string hasharray[69997]; // hashtable is defined
    unsigned int collision = 0;

   
    /* the hashfunc1 is the main function in the hashtable i.e 
      it is the hashfunction h1 in the equation
      hash(key) = (h1(key) +f(i))mod tablesize
     is implemented as given in the handout
     */
    unsigned int hashfunc1(string key){
        unsigned int h =0;
        for (int i =0; i<key.length(); i++){
            h = (h<<5) | (h>>27);
            h += (unsigned int)key[i];
        }
        return h;
    }
    /* the hashfunc2 is a part of the f(i) function in the hashtable i.e
    in the equation
     f(i) = i(R- (key)modR)
     Where R is chosen as 30011 which is a prime no
     */
    unsigned int hashfunc2(string key){
        unsigned int h = 0;
        for (int i =0; i<key.length(); i++){
            h += (unsigned int)key[i];
        }
        unsigned int k = 30011 - h%30011;
        return k;

    }
    /* the hashfunc is the main function in the hashtable i.e
     hash(key) in the equation
     hash(key) = (h1(key) +f(i)) mod tablesize
     */
    unsigned int hashfunc(string key,int i){
        int k,k1,k2;
        k1 = hashfunc1(key);
        k2 = hashfunc2(key);
        k= (k1 +i*k2)%tablesize;
        return k;
    }
    /*This is used in order to print the dictionary
    not necessary in the assignment
     */
    void printhasht(){
        for (int i =0; i<tablesize;i++){
        cout<<hasharray[i]<<endl;
        }
    }
    /*
     The insert functions logic is as follows:
     1. The hashfunc value is calculated depending on the key
     2. depending on the return value of the hashfunc the string is mapped onto the hashtable
       i. if the free space or delete is found then it is placed in that location in the hashtable.
       ii. else the value of collision is updated and then this is used to again generate a key which is then used to recursively check the hashtable and insert the value as and when a position is found
     Precautions taken:
      A difference of 50 between the tablesize and the total no of elements is maintained
      If collisions occur more than the tablesize then the function returns
     If the data is already in the table this function will return and not duplicate the value
     */
    void insert(string key){
        unsigned int k = hashfunc(key, collision);
        if(hasharray[k] == key){
            return;
        }
        else if (hasharray[k] == "" || hasharray[k] == "delete" )
        {
            hasharray[k] = key;
            return;
        }
        
        else{
            if(collision<tablesize){
            collision =collision + 1;
             insert(key);
            }
            else{
                cout<<"table is full";
                return ;
            }
        }
        collision = 0;
        return ;}
    
    /*The logic for the search function is as follows:
     1.depending on the key hashfunc calculates the int k
     2. this k is used to jump to the kth location in the hashtable
     3. if the string is found true value is returned
     4. else the collision is updated and the table is searched again recursively
    Precaution:
     If collisions occur more than the tablesize then the function returns

     */
    
     bool search(string key){
         unsigned int collision;
        
        bool ret;
        unsigned int k = hashfunc(key, collision);
        if (hasharray[k] == key )
        {
            ret = true;
        }
        else if(hasharray[k] == "")
        {
            ret = false;
        }
        else{
            if(collision<tablesize){
            collision =collision + 1;
            ret = search(key);
            }
            else{
                ret = false;
            }
        }
        collision = 0;
         return ret;
    }
    
    /*
     This is check function that is implemented in order to check the value of the string by deleleting each character of the string and then searching it in the dictionary
     If the manipulated string is found then the string is printed on the screen
     Precaution:
     incase of continuos similar characters this function will print the output only once
     */
    void checkdelete(string key){
        for(int i=0;i<key.length();i++){
            if (key[i] == key[i+1]){
                i = i+1;
            }
            if (key[i] == key[i+1] && key[i] == key[i+2]){
                i = i+2;
            }
            if (key[i] == key[i+1] && key[i] == key[i+2] && key[i] == key[i+3]){
                i = i+3;
            }
            string ret = key.substr(0,i) + key.substr(i+1,key.length());
            bool searchret;
            searchret = search(ret);
            if (searchret == true){
                cout<<" "<<ret<<endl;
            }
        }
    }
    /*
     This is check function is implemented in order to check the value of the string by inserting space after each character of the string and then searching it in the dictionary
     If both the strings are found in the dictionary then the string is printed on the screen
     */
    void checksplit(string key){
        
        for(int i=1; i<key.length();i++){
            string a;
            string b;
            bool c,d;
            a = key.substr(0,i);
            b = key.substr(i,key.length());
            c = search(a);
            d = search(b);
            if (c==true and d==true){
                cout<<a<<" "<<b<<endl;
            }
            
        }
    }
    /*
     The logic in remove is as follows:
     1.the input string is checked in the table if it the search value is true then the next steps are implemented or else the function returns
     2.The hashfunc is created and then the table is searched recrusively  in order to find the location of the string
     3.Once the location is found then the string is replaced with "delete"
     */
    
    void remove(string key){
        bool s = false;
        s = search(key);
        if (s == true){
            
            unsigned int k = hashfunc(key, collision);
            if (hasharray[k] == key )
            {
                hasharray[k] = "delete";
                cout <<"key "<<key<<endl;
            }
            
        else{
            collision =collision + 1;
            remove(key);
            

                }
            

        }
    }
    /*
     This is check function is implemented in order to check the value of the string by swapping the adjacent characters in the string and then searching it in the dictionary
     If the string is found in the dictionary then the string is printed on the screen
     */

    
    void checkswap(string key){
        for (int i =0;i<key.length();i++){
            if(i<key.length()-1){
                
            char s;
            s = key[i];
            key[i] = key[i+1];
            key[i+1] = s;
            bool ret= search(key);
                if (ret == true) {
                    cout<<key<<endl;
                }
                key[i+1] = key[i];
                key[i] = s;
                
            }
            
        }
    }
  
  
};

#endif
