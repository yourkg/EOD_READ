"""


"""

import cv2
import numpy as np

if __name__=="__main__":

    
    list_img=[]
    with open("od-3dscan-macular-20210104-150822-001_analy.dat", "rb") as f:
        f.seek(16)
        for i in range(120):
            list_7line=[]
            for j in range(7):
                list_point=[]
                for k in range(1024):
                    setpp = f.read(4)
                    list_point.append(int.from_bytes(setpp,byteorder='little',signed=False))
                list_7line.append(list_point)
            list_img.append(list_7line)

    for i in list_img:
        img = np.zeros((500, 1000, 3), np.uint8)
        colorr=0
        
        for j in i:
            l=0
            for k in j:
                cv2.line(img,(l,500-k),(l,500-k-1),(0,255-colorr,colorr),1,4)
                l+=1
            colorr+=int(255/7)

        cv2.imshow("okk?",img)
        cv2.waitKey(0)
