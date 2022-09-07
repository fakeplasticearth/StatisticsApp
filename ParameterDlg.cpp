// ParameterDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "ParameterDlg.h"
#include "afxdialogex.h"


// Диалоговое окно ParameterDlg

IMPLEMENT_DYNAMIC(ParameterDlg, CDialog)

ParameterDlg::ParameterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
{

}

ParameterDlg::ParameterDlg(int id, CWnd* pParent)
	: CDialog(id, pParent)
{

}

ParameterDlg::~ParameterDlg()
{
}

void ParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ParameterDlg, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений ParameterDlg

int ParameterDlg::check_string(CString str, int mode) {
	//Input: str - text string from edit box, mode - 0 for decimal input rule, 1 for floating point number rule
	int dot_num = 0;
	if (str.GetLength() == 0)
		return EMPTY_BOX;

	for (int i = 0; i < str.GetLength(); ++i) {
		if ((str[i] == '.') && dot_num)
			return NOT_A_NUMBER;
		else if (str[i] == '.')
			++dot_num;
		else if (str[i] == '-') {
			if (i)
				return NOT_A_NUMBER;
		}
		else if (!isdigit(str[i]))
			return NOT_A_NUMBER;
	}
	if ((mode == 0) && (dot_num > 0))
		return NOT_AN_INT;

	return -1;
}

int ParameterDlg::GetErrorCode(CEdit* edit_box, int mode) {
	// Input: id of edit box, mode - 0 for absolute frequency box, 1 for value box, 2 for sample size box
	// Output: code of error

	CString buff;
	int len = edit_box->LineLength();
	edit_box->GetLine(0, buff.GetBuffer(len), len);
	buff.ReleaseBuffer(len);
	if (mode == 2) {
		int code = check_string(buff, 0);
		if (code == NOT_AN_INT)
			return NOT_AN_INT_SAMPLE_SIZE;
		else
			return code;
	}
	else
		return check_string(buff, mode);
}

CString ParameterDlg::GetErrorMessage(int error_code) {
	switch (error_code) {
	case NOT_A_NUMBER:
		return L"Please enter only numbers.\n";
	case NOT_AN_INT:
		return L"Absolute frequencies must be decimal numbers.\n";
	case EMPTY_BOX:
		return L"Please complete all created boxes.\n";
	case INVALID_FREQ:
		return L"Absolute frequencies must be greater than 0.\n";
	case COINCIDING_VALUES:
		return L"Values should not coincide.\n";
	case NOT_AN_INT_SAMPLE_SIZE:
		return L"Sample size must be decimal number.\n";
	case INVALID_SAMPLE_SIZE:
		return L"Sample size must be greater than 0.\n";
	default:
		return L"";
	}
}
