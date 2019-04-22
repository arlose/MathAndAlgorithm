import pygame #导入pygame工具包
import time #导入时间工具

pygame.init() #检查工具箱

sc=pygame.display.set_mode((480,800),0,32) #新建指定大小的窗体
bg=pygame.image.load('background.png') #载入背景图片

#载入飞机图片
hero0 = pygame.image.load('hero0.png') 
hero1 = pygame.image.load('hero1.png')

#定义飞机的位置以及计数器
herox=240
heroy=400
num=0

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
      
      pygame.display.update() #刷新屏幕

      #实现窗体关闭
      for event in pygame.event.get():
            if event.type == pygame.QUIT:
                  pygame.quit()
