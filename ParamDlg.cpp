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
	, m_method_type(0)
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
	DDX_Radio(pDX, IDC_RADIO1, m_method_type);
}


BEGIN_MESSAGE_MAP(ParamDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ParamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ParamDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &ParamDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &ParamDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &ParamDlg::OnBnClickedOk)
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
	m_method_type = 0;
	SetDlgItemText(IDC_STATIC1, L"Abs. freqs");
	SetDlgItemText(IDC_STATIC3, L"Abs. freqs");
}

void ParamDlg::OnBnClickedRadio2()
{
	m_method_type = 1;
	SetDlgItemText(IDC_STATIC1, L"Rel. freqs");
	SetDlgItemText(IDC_STATIC3, L"Rel. freqs");
}


int ParamDlg::check_string(CString str, int mode) {
	//Input: str - text string from edit box, mode - 0 for decimal input rule, 1 for floating point number rule
	int dot_num = 0;
	if (str.GetLength() == 0)
		return EMPTY_BOX;

	for (int i = 0; i < str.GetLength(); ++i) {
		if ((str[i] == '.') && dot_num)
			return NOT_A_NUMBER;
		else if (str[i] == '.')
			++dot_num;
		else if (!isdigit(str[i]))
			return NOT_A_NUMBER;
	}
	if ((mode == 0) && (dot_num > 0))
		return NOT_AN_INT;
	return -1;
}

int ParamDlg::GetErrorCode(CEdit* edit_box, int mode) {
	// Input: id of edit box, mode - 0 for absolute frequency box, 1 for relative frequency box and value box
	// Output: code of error

	CString buff;
	int len = edit_box->LineLength();
	edit_box->GetLine(0, buff.GetBuffer(len), len);
	buff.ReleaseBuffer(len);
	return check_string(buff, mode);
}

CString GetErrorMessage(int error_code) {
	switch (error_code) {
	case NOT_A_NUMBER:
		return L"Please enter only numbers.\n";
	case NOT_AN_INT:
		return L"Absolute frequencies must be decimal numbers.\n";
	case EMPTY_BOX:
		return L"Please complete all created boxes.\n";
	case SUM_MORE_THAN_ONE:
		return L"Sum of relative frequencies must be 1.\n";
	default:
		return L"";
	}
}

void ParamDlg::ProcessBoxData(CEdit* edit_box, int mode, int index) {
	/*Input: edit_box_id - id of edit box, 
	* mode - 0 for absolute frequency box, 1 for relative frequency box, 2 for value box 
	* index - index for saving values to class fields
	*/
	int error_code = GetErrorCode(edit_box, m_method_type);
	if (error_code > -1) {
		error_found = 1;
		if (error_type_status[error_code] == 0) {
			error_type_status[error_code] = 1;
			error_message += GetErrorMessage(error_code);
		}

	}
	else if (!error_found) {
		CString buff;
		int len = edit_box->LineLength();
		edit_box->GetLine(0, buff.GetBuffer(len), len);
		buff.ReleaseBuffer(len);
		switch (mode) {
		case 0:
			abs_freqs[index] = _wtoi(buff);
			break;
		case 1:
			rel_freqs[index] = _wtof(buff);
			break;
		case 2:
			values[index] = _wtoi(buff);
		}
	}
}

void ParamDlg::OnBnClickedOk()
{
	error_found = 0;
	error_message = L"";
	for (int i = 0; i < 3; ++i)
		error_type_status[i] = 0;
	
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT2), m_method_type, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT1), 2, 0);
	for (int i = 0; i < box_num; ++i) {
		ProcessBoxData(edit_freq_vector[i], m_method_type, i + 1);
		ProcessBoxData(edit_val_vector[i], 2, i + 1);
	}

	if (error_found)
		AfxMessageBox(error_message);
	else
		CDialog::OnOK();
}
