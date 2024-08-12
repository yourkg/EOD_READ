#include <iostream>
#include <fstream>
#include <malloc.h>
#include <string>
#include "x08middleware_common.h"
#include <opencv2/opencv.hpp>
#include <bitset>
#include <Windows.h>
#include "spline.h"
using namespace std;

typedef unsigned char uint8;
typedef unsigned short uint16;

#define PI 3.1415926535

int left_delet_line = 0;
int right_delet_line = 0;

void mouseCallfuc(int event, int x, int y, int flags, void* param) {
	cv::Mat *okk = (cv::Mat *)param;
	if (event == cv::EVENT_MOUSEMOVE) {
		if (flags & cv::EVENT_FLAG_LBUTTON) {
			string text = to_string(x) + "," + to_string(y);
			cv::putText(*okk, text, cv::Point(50,50), 1, 5, cv::Scalar(255));
		}
	}
}

void lambda2kplus(uchar* pa, double* pb, int alen, double l_nm, double r_nm) {
	/*
	version 1.1 yang
	arr:	 input array
	alen:    input array lenth
	l_nm:    left 波长,nm
	r_nm:    right 波长,nm
	*/
	/*

	l_nm *= 0.000001;
	double l_k = 2 * PI / l_nm;
	r_nm *= 0.000001;
	double r_k = 2 * PI / r_nm;

	double step_nm = abs(r_nm - l_nm) / (len - 1);
	double step_k = abs(l_k - r_k) / (len - 1);

	double x_nm[2048] = { 0 }, x_k[2048] = { 0 },y_k[2048]={0}, x_k_[2048] = {0};
	for (int i = 0; i < 2048; i++) {
		x_nm[i] = l_nm + i * step_nm;
		x_k[i] = 2 * PI / x_nm[i];
		y_k[i] = (double)arr[i];
		x_k_[i] = l_k - step_k * i;
	}
	*/
	//for (int i = 0; i < len; i++)
	//	cout <<" x_nm:" << x_nm[i] << "  x_k:" <<x_k[i]<<"  y_k:"<<y_k[i]<<"  x_k_:"<<x_k_[i]<< endl;
	/*
	vector<double> out_arr(len);
	for (int i = 0; i < len; i++) {
		if (i == 0) {
			out_arr[i] = y_k[i];
			continue;
		}
		for (int j = 0; j < len; j++) {
			//cout << "=>" << x_k_[i] << "  " << x_k[j] << "  " << x_k[j + 1] << endl;
			if (x_k_[i]>x_k[j + 1] && x_k_[i]<x_k[j]) {
				//cout << "->" << (x_k_[i] - x_k[j]) / (x_k[j + 1] - x_k[j]) << "   ->" << (y_k[j + 1] - y_k[j]) << "  ->" << y_k[j]<<endl;
				
				out_arr[i] = y_k[j] + (y_k[j+1] - y_k[j]) * (x_k_[i] - x_k[j]) / (x_k[j+1] - x_k[j]);
				break;
			}
		}
	}*/

	//for (int i = 0; i < len; i++)
		//cout << (int)arr[i] << " " << out_arr[i] << endl;
	
	l_nm *= 0.000001;
	r_nm *= 0.000001;
	double left = 2 * PI / l_nm;
	double right = 2 * PI / r_nm;
	double step_nm = abs(r_nm - l_nm) / (alen - 1);
	double step = abs(left - right) / (alen-1);

	
	pb[0] = (double)pa[0];
	for (int i = 0; i < alen; i++) {
		while (1) {
			if (left - step > 2 * PI / (l_nm + step_nm))break;
			l_nm += step_nm;
		}
		pb[i + 1] = pa[i] + (pa[i + 1] - pa[i])* ((2 * PI / l_nm) - (left - step)) / ((2 * PI / l_nm) - (2 * PI / (l_nm + step_nm)));
		left -= step;
	}
	return ;
}


