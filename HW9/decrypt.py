#
# Name: Siddhant Chaudhary
# Roll: BMC201953
# Batch: BSC II
#

import sys

#reading the ciphertext
ciphertext = open("ciphertext.txt" , 'r')
c = int(ciphertext.readline())

#reading the key
private_key_file = open("Private.key.txt" , 'r')
n = int(private_key_file.readline())
d = int(private_key_file.readline())

#we assume that c < n
c = c % n

#recovering the message
m = pow(c , d , n)

#writing to decrypted_plaintext
decr_plaintext = open("decrypted-plaintext.txt" , 'w')
decr_plaintext.write(str(m))

#printing on screen
print(m)

#closing the files
ciphertext.close()
private_key_file.close()
decr_plaintext.close()
