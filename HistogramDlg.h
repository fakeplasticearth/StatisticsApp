#pragma once
#include "pch.h"
#include "BPv1Doc.h"

class HistogramDlg : public CDialog
{
	DECLARE_DYNAMIC(HistogramDlg)

public:
	HistogramDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~HistogramDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
public:
	int abs_freqs[14];
	double values[14];
	CButton m_add_box;
	unsigned int box_num = 0; // количество созданных edit box
	bool init_mode = 1;
	CFont* box_font;
	std::vector<CEdit*> edit_freq_vector = {};
	std::vector<CEdit*> edit_val_vector = {};
	int check_string(CString str, int mode);
	afx_msg void OnBnClickedButton1();
	CButton m_delete_box;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	INT m_method_type;
	bool error_type_status[5];
	afx_msg void OnBnClickedOk();
	int GetErrorCode(CEdit* edit_box, int mode);
	bool error_found;
	void ProcessBoxData(CEdit* edit_box, int mode, int index);
	CString error_message;
	void fill_values(CBPv1Doc* doc);
	BOOL OnInitDialog();
	int m_sample_size;
};