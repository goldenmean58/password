#coding:utf-8
#download from git clone https://github.com/m654z/Encipher
from itertools import cycle
import random
import string
import sys

# Simple XOR encryption
def xor(p, k):
    o = ""
    for i, c in enumerate(p):
        o += chr(ord(c) ^ ord(k[i % len(k)]))

    return o

def encode(text):

    digits = list(string.digits)
    text = list(text)
    pword = ""
    
    # Get a random sequence of integers from 0-9
    for i in range(0, len(text)):
        pword += str(random.choice(digits))
        
    key = list(str(pword))
    text = xor(text, key)
    
    encoded = ""
    keyI = 0

    # Add the random sequence to the ASCII values of the string
    for c in text:
        encoded += chr(ord(c) + int(key[keyI]))
        keyI += 1

    return [encoded, ''.join(key)]

def decode(text, key):
    text = list(text)
    pword = str(key)

    key = list(str(pword))
        
    decoded = ""
    keyI = 0

    # Subtract the key from the ASCII values of the ciphertext
    for c in text:
        decoded += chr(ord(c) - int(key[keyI]))
        keyI += 1

    decoded = xor(decoded, key)

    return decoded
if(sys.argv[1]=='-a'): #add
	data=sys.argv[2]
	r=encode(data)
	mText=r[0] #密文
	key=r[1] #密钥
	#写入文件 密文-pdd 密钥-pk
	f=open('pdd','a')
	f.write(mText+'\n')
	f.close()
	f=open('pk','a')
	f.write(key+'\n')
	f.close()
	
if(sys.argv[1]=='-l'): # list all
	mText=[]
	for line in open('pdd'):
		mText.append(line.rstrip('\n'))
	key=[]
	for line in open('pk'):
		key.append(line.rstrip('\n'))
	for i in range(0,len(mText)):
		print decode(mText[i],key[i])
