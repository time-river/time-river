#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def normalize(name):
    return name[0].upper() + name[1:].lower();

print(list(map(normalize, ['adam', 'LISA', 'barT'])));


from functools import reduce;
def mul(x, y):
    return x * y;
def prod(func, L):
    return reduce(func, L);

print('3 * 5 * 7 * 9 = ', prod(mul, [3, 5, 7, 9]));

from functools import reduce;
def char2num(s):
    return {
                '0': 0,
                '1': 1,
                '2': 2,
                '3': 3,
                '4': 4,
                '5': 5,
                '6': 6,
                '7': 7,
                '8': 8,
                '9': 9,
                }[s];
def str2int(s):
    return reduce(lambda x, y: x*10+y, map(char2num, s));
def str3int(s):
    return reduce(lambda x, y: x*0.1+y*1, map(char2num, s[::-1]));
def str2float(s):
    L = s.split('.'); 
    print(L[0]+ L[1]);
    sum = str2int(L[0]) + str3int(L[1]) * 0.1;
    return sum;
"""python 切片
http://blog.csdn.net/imwhatiam/article/details/17458639
[s.lower() if isinstance(s,str) else s for s in L] 补
"""
print('str2float(\'123.456\') =', str2float('123.456'));

