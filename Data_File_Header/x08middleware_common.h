#ifndef X08MIDDLEWARE_COMMON_H
#define X08MIDDLEWARE_COMMON_H

#include <stdint.h>
#include <time.h>

typedef struct IMAGE_SPLIT_HEADER
{
    uint32_t   nVersion;       // 版本
    uint32_t   nLineCount;     // 每一帧线条数
    uint32_t   nRealCount;     // 每条线的实际个数
    unsigned char   Reserved[4];       // 预留字段
} ImageSplitHeader;

typedef struct {
    double averageThickness;    // RFNL 厚度平均值
    double symmetry;            // RFNL 比例
    double rimArea;             // 盘沿面积
    double discArea;            // 视盘面积
    double averageCDR;          // 平均杯盘比
    double verticalCDR;         // 垂直杯盘比
    double cupVolume;           // 杯容积
    double discCenter[2];       // 视盘中心
    double discedgeThickness[512]; // 盘沿厚度
    double placeholder[50];     // 占位
} DiscInfo;

typedef struct
{
    double edgeThickness[512]; //长度512需要确认, 高度unsigned short需确认
} NeuralRetina;

typedef struct
{
    unsigned int    version;     // 版本
    DiscInfo        discInfo;
    NeuralRetina    neuralRetina;
} Disc3dReport;

typedef struct _OCT_SCAN_DATA_HEADER
{
    unsigned int	nDataType;				// 0 for raw data, 1 for image data
    unsigned int	nFrames;
    unsigned int	nWidth;
    unsigned int	nHeight;
    unsigned int	nBytesPerPixel;			// 2 for raw data, 1 for image data
    unsigned int	nDataOffset;
    unsigned int	nCompressType;			// 0 for non-compressed, others TBD
}OCTScanDataHeader;

typedef struct _OCT_PATIENT_SCAN_INFO
{
    unsigned char	szPatientID[60];		// string encoded by UTF16
    unsigned char	szName[60];				// string encoded by UTF16
    unsigned int	nGender;				// 1 for male, 0 for female , 2 is other
    unsigned char	szBirthDay[22];			// string encoded by UTF16
    unsigned char	szEmail[100];			// string encoded by UTF16
    unsigned char	szTel[40];				// string encoded by UTF16
    time_t			tCheckTime;
    unsigned int	nScanType;              // ST_RETINA = 0, ST_CORNEA = 1
    unsigned int	nScanPart;              // SP_MACULAR = 0, SP_DISC = 1,SP_CT = 2,SP_ACA = 3, SP_AC = 4,
    // SP_OTHER_RETINA = 5, SP_OTHER_CORNEA = 6,S_PRETINA_FUNDUS = 7;
    unsigned int	nScanMode;              // SM_3D_SCAN=0, SM_GENERAL_RASTER=1, SM_GENERAL_CIRCLE=2, SM_GENERAL_RADIAL=3,
    // SM_HD_SCAN=4, SM_HD_5LINE=5
    unsigned int	nEye;					// 0 for left eye, 1 for right eye
    unsigned char	szDoctor[60];			// string encoded by UTF16
    unsigned int	nFixationPos[2];		// Fixation LED pos(x, y)
    double			fScanCenter[2];			// center position of the scan area
    double			fScanAngle;				// rotate angle of the scan line, use only by single line High Definition scan pattern
    double			fScale[2];				// scale factor for width and height of the scan area
    unsigned char fPreviewLengthX;
    unsigned char fPreviewLengthY;
    unsigned char fAcqLengthX;
    unsigned char fAcqLengthY;
    unsigned char fxCenterRatioH; // 该死的大端, 无法转short
    unsigned char fxCenterRatioL;
    unsigned char fyCenterRatioH;
    unsigned char fyCenterRatioL;
    char Reserved[48];
} OCTPatientScanInfoV1;

