
// ChildView.cpp : CChildView Ŭ������ ����
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

	xml.AddElem(_T("Machine"));             // ���� Level ���ؿ��� Element�� �߰��մϴ�.
	xml.AddChildElem(_T("MachineSize"));    // ���� Level ���� Element�� Child�� �߰��մϴ�.

	xml.IntoElem();                         // �Ѵܰ� ������ ���ϴ�.
	xml.AddAttrib(_T("XSIZE"), _T("200"));   // ���� Element�� Attribute �� �߰��մϴ�.
	xml.AddAttrib(_T("YSIZE"), _T("200"));   //IntoElem �� AddAttrib �� AddChildAttrib �� �Ȱ��� ȿ���� ���ϴ�.
	xml.OutOfElem();                        // ���� Level����(Machine) ���ɴϴ�.

	xml.AddElem(_T("X"));
	xml.AddChildElem(_T("COL"));
	xml.IntoElem();
	xml.AddAttrib(_T("Count"), _T("3"));
	xml.AddChildElem(_T("Data"), _T("4")); // IntoElem �� AddElem �� �Ȱ��� ȿ���� ���ϴ�.
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
		AfxMessageBox(_T("�ȳ��ϼ���."));
		return;
	}
	
	xml.FindElem(_T("channel"));  //Element �� ã���ϴ�.
	xml.IntoElem();				  //channel ���� ���� Ȯ��
		xml.FindElem(_T("title"));
		str[0] = xml.GetData();
		xml.FindElem(_T("description"));
		str[1] = xml.GetData();
		xml.FindElem(_T("generator"));
		str[2] = xml.GetData();
		xml.FindElem(_T("item"));		//Element�� ã���ϴ�.
		xml.IntoElem();					// channel -> item ���� ���� Ȯ��
			xml.FindElem(_T("category"));
			str[3] = xml.GetData();
			xml.FindElem(_T("title"));
			str[4] = xml.GetData();
			xml.FindElem(_T("description")); //Element�� ã���ϴ�.
			xml.IntoElem();					// channel ->item -> description ���� ���� Ȯ��
				xml.FindElem(_T("header"));	//Element�� ã���ϴ�.
				xml.IntoElem();             // channel ->item -> header ���� ����
					xml.FindElem(_T("title"));
					str[5] = xml.GetData();
					xml.FindElem(_T("tm"));
					str[6] = xml.GetData();
					xml.OutOfElem();		// �Ѵܰ� ���ؿ��� ����
				xml.FindElem(_T("body"));	// Element�� ã���ϴ�.
				xml.IntoElem();				// channel ->item -> body ���� ����
					xml.FindElem(_T("location")); // Element�� ã���ϴ�.
					xml.IntoElem();				  // channel ->item -> body -> location ���� ����
						xml.FindElem(_T("province"));
						str[7] = xml.GetData();
						xml.FindElem(_T("city"));
						str[8] = xml.GetData();
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	CRect rect;
	GetClientRect(&rect);
//	TestCMarkUp();
	TestCMarkupToLoad();
	_tsetlocale(LC_ALL, _T(""));
	dc.TextOutW(rect.right / 2, rect.bottom / 2, asd);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}
