import random
print('=' * 60)
print('石头剪刀布游戏')
print('='*60)
print('注意：1代表剪刀，2代表石头，3代表布')
game_info = {1:'剪刀',2:'石头',3:'布'}
score = 100
while True:
    robots_choice = random.randint(1,3)
    user_choice = input('你出什么？:')
    if user_choice == 'q':
        print('游戏结束')
        break
    elif user_choice not in '123':
        print('出拳都不会？')
    else :
        user_choice = int(user_choice)

        if (user_choice==2 and robots_choice==1) or (user_choice==1 and robots_choice==3) or (user_choice==3 and robots_choice==2):
            print(f'对方出的是{game_info[robots_choice]}')
            print('你赢了')
            score += 10
            print(f'你现在有{score}分')
        elif robots_choice == user_choice:
            print(f'对方出的是{game_info[robots_choice]}')
            print('平局')
            print(f'你现在有{score}分')
        else:
            print(f'对方出的是{game_info[robots_choice]}')
            print('你输了')
            score-=10
            print(f'你现在有{score}分')
        if score >= 200:
            print('victory')
            break
        elif score <= 0:
            print('defeat')
            break