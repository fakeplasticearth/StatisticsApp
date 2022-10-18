#pragma once

#include "pch.h"
#include "ParameterDlg.h"
#include "BPv1Doc.h"
#include <vector>

#define H0_BOX_START1X 177 // координата x левого верхнего угла первой линии edit box
#define H0_BOX_START1Y 46 // координата y левого верхнего угла первой линии edit box
#define H0_BOX_START2X 128 // координата x левого верхнего угла второй линии edit box
#define H0_BOX_START2Y 115 // координата y левого верхнего угла второй линии edit box

#define H1_BOX_START1X 177 // координата x левого верхнего угла первой линии edit box
#define H1_BOX_START1Y 216 // координата y левого верхнего угла первой линии edit box
#define H1_BOX_START2X 128 // координата x левого верхнего угла второй линии edit box
#define H1_BOX_START2Y 285 // координата y левого верхнего угла второй линии edit box

// Диалоговое окно PvalueDlg

class PvalueDlg : public ParameterDlg
{
	DECLARE_DYNAMIC(PvalueDlg)

public:
	int m_method_type;
	int h0_abs_freqs[14];
	double h0_values[14];
	unsigned int h0_box_num = 0;
	std::vector<CEdit*> h0_edit_freq_vector = {};
	std::vector<CEdit*> h0_edit_val_vector = {};

	int h1_abs_freqs[14];
	double h1_values[14];
	unsigned int h1_box_num = 0;
	std::vector<CEdit*> h1_edit_freq_vector = {};
	std::vector<CEdit*> h1_edit_val_vector = {};

	afx_msg void OnBnClickedOk();
	void ProcessBoxData(CEdit* edit_box, int mode, int hyp_num, int index);
	void fill_values(CBPv1Doc* doc);
	BOOL OnInitDialog();

	PvalueDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~PvalueDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CButton m_h0_add_box;
	CButton m_h0_delete_box;
	CButton m_h1_add_box;
	CButton m_h1_delete_box;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	int m_pvalue_sample_size;
	int m_parameter;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
