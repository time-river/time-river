#!/usr/bin/env python3
# -*- coding: utf-8 -*-

####################
#x,n为位置参数
def power(x, n):
    s = 1;
    while n > 0:
        n = n - 1;
        s = s * x;
    return s;

print(power(5,3));

####################
#age,city为默认参数
def enroll(name, gender, age=6, city='Beijing'):
    print('name:', name);
    print('gender', gender);
    print('age', age);
    print('city', city);

print(enroll('Sarsh', 'F'));
print(enroll('Bob', 'M', 7));
print(enroll("Adam", 'M', city='Tianjing'));

#默认参数的坑
def add_end(L=[]):
    L.append('END');
    return L;

print(add_end());
print(add_end());
print(add_end());

def add_end(L=None):
    if L is None:
        L = [];
    L.append('END');
    return L;

print(add_end());
print(add_end());
print(add_end());
#解释：Python函数在定义的时候，默认参数L的值就被计算出来了,即[],因为默认参数L也是一个变量,它指向对象[],每次调用该函数,如果改变了L的内容,则下次调用时,默认参数的内容就变了,不再是函数定义时的[]了。
#默认参数必须指向不变对象!

####################
#可变参数
#引入
def calc(numbers):
    sum = 0;
    for n in numbers:
        sum = sum + n * n;
    return sum;

print(calc([1,2,3]));
print(calc((1,3,5,7)));

#numbers为可变参数
def calc(*numbers):
    sum = 0;
    for n in numbers:
        sum = sum + n * n;
    return sum;

print(calc(1,2));
print(calc());

nums = [1, 2, 3];
print(calc(nums[0], nums[1], nums[2]));
print(calc(*nums));

####################
#kw为关键字参数
def person(name, age, **kw):
    print('name', name, 'age', age, 'other', kw);

person('Michael', 30);
person('Bob', 35, city='Beijing');
person('Adam', 45, gender='M', job='Engineer');

extra = {
    'city': 'Beijing',
    'job' : 'Engineer',
    };
person('Jack', 24, city=extra['city'],job=extra['job']);
person('Jack', 24, **extra);

####################
#*后面的参数为命名关键字参数
def person(name, age, *, city, job):
    print(name, age, city, job);

person('Jack', 24, city='Beijing', job='Engineer');
#命名关键字参数必须传入参数名,这与位置参数不同
#缺少分隔符*,将被视为位置参数
def person(name, age, *, city='Beijing', job):
    print(name, age, city, job);

person('Jack', 24, job='Engineer');


#参数组合
'''
在python定义函数,可以使用必选参数、默认参数、可变参数、关键字参数和命名关键字参数。
参数定义的顺序必须是：必选参数、默认参数、可变参数/命名关键字参数和关键字参数
def f1(a, b, c=0, *agrs, **kw)
def f2(a, b, c=0, *, d, **kw)
'''
'''
总结:
    默认参数一定要用不可变对象，如果是可变对象，程序运行时会有逻辑错误！
    注意定义可变参数和关键字参数的语法:
        *args是可变参数，args接受的是一个tuple
        **kw是关键字参数，kw接收的是一个dict
    调用函数时如何传入可变参数和关键字参数的语法:
        可变参数既可以直接传入:func(1, 2, 3),又可以先组装dict,再通过*args传入:func(*(1, 2, 3));
        关键字参数既可以直接传入:func(a=1, b=2),又可以先组装dict,再通过**传入:func(**{'a':1,'b':2,});
    使用*args和**kw是python的习惯写法。
    命名关键字参数是为了限制调用者可以传入的参数名，同时可以提供默认值。
    定义命名的关键字参数不要忘了写分隔符*，否则定义的将是位置参数
'''
