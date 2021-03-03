/*
    Name: Siddhant Chaudhary
    Roll: BMC201953
    Batch: BSC II
*/
#include <iostream>
#include <stdio.h>
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
    FILE *inp = fopen("Input-1.jpg" , "rb");
    FILE *out = fopen("Output" , "wb");
    FILE *key = fopen("Key" , "rb");

    /*
        reading the key
	*/
    char buffer[8];
	fread(buffer , 1 , 8 , key);


	/*
        getting the initial states from the key
	*/
	int cur_states_1[16] , cur_states_2[17] , cur_states_3[31];

	for (i = 0; i < 64; i++){
		/*
			index of current character in buffer is i/8, and
			index of current bit in the current character is (i % 8) + 1 (from left)
			So, to get this bit, just to (buffer[i/8] >> (8 - (i % 8)) & 1)
			Recall: we are reading bits from left to right
		*/
		//setting cur_states_1
		if (0 <= i && i <= 15){
			cur_states_1[i] = int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1);
		}
		//setting cur_states_2
		else if(16 <= i && i <= 32){
			cur_states_2[i - 16] = int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1);
		}
		//setting cur_states_3
		else if (33 <= i && i <= 63){
			cur_states_3[i - 33] = int((buffer[i/8] >> (8 - (i % 8) - 1)) & 1);
		}
	}
    /*
        the main code
    */
    deque<int> curr1 , curr2 , curr3;
    deque<int>::iterator it;

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
            if (curr1.size() < 16)
                curr1.push_back(cur_states_1[curr1.size()]);
            else {
                int y = 0;
                for (j = 16 , it = curr1.begin(); j >= 1 , it != curr1.end(); it++ , j--)
                    y = (y + *(it) * p1[j - 1]) % 2;
                curr1.push_back(y);
                curr1.pop_front();
            }
            //generating the current bit of the second LFSR
            if (curr2.size() < 17)
                curr2.push_back(cur_states_2[curr2.size()]);
            else {
                int y = 0;
                for (j = 17 , it = curr2.begin(); j >= 1 , it != curr2.end(); it++ , j--)
                    y = (y + *(it) * p2[j - 1]) % 2;
                curr2.push_back(y);
                curr2.pop_front();
            }
            //generating the current bit of the third LFSR
            if (curr3.size() < 31)
                curr3.push_back(cur_states_3[curr3.size()]);
            else {
                int y = 0;
                for (j = 31 , it = curr3.begin(); j >= 1 , it != curr3.end(); it++ , j--)
                    y = (y + *(it) * p3[j - 1]) % 2;
                curr3.push_back(y);
                curr3.pop_front();
            }

            //using the combiner function
            int wi = curr1[curr1.size() - 1] , ui = curr2[curr2.size() - 1] , vi = curr3[curr3.size() - 1];
            int ri = (vi*wi + (1 - vi)*ui) % 2;

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
