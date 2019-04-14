#include "StdAfx.h"
#include "GISWorkSpace.h"
#include "IGIS_GeoEleBase.h"
#include "GIS_GeoLine.h"
#include "GIS_GeoPoint.h"

CRect CGISWorkSpace::viewRect;									//视口大小
CAreaRect CGISWorkSpace::viewArea=CAreaRect(0,800,600,0);		//视口范围
CAreaRect CGISWorkSpace::mapArea;								//地图范围
CString CGISWorkSpace::currentToolName="CGIS_ToolPan";			//当前交互工具名称
int CGISWorkSpace::currentSymId=0;								//当前符号ID

vector<IGIS_ToolBase*> CGISWorkSpace::ToolList;		//交互链表容器 
vector<IGIS_GeoEleBase*> CGISWorkSpace::GeoEleList;	//要素链表容器 
vector<IGIS_SymBase*> CGISWorkSpace::SymbolList;	//符号链表容器 

CView* CGISWorkSpace::pView=NULL;		//视图初始化为NULL
float CGISWorkSpace::mapScale=1.0f;		//初始地图比例大小
CGISWorkSpace::CGISWorkSpace(void)
{
	viewRect.left=0;
	viewRect.right=0;
	viewRect.bottom=0;
	viewRect.top=0;

	viewArea.Left=0;
	viewArea.Right=0;
	viewArea.Down=0;
	viewArea.Up=0;

	mapArea.Left=0;
	mapArea.Right=0;
	mapArea.Down=0;
	mapArea.Up=0;

	currentToolName="";
	currentSymId=-1;

	ToolList.clear();
	GeoEleList.clear();
	SymbolList.clear();
}


CGISWorkSpace::~CGISWorkSpace(void)
{
	ToolList.clear();
	GeoEleList.clear();
	SymbolList.clear();
}

IGIS_ToolBase* CGISWorkSpace::GetCurTool()
{
	for (int i=0;i<int(ToolList.size());i++)
	{
		if (currentToolName==ToolList[i]->GetToolType())
		{
			return ToolList[i];
		}
	}
	return NULL;
}
IGIS_ToolBase* CGISWorkSpace::GetTool(CString toolName)
{
	for (int i=0;i<int(ToolList.size());i++)
	{
		if (toolName==ToolList[i]->GetToolType())
		{
			return ToolList[i];
		}
	}
	return NULL;
}
IGIS_SymBase * CGISWorkSpace::GetCurSymbol()
{
	for (int i=0;i<int(SymbolList.size());i++)
	{
		if (currentSymId==SymbolList[i]->GetSymID())
		{
			return SymbolList[i];
		}
	}
	return NULL;
}
IGIS_SymBase * CGISWorkSpace::GetSymbol(long symId)
{
	for (int i=0;i<int(SymbolList.size());i++)
	{
		if (SymbolList[i]->GetSymID()==symId)
		{
			return SymbolList[i];
		}
	}
	return NULL;
}


bool CGISWorkSpace::WndToGeo(CPoint Wnd,float &x,float &y)
{
	if (viewArea.GetHeigh()==0||viewArea.GetWidth()==0)
	{
		return false;
	}
	float k=0;//比例尺 取比值大的
	k=viewArea.GetWidth()/viewRect.Width()>viewArea.GetHeigh()/viewRect.Height()?
		viewArea.GetWidth()/viewRect.Width():viewArea.GetHeigh()/viewRect.Height();

	x=(float(Wnd.x)-float(viewRect.Width()/2))*k+(viewArea.Left+viewArea.Right)/2;
	y=(float(viewRect.Height()/2-float(Wnd.y)))*k+(viewArea.Up+viewArea.Down)/2;
	return true;
}

bool CGISWorkSpace::GeoToWnd(float x,float y,CPoint &Wnd)
{
	if (viewArea.GetHeigh()==0||viewArea.GetWidth()==0)
	{
		return false;
	}
	float k=0;//比例尺 取比值大的
	k=viewArea.GetWidth()/viewRect.Width()>viewArea.GetHeigh()/viewRect.Height()?
		viewArea.GetWidth()/viewRect.Width():viewArea.GetHeigh()/viewRect.Height();
	Wnd.x=int((x-(viewArea.Left+viewArea.Right)/2)/k+viewRect.Width()/2+0.5);
	Wnd.y=viewRect.Height()-int((y-(viewArea.Up+viewArea.Down)/2)/k+viewRect.Height()/2+0.5);
	return true;
}

