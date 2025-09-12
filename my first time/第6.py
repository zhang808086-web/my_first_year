class Car:
    def __init__(self,performance_level,brand):
        self.performance_level = performance_level
        self.brand = brand

class Electriccar(Car):
    def __init__(self,performance_level , brand , power_consumption):
        super().__init__(performance_level,brand)
        self.power_consumption = power_consumption

    def maintenance(self):
        pass

class Sportscar(Car):
    def __init__(self,performance_level,brand,power_consumption):
        super().__init__(performance_level,brand)
        self.power_consumption = power_consumption

    def maintenance(self):
        pass


electric_car1 = Electriccar("high","toyota",15)
electric_car2 = Electriccar("medium","honda",18)
electric_car3 = Electriccar("high","tesla",12)

sports_car1 = Sportscar("very high","benz",25)
sports_car2 = Sportscar("high","ferrari",30)

with open("../car_info.txt", "w") as f:
    f.write("Electric_car 1 : performance_level - {}, brand - {},power_consumption_per_100km - {}\n".format(
        electric_car1.performance_level,electric_car1.brand,electric_car1.power_consumption))
    f.write("Electric_car 2 : performance_level - {}, brand - {},power_consumption_per_100km - {}\n".format(
        electric_car2.performance_level, electric_car2.brand, electric_car2.power_consumption))
    f.write("Electric_car 3 : performance_level - {}, brand - {},power_consumption_per_100km - {}\n".format(
        electric_car3.performance_level, electric_car3.brand, electric_car3.power_consumption))
    f.write("Sport_car 1 : performance_level - {}, brand - {},power_consumption_per_100km - {}\n".format(
        sports_car1.performance_level,sports_car1.brand,sports_car1.power_consumption))
    f.write("Sport_car 2 : performance_level - {}, brand - {},power_consumption_per_100km - {}\n".format(
        sports_car2.performance_level, sports_car2.brand, sports_car2.power_consumption))

