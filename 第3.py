from typing import Any


def fib1(x):
    b = 5**0.5
    a = ((1+b)/2)**x/b - ((1-b)/2)**x/b
    a = int(a)
    return a

def fib2(x):
    a1 = 1
    a2 = 1
    if x==1 or x==2:
        return 1
    while x>2:
        a3 = a1+a2
        a1 = a2
        a2 = a3
        x-=1
    return a3

def fib3(x):
    if x == 1 or x == 2:
        return 1
    else:
        return fib3(x-1)+fib3(x-2)

print(fib2(5))






