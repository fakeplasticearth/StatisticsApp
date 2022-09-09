#pragma once
#include "pch.h"
#include "BPv1Doc.h"

// Диалоговое окно ParameterDlg

class ParameterDlg : public CDialog
{
	DECLARE_DYNAMIC(ParameterDlg)

public:
	CFont* box_font;
	bool init_mode = 1;
	bool error_found;
	bool error_type_status[11];
	CString error_message;
	int m_sample_size;
	ParameterDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	ParameterDlg(int id, CWnd* pParent = nullptr);
	virtual ~ParameterDlg();
	int check_string(CString str, int mode);
	int GetErrorCode(CEdit* edit_box, int mode);
	CString GetErrorMessage(int error_code);

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
