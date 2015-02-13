//
//  main.cpp
//  spellchecking
//
//  Created by Aakash Anand Mishra on 11/17/14.
//  Copyright (c) 2014 Aakash Anand Mishra. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include "hashtable.h"
using namespace std;
//stringtoupper function is a function that converts the input strings to uppercase which is used to make the dictionary as well as search it.
void stringtoupper(string &s){
    for(unsigned int l =0; l<s.length();l++){
        s[l] = toupper(s[l]);
        
    }
}

// removeextra removes all the "." and "," that are present in the input strings.
void removeextra(string &s){
    if(s==""){          // to check for "" value
        
    }
    else{
    char i = s[s.length()-1];

    if(i == ',' or i== '.'){// to check for . and , in the end of a string
        s.erase(s.length()-1) ;// to erase the last char incase above condition holds true
    }
    }
    
}
int main(int argc, char *argv[]) {
    int global = 0;
    string input;   // to get the input in the line for the dicitionary
    ifstream commandfile;  // this is used to access the input wordlist
    commandfile.open("Program3Fall2014wordlist"); // takes wordlist and streams it in input
   string inarra[70000];
    hashtable H;
    string input1;  // to get the input in the line for the input file
    ifstream commandfile1; // this is used to access the input file
    commandfile1.open(argv[1]); // streams the input sentence to check.
   /* To get the input dictionary
    the commandfile is used to get input into the string tmp_s which
    is then used to insert the valuues into the dictionary
    
    */
    while (getline(commandfile, input))
    {istringstream istr(input);
       
    while( !istr.eof() )
    {
          string tmp_s;
            istr >> tmp_s;
        stringtoupper(tmp_s);
        H.insert(tmp_s);
        
      
    }
        
        
        
        
    
   }
    
    /* To get the input file for checking
     the commandfile1 is used to get input1 into the string tmp_s which
     is then passed onto stringupper and removeextra functions and then looked up in the dictionary.
     If the search returns a true value then nothing's done
     else if the search returns a false value then these three functions are used in order to suggest the correct word:
     1. Checkswap
     2. Checkdelete
     3. Checksplit
     */

    string arrayin[70000];
    while (getline(commandfile1, input1))
    {istringstream istr1(input1);
        int i=0;
        while( !istr1.eof() )
        {
            string tmp_s;
            istr1 >> tmp_s;
            inarra[i] = tmp_s;
                       i = i+1;
            
        }
        global = i;
        cout<<"INPUT:";
        for(int j =0;j<i;j++){
            string k ;
            
            cout<< inarra[j]<<" ";
            stringtoupper(inarra[j]);
            removeextra(inarra[j]);
            arrayin[j] = inarra[j];
            
            
        }
      
        cout<<'\n';
        for(int k=0;k<i;k++){
            string s = arrayin[k];
            bool found;     // found is used to detect if the string is present in the dictionary or not.
            found = H.search(s);
            if(found == false){
                cout<<"word not found: "<<s<<endl;
                cout<<"perhaps you meant: "<<endl;
                H.checkswap(arrayin[k]);
                H.checksplit(arrayin[k]);
            H.checkdelete(arrayin[k]);
                
                
                                        }
                   }
        for(int k=0;k<i;k++){        // to clear the array
            arrayin[k] ="";
        }

    }

}