void CGISWorkSpace::DrawMap()
{
	if (pView==NULL)
	{
		AfxMessageBox("绘制前，请绑定视图！");
		return;
	}
	CClientDC dc(pView);//这时不需要调用 ReleaseDC 因为它会自动去析构
	dc.FillSolidRect(viewRect.left,viewRect.top,viewRect.Width(),viewRect.Height(),RGB(255,255,255));
	CBitmap*   pMemBitmap=new CBitmap();//定义一个位图对象
	int nWidth=viewRect.Width();
	int nHeight=viewRect.Height();
	pMemBitmap->CreateCompatibleBitmap(&dc,nWidth,nHeight);  //这里一般设置成为视窗大小
	CDC *pMemDc=new CDC();
	pMemDc->CreateCompatibleDC(NULL);
	CBitmap *oldBmp=pMemDc->SelectObject(pMemBitmap); 
	pMemDc->FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
	for (int i=0;i<int(GeoEleList.size());i++)
	{
		GeoEleList[i]->Draw(pMemDc);
	}
	::TransparentBlt(dc.m_hDC,0,0,nWidth,nHeight,pMemDc->m_hDC,0,0,nWidth,nHeight,RGB(255,255,255));
	pMemDc->SelectObject(oldBmp);
	pMemBitmap->DeleteObject();
	pMemDc->DeleteDC();
}

bool CGISWorkSpace::BindView(CView* tView)
{
	pView=tView;
	return true;
}

void CGISWorkSpace::OnSize(UINT nType, int cx, int cy)
{
	viewRect.top=0;
	viewRect.left=0;
	viewRect.bottom=cy;
	viewRect.right=cx;
	//重计算矩形范围
	float xCenter=(viewArea.Left+viewArea.Right)/2;
	float yCenter=(viewArea.Up+viewArea.Down)/2;
	ReCalRealArea(xCenter,yCenter,mapScale);
}

void CGISWorkSpace::ReCalRealArea(float xCenter,float yCenter,float scale)
{
	float left=xCenter-scale*(viewRect.left+viewRect.right)/2;
	float right=xCenter+scale*(viewRect.left+viewRect.right)/2;
	float down=yCenter-scale*(viewRect.top+viewRect.bottom)/2;
	float up=yCenter+scale*(viewRect.top+viewRect.bottom)/2;
	viewArea=CAreaRect(left,right,up,down);
}

