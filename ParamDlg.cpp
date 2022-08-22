// ParamDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "ParamDlg.h"
#include "afxdialogex.h"

#define BOX_HEIGHT 28 // высота edit box
#define BOX_WIDTH 50 // ширина edit box
#define BOX_START1X 159 // координата x левого верхнего угла первой линии edit box
#define BOX_START1Y 30 // координата y левого верхнего угла первой линии edit box
#define BOX_START2X 110 // координата x левого верхнего угла второй линии edit box
#define BOX_START2Y 90 // координата y левого верхнего угла второй линии edit box


// Диалоговое окно ParamDlg

IMPLEMENT_DYNAMIC(ParamDlg, CDialog)

ParamDlg::ParamDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

ParamDlg::~ParamDlg()
{
}

void ParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_add_box);
	DDX_Control(pDX, IDC_BUTTON2, m_delete_box);
}


BEGIN_MESSAGE_MAP(ParamDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ParamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ParamDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &ParamDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &ParamDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// Обработчики сообщений ParamDlg


void ParamDlg::OnBnClickedButton1()
{
	unsigned int x, y;
	unsigned int shifted_box_num;
	if (box_num < 5) {
		x = BOX_START1X;
		y = BOX_START1Y;
		shifted_box_num = box_num;
	}
	else {
		x = BOX_START2X;
		y = BOX_START2Y;
		shifted_box_num = box_num - 5;
		CWnd* freq_text = GetDlgItem(IDC_STATIC3);
		freq_text -> ShowWindow(SW_SHOW);
		CWnd* value_text = GetDlgItem(IDC_STATIC4);
		value_text->ShowWindow(SW_SHOW);
	}
	edit_freq_vector.push_back(new CEdit);
	edit_freq_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 
		CRect(x + BOX_WIDTH * shifted_box_num, y, x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT), this, 1);
	edit_val_vector.push_back(new CEdit);
	edit_val_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 
		CRect(x + BOX_WIDTH * shifted_box_num, y + BOX_HEIGHT, 
			x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT + BOX_HEIGHT), this, 1);
	if (box_num == 0)
		m_delete_box.EnableWindow(1);
	++box_num;
	if (box_num == 11)
		m_add_box.EnableWindow(0);
}


void ParamDlg::OnBnClickedButton2()
{
	edit_freq_vector.back()->Clear();
	delete edit_freq_vector.back();
	edit_freq_vector.pop_back();
	edit_val_vector.back()->Clear();
	delete edit_val_vector.back();
	edit_val_vector.pop_back();
	if (box_num == 11)
		m_add_box.EnableWindow(1);
	if (box_num == 6) {
		CWnd* freq_text = GetDlgItem(IDC_STATIC3);
		freq_text->ShowWindow(SW_HIDE);
		CWnd* value_text = GetDlgItem(IDC_STATIC4);
		value_text->ShowWindow(SW_HIDE);
	}
	--box_num;
	if (box_num == 0)
		m_delete_box.EnableWindow(0);
}


void ParamDlg::OnBnClickedRadio1()
{
	SetDlgItemText(IDC_STATIC1, L"Abs. freqs");
	SetDlgItemText(IDC_STATIC3, L"Abs. freqs");
}

void ParamDlg::OnBnClickedRadio2()
{
	SetDlgItemText(IDC_STATIC1, L"Rel. freqs");
	SetDlgItemText(IDC_STATIC3, L"Rel. freqs");
}
