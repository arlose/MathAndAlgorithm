#--------准备工作------
import pygame #导入pygame工具箱  pygame--->python game
from pygame.locals import *  #从pygame工具箱，本地导入所有工具
from sys import exit    #sys-->system  从系统中导入退出方法
import time #导入时间对象
import random #导入随机对象

pygame.init() #告诉程序可以执行pygame的东西了。(初始化pygame)

#创建一个窗口
screen=pygame.display.set_mode((480,852),0,32)

#在窗口上显示游戏名称“飞机大战”
pygame.display.set_caption('飞机大战')

#加载背景图片
background=pygame.image.load('background.png')

#加载英雄机图片
hero0=pygame.image.load('hero0.png')
hero1=pygame.image.load('hero1.png')
#加载英雄机爆炸图片
hero_down=pygame.image.load('hero_down.png')

#计数器 num--->number
num=0

#英雄机的坐标
heroX=200
heroY=400

#加载普通敌机图片
enemy1=pygame.image.load('enemy1.png')
#加载普通敌机爆炸图片
enemy1_down1=pygame.image.load('enemy1_down1.png')
enemy1_down2=pygame.image.load('enemy1_down2.png')
enemy1_down3=pygame.image.load('enemy1_down3.png')

#创建普通敌机的坐标列表
enemy1_x=[]
enemy1_y=[]

#加载中级敌机图片
enemy2=pygame.image.load('enemy2.png')
#加载中级敌机爆炸图片
enemy2_down1=pygame.image.load('enemy2_down1.png')
enemy2_down2=pygame.image.load('enemy2_down2.png')
enemy2_down3=pygame.image.load('enemy2_down3.png')

#创建中级敌机的坐标列表
enemy2_x=[]
enemy2_y=[]

#创建中级敌机的血量
enemy2_blood=[]

#加载高级敌机图片
enemy3=pygame.image.load('enemy3.png')
#加载高级敌机爆炸图片
enemy3_down1=pygame.image.load('enemy3_down1.png')
enemy3_down2=pygame.image.load('enemy3_down2.png')
enemy3_down3=pygame.image.load('enemy3_down3.png')

#创建高级敌机的坐标列表
enemy3_x=[]
enemy3_y=[]

#创建高级敌机的血量
enemy3_blood=[]

#加载子弹图片
bullet=pygame.image.load('bullet.png')
#创建子弹的坐标列表
bullet_x=[]
bullet_y=[]

#子弹的切换
flag=0

#加载游戏结束图片
gameover=pygame.image.load('gameover.png')
isgameover=1 #是否游戏结束，如果是0游戏结束
gameover=pygame.transform.scale(gameover,(480,852))

#创建字体格式
font=pygame.font.Font('simsun.ttc',30)
text=font.render('分数:',True,(34,177,76))
score=0 #分数

