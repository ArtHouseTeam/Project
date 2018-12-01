
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "ChildView.h"
#include "Markup.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
//	CString asd;
}

CChildView::~CChildView()
{
}

void CChildView::TestCMarkUp()
{
	CMarkup xml;

	xml.AddElem(_T("Machine"));             // 현재 Level 수준에서 Element를 추가합니다.
	xml.AddChildElem(_T("MachineSize"));    // 현재 Level 에서 Element를 Child로 추가합니다.

	xml.IntoElem();                         // 한단계 안으로 들어갑니다.
	xml.AddAttrib(_T("XSIZE"), _T("200"));   // 현재 Element에 Attribute 를 추가합니다.
	xml.AddAttrib(_T("YSIZE"), _T("200"));   //IntoElem 후 AddAttrib 는 AddChildAttrib 와 똑같은 효과를 냅니다.
	xml.OutOfElem();                        // 현재 Level에서(Machine) 나옵니다.

	xml.AddElem(_T("X"));
	xml.AddChildElem(_T("COL"));
	xml.IntoElem();
	xml.AddAttrib(_T("Count"), _T("3"));
	xml.AddChildElem(_T("Data"), _T("4")); // IntoElem 후 AddElem 와 똑같은 효과를 냅니다.
	xml.AddChildElem(_T("Data"), _T("2"));
	xml.AddChildElem(_T("Data"), _T("2"));
	xml.OutOfElem();

	CString strXML = xml.GetDoc();
	AfxMessageBox(strXML);

	xml.Save(_T("TestXml.XML"));
}


void CChildView::TestCMarkupToLoad()
{
	CMarkup xml;
	CString strFileName = _T("Weather.XML");
	CString str[10];

	if (xml.Load(strFileName) == true)
	{
		AfxMessageBox(_T("안녕하세요."));
		return;
	}
	
	xml.FindElem(_T("channel"));  //Element 를 찾습니다.
	xml.IntoElem();				  //channel 안의 내용 확인
		xml.FindElem(_T("title"));
		str[0] = xml.GetData();
		xml.FindElem(_T("description"));
		str[1] = xml.GetData();
		xml.FindElem(_T("generator"));
		str[2] = xml.GetData();
		xml.FindElem(_T("item"));		//Element를 찾습니다.
		xml.IntoElem();					// channel -> item 안의 내용 확인
			xml.FindElem(_T("category"));
			str[3] = xml.GetData();
			xml.FindElem(_T("title"));
			str[4] = xml.GetData();
			xml.FindElem(_T("description")); //Element를 찾습니다.
			xml.IntoElem();					// channel ->item -> description 안의 내용 확인
				xml.FindElem(_T("header"));	//Element를 찾습니다.
				xml.IntoElem();             // channel ->item -> header 안의 내용
					xml.FindElem(_T("title"));
					str[5] = xml.GetData();
					xml.FindElem(_T("tm"));
					str[6] = xml.GetData();
					xml.OutOfElem();		// 한단계 수준에서 나옴
				xml.FindElem(_T("body"));	// Element를 찾습니다.
				xml.IntoElem();				// channel ->item -> body 안의 내용
					xml.FindElem(_T("location")); // Element를 찾습니다.
					xml.IntoElem();				  // channel ->item -> body -> location 안의 내용
						xml.FindElem(_T("province"));
						str[7] = xml.GetData();
						xml.FindElem(_T("city"));
						str[8] = xml.GetData();
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	CRect rect;
	GetClientRect(&rect);
//	TestCMarkUp();
	TestCMarkupToLoad();
	_tsetlocale(LC_ALL, _T(""));
	dc.TextOutW(rect.right / 2, rect.bottom / 2, asd);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}
