#pragma once
#include <QTextCodec>
#define ToLocal8Bit( str ) \
	QString::fromLocal8Bit( str )
inline QString ToGbk(QString& input)
{
#if 1
	QTextCodec* codec = QTextCodec::codecForName("gbk");
	return QString::fromLatin1(codec->fromUnicode(input));
#else
	return input;
#endif
}


#define StrPrism ToLocal8Bit( "棱柱" )
#define StrPyramid ToLocal8Bit( "棱锥" )
#define StrRegularPolyhedron ToLocal8Bit( "球体" )
#define StrActerObj ToLocal8Bit( "道具对象" )

enum UserRole {
	Type = 1
};

enum Type {
	Prism = 0,
	Pyramid,
	RegularPolyhedron,
	StlModel,
	ObjModel,
	PlyModel,
	VtkModel,
	VtpModel,
	GModel,
	C3DsModel
};
#define DefaultHeight 0.1
#define DefaultRadius 0.1
#define DefaultSide 3
#define DefaultThetaResolution 100
#define DefaultPhiResolution 50
#define PrismDefaultColor 0xffffffff

typedef struct
{
	int nThetaResolution;//θ分辨率
	int nPhiResolution;//Φ分辨率
	double lfRadius;//半径
}RegularPolyhedronProperties;

typedef struct
{
	double lfHeight;//高
	double lfRadius;//半径
	int lluSide;//棱数
}PyramidProperties;

typedef struct 
{
	double lfHeight;//高
	double lfRadius;//半径
	int lluSide;//棱数
}PrismProperties;

typedef struct
{
	double pos[3];
	double rot[3];
	unsigned int uColor;//颜色 红 绿 蓝 透明度
}CommonProperties;

typedef struct
{
	CommonProperties commonProperties;
	PrismProperties prismProperties;
}PropertiesCollection;

inline void UInt32ToRGBDouble(unsigned int value, double outRGB[3])
{
	unsigned char* rgba = (unsigned char*)&value;
	outRGB[0] = (double)rgba[0] / (double)0xff;
	outRGB[1] = (double)rgba[1] / (double)0xff;
	outRGB[2] = (double)rgba[2] / (double)0xff;
}