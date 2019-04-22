import pygame #导入pygame工具包
import time #导入时间工具
import random #导入随机数工具包

pygame.init() #检查工具箱

sc=pygame.display.set_mode((480,800),0,32) #新建指定大小的窗体
bg=pygame.image.load('background.png') #载入背景图片

#载入飞机图片
hero0 = pygame.image.load('hero0.png') 
hero1 = pygame.image.load('hero1.png')

#载入敌机1
enemy1 = pygame.image.load('enemy1.png')

#载入子弹
bullet = pygame.image.load('bullet.png')


#定义列表，存放敌机1的位置
enemy1_x=[] #存放x坐标
enemy1_y=[] #存放y坐标


#定义飞机的位置以及计数器
herox=240
heroy=400
num=0

#定义列表，存放子弹的位置
bullet_x=[]
bullet_y=[]

while True:
      sc.blit(bg,(0,0)) #贴背景
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

    
                             
      
      pygame.display.update() #刷新屏幕

      #实现窗体关闭
      for event in pygame.event.get():
            if event.type == pygame.QUIT:
                  pygame.quit()