typedef struct
{
    unsigned char	szPatientID[60];		// string encoded by UTF16
    unsigned char	szName[60];				// string encoded by UTF16
    unsigned int	nGender;				// 1 for male, 0 for female , 2 is other
    unsigned char	szBirthDay[22];			// string encoded by UTF16
    unsigned char	szEmail[100];			// string encoded by UTF16
    unsigned char	szTel[40];				// string encoded by UTF16
    time_t			tCheckTime;
    unsigned int	nScanType;              // ST_RETINA = 0, ST_CORNEA = 1
    unsigned int	nScanPart;              // SP_MACULAR = 0, SP_DISC = 1,SP_CT = 2,SP_ACA = 3, SP_AC = 4,
    // SP_OTHER_RETINA = 5, SP_OTHER_CORNEA = 6,S_PRETINA_FUNDUS = 7;
    unsigned int	nScanMode;              // SM_3D_SCAN=0, SM_GENERAL_RASTER=1, SM_GENERAL_CIRCLE=2, SM_GENERAL_RADIAL=3,
    // SM_HD_SCAN=4, SM_HD_5LINE=5
    unsigned int	nEye;					// 0 for left eye, 1 for right eye
    unsigned char	szDoctor[60];			// string encoded by UTF16
    unsigned int	nFixationPos[2];		// Fixation LED pos(x, y)
    double			fScanCenter[2];			// center position of the scan area
    double			fScanAngle;				// rotate angle of the scan line, use only by single line High Definition scan pattern
    double			fScale[2];				// scale factor for width and height of the scan area

    double          fxCenterRatio;          //  ratio of area scanning center X to enface center point X
    double          fyCenterRatio;          //  ratio of area scanning center Y to enface center point Y
    double          fPreviewLengthX;        //  oct preview x scan length (mm)
    double          fPreviewLengthY;        //  oct preview y scan length (mm)
    double          fAcqLengthX;            //  oct  capture x length (mm)
    double          fAcqLengthY;            //  oct  capture y length (mm)
    char Reserved[8];
} OCTPatientScanInfoV3;

typedef struct
{
    unsigned char	szPatientID[60];		// string encoded by UTF16
    unsigned char	szName[60];				// string encoded by UTF16
    unsigned int	nGender;				// 1 for male, 0 for female , 2 is other
    unsigned char	szBirthDay[22];			// string encoded by UTF16
    unsigned char	szEmail[100];			// string encoded by UTF16
    unsigned char	szTel[40];				// string encoded by UTF16
    time_t			tCheckTime;
    unsigned int	nScanType;              // ST_RETINA = 0, ST_CORNEA = 1
    unsigned int	nScanPart;              // SP_MACULAR = 0, SP_DISC = 1,SP_CT = 2,SP_ACA = 3, SP_AC = 4,
    // SP_OTHER_RETINA = 5, SP_OTHER_CORNEA = 6,S_PRETINA_FUNDUS = 7;
    unsigned int	nScanMode;              // SM_3D_SCAN=0, SM_GENERAL_RASTER=1, SM_GENERAL_CIRCLE=2, SM_GENERAL_RADIAL=3,
    // SM_HD_SCAN=4, SM_HD_5LINE=5
    unsigned int	nEye;					// 0 for left eye, 1 for right eye
    unsigned char	szDoctor[60];			// string encoded by UTF16
    unsigned int	nFixationPos[2];		// Fixation LED pos(x, y)
    double			fScanCenter[2];			// center position of the scan area
    double			fScanAngle;				// rotate angle of the scan line, use only by single line High Definition scan pattern
    double			fScale[2];				// scale factor for width and height of the scan area

    double          fxCenterRatio;          //  ratio of area scanning center X to enface center point X
    double          fyCenterRatio;          //  ratio of area scanning center Y to enface center point Y
    double          fPreviewLengthX;        //  oct preview x scan length (mm)
    double          fPreviewLengthY;        //  oct preview y scan length (mm)
    double          fAcqLengthX;            //  oct  capture x length (mm)
    double          fAcqLengthY;            //  oct  capture y length (mm)
    double          fAxialResolution;       //  oct  axial resolution (mm)
} OCTPatientScanInfoV4;

typedef struct _OCT_FILE_HEADER_V1
{
    unsigned char		 szSignature[4];		// should be string "EOD\0"
    unsigned int		 nFileVersion;		// current version 3
    OCTScanDataHeader	 scanDataHeader;
    OCTPatientScanInfoV1 patientInfo;
    unsigned char		 Reserved[504]; //560 -48(fxCenterScale and fyCenterScale)    // the 0,1, saved  preview scan length x y, 2，3 saved acq scan length x y , (mm)
}OCTFileHeaderV1;

typedef struct _OCT_FILE_HEADER_V3
{
    unsigned char		 szSignature[4];		// should be string "EOD\0"
    unsigned int		 nFileVersion;		// current version 3
    OCTScanDataHeader	 scanDataHeader;
    OCTPatientScanInfoV3 patientInfo;
    unsigned char		 Reserved[504]; //560 -48(fxCenterScale and fyCenterScale)    // the 0,1, saved  preview scan length x y, 2，3 saved acq scan length x y , (mm)
}OCTFileHeaderV3;

typedef struct _OCT_FILE_HEADER_V4
{
    unsigned char		 szSignature[4];		// should be string "EOD\0"
    unsigned int		 nFileVersion;		// current version 3
    OCTScanDataHeader	 scanDataHeader;
    OCTPatientScanInfoV4 patientInfo;
    unsigned char		 Reserved[504]; //560 -48(fxCenterScale and fyCenterScale)    // the 0,1, saved  preview scan length x y, 2，3 saved acq scan length x y , (mm)
}OCTFileHeaderV4;

#endif // X08MIDDLEWARE_COMMON_H
