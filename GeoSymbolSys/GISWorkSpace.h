#pragma once
#include "AreaRect.h"
#include "IGIS_GeoEleBase.h"
#include "IGIS_ToolBase.h"
#include "IGIS_SymBase.h"
#include <vector>
using namespace std;
class CGISWorkSpace
{
public:
	CGISWorkSpace(void);
	~CGISWorkSpace(void);
public:
	static IGIS_ToolBase* GetCurTool();
	static IGIS_ToolBase* GetTool(CString toolName);
	static IGIS_SymBase * GetCurSymbol();
	static IGIS_SymBase * GetSymbol(long symId);		//通过ID寻找符号
	static bool GeoToWnd(float x,float y,CPoint &Wnd);  //地理座标转换为窗口座标
	static bool WndToGeo(CPoint Wnd,float &x,float &y); //窗口座标转换为地理座标
	static bool BindView(CView* tView);					//绑定视图
	static void DrawMap();								//绘制地图
	static CView* GetDispView(){return pView;}			//获取视图指针
	static void OnSize(UINT nType, int cx, int cy);		//窗口大小变化
	static void ReCalRealArea(float xCenter,float yCenter,float scale);//重计算窗口实际范围
	static void Restore();								//复位
	static bool SaveGeoElements(CString pathName);		//保存地理要素
	static bool ReadGeoElements(CString pathName);		//读取地理要素
	static bool SaveSymbolFile(CString pathName);		//保存符号文件
	static bool ReadSymbolFile(CString pathName);		//读取符号文件
	static bool ClearGeoData();							//清理工作空间数据
public:
	static CRect viewRect;			//视口大小
	static CAreaRect viewArea;		//视口范围
	static CAreaRect mapArea;		//地图范围
	static CString currentToolName;	//当前交互工具名称
	static int currentSymId;		//当前符号ID
	static float mapScale;			//比例尺系数

	static vector<IGIS_ToolBase*> ToolList;		//交互链表容器 
	static vector<IGIS_GeoEleBase*> GeoEleList;	//要素链表容器 
	static vector<IGIS_SymBase*> SymbolList;	//符号链表容器 

private:
	static CView* pView;						//视图窗口
};