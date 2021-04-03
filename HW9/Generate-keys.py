#
# Name: Siddhant Chaudhary
# Roll: BMC201953
# Batch: BSC II
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

def millerRabin(n , t):
	#handling negative n
	if (n < 0):
		n = -n
    #handling boundary cases
	if (n == 0):
		return 0
	elif (n == 1):
		return 0
	elif (n == 2 or n == 3):
		return 1
	# if n is even and not 2
	elif (not(n & 1)):
		return 0
    
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
					return 0
				j += 1
			if (y != n - 1):
				return 0
	return 1

#the random search function
#we will use t = 25 and B = 1024
def randomSearch(k , t):
	#making the k+1-bit base
	base = 1
	temp = k
	while (temp > 0):
		base = base << 1
		temp = temp - 1
	n = 0
	B = 1024
	while (1):
		#generate random n of k + 1-bits
		n = base + random.getrandbits(k)

		#if n is even, repeat the loop
		if (not (n & 1)):
			continue;

		#if n is odd, check if it is divisible
		#by a prime <= B
		flag = 1
		for i in range(2 , B + 1):
			if (n % i == 0):
				flag = 0
				break
		if (flag == 0):
			continue
		#check if miller rabin on n returns true
		else:
			if (millerRabin(n , t) == 1):
				return n
			else:
				continue
	return n

#extended gcd
def extgcd(a , b , x = 1 , y = 0):
	x = 1; y = 0;
	x1 = 0; y1 = 1;
	a1 = a; b1 = b;
	while (b1):
		q = int(a1 / b1)
		temp = x
		x = x1
		x1 = temp - q * x1

		temp = y
		y = y1
		y1 = temp - q * y1

		temp = a1
		a1 = b1
		b1 = temp - q * b1
	return [a1 , x , y]

#to calculate modular inverse, assuming a,m are coprime
def modinv(a , m):
	x = extgcd(a , m , 1 , 0)[1]
	return (x % m + m) % m 

#computing a random e and the corresponding d
def compute_key(k , p , q):
	#making phi
	phi = (p - 1)*(q - 1)

	#making a k + 1-bit base
	base = 1
	temp = k
	while (temp > 0):
		base = base << 1
		temp = temp - 1

	#generating e
	while(1):
		#making sure 2^k = base < e < phi
		e = random.randint(base + 1 , phi - 1)
		mlist = extgcd(e , phi , 1 , 0)
		if (mlist[0] != 1):
			continue
		else:
			#x is the inverse of e mod phi
			x = mlist[1]
			d = (x % phi + phi) % phi
			break
	return [e , d]

#--------------------the main code--------------------

#initialising random using the command line seed
mseed = int(sys.argv[1])
random.seed(mseed)

#generating the random primes p,q with p != q
#using t = 25
p = randomSearch(63 , 25)
q = p
while(q == p):
	q = randomSearch(63 , 25)

#generating the key
mlist = compute_key(126 , p , q)
e = mlist[0]
d = mlist[1]

#writing to the file
n = p * q
public_key_file = open('Public.key.txt' , 'w')
private_key_file = open('Private.key.txt' , 'w')

public_key_file.write(str(n) + "\n" + str(e))
private_key_file.write(str(n) + "\n" + str(d))

#printing everything on the terminal
print(p)
print(q)
print(n)
print(e)
print(d)

#closing the files
public_key_file.close()
private_key_file.close()





