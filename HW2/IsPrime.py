#
#    Name: Siddhant Chaudhary
#    Roll: BMC201953
#    Batch: BSC II   
#

import sys
import random

#efficient modular exponentiation
def modExpo(base , exp , mod):
    res = 1
    base = base % mod
    while (exp > 0):
        if(exp & 1):
            res = (res * base) % mod
        exp >>= 1
        base = (base * base) % mod
    return res
    
#the extra bit temp is for the sign of n
def millerRabin(n , t , temp):
    sign = ""
    if (temp):
        sign = "-"
    #handling boundary cases
    if (n == 0):
        return "No 0 is composite"
    elif (n == 1):
        return "No " + sign + "1 is composite"
    elif (n == 2 or n == 3):
        return "Yes, " + sign + str(n) + " is a Prime"
    elif (not(n & 1)): # if n is even and not 2
        return "No " + sign + str(n) + " is composite"
    
    #finding s,r such that n - 1 = r*2^s
    r = n - 1
    s = 0
    while(not(r & 1)): #while temp is even
        s += 1
        r >>= 1

    #main loop of miller rabin
    for i in range(1 , t + 1):
        a = random.randint(2 , n - 2) #get a random integer in this range
        y = modExpo(a , r , n)
        if (y != 1 and y != n - 1):
            j = 1
            while (j <= s - 1 and y != n - 1):
                y = (y * y) % n
                if (y == 1):
                    return "No " + sign + str(n) + " is composite";
                j += 1
            if (y != n - 1):
                return "No " + sign + str(n)+ " is composite";
    return "Yes, " + sign + str(n) + " is a Prime"

#taking the input
#if there is no command line argument
if (len(sys.argv) == 1):
    s = input().split()
    n = int(s[0])
#if there is a command line argument
else: 
    n = int(sys.argv[1])
# handling the negative case
temp = 0
if (n < 0):
    n = -n
    temp = 1
# here t = 100
print(millerRabin(n , 100 , temp))

