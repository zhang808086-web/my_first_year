import matplotlib.pyplot as plt
import numpy as np
import math
a = math.e
def f(n):
    if (n<0):
        return 0
    else:
        return n
x =np.linspace(-100,100)
y = []
for i in x :
    y_1 = f(i)
    y.append(y_1)
plt.plot(x,y)
plt.title("ReLU(x)")
plt.xlabel("x")
plt.ylabel("y")
plt.show()


x3 = np.linspace(-100,100)
y3 = 1/(1+a**-x3)
plt.plot(x3,y3)
plt.title("Sigmoid(x)")
plt.xlabel("x")
plt.ylabel("y")
plt.show()


x4 = np.linspace(-100,100)
y4 = (a**x4-a**-x4)/(a**x4+a**-x4)
plt.plot(x4,y4)
plt.title("Tanh(x)")
plt.xlabel("x")
plt.ylabel("y")
plt.show()
