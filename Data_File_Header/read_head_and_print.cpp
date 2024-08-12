#include <iostream>
#include <fstream>
#include <malloc.h>
#include <string>
#include "x08middleware_common.h"
using namespace std;

typedef unsigned char uint8;

int main()
{
    OCTFileHeaderV4 s;       
    ifstream inFile("od-3dscan-macular-20210104-150822-001.dat",ios::in|ios::binary); 
    if(!inFile) {
        cout << "error" <<endl;
        return 0;
    }
    cout<<sizeof(s)<<endl;
    int i=0;
    inFile.read((char *)&s, sizeof(s)); 
    int readedBytes = inFile.gcount(); 
	
	
	cout<<s.szSignature<<"\t文件头校验必须为'EOD\\0'\n";
	cout<<s.nFileVersion<<"\t文件版本\n";
	cout<<"scanDataHeader：\n";
	cout<<s.scanDataHeader.nDataType<<"\t数据类型，[0是原始数据，1是图像数据]\n";
	cout<<s.scanDataHeader.nFrames<<"\tb-scan数目\n";
	cout<<s.scanDataHeader.nWidth<<"\tb-scan宽\n";
	cout<<s.scanDataHeader.nHeight<<"\tb-scan高\n";
	cout<<s.scanDataHeader.nBytesPerPixel<<"\t像素深度，[2是原始数据，1是图像数据]\n";
	cout<<s.scanDataHeader.nDataOffset<<"\t偏移，[文件开头到'第一个数据'的偏移，大小相当于文件头的长度]\n";
	cout<<s.scanDataHeader.nCompressType<<"\t是否压缩，0表示没压缩，其它没有用\n";
	cout<<"OCTPatientScanInfoV4：\n";
	cout<<s.patientInfo.szPatientID<<"\t患者号，[UTF16编码字符串]\n";
	cout<<s.patientInfo.szName<<"\t名字，[UTF16编码字符串]\n";
	cout<<s.patientInfo.nGender<<"\t性别，[1是男，0是女，2是其它]\n";
	cout<<s.patientInfo.szBirthDay<<"\t生日，[UTF16编码字符串]\n";
	cout<<s.patientInfo.szEmail<<"\t邮箱，[UTF16编码字符串]\n";
	cout<<s.patientInfo.szTel<<"\t电话，[UTF16编码字符串]\n";
	cout<<s.patientInfo.tCheckTime<<"\t检查时间\n";
	cout<<s.patientInfo.nScanType<<"\t扫描类型？[0是视网膜，1是角膜]\n";
	cout<<s.patientInfo.nScanPart<<"\t扫描部位？[0黄斑，1视盘，2CT，3ACA?，4AC?，5视网膜，6角膜，7PRETINA FUNDUS]\n";
	cout<<s.patientInfo.nScanMode<<"\t扫描模式，[03D_SCAN，1光栅，2环形，3径向，4HDScan，5HD5line]\n";
	cout<<s.patientInfo.nEye<<"\t左右眼，[0是左眼，1是右眼]\n";
	cout<<s.patientInfo.szDoctor<<"\t医生？[UTF16编码字符串]\n";
	cout<<s.patientInfo.nFixationPos[0]<<","<<s.patientInfo.nFixationPos[1]<<"\tLED固定位置\n";
	cout<<s.patientInfo.fScanCenter[0]<<","<<s.patientInfo.fScanCenter[1]<<"\t扫描区中心位置\n";
	cout<<s.patientInfo.fScanAngle<<"\t扫描线旋转角度，仅用于高清一线\n";
	cout<<s.patientInfo.fScale[0]<<","<<s.patientInfo.fScale[1]<<"\t扫描区宽高比例因子？\n";
	cout<<s.patientInfo.fxCenterRatio<<"\t区域扫描中心X与c-scan中心X之比\n";
	cout<<s.patientInfo.fyCenterRatio<<"\t区域扫描中心Y与c-scan中心Y之比\n";
	cout<<s.patientInfo.fPreviewLengthX<<"\t预览扫描x长度(mm)？\n";
	cout<<s.patientInfo.fPreviewLengthY<<"\t预览扫描y长度(mm)？\n";
	cout<<s.patientInfo.fAcqLengthX<<"\t采集x长度(mm)？\n";
	cout<<s.patientInfo.fAcqLengthY<<"\t采集y长度(mm)？\n";
	cout<<s.patientInfo.fAxialResolution<<"\t轴向分辨率(mm)？\n";
	//cout<<s.Reserved<<"保留"; 
	
	
    inFile.close();
    return 0;
}