#-------程序的主运行------
while True:
    #将背景图片贴到窗口上
    screen.blit(background,(0,0))
    #将得分贴到窗口上
    screen.blit(text,(10,10))
    text_score=font.render(str(score),True,(34,177,76))
    screen.blit(text_score,(100,10))
    if isgameover==1:
        if num%2==0: #计数器对2求余，余数为0表示偶数
            #将英雄机图片贴到窗口上
            screen.blit(hero0,(heroX,heroY))
        else:  #否则，判断为奇数
            screen.blit(hero1,(heroX,heroY))

        #每次循环体执行时等待0.1
        time.sleep(0.01)
        #计数器加1
        num=num+1  #---->num+=1

        #实现英雄机的移动
        pos=pygame.mouse.get_pos()
        heroX=pos[0]-hero0.get_width()/2  #get_width() 获取宽度的方法
        heroY=pos[1]-hero0.get_height()/2 #get_height() 获取长度的方法

        #普通敌机的移动
        if num%20==0:
            enemy1_x.append(random.randint(0,480-enemy1.get_width()))
            enemy1_y.append(0)
        #将普通敌机贴到窗口上
        for i in range(len(enemy1_x)):
            screen.blit(enemy1,(enemy1_x[i],enemy1_y[i]))
        #普通敌机下落方法
        for i in range(len(enemy1_x)):
            enemy1_y[i]+=2
            if enemy1_y[i]>852:
                del enemy1_x[i]
                del enemy1_y[i]
                break

        #中级敌机的移动
        if num%120==0:
            enemy2_x.append(random.randint(0,480-enemy2.get_width()))
            enemy2_y.append(0)
            enemy2_blood.append(70)
        #将中级敌机贴到窗口上
        for i in range(len(enemy2_x)):
            screen.blit(enemy2,(enemy2_x[i],enemy2_y[i]))
        #普中级敌机下落方法
        for i in range(len(enemy2_x)):
            enemy2_y[i]+=2
            if enemy2_y[i]>852:
                del enemy2_x[i]
                del enemy2_y[i]
                del enemy2_blood[i]
                break

        #高级敌机的移动
        if num%360==0:
            enemy3_x.append(random.randint(0,480-enemy3.get_width()))
            enemy3_y.append(0)
            enemy3_blood.append(150)
        #将高级敌机贴到窗口上
        for i in range(len(enemy3_x)):
            screen.blit(enemy3,(enemy3_x[i],enemy3_y[i]))
        #普高级机下落方法
        for i in range(len(enemy3_x)):
            enemy3_y[i]+=2
            if enemy3_y[i]>852:
                del enemy3_x[i]
                del enemy3_y[i]
                del enemy3_blood[i]
                break

        #子弹的移动
        if num%10==0:
            if flag==0:#出现单子弹
                bullet_x.append(heroX+hero1.get_width()/2-bullet.get_width()/2)
                bullet_y.append(heroY-bullet.get_height())
            if flag==1:#出现双子弹
                bullet_x.append(heroX+hero1.get_width()/4-bullet.get_width()-4)
                bullet_y.append(heroY+hero1.get_height()/4-bullet.get_height()/2)
                bullet_x.append(heroX+3*hero1.get_width()/4+4)
                bullet_y.append(heroY+hero1.get_height()/4-bullet.get_height()/2)
            

        #将子弹贴到窗口上
        for i in range(len(bullet_x)):
            screen.blit(bullet,(bullet_x[i],bullet_y[i]))
        #将子弹飞方法
        for i in range(len(bullet_x)):
            bullet_y[i]-=5
            if bullet_y[i]<0:
                del bullet_x[i]
                del bullet_y[i]
                break

        #实现普通敌机被打死
        for i in range(len(bullet_x)):
            for j in range(len(enemy1_x)):
                #判断子弹的x坐标是否打中普通敌机的范围内
                if bullet_x[i]>enemy1_x[j]-bullet.get_width() and bullet_x[i]<enemy1_x[j]+enemy1.get_width():
                    #判断子弹的y坐标是否打中普通敌机的范围内
                    if bullet_y[i]>enemy1_y[j]-bullet.get_height() and bullet_y[i]<enemy1_y[j]+enemy1.get_height():
                        screen.blit(enemy1_down1,(enemy1_x[j],enemy1_y[j]))
                        screen.blit(enemy1_down2,(enemy1_x[j],enemy1_y[j]))
                        screen.blit(enemy1_down3,(enemy1_x[j],enemy1_y[j]))
                        score+=1
                        del enemy1_x[j]
                        del enemy1_y[j]
                        break

        #实现中级敌机被打死
        for i in range(len(bullet_x)):
            for j in range(len(enemy2_x)):
                #判断子弹的x坐标是否打中普通敌机的范围内
                if bullet_x[i]>enemy2_x[j]-bullet.get_width() and bullet_x[i]<enemy2_x[j]+enemy2.get_width():
                    #判断子弹的y坐标是否打中普通敌机的范围内
                    if bullet_y[i]>enemy2_y[j]-bullet.get_height() and bullet_y[i]<enemy2_y[j]+enemy2.get_height():
                        enemy2_blood[j]-=1
                        if enemy2_blood[j]<=0:
                            #显示爆炸的效果
                            screen.blit(enemy2_down1,(enemy2_x[j],enemy2_y[j]))
                            screen.blit(enemy2_down2,(enemy2_x[j],enemy2_y[j]))
                            screen.blit(enemy2_down3,(enemy2_x[j],enemy2_y[j]))
                            score+=2
                            del enemy2_x[j]
                            del enemy2_y[j]
                            del enemy2_blood[j]
                            break
                        
        #实现高级敌机被打死
        for i in range(len(bullet_x)):
            for j in range(len(enemy3_x)):
                #判断子弹的x坐标是否打中普通敌机的范围内
                if bullet_x[i]>enemy3_x[j]-bullet.get_width() and bullet_x[i]<enemy3_x[j]+enemy3.get_width():
                    #判断子弹的y坐标是否打中普通敌机的范围内
                    if bullet_y[i]>enemy3_y[j]-bullet.get_height() and bullet_y[i]<enemy3_y[j]+enemy3.get_height():
                        enemy3_blood[j]-=1
                        if enemy3_blood[j]<=0:
                            screen.blit(enemy3_down1,(enemy3_x[j],enemy3_y[j]))
                            screen.blit(enemy3_down2,(enemy3_x[j],enemy3_y[j]))
                            screen.blit(enemy3_down3,(enemy3_x[j],enemy3_y[j]))
                            score+=3
                            del enemy3_x[j]
                            del enemy3_y[j]
                            del enemy3_blood[j]
                            break
                        
        #英雄机被普通敌机装死
        for i in range(len(enemy1_x)):
            if enemy1_x[i]>heroX-enemy1.get_width() and enemy1_x[i]<heroX+enemy1.get_width():
                if enemy1_y[i]>heroY-enemy1.get_height() and enemy1_y[i]<heroY+enemy1.get_height():
                    isgameover=0
                    screen.blit(hero_down,(heroX,heroY))

        #英雄机被中级敌机装死
        for i in range(len(enemy2_x)):
            if enemy2_x[i]>heroX-enemy2.get_width() and enemy2_x[i]<heroX+enemy2.get_width():
                if enemy2_y[i]>heroY-enemy2.get_height() and enemy2_y[i]<heroY+enemy2.get_height():
                    isgameover=0
                    screen.blit(hero_down,(heroX,heroY))

        #英雄机被高级敌机装死
        for i in range(len(enemy3_x)):
            if enemy3_x[i]>heroX-enemy3.get_width() and enemy3_x[i]<heroX+enemy3.get_width():
                if enemy3_y[i]>heroY-enemy3.get_height() and enemy3_y[i]<heroY+enemy3.get_height():
                    isgameover=0
                    screen.blit(hero_down,(heroX,heroY))

    elif isgameover==0:
        screen.blit(gameover,(0,0))
    else:
        num=0             #计数器初始化
        heroX=200         #英雄机的X坐标
        heroY=400         #英雄机的Y坐标
        enemy1_x=[]       #普通敌机的X坐标列表
        enemy1_y=[]       #普通敌机的Y坐标列表
        enemy2_x=[]       #中级敌机的X坐标列表
        enemy2_y=[]       #中级敌机的Y坐标列表
        enemy2_blood=[]   #中级敌机的血量标列表
        enemy3_x=[]       #高级敌机的X坐标列表
        enemy3_y=[]       #高级敌机的Y坐标列表
        enemy3_blood=[]   #高级敌机的血量列表
        flag=0            #子弹的切换
        bullet_x=[]       #子弹的X坐标列表
        bullet_y=[]       #子弹的Y坐标列表
        score=0           #将得分初始化
        isgameover=1      #游戏重新开始
    #将屏幕更新
    pygame.display.update()

    #实现窗口退出
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            pygame.quit()
            exit()
        if event.type==KEYDOWN:
            if event.key==K_a:
                flag=0
            if event.key==K_s:
                flag=1
            if event.key==K_SPACE:
                if isgameover==0:
                    isgameover=2 
                
            


            
