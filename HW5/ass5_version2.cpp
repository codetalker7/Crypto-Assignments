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
    storing the polynomials. write the
    coefficients in reverse order. So the formula
    is c_i = p[i - 1]
*/
int p1[16] = {0 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1};
int p2[17] = {0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1};
int p3[31] = {0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1};


int main(int argc , char *argv[]){ //used for command line arguments
    //loop variables
    int i , j;

    /*
        loading the files
    */
    FILE *inp = fopen(argv[1] , "rb");
    FILE *out = fopen(argv[2] , "wb");
    FILE *key = fopen(argv[3] , "rb");

    /*
        reading the key
	*/
    char buffer[8];
	fread(buffer , 1 , 8 , key);


	/*
        getting the initial states from the key
	*/
	vector<int> cur_states_1 , cur_states_2 , cur_states_3;

	for (i = 0; i < 64; i++){
		/*
			index of current character in buffer is i/8, and
			index of current bit in the current character is (i % 8) + 1 (from left)
			So, to get this bit, just to (buffer[i/8] >> (8 - (i % 8)) & 1)
			Recall: we are reading bits from left to right
		*/
		//setting cur_states_1
		if (0 <= i && i <= 15){
			cur_states_1.push_back(int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1));
		}
		//setting cur_states_2
		else if(16 <= i && i <= 32){
			cur_states_2.push_back(int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1));
		}
		//setting cur_states_3
		else if (33 <= i && i <= 63){
			cur_states_3.push_back(int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1));
		}
	}
    /*
        the main code
    */
    long long int t1 = 0, t2 = 0, t3 = 0;

    char buffer_read[1];
    char buffer_write[1];
    while(!feof(inp)){
        //read a byte at a time
        fread(buffer_read , 1 , 1 , inp);

        //ignore the end of file character
        if (feof(inp))
            break;

        char x = 0; //represents the byte 00000000

        //processing the byte
        for (i = 0; i < 8; i++){
            /*
                at each step, curr1.back() will contain the current bit of the
                first LFSR. Similarly for curr2.back() and curr3.back()
            */
            //generating the current bit of the first LFSR
            if(t1 >= 16) {
                int y = (cur_states_1[t1 - 2] + cur_states_1[t1 - 3] + cur_states_1[t1 - 5] + cur_states_1[t1 - 16]) % 2;
                cur_states_1.push_back(y);
            }
            //generating the current bit of the second LFSR
            if (t2 >= 17) {
                int y = (cur_states_2[t2 - 3] + cur_states_2[t2 - 17]) % 2;
                cur_states_2.push_back(y);
            }
            //generating the current bit of the third LFSR
            if(t3 >= 31) {
                int y = (cur_states_3[t3 - 3] + cur_states_3[t3 - 31]) % 2;
                cur_states_3.push_back(y);
            }

            //using the combiner function
            int wi = cur_states_1[t1] , ui = cur_states_2[t2] , vi = cur_states_3[t3];
            int ri = (vi*wi + (1 - vi)*ui) % 2;

            //increment the counters
            t1++; t2++; t3++;
            //set the i + 1th bit of x (from the left) to ri
            x = x | (ri << (8 - i - 1));
        }
        //write to the output file

        //doing the bitwise or of the byte with the random bitstream
        x = x ^ buffer_read[0];
        //write to the output file
        buffer_write[0] = x;
        fwrite(buffer_write , 1 , 1 , out);
    }

    /*
        closing the files
	*/
    fclose(inp);
    fclose(out);
    fclose(key);
    return 0;
}
