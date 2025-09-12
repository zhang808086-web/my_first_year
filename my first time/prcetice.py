from itertools import count


class per_son:
    def __init__(self,name,weight):
        self.name = name
        self.weight = weight

    def __str__(self):
        return 'my name is %s,my weight is %.2f' % (self.name,self.weight)

    def run(self):
        self.weight -= 0.5

    def eat(self):
        self.weight += 1


if __name__ == '__main__':
    xiaoming = per_son('xiaoming',75.0)
    count = 0
    while(xiaoming.weight > 70.0):
        xiaoming.run()
        count += 1
print(xiaoming,count)