int main()
{
	//ofstream ofile("new_sys_spectrum.csv", ios::out);
	//if (!ofile.is_open()) {
	//	cout << "sys_spectrum.txt okk" << endl;
	//	return 0;
	//}

	ifstream inFile("qwer", ios::in | ios::binary);
	if (!inFile) {
		cout << "error" << endl;
		return 0;
	}
	
	//int readedBytes = inFile.gcount();
	vector<int> my_arr;
	//inFile.seekg(8, ios::beg);
	long long numberS = 0;
	inFile.read((char*)&numberS, 8);
	cout << (hex) << numberS << (dec) << endl;
	int loc_kg = 8;
	int this_socket_bock = 0;

	int ijk = 0;
	cv::Mat img_thisBscan = cv::Mat::zeros(cv::Size(1000, 1024), CV_8U);

	vector<vector<int>> my_arr_3;
	cv::namedWindow("光谱FFT_log");
	while(!inFile.eof()) {
		
		uint16 n1, n2;
		int this_tell = inFile.tellg();
		if (this_socket_bock == 88 && loc_kg==1128) {
			inFile.seekg(60,ios::cur);
			long long numberS = 0;
			inFile.read((char*)&numberS, 8);

			cout << (hex) << numberS << (dec) <<"<---------------------------epoch" << endl;
			loc_kg = 8;
			this_socket_bock = 0;
			int num = 0;
			inFile.read((char*)&num, 3);//00B 800
			//cout << "num " << (hex) << num << (dec) << endl;
			loc_kg += 3;
			//cout << bitset<24>(num)<< endl;
			uint8 c1, c2, c3;
			c1 = num;
			c2 = num >> 8;
			c3 = num >> 16;
			uint8 c2_left, c2_right;
			c2_left = c2 >> 4;
			c2_right = c2 << 4;
			c2_right = c2_right >> 4;
			//cout << bitset<8>(c1) << " " << bitset<8>(c2) << " " << bitset<8>(c3) << endl;
			//cout << bitset<8>(c2_left) << " " << bitset<8>(c2_right) << endl;

			n1 = c1;
			n1 = n1 << 4;
			n1 = n1 + c2_right;
			n2 = c3;
			n2 = n2 << 4;
			n2 = n2 + c2_left;
			//cout << bitset<16>(n1)<<" " << n1<< "\n" << bitset<16>(n2)<<" "<<n2<<"  ->"<< inFile.gcount()<<" -->"<< this_tell<< endl;
			//cout << "-----------------------------------size_arr" << my_arr.size() << endl;


		}else
		//cout << " ----------------------------------->" << loc_kg<<" "<<this_tell <<" arr_size:" << my_arr.size()<<"   bolck" << this_socket_bock << endl;
		if (loc_kg>=8930&&loc_kg<8933) {
			cout <<loc_kg<<" " <<this_tell<<"   **" <<loc_kg-8930<<" <-misplacement number!" << endl;
			int num1 = 0, num2 = 0, num3 = 0;
			long long number = 0;
			if (loc_kg == 8930) {
				inFile.read((char*)&num1, 2);
				cout <<(hex) << num1 <<(dec) << endl;


				inFile.read((char*)&number, 8);
				cout << (hex) << number << (dec)<< " number: " << (number>>(7*8)) << endl;


				inFile.read((char*)&num2, 1);
				cout << (hex) << num2 << (dec) << endl;

				num3 = num1 + (num2 << 16);
				cout <<(hex) << num3 << (dec) << endl;
				//inFile.seekg(1, ios::cur);
				//cout << " ---------------------------------------------------------------seek +1 = " << inFile.tellg() << endl;
				loc_kg = 9;
				//loc_kg_p++;
			}
			else if (loc_kg == 8931) {
				inFile.read((char*)&num1, 1);
				cout << (hex) << num1 << (dec) << endl;


				inFile.read((char*)&number, 8);
				cout << (hex) << number << (dec) << " number: " << (number >> (7 * 8)) << endl;


				inFile.read((char*)&num2, 2);
				cout << (hex) << num2 << (dec) << endl;

				num3 = num1 + (num2 << 8);
				cout << (hex) << num3 << (dec) << endl;
				//inFile.seekg(1, ios::cur);
				//cout << " ---------------------------------------------------------------seek +1 = " << inFile.tellg() << endl;
				loc_kg = 10;
				//loc_kg_p++;
			}
			else {
				//inFile.read((char*)&num1, 1);
				//cout <<"num1 " << (hex) << num1 << (dec) << endl;


				inFile.read((char*)&number, 8);
				cout << (hex) << number << (dec) << " number: " << (number >> (7 * 8)) << endl;


				inFile.read((char*)&num2, 3);
				//cout << "num2 " << (hex) << num2 << (dec) << endl;

				num3 = num2;
				cout << (hex) << num3 << (dec) << endl;
				//inFile.seekg(1, ios::cur);
				//cout << " ---------------------------------------------------------------seek +1 = " << inFile.tellg() << endl;
				loc_kg = 11;
				//loc_kg_p++;
			}
			this_socket_bock++;

			int num = num3;
			//cout << "num " << (hex) << num << (dec) << endl;
			//cout << bitset<24>(num)<< endl;
			uint8 c1, c2, c3;
			c1 = num;
			c2 = num >> 8;
			c3 = num >> 16;
			uint8 c2_left, c2_right;
			c2_left = c2 >> 4;
			c2_right = c2 << 4;
			c2_right = c2_right >> 4;
			//cout << bitset<8>(c1) << " " << bitset<8>(c2) << " " << bitset<8>(c3) << endl;
			//cout << bitset<8>(c2_left) << " " << bitset<8>(c2_right) << endl;

			n1 = c1;
			n1 = n1 << 4;
			n1 = n1 + c2_right;
			n2 = c3;
			n2 = n2 << 4;
			n2 = n2 + c2_left;
			//cout << bitset<16>(n1)<<" " << n1<< "\n" << bitset<16>(n2)<<" "<<n2<<"  ->"<< inFile.gcount()<<" -->"<< this_tell<< endl;
			//cout << "-----------------------------------size_arr" << my_arr.size() << endl;
		}
		else {
			int num = 0;
			inFile.read((char*)&num, 3);//00B 800
			//cout << "num " << (hex) << num << (dec) << endl;
			loc_kg += 3;
			//cout << bitset<24>(num)<< endl;
			uint8 c1, c2, c3;
			c1 = num;
			c2 = num >> 8;
			c3 = num >> 16;
			uint8 c2_left, c2_right;
			c2_left = c2 >> 4;
			c2_right = c2 << 4;
			c2_right = c2_right >> 4;
			//cout << bitset<8>(c1) << " " << bitset<8>(c2) << " " << bitset<8>(c3) << endl;
			//cout << bitset<8>(c2_left) << " " << bitset<8>(c2_right) << endl;

			n1 = c1;
			n1 = n1 << 4;
			n1 = n1 + c2_right;
			n2 = c3;
			n2 = n2 << 4;
			n2 = n2 + c2_left;
			//cout << bitset<16>(n1)<<" " << n1<< "\n" << bitset<16>(n2)<<" "<<n2<<"  ->"<< inFile.gcount()<<" -->"<< this_tell<< endl;
			//cout << "-----------------------------------size_arr" << my_arr.size() << endl;

		}
		
		if (my_arr.size() == 2048) {
			cv::Mat img(4100, my_arr.size(), CV_8UC1);
			for (int i = 0; i < my_arr.size(); i++) {
				cv::line(img, cv::Point(i, 4100 - my_arr[i]), cv::Point(i, 4100 - my_arr[i + 1]), cv::Scalar(255), 2, 4);
			}
			cv::resize(img, img, cv::Size(), 0.5, 0.05);
			cv::imshow("光谱", img);
			//cv::waitKey(1);
			my_arr_3.push_back(my_arr);
			if (my_arr_3.size() > 33) {
				vector<vector<int>>::iterator k = my_arr_3.begin();
				my_arr_3.erase(k);
			}
			for (int i = 0; i < my_arr.size(); i++) {
				int sum=0;
				for (auto xx : my_arr_3) {
					sum += xx[i];
				}
				my_arr[i] = my_arr[i]-(int)(sum / 32);
			}

			cv::Mat img_(4100, my_arr.size(), CV_8UC1);
			for (int i = 0; i < my_arr.size(); i++) {
				cv::line(img_, cv::Point(i, 4100 - my_arr[i]), cv::Point(i, 4100 - my_arr[i + 1]), cv::Scalar(255), 2, 4);
			}
			cv::resize(img_, img_, cv::Size(), 0.5, 0.05);
			cv::imshow("减去背景光谱", img_);

			uchar* paa = (uchar*)malloc(sizeof(uchar) * 2048);
			for (int i = 0; i < 2048; i++)
				paa[i] = (uchar)my_arr[i];
			double* pnew = (double*)malloc(sizeof(double) * 2048);
			lambda2kplus(paa, pnew, 2048, 800, 900);
			
			cv::Mat img2(4100, 2048, CV_8UC1);
			for (int i = 0; i < 2048; i++) {
				cv::line(img2, cv::Point(i, 4100 - (int)pnew[i]), cv::Point(i, 4100 - (int)pnew[i + 1]), cv::Scalar(255), 2, 4);

			}
			cv::resize(img2, img2, cv::Size(), 0.5, 0.05);
			cv::imshow("插值后光谱", img2);
			cv::waitKey(1);
			free(paa);
			//double* test_out_IF = (double*)malloc(sizeof(double) * 2048);
			//IDFT(test_out, test_out_IF, 2048);

			cv::Mat line_k(1, 2048, CV_64F, pnew);

			cv::Mat plane[] = { line_k.clone(), cv::Mat::zeros(cv::Size(2048,1) , CV_64FC1)};
			cv::Mat complexIm;
			cv::merge(plane, 2, complexIm);
			idft(complexIm, complexIm, cv::DFT_INVERSE);

			split(complexIm, plane);
			//fftshift(plane[0], plane[1]);
			cv::Mat mag;// mag_log, mag_nor;
			magnitude(plane[0], plane[1], mag);

			cv::Mat img3(4100, 2048, CV_8UC1);
			for (int i = 0; i < 2048; i++) {
				cv::line(img3, cv::Point(i, 4100 - (int)mag.at<double>(0,i)), cv::Point(i, 4100 - (int)mag.at<double>(0, i+1)), cv::Scalar(255), 2, 4);
			}
			cv::resize(img3, img3, cv::Size(), 0.5, 0.05);
			cv::imshow("光谱FFT", img3);

			mag += 512;
			cv::log(mag, mag);
			normalize(mag, mag, 4095, 0, cv::NORM_MINMAX);


			//mag = mag * 3;
			cv::Mat img4(4100, 2048, CV_8UC1);
			for (int i = 0; i < 2048; i++) {
				//if (i<10)mag.at<double>(0, i) = cv::mean(mag).val[0];
				//else mag.at<double>(0, i) = mag.at<double>(0, i) + 800;
				//if (mag.at<double>(0, i) > 3000)mag.at<double>(0, i) = 3000;
				
				cv::line(img4, cv::Point(i, 4100 - (int)mag.at<double>(0, i)), cv::Point(i, 4100 - (int)mag.at<double>(0, i + 1)), cv::Scalar(255), 2, 4);
			}
			cv::resize(img4, img4, cv::Size(), 0.5, 0.05);
			cv::imshow("光谱FFT_log", img4);
			cv::setMouseCallback("光谱FFT_log", mouseCallfuc,&img4);
			//cv::imshow("光谱FFT_log", img4);

			cv::Mat mag_T = mag.t()(cv::Rect(0, 0, 1, 1024));
			double Min = 0.0, Max = 0.0;
			double* minp = &Min;
			double* maxp = &Max;
			minMaxIdx(mag_T, minp, maxp);
			if (Min != Max) {
				mag_T.convertTo(img_thisBscan.col(ijk), CV_8U, 255.0 / (Max - Min), -255.0 * Min / (Max - Min));//转换
			}
			free(pnew);
			cv::Mat clahe_img = img_thisBscan.clone();
			cv::Mat clahe_dst;
			cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
			clahe->setClipLimit(32.);   
			clahe->setTilesGridSize(cv::Size(120,100)); 
			clahe->apply(clahe_img, clahe_dst);
			cv::Mat img_thisBscan_show;
			cv::resize(img_thisBscan, img_thisBscan_show, cv::Size(), 2, 0.3);

			//cv::blur(img_thisBscan_show, img_thisBscan_show, cv::Size(3, 3));
			cv::imshow("BSCAN_ALINE_TIME", img_thisBscan_show);
			
			ijk++;
			if (ijk >= 1000)ijk = 0;
			
			//for (auto val : my_arr) {
			//	ofile << val << ",";
			//}
			//ofile << endl;

			my_arr.clear();
			//vector<int>::iterator k = my_arr.begin();
			//my_arr.erase(k);
			//my_arr.erase(k+1);
		}

		my_arr.push_back(n1);
		my_arr.push_back(n2);
		
	}
	inFile.close();
	//ofile.close();
	return 0;


	/*
	ifstream myfile("od-3dscan-macular-20210104-150822-001_analy.dat", ios::in | ios::binary);
	myfile.seekg(16, ios::beg);
	vector<vector<vector<int>>> list_img;
	for (int i = 0; i < 120; i++) {
		vector<vector<int>> list_7line;
		for (int j = 0; j < 7; j++) {
			vector<int> list_point;
			for (int k = 0; k < 1024; k++) {
				int num = 0;
				myfile.read((char*)&num, sizeof(int));
				list_point.push_back(int(num));
			}
			list_7line.push_back(list_point);
		}
		list_img.push_back(list_7line);
	}


	for (auto i : list_img) {
		cv::Mat img(500, 1000, CV_8UC3);
		int colorr = 0;
		for (auto j : i) {
			for (int k = 0; k < 1024; k++)
				cv::line(img, cv::Point(k, 700 - j[k]), cv::Point(k, 700 - j[k] - 1), cv::Scalar(255, 255 - colorr, colorr), 1, 4);
			colorr += int(255 / 7);
		}
		cv::imshow("okk?", img);
		cv::waitKey(0);
	}



	//return 0;





	

    OCTFileHeaderV4 s; 
	
	unsigned char *p_img=(unsigned char *)malloc(432*700*sizeof(unsigned char));
	      
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
	
	for(int i=0;i<120;i++){
		inFile.read((char *)p_img, 432*700*sizeof(unsigned char));
		cv::Mat img(432, 700, CV_8U, p_img);
		cv::rotate(img, img,cv::ROTATE_90_COUNTERCLOCKWISE);

		cv::Mat showImg;
		cv::cvtColor(img, showImg, cv::COLOR_GRAY2RGB);
		int colorr = 0;
		for (auto j : list_img[i]) {
			for (int k = 0; k < 1024; k++)
				cv::line(showImg, cv::Point(k, 700 - j[k]), cv::Point(k, 700 - j[k] - 1), cv::Scalar(255, 255 - colorr, colorr), 1, 4);
			colorr += int(255 / 7);
		}

		cv::imshow("", showImg);
		cv::waitKey(0);         
		
		//for(int j=0;j<432*700;j++){
			//cout<<*(p_img+j)<<" ";
		//	printf("%d  ",*(p_img+j));
		//	if(j%700==0)cout<<endl;
		//}
		//break;
	}
	
    inFile.close();
	*/
    return 0;
}
