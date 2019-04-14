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
	static IGIS_SymBase * GetSymbol(long symId);		//ͨ��IDѰ�ҷ���
	static bool GeoToWnd(float x,float y,CPoint &Wnd);  //��������ת��Ϊ��������
	static bool WndToGeo(CPoint Wnd,float &x,float &y); //��������ת��Ϊ��������
	static bool BindView(CView* tView);					//����ͼ
	static void DrawMap();								//���Ƶ�ͼ
	static CView* GetDispView(){return pView;}			//��ȡ��ͼָ��
	static void OnSize(UINT nType, int cx, int cy);		//���ڴ�С�仯
	static void ReCalRealArea(float xCenter,float yCenter,float scale);//�ؼ��㴰��ʵ�ʷ�Χ
	static void Restore();								//��λ
	static bool SaveGeoElements(CString pathName);		//�������Ҫ��
	static bool ReadGeoElements(CString pathName);		//��ȡ����Ҫ��
	static bool SaveSymbolFile(CString pathName);		//��������ļ�
	static bool ReadSymbolFile(CString pathName);		//��ȡ�����ļ�
	static bool ClearGeoData();							//�������ռ�����
public:
	static CRect viewRect;			//�ӿڴ�С
	static CAreaRect viewArea;		//�ӿڷ�Χ
	static CAreaRect mapArea;		//��ͼ��Χ
	static CString currentToolName;	//��ǰ������������
	static int currentSymId;		//��ǰ����ID
	static float mapScale;			//������ϵ��

	static vector<IGIS_ToolBase*> ToolList;		//������������ 
	static vector<IGIS_GeoEleBase*> GeoEleList;	//Ҫ���������� 
	static vector<IGIS_SymBase*> SymbolList;	//������������ 

private:
	static CView* pView;						//��ͼ����
};