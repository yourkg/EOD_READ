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
	
	
	cout<<s.szSignature<<"\t�ļ�ͷУ�����Ϊ'EOD\\0'\n";
	cout<<s.nFileVersion<<"\t�ļ��汾\n";
	cout<<"scanDataHeader��\n";
	cout<<s.scanDataHeader.nDataType<<"\t�������ͣ�[0��ԭʼ���ݣ�1��ͼ������]\n";
	cout<<s.scanDataHeader.nFrames<<"\tb-scan��Ŀ\n";
	cout<<s.scanDataHeader.nWidth<<"\tb-scan��\n";
	cout<<s.scanDataHeader.nHeight<<"\tb-scan��\n";
	cout<<s.scanDataHeader.nBytesPerPixel<<"\t������ȣ�[2��ԭʼ���ݣ�1��ͼ������]\n";
	cout<<s.scanDataHeader.nDataOffset<<"\tƫ�ƣ�[�ļ���ͷ��'��һ������'��ƫ�ƣ���С�൱���ļ�ͷ�ĳ���]\n";
	cout<<s.scanDataHeader.nCompressType<<"\t�Ƿ�ѹ����0��ʾûѹ��������û����\n";
	cout<<"OCTPatientScanInfoV4��\n";
	cout<<s.patientInfo.szPatientID<<"\t���ߺţ�[UTF16�����ַ���]\n";
	cout<<s.patientInfo.szName<<"\t���֣�[UTF16�����ַ���]\n";
	cout<<s.patientInfo.nGender<<"\t�Ա�[1���У�0��Ů��2������]\n";
	cout<<s.patientInfo.szBirthDay<<"\t���գ�[UTF16�����ַ���]\n";
	cout<<s.patientInfo.szEmail<<"\t���䣬[UTF16�����ַ���]\n";
	cout<<s.patientInfo.szTel<<"\t�绰��[UTF16�����ַ���]\n";
	cout<<s.patientInfo.tCheckTime<<"\t���ʱ��\n";
	cout<<s.patientInfo.nScanType<<"\tɨ�����ͣ�[0������Ĥ��1�ǽ�Ĥ]\n";
	cout<<s.patientInfo.nScanPart<<"\tɨ�貿λ��[0�ưߣ�1���̣�2CT��3ACA?��4AC?��5����Ĥ��6��Ĥ��7PRETINA FUNDUS]\n";
	cout<<s.patientInfo.nScanMode<<"\tɨ��ģʽ��[03D_SCAN��1��դ��2���Σ�3����4HDScan��5HD5line]\n";
	cout<<s.patientInfo.nEye<<"\t�����ۣ�[0�����ۣ�1������]\n";
	cout<<s.patientInfo.szDoctor<<"\tҽ����[UTF16�����ַ���]\n";
	cout<<s.patientInfo.nFixationPos[0]<<","<<s.patientInfo.nFixationPos[1]<<"\tLED�̶�λ��\n";
	cout<<s.patientInfo.fScanCenter[0]<<","<<s.patientInfo.fScanCenter[1]<<"\tɨ��������λ��\n";
	cout<<s.patientInfo.fScanAngle<<"\tɨ������ת�Ƕȣ������ڸ���һ��\n";
	cout<<s.patientInfo.fScale[0]<<","<<s.patientInfo.fScale[1]<<"\tɨ������߱������ӣ�\n";
	cout<<s.patientInfo.fxCenterRatio<<"\t����ɨ������X��c-scan����X֮��\n";
	cout<<s.patientInfo.fyCenterRatio<<"\t����ɨ������Y��c-scan����Y֮��\n";
	cout<<s.patientInfo.fPreviewLengthX<<"\tԤ��ɨ��x����(mm)��\n";
	cout<<s.patientInfo.fPreviewLengthY<<"\tԤ��ɨ��y����(mm)��\n";
	cout<<s.patientInfo.fAcqLengthX<<"\t�ɼ�x����(mm)��\n";
	cout<<s.patientInfo.fAcqLengthY<<"\t�ɼ�y����(mm)��\n";
	cout<<s.patientInfo.fAxialResolution<<"\t����ֱ���(mm)��\n";
	//cout<<s.Reserved<<"����"; 
	
	
    inFile.close();
    return 0;
}
