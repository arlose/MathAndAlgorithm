import pygame #导入pygame工具包
import time #导入时间工具
import random #导入随机数工具包
from pygame.locals import *

pygame.init() #检查工具箱

sc=pygame.display.set_mode((480,800),0,32) #新建指定大小的窗体
bg=pygame.image.load('background.png') #载入背景图片

#载入英雄飞机图片
hero0 = pygame.image.load('hero0.png') 
hero1 = pygame.image.load('hero1.png')
hero_down=pygame.image.load('hero_down.png')

#载入敌机1
enemy1 = pygame.image.load('enemy1.png')
enemy1_down1=pygame.image.load('enemy1_down1.png')
enemy1_down2=pygame.image.load('enemy1_down2.png')
enemy1_down3=pygame.image.load('enemy1_down3.png')

#载入子弹
bullet = pygame.image.load('bullet.png')


#载入游戏结束
gameover=pygame.image.load('gameover.png')
#图片大小不对，做大小调整
gameover=pygame.transform.scale(gameover,(480,800))

#定义列表，存放敌机1的位置
enemy1_x=[] #存放x坐标
enemy1_y=[] #存放y坐标

enemy1_blood = []
#定义飞机的位置以及计数器
herox=240
heroy=400
num=0

#定义列表，存放子弹的位置
bullet_x=[]
bullet_y=[]
#定义是否结束游戏
ifgameover=0
#定义分数
score=0
#创建字体

ft=pygame.font.Font('simsun.ttc',30)


while True:
      if ifgameover==0:
            sc.blit(bg,(0,0)) #贴背景
            text=ft.render('得分：'+str(score),True,(255,0,0))
            sc.blit(text,(10,10)) #贴得分
            #计数器加1
            num = num+1
            #实现飞机两个图片的切换喷气
            if num%2 ==1:            
                  sc.blit(hero0,(herox,heroy)) #贴飞机图片1
            else:
                  sc.blit(hero1,(herox,heroy)) #贴飞机图片2
            #每次循环等待一些时间 0.01
            time.sleep(0.01)

            #实现英雄级移动
            pos=pygame.mouse.get_pos() #获取鼠标指针位置
            herox=pos[0]-hero0.get_width()/2 #x坐标
            heroy=pos[1]-hero0.get_height()/2 #y坐标

            #添加敌机1
            if num%20==0:
                  enemy1_x.append(random.randint(0,480)) #随机的x坐标，存入列表
                  enemy1_y.append(0) #固定y到舞台上方
                  enemy1_blood.append(50)
            for i in range(len(enemy1_x)):
                  sc.blit(enemy1,(enemy1_x[i],enemy1_y[i]))
            #实现敌机1移动
            for i in range(len(enemy1_y)):
                  enemy1_y[i]+=1
                  #删除跑出舞台的飞机
                  if enemy1_y[i]>800:
                        del enemy1_x[i]
                        del enemy1_y[i]
                        break #跳出循环
         
            #添加子弹
            if num%10 ==0:      
                  bullet_x.append(herox+hero0.get_width()/2-bullet.get_width()/2)
                  bullet_y.append(heroy-bullet.get_height())
            #贴子弹
            for i in range(len(bullet_x)):
                  sc.blit(bullet,(bullet_x[i],bullet_y[i]))
            
            #子弹移动      
            for i in range(len(bullet_y)):
                  bullet_y[i]-=3
                  #删除舞台上方的子弹
                  if bullet_y[i]<0:
                        del bullet_x[i]
                        del bullet_y[i]
                        break

            #实现击中效果
            for j in range(len(enemy1_x)):
                  ifdel=0
                  for i in range(len(bullet_x)):
                        if (bullet_x[i]>enemy1_x[j]-bullet.get_width())and(bullet_x[i]<enemy1_x[j]+enemy1.get_width()):
                              if(bullet_y[i]>enemy1_y[j]-bullet.get_height())and(bullet_y[i]<enemy1_y[j]+enemy1.get_height()):
                                    #实现爆炸效果
                                    enemy1_blood[j] -= 1
                                    
                                    if enemy1_blood[j]<=0:
                                          sc.blit(enemy1_down1,(enemy1_x[j],enemy1_y[j]))
                                          sc.blit(enemy1_down2,(enemy1_x[j],enemy1_y[j]))
                                          sc.blit(enemy1_down3,(enemy1_x[j],enemy1_y[j]))
                                          #删除子弹
                                          
                                          
                                          del bullet_x[i]
                                          del bullet_y[i]
                                          score+=1
                                          ifdel=1
                                          break
                  if ifdel==1:
                        #删除敌机
                        del enemy1_x[j]  
                        del enemy1_y[j]
                        del enemy1_blood[j]
                        break

            #实现英雄机被撞效果
            for i in range(len(enemy1_x)):
                  if (enemy1_x[i]>herox-enemy1.get_width())and(enemy1_x[i]<herox+hero0.get_width()):
                        if(enemy1_y[i]>heroy-enemy1.get_height())and(enemy1_y[i]<heroy+hero0.get_height()):
                              #英雄机爆炸
                              sc.blit(hero_down,(herox,heroy))
                              ifgameover=1


      elif ifgameover==1:
            #游戏结束
            sc.blit(gameover,(0,0))
      else:
            num=0
            bullet_x=[]
            bullet_y=[]
            enemy1_x=[]
            enemy1_y=[]
            score=0
            ifgameover=0
      pygame.display.update() #刷新屏幕

      #实现窗体关闭
      for event in pygame.event.get():
            if event.type == pygame.QUIT:
                  pygame.quit()
            if event.type == pygame.KEYDOWN:
                  if event.key == K_SPACE:
                        ifgameover=2;
