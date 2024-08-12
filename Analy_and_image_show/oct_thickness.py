import numpy as np
import cv2
from PIL import Image
import matplotlib.pyplot as plt
from numpy import arange
import numpy as np
import pandas as pd
import seaborn as sns
import os
import random





#

pix_x=6/700
pix_y=6/432
pix_z=0.00244141

print(pix_x,pix_y,pix_z)
#




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
        thickness = oct_pos[i][1][j] - oct_pos[i][2][j]
        one_thickness.append(thickness)
    oct_thickness.append(one_thickness)
max_=0
min_=0
for i in range(len(oct_thickness)):
    for j in range(len(oct_thickness[0])):
        if max_<oct_thickness[i][j]:
            max_=oct_thickness[i][j]
        if min_>oct_thickness[i][j]:
            min_=oct_thickness[i][j]

print(max_*1000*pix_z,min_*1000*pix_z)


#print(oct_thickness[0])
#print(len(oct_thickness[1]))
#根据厚度信息赋予颜色值
img2_array = np.zeros((120,432,3))
#厚度放大
for i in range(120):
    for j in range(432):
        oct_thickness[i][j] = oct_thickness[i][j]*1000
#归一化到0~255
#归一化处理，0~255
ymax = 255
ymin = 0
xmax = max(map(max, oct_thickness))
xmin = min(map(min, oct_thickness))

array = np.random.rand(120, 432)
for i in range(120):
    for j in range(432):
        array[i][j] = round(((ymax - ymin) * (oct_thickness[i][j] - xmin) / (xmax - xmin)) + ymin)
print(array)

for i in range(120):
    for j in range(432):
        color_g = array[i][j]
        #print(color_g)
        #print([255,color_g,0])
        n = random.randint(0,155)
        if color_g>127:
            color = [0,(255-color_g)*255//127,255]
        else:
            color = [0,255,color_g*255//127]
        #print(color)
        img2_array[i,j] = color



print(img2_array)
img2_array = np.array(img2_array,dtype="uint8")
cv2.imshow("z",img2_array)
cv2.waitKey(0)
cv2.imwrite("oct_thickness.png", img2_array)
#读取图片,读取图片进行放大处理
image=cv2.imread("oct_thickness.png")
#按尺寸进行缩放
image_resize_0=cv2.resize(image,(432,432))
cv2.imwrite("oct_thickness.png", image_resize_0)
