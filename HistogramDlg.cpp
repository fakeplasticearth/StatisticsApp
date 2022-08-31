// HistogramDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"

#define BOX_HEIGHT 28 // высота edit box
#define BOX_WIDTH 50 // ширина edit box
#define BOX_START1X 159 // координата x левого верхнего угла первой линии edit box
#define BOX_START1Y 30 // координата y левого верхнего угла первой линии edit box
#define BOX_START2X 110 // координата x левого верхнего угла второй линии edit box
#define BOX_START2Y 90 // координата y левого верхнего угла второй линии edit box


// Диалоговое окно HistogramDlg

IMPLEMENT_DYNAMIC(HistogramDlg, CDialog)

HistogramDlg::HistogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_method_type(0)
	, m_sample_size(0)
{
	
}

HistogramDlg::~HistogramDlg()
{
}

void HistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_add_box);
	DDX_Control(pDX, IDC_BUTTON2, m_delete_box);
	DDX_Radio(pDX, IDC_RADIO1, m_method_type);
	DDX_Text(pDX, IDC_EDIT3, m_sample_size);
	DDV_MinMaxInt(pDX, m_sample_size, 1, 999999);
}


BEGIN_MESSAGE_MAP(HistogramDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &HistogramDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &HistogramDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &HistogramDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &HistogramDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &HistogramDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений HistogramDlg


void HistogramDlg::OnBnClickedButton1()
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

	edit_val_vector[box_num]->SetFont(box_font, 1);
	edit_freq_vector[box_num]->SetFont(box_font, 1);


	if (!init_mode) {
		if (box_num == 0)
			m_delete_box.EnableWindow(1);
		++box_num;
		if (box_num == 11)
			m_add_box.EnableWindow(0);
	}
}


void HistogramDlg::OnBnClickedButton2()
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


void HistogramDlg::OnBnClickedRadio1()
{
	m_method_type = 0;
}

void HistogramDlg::OnBnClickedRadio2()
{
	m_method_type = 1;
}


int HistogramDlg::check_string(CString str, int mode) {
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

int HistogramDlg::GetErrorCode(CEdit* edit_box, int mode) {
	// Input: id of edit box, mode - 0 for absolute frequency box, 1 for value box
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

void HistogramDlg::ProcessBoxData(CEdit* edit_box, int mode, int index) {
	/*Input: edit_box_id - id of edit box, 
	* mode - 0 for absolute frequency box, 1 for value box 
	* index - index for saving values to class fields
	*/
	int error_code = GetErrorCode(edit_box, mode);
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
			values[index] = _wtof(buff);
			break;
		}
	}
}

void HistogramDlg::OnBnClickedOk()
{
	
	error_found = 0;
	error_message = L"";
	for (int i = 0; i < 3; ++i)
		error_type_status[i] = 0;
	
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT2), 0, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT1), 1, 0);
	for (int i = 0; i < box_num; ++i) {
		ProcessBoxData(edit_freq_vector[i], 0, i + 1);
		ProcessBoxData(edit_val_vector[i], 1, i + 1);
	}

	if (error_found)
		AfxMessageBox(error_message);
	else {
		CDialog::OnOK();
	}
}

void HistogramDlg::fill_values(CBPv1Doc* doc) {
	box_num = doc->d0.get_size() - 1;
	m_method_type = doc->method_type;
	box_font = doc->box_font;
	m_sample_size = doc->sample_size;
	if ((int)box_num > -1) {
		for (int i = 0; i < box_num + 1; ++i) {
			values[i] = doc->d0.get_ith_value(i);
			abs_freqs[i] = doc->sum_freqs_h0 * doc->d0.get_ith_freq(i);
		}
	}
 	
}

BOOL HistogramDlg::OnInitDialog() {
	CString tmp;
	GetDlgItem(IDC_EDIT1)->SetWindowText(tmp);
	if (box_num == -1) {
		box_num = 0;
	}
	else {
		CString tmp_text;

		CEdit* first_freq_box = (CEdit*)GetDlgItem(IDC_EDIT2);
		CEdit* first_val_box = (CEdit*)GetDlgItem(IDC_EDIT1);

		tmp.Format(L"%d", abs_freqs[0]);
		first_freq_box->SetWindowText(tmp);
		first_freq_box->SetFont(box_font, 1);
		tmp.Format(L"%.3f", values[0]);
		first_val_box->SetWindowText(tmp);
		first_val_box->SetFont(box_font, 1);

		CEdit* sample_size_box = (CEdit*)GetDlgItem(IDC_EDIT3);
		sample_size_box->SetFont(box_font, 1);
		sample_size_box->SetLimitText(6);

		first_val_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_freq_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_val_box->SetLimitText(5);
		first_freq_box->SetLimitText(5);


		int tmp_box_num = box_num;
		for (int i = 0; i < tmp_box_num; ++i) {
			box_num = i;
			OnBnClickedButton1();
			tmp.Format(L"%d", abs_freqs[i + 1]);
			edit_freq_vector[i]->SetWindowText(tmp);
			tmp.Format(L"%.3f", values[i + 1]);
			edit_val_vector[i]->SetWindowText(tmp);
		}
		box_num = tmp_box_num;
	}
	init_mode = 0;
	UpdateData(0);
	return 1;
}
