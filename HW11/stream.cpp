/*
    Name: Siddhant Chaudhary
    Roll: BMC201953
    Batch: BSC II
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <deque>

using namespace std;

/*
    hardcoding the entities
*/

//the permutation of 256 digits
int P[256] = {
    99,217,3,113,189,127,235,224,120,142,79,78,24,45,218,177,198,141,203,51,251,181,
163,112,4,67,91,216,240,164,124,146,28,172,81,75,61,36,212,93,144,11,26,237,219,
94,44,66,35,122,173,135,100,73,200,76,145,117,211,126,92,132,202,232,82,154,210,129,
201,8,41,214,152,161,182,220,98,1,248,187,239,231,77,85,68,165,25,138,155,27,30,206,
43,131,209,125,195,140,153,225,247,37,207,255,80,84,188,33,22,7,167,105,16,72,108,
139,13,34,168,242,191,160,205,107,147,169,47,49,171,222,101,159,70,204,223,233,38,
236,65,234,254,151,118,19,57,229,158,116,20,150,40,197,137,143,10,157,14,175,252,123,
136,134,64,246,42,21,62,111,249,149,109,90,60,128,186,199,88,87,48,253,102,148,74,133,
58,213,23,54,115,121,228,31,174,55,0,170,185,166,190,178,18,59,179,110,196,245,238,
162,156,63,53,130,71,15,184,12,97,89,5,183,17,104,106,103,250,243,9,50,56,114,227,86,
29,180,208,244,96,241,52,32,83,221,95,192,2,193,6,230,226,46,176,119,215,194,39,69
};

//the degrees of the primitive polynomials
int n[8] = {41, 29, 39, 31, 35, 28, 49, 36};

//coefficients of the polynomials, just for reference
int c[8][50] = {
    {1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
    {1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1},
    {1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
};

//declaring lfsrs as vectors
vector <vector <int> > lfsr;
vector <int> blank;

//declaring a,b,c as vectors
vector <int> at;
vector <int> bt;
vector <int> ct;

//fuction to insert a new element into the lfsr
void gen_new_term(int i){
    int t , newterm;
    switch(i){
        case 0: 
            t = lfsr[0].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[0][t - 3] + lfsr[0][t - 41]) % 2;
            lfsr[0].push_back(newterm);
            return;
        case 1: 
            t = lfsr[1].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[1][t - 2] + lfsr[1][t - 29]) % 2;
            lfsr[1].push_back(newterm);
            return;
        case 2: 
            t = lfsr[2].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[2][t - 4] + lfsr[2][t - 39]) % 2;
            lfsr[2].push_back(newterm);
            return;
        case 3: 
            t = lfsr[3].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[3][t - 3] + lfsr[3][t - 31]) % 2;
            lfsr[3].push_back(newterm);
            return;
        case 4: 
            t = lfsr[4].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[4][t - 2] + lfsr[4][t - 35]) % 2;
            lfsr[4].push_back(newterm);
            return;
        case 5: 
            t = lfsr[5].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[5][t - 3] + lfsr[5][t - 28]) % 2;
            lfsr[5].push_back(newterm);
            return;
        case 6: 
            t = lfsr[6].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[6][t - 9] + lfsr[6][t - 49]) % 2;
            lfsr[6].push_back(newterm);
            return;
        case 7: 
            t = lfsr[7].size(); //new index of the ith lfsr to be defined
            newterm = (lfsr[7][t - 11] + lfsr[7][t - 36]) % 2;
            lfsr[7].push_back(newterm);
            return;
    }
}

//function to calculate f
int f(int a , int b , int c){
    return ((a * c) + (b * (1 + c) % 2)) % 2;
}

int main(int argc , char *argv[]){ //used for command line arguments
    /*
        loading the files
    */
    FILE *inp = fopen(argv[1] , "rb");
    FILE *out = fopen(argv[2] , "wb");
    FILE *key = fopen(argv[3] , "rb");

    /*
        the main code
    */

    //initialising the lfsrs as blank vectors
    //initialising a,b,c
    for (int i = 0; i < 8; i++){
        lfsr.push_back(blank);
        at.push_back(0);
        bt.push_back(0);
        ct.push_back(0);
    }

    //reading the key, which is of 36 bytes
    char buffer[36];
    fread(buffer, 1 , 36 , key);

    //getting the initial bits of the lfsrs
    int s = 0;
    for (int i = 0; i < 8; i++){
        if (i == 0)
            s = 0;
        else 
            s = s + n[i - 1]; 
        for (int j = 0; j < n[i]; j++){
            //using the formula x[i][j] = k[s + j]. In our case, k = buffer
            int xij;

            /*
                -consider the number s + j. The index of the corresponding byte of s + j in buffer is (s+j)/8; 
                -index of corresponding bit in this byte is (s+j)%8
                -so to obtain the bit, we simply have to do: (buffer[(s + j)/8] >> (8 - (s + j)%8 - 1)) & 1
                -recall- we are reading bits from left to right
            */
           xij = (buffer[(s + j)/8] >> (8 - (s + j)%8 - 1)) & 1;
           lfsr[i].push_back(xij);
        }
    }

    /*
        at a point of time 0 <= t < N, for any index i, we might need 
        any value uptill lfsr[i][n[i] + t + 5]. So, we precalculate these values for t = 0,
        and later we just add a new value for the lfsr each time
    */
    for (int i = 0; i < 8; i++){
        while(lfsr[i].size() < n[i] + 6){
            //generate a new term of the lfsr
            gen_new_term(i);
        }
    }

    /*
        the main code
    */

    //initially t will be 0
    long long int t = 0;

    char buffer_read[1];
    char buffer_write[1];
    while(!feof(inp)){
        //read a byte at a time
        fread(buffer_read , 1 , 1 , inp);

        //ignore the end of file character
        if (feof(inp))
            break;

        char z = 0; //represents the byte  00000000

        //adding a new term to each lfsr
        for (int i = 0; i < 8; i++)
            gen_new_term(i);

        //getting the values of a , b , c
        for (int i = 0; i < 8; i++){
            int hi = (i + 3) % 8 , gi = (i + 5) % 8;
            at[i] = lfsr[i][n[i] + t];
            bt[i] = lfsr[hi][n[hi] + t + 2];
            ct[i] = lfsr[gi][n[gi] + t + 5];
        }

        //getting the values of u[t] , v[t] and w[t]
        int u = f(at[0] , bt[0] , ct[0]) , v = f(bt[0] , ct[0] , at[0]), w = f(ct[0] , at[0] , bt[0]) , temp = 1;
        for (int i = 1; i < 8; i++){
            temp <<= 1;
            u = u + temp * f(at[i] , bt[i] , ct[i]);
            v = v + temp * f(bt[i] , ct[i] , at[i]);
            w = w + temp * f(ct[i] , at[i] , bt[i]);
        }

        //finding z
        z = z ^ P[u];
        z = z ^ P[v];
        z = z ^ P[w];

        //write to the output file

        //doing the bitwise xor of the byte with the generated bitstream
        z = z ^ buffer_read[0];
        //write to the output file
        buffer_write[0] = z;
        fwrite(buffer_write , 1 , 1 , out);

        //incrementing the value of t
        t++;
    }

    /*
        closing the files
	*/
    fclose(inp);
    fclose(out);
    fclose(key);
    return 0;
}
