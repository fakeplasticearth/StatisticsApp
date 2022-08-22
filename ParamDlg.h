#pragma once
#include <vector>
#include <iostream>


// Диалоговое окно ParamDlg

class ParamDlg : public CDialog
{
	DECLARE_DYNAMIC(ParamDlg)

public:
	ParamDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ParamDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
public:
	CButton m_add_box;
	unsigned int box_num = 0; // количество созданных edit box
	std::vector<CEdit*> edit_freq_vector = {};
	std::vector<CEdit*> edit_val_vector = {};
	afx_msg void OnBnClickedButton1();
	CButton m_delete_box;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
