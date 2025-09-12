class Student:
    def __init__(self,name,age):
        self.name = input('name:')
        self.age = input("age:")


    def newCourse(self,course):
        newcourse = input("新课程：")
        course.append(newcourse)
    def newGrade(self,grade):
        downgrade = float(input("新成绩:"))
        grade.append(downgrade)
    def __gt__(self, other):
        pass









