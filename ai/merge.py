# -*- coding: utf-8 -*-
"""
Created on Sun Jul 25 23:20:10 2021

@author: 11200
"""


f1=open('weights.txt','r')
f2=open('weights_1.txt','r')
f3=open('weights_1.txt','r')

w1=f1.read().split()
w2=f2.read().split()
w3=f3.read().split()

s=[]
for a,b,c in zip(w1,w2,w3):
    s.append(int(a)+int(b)+int(c))


f1.close()
f2.close()
f3.close()



f0=open("weights.txt","w")

for i in s:
    f0.write(str(int(i/3)))
    f0.write(" ")

f0.close()
