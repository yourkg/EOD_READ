import numpy as np
import cv2
from PIL import Image
import matplotlib.pyplot as plt
from numpy import arange
import numpy as np
import pandas as pd
import seaborn as sns
import os


#读取分界线坐标
img_len = 700*432*1
k=1024
list_img = []
with open("od-3dscan-macular-20210104-150822-001_analy.dat", "rb") as f:
    f.seek(16)
    for i in range(120):
        list_7line = []
        for j in range(7):
            list_point = []
            for k in range(1024):
                setpp = f.read(4)
                list_point.append(int.from_bytes(setpp, byteorder='little', signed=False))
            list_7line.append(list_point)
        list_img.append(list_7line)
#去掉0值
oct_pos = []
for pic_num in range(120):
    one_pos = []
    for i in range(7):
        line_pos = []
        point = list_img[pic_num][i]
        for m in point:
            if m == 0:
                break
            else:
                line_pos.append(700 - m )
        one_pos.append(line_pos)
    oct_pos.append(one_pos)
#print(oct_pos[0][6])

#整理分层的正确顺序



#相减得到0~1的厚度信息
oct_thickness = []
for i in range(120):
    one_thickness = []
    for j in range(432):
        thickness = oct_pos[i][0][j] - oct_pos[i][6][j]
        one_thickness.append(thickness)
    oct_thickness.append(one_thickness)
#print(oct_thickness[0])

#池化
t_polling = []
for i in range(24):
    one_polling = []
    h = 5*i
    for j in range (24):
        poll = 0
        w = j*18
        for m in range(5):
            for n in range(18):
                poll = oct_thickness[m+h][n+w]+poll
        one_polling.append(int(poll/90))
    t_polling.append(one_polling)

print(t_polling-np.asarray([50]))

#绘制厚度误差图
#假定标准的厚度是28
nom_thickness = 28
#误差记录表，1代表误差1%，5代表误差在5%，10代表误差在5%~95%，95代表误差在95%以上，99代表误差在99%以上
x = arange(576).reshape(24, 24)
for i in range(24):
    for j in range(24):
        # print(abs((t_polling[i][j]-nom_thickness)/nom_thickness))
        # print(i)
        # print(j)
        if abs((t_polling[i][j]-nom_thickness)/nom_thickness)>0.99:
            x[i][j] = 99
        elif abs((t_polling[i][j]-nom_thickness)/nom_thickness)>0.95:
            x[i][j] = 95
        elif abs((t_polling[i][j] - nom_thickness) / nom_thickness) > 0.5:
            x[i][j] = 10
        elif abs((t_polling[i][j] - nom_thickness) / nom_thickness) > 1:
            x[i][j] = 5
        else : x[i][j] = 1
# print(x)
# x[15][15] = 100;
# x[7][15] = 100;
# x[15][9] = 100;
# x[5][15] = 100;
# x[15][20] = 100;
# x[6][15] = 100;
# print(x)



#画出热力图
sns.set(rc={"figure.figsize":(4.32, 4.32)})
im = sns.heatmap(pd.DataFrame(np.round(x,4)),vmax=100,vmin=0,
                cbar = False,xticklabels=False,yticklabels=False,square=False,cmap='Accent')

im.figure.subplots_adjust(top=1,bottom=0,left=0,right=1,hspace=0.5,wspace=0.5)
im.figure.savefig("thickness_hot.png")



#file = Image.open('oct_cscan.png')
# file.show()
'''
## 图片背景透明化
def transPNG(srcImageName):
    img = Image.open(srcImageName)
    img = img.convert("RGBA")
    datas = img.getdata()
    newData = list()
    for item in datas:
        if item[0] > 220 and item[1] > 220 and item[2] > 220:
            newData.append((255, 255, 255, 50))
        else:
            newData.append(item)
    img.putdata(newData)
    return img


# 图片融合
def mix(img1,img2,coordinator):
    im = img1
    mark = img2
    print(img2,img1)
    #layer = Image.new('RGBA', im.size)
    #layer.paste(mark, coordinator)
    out = Image.composite(mark, im, mark)
    return out

co = (0,0)
verse = transPNG('thickness_hot.png')
file = transPNG('oct_cscan.png')
file = mix(file, verse, co)
#file.show()
file.save("oct_DeviationMap.png")
#os.remove("thickness_hot.png")
'''

img1 = cv2.imread('oct_cscan.png')
#cv2.imshow('img1',img1)
img2 = cv2.imread('thickness_hot.png')
#cv2.imshow('img2',img2)
new_img2np.zeros(img1.shape,dtype=np.uint8)
img2=cv2.resize(img2,(400,400))
new_img2[16:416,16:416]=img2
#cv2.imshow('new_img1',new_img1)
imgadd = cv2.add(cv2.resize(img1,(432,432)),cv2.resize(new_img2,(432,432)))
cv2.imshow('imgadd',imgadd)
cv2.waitKey(0)













