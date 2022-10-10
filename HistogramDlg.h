#pragma once

#include "pch.h"
#include "BPv1Doc.h"


#define BOX_START1X 159 // координата x левого верхнего угла первой линии edit box
#define BOX_START1Y 30 // координата y левого верхнего угла первой линии edit box
#define BOX_START2X 110 // координата x левого верхнего угла второй линии edit box
#define BOX_START2Y 90 // координата y левого верхнего угла второй линии edit box

class HistogramDlg : public ParameterDlg
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
	std::vector<CEdit*> edit_freq_vector = {};
	std::vector<CEdit*> edit_val_vector = {};
	afx_msg void OnBnClickedButton1();
	CButton m_delete_box;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	INT m_method_type;
	afx_msg void OnBnClickedOk();
	void ProcessBoxData(CEdit* edit_box, int mode, int index);
	void fill_values(CBPv1Doc* doc);
	BOOL OnInitDialog();
	int m_parameter;
};