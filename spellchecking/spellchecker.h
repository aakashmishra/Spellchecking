//
//  spellchecker.h
//  spellchecking
//
//  Created by Aakash Anand Mishra on 11/19/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//

#ifndef spellchecking_spellchecker_h
#define spellchecking_spellchecker_h
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <vector>
#include "hashtable.h"
using namespace std;

class spellchecker{
public:
    int k;
    void checksearch(string key,hashtable H){
        sort(key.begin(),key.end());
        do{
            bool searchret;
            searchret = H.search(key);
            if (searchret == true){
              cout<<" "<<key<<endl;
            }
            
        }    while(next_permutation(key.begin(), key.end()));
        
    }
    void checkdelete(string key, hashtable H){
        for(int i=0;i<key.length();i++){
            string ret = key.substr(0,i) + key.substr(i+1,key.length());
            bool searchret;
            searchret = H.search(ret);
            if (searchret == true){
                cout<<" "<<ret<<endl;
            }
        }
    }
    void checksplit(string key, hashtable H){
        
        for(int i=1; i<key.length();i++){
            string a;
            string b;
            bool c,d;
            a = key.substr(0,i);
            b = key.substr(i,key.length());
            c = H.search(a);
            d = H.search(b);
            if (c==true and d==true){
                cout<<a<<" "<<b<<endl;
            }
            
        }
    }
    void checkswap(string key,hashtable H){
        for (int i =0;i<key.length();i++){
            if(i<key.length()-1){
                
                char s;
                s = key[i];
                key[i] = key[i+1];
                key[i+1] = s;
                bool ret= H.search(key);
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
