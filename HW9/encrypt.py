#
# Name: Siddhant Chaudhary
# Roll: BMC201953
# Batch: BSC II
#

import sys

#reading the plaintext
plaintext = open("plaintext.txt" , 'r')
m = int(plaintext.readline())

#reading the key
public_key_file = open("Public.key.txt" , 'r')
n = int(public_key_file.readline())
e = int(public_key_file.readline())

#we assume that m < n
m = m % n

#making the cipher
c = pow(m , e , n)

#writing to the ciphertext
ciphertext = open("ciphertext.txt" , 'w')
ciphertext.write(str(c))

#printing on screen
print(c)

#closing the files
plaintext.close()
public_key_file.close()
ciphertext.close()
