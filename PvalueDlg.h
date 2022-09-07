#pragma once
#include "pch.h"
#include "BPv1Doc.h"

// Диалоговое окно PvalueDlg

class PvalueDlg : public CDialog
{
	DECLARE_DYNAMIC(PvalueDlg)

public:
	int h0_abs_freqs[14];
	double h0_values[14];
	PvalueDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	int check_string(CString str, int mode);
	void fill_values(CBPv1Doc* doc);
	virtual ~PvalueDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
