// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once


// CChildView â

class CChildView : public CWnd
{
	// �����Դϴ�.
public:
	CChildView();

	// Ư���Դϴ�.
public:
	CString asd;
	// �۾��Դϴ�.
public:

	// �������Դϴ�.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// �����Դϴ�.
public:
	virtual ~CChildView();
	void TestCMarkUp();
	void TestCMarkupToLoad();
	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};
