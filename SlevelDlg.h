#pragma once

#include "pch.h"
#include "BPv1Doc.h"
#include "ParameterDlg.h"
#include <vector>

#define BOX_START1X 159 // координата x левого верхнего угла первой линии edit box
#define BOX_START1Y 30 // координата y левого верхнего угла первой линии edit box
#define BOX_START2X 110 // координата x левого верхнего угла второй линии edit box
#define BOX_START2Y 90 // координата y левого верхнего угла второй линии edit box

// Диалоговое окно SlevelDlg

class SlevelDlg : public ParameterDlg
{
	DECLARE_DYNAMIC(SlevelDlg)

public:
	SlevelDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~SlevelDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
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
	CButton m_delete_box;
	afx_msg void OnBnClickedOk();
	void ProcessBoxData(CEdit* edit_box, int mode, int index);
	void fill_values(CBPv1Doc* doc);
	BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	int m_method_type;
	int m_parameter;
	int m_pvalue_sample_size;
	int m_max_sample_size;
	int min_sample_size;
	double m_alpha;
};
