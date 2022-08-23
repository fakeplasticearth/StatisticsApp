#pragma once
#include <vector>
#include <iostream>
#include <string>

#define NOT_A_NUMBER 0
#define NOT_AN_INT 1
#define EMPTY_BOX 2
#define SUM_MORE_THAN_ONE 3


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
	double values[14], rel_freqs[14];
	int abs_freqs[14];
	int check_string(CString str);
	afx_msg void OnBnClickedButton1();
	CButton m_delete_box;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	bool check_freqs(int method_type); // Проверка частот на соответствие
	INT m_method_type;
	int error_status = -1;
	afx_msg void OnBnClickedOk();
};
