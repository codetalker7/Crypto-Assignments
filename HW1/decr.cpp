/*
    Name: Siddhant Chaudhary
    Roll: BMC201953
    Batch: BSC II
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

//storing the permutation
char perm_string[27];
// getting the inverse permutation
char inv[27];

int main(){

    //making Key, Plain and Cipher Files
    FILE *key = fopen("Key.txt" , "r");
    FILE *cipher = fopen("Cipher.txt" , "r");
    FILE *message = fopen("Message.txt" , "w");

    //loop variables
    ll i , j , k; char c;

    //taking the permutation
    fscanf(key , "%s" , &perm_string);

    //getting the inverse permutation
    for (i = 0; i < 26; i++)
        inv[perm_string[i] - 'A'] = 'A' + i;

    /*
        below, we will be using the fact that in the ASCII
        table, characters ABCD...Z appear consecutively, and
        characters abcd...z appear consecutively
    */
    ll toggle = -1; //used to replace consecutive whitespace with a single whitespace
    while(!feof(cipher)){
        c = fgetc(cipher);
        //handling spaces, tabs and newline
        if (c == ' ' || c == '\n' || c == '\t'){
            if(toggle == 0)
                toggle = 1;
        }

        //ignoring all other non-alphabet characters
        else if (!(c - 'a' >= 0 && 'z' - c >= 0) && !(c - 'A' >= 0 && 'Z' - c >= 0))
            continue;

        //handling alphabetic letters
        else{
            // if c is in lowercase
            if (c - 'a' >= 0 && 'z' - c >= 0){
                if (toggle == 1)
                    fprintf(message , " %c" , inv[c - 'a']);
                else
                    fprintf(message , "%c" , inv[c - 'a']);
                toggle = 0;
            }

            // else c must be uppercase
            else{
                if(toggle == 1)
                    fprintf(message , " %c" , inv[c - 'A']);
                else
                    fprintf(message , "%c" , inv[c - 'A']);
                toggle = 0;
            }
        }
    }

    //closing all the files
    fclose(key); fclose(cipher); fclose(message);
    return 0;
}

