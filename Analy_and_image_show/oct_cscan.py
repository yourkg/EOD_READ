import numpy as np
import cv2
from PIL import Image
import matplotlib.pyplot as plt

img_len = 700*432*1
k=1024
list_img = []
oct_dat = []

#读取dat数据，转换为图片保存
with open("od-3dscan-macular-20210104-150822-001.dat", "rb") as f:
    f.read(k)
    while True:
        a = f.read(img_len)
        if not a:
            break
        if len(a) == 120:
            break
        a = list(map(int, a))
        img_read = np.array(a,dtype=np.uint8).reshape((432,700,1))
        img_read=img_read.reshape(432,700)
        img_read=Image.fromarray(img_read)
        img_readd=np.array(img_read.transpose(Image.ROTATE_90))
        oct_dat.append(img_readd)
    print("Ok")

#cscan，700层相加
oct_cscan = []
for i in range(120):
    one_cscan = []
    for k in range(432):
        cscan = 0
        for j in range(700):
            cscan = cscan + oct_dat[i][j][k]
        one_cscan.append(cscan)
    oct_cscan.append(one_cscan)
#print(oct_cscan[1])



#归一化处理，0~255
ymax = 255
ymin = 0
xmax = max(map(max, oct_cscan))
xmin = min(map(min, oct_cscan))

array = np.random.rand(120, 432)
for i in range(120):
    for j in range(432):
        array[i][j] = round(((ymax - ymin) * (oct_cscan[i][j] - xmin) / (xmax - xmin)) + ymin)
#print(len(array[1]))


#画出cscan的灰度图
img_cscan = Image.fromarray(array)
if img_cscan.mode == "F":
    img_cscan = img_cscan.convert('RGB')
img_cscan.save("oct_cscan.png")
#读取图片,读取图片进行放大处理
image=cv2.imread("oct_cscan.png")
#按尺寸进行缩放
image_resize_0=cv2.resize(image,(432,432))
cv2.imwrite("oct_cscan.png", image_resize_0)