void CGISWorkSpace::Restore()
{
	float xmin=0,xmax=0,ymin=0,ymax=0;
	int sum=int(GeoEleList.size());
	if (sum<1)return ;
	CString eleType=GeoEleList[0]->GetEleType();
	if (eleType=="CGIS_GeoPoint")
	{
		CGIS_GeoPoint *pElePnt=(CGIS_GeoPoint*)(GeoEleList[0]);
		xmin=pElePnt->m_PntPos.posX;
		xmax=xmin;
		ymin=pElePnt->m_PntPos.posY;
		ymax=ymin;
	}
	else if (eleType=="CGIS_GeoLine")
	{
		CGIS_GeoLine *pEleLine=(CGIS_GeoLine*)(GeoEleList[0]);
		xmin=pEleLine->m_LinePnts[0].posX;
		xmax=xmin;
		ymin=pEleLine->m_LinePnts[0].posY;
		ymax=ymin;
	}

	for (int i=0;i<sum;i++)
	{
		eleType=GeoEleList[i]->GetEleType();
		if (eleType=="CGIS_GeoPoint")
		{
			CGIS_GeoPoint *pElePnt=(CGIS_GeoPoint*)(GeoEleList[i]);
			if(xmax-xmin<pElePnt->m_PntPos.posX-xmin)
				xmax=pElePnt->m_PntPos.posX;
			if(xmax-xmin<xmax-pElePnt->m_PntPos.posX)
				xmin=pElePnt->m_PntPos.posX;
			if(ymax-ymin<pElePnt->m_PntPos.posY-ymin)
				ymax=pElePnt->m_PntPos.posY;
			if(ymax-ymin<ymax-pElePnt->m_PntPos.posY)
				ymin=pElePnt->m_PntPos.posY;
		}
		else if (eleType=="CGIS_GeoLine")
		{
			CGIS_GeoLine *pEleLine=(CGIS_GeoLine*)(GeoEleList[i]);
			for(int j=0;j<int(pEleLine->m_LinePnts.size());j++)
			{
				if(xmax-xmin<pEleLine->m_LinePnts[j].posX-xmin)
					xmax=pEleLine->m_LinePnts[j].posX;
				if(xmax-xmin<xmax-pEleLine->m_LinePnts[j].posX)
					xmin=pEleLine->m_LinePnts[j].posX;
				if(ymax-ymin<pEleLine->m_LinePnts[j].posY-ymin)
					ymax=pEleLine->m_LinePnts[j].posY;
				if(ymax-ymin<ymax-pEleLine->m_LinePnts[j].posY)
					ymin=pEleLine->m_LinePnts[j].posY;
			}
		}
	}
	if (xmax==xmin)
	{
		xmin=0;
		xmax=800;
	}
	if(ymin==ymax)
	{
		ymin=0;
		ymax=600;
	}
	mapArea=CAreaRect(xmin,xmax,ymax,ymin);
	viewArea=mapArea;
	//取比值大的那个
	float widRate=(xmax-xmin)/viewRect.Width();
	float heiRate=(ymax-ymin)/viewRect.Height();
	mapScale=widRate>heiRate?widRate:heiRate;
	DrawMap();
}

bool CGISWorkSpace::SaveGeoElements(CString pathName)		//保存地理要素
{
	CFile *pFile=new CFile(pathName,CFile::modeCreate|CFile::modeWrite);
	int sum=int(GeoEleList.size());
	pFile->Write(&sum,sizeof(int));
	int cstSize=0;
	CString clsName="";
	for (int i=0;i<sum;i++)
	{
		clsName=CGISWorkSpace::GeoEleList[i]->GetEleType();
		cstSize=clsName.GetLength();
		pFile->Write(&cstSize,sizeof(int));
		pFile->Write(clsName,sizeof(char)*cstSize);
		GeoEleList[i]->Save(pFile);
	}
	pFile->Flush();
	pFile->Close();
	AfxMessageBox("保存成功");
	return false;
}
bool CGISWorkSpace::ReadGeoElements(CString pathName)		//读取地理要素
{
	CFile *pFile=new CFile(pathName,CFile::modeRead);
	if (pFile==NULL)
	{
		AfxMessageBox("读取文件失败！");
		return false;
	}
	int sum=0;
	pFile->Read(&sum,sizeof(int));
	int cstSize=0;
	char *tmpChars;
	CString clsName="";
	IGIS_GeoEleBase *tmpGeoBase=NULL;
	for (int i=0;i<sum;i++)
	{
		pFile->Read(&cstSize,sizeof(int));
		tmpChars=new char[cstSize+1];
		tmpChars[cstSize]='\0';
		pFile->Read(tmpChars,sizeof(char)*cstSize);
		clsName=tmpChars;
		if (clsName=="CGIS_GeoPoint")
		{
			tmpGeoBase=new CGIS_GeoPoint();
		}
		else if (clsName=="CGIS_GeoLine")
		{
			tmpGeoBase=new CGIS_GeoLine();
		}
		tmpGeoBase->Read(pFile);
		GeoEleList.push_back(tmpGeoBase);
	}
	pFile->Close();
	AfxMessageBox("读取成功");
	return true;
}
bool CGISWorkSpace::SaveSymbolFile(CString pathName)		//保存符号文件
{
	return false;
}
bool CGISWorkSpace::ReadSymbolFile(CString pathName)		//读取符号文件
{
	return false;
}

bool CGISWorkSpace::ClearGeoData()							//清理工作空间数据
{
	GeoEleList.clear();
	GetDispView()->GetClientRect(&(viewRect));
	viewArea=CAreaRect(0,float(viewRect.Width()),float(viewRect.Height()),0);
	Restore();
	currentToolName="CGIS_ToolPan";			//当前交互工具名称
	return true;
}