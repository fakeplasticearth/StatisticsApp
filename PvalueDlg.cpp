// PvalueDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "PvalueDlg.h"
#include "afxdialogex.h"


// Диалоговое окно PvalueDlg

IMPLEMENT_DYNAMIC(PvalueDlg, CDialog)

PvalueDlg::PvalueDlg(CWnd* pParent /*=nullptr*/)
	: ParameterDlg(IDD_DIALOG2, pParent)
	, m_method_type(0)
	, m_pvalue_sample_size(0)
	, m_parameter(0)
{

}

PvalueDlg::~PvalueDlg()
{
}



void PvalueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_h0_add_box);
	DDX_Control(pDX, IDC_BUTTON4, m_h0_delete_box);
	DDX_Control(pDX, IDC_BUTTON5, m_h1_add_box);
	DDX_Control(pDX, IDC_BUTTON6, m_h1_delete_box);
	DDX_Radio(pDX, IDC_RADIO3, m_method_type);
	DDX_Text(pDX, IDC_EDIT9, m_sample_size);
	DDV_MinMaxInt(pDX, m_sample_size, 1, 999999);
	DDX_Text(pDX, IDC_EDIT8, m_pvalue_sample_size);
	DDV_MinMaxInt(pDX, m_pvalue_sample_size, 1, 999999);
	DDX_Text(pDX, IDC_M_EDIT2, m_parameter);
	DDV_MinMaxInt(pDX, m_parameter, 1, 20);
}


BEGIN_MESSAGE_MAP(PvalueDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &PvalueDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PvalueDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &PvalueDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &PvalueDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDOK, &PvalueDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO3, &PvalueDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &PvalueDlg::OnBnClickedRadio4)
END_MESSAGE_MAP()


// Обработчики сообщений PvalueDlg

void PvalueDlg::fill_values(CBPv1Doc* doc) {
	h0_box_num = doc->d0.get_size() - 1;
	h1_box_num = doc->d1.get_size() - 1;
	m_method_type = doc->method_type;
	box_font = doc->box_font;
	m_sample_size = doc->sample_size;
	m_pvalue_sample_size = doc->pvalue_sample_size;
	m_parameter = doc->chen_parameter;
	if ((int)h0_box_num > -1) {
		for (int i = 0; i < h0_box_num + 1; ++i) {
			h0_values[i] = doc->d0.get_ith_value(i);
			h0_abs_freqs[i] = doc->sum_freqs_h0 * doc->d0.get_ith_freq(i);
		}
	}

	if ((int)h1_box_num > -1) {
		for (int i = 0; i < h1_box_num + 1; ++i) {
			h1_values[i] = doc->d1.get_ith_value(i);
			h1_abs_freqs[i] = doc->sum_freqs_h1 * doc->d1.get_ith_freq(i);
		}
	}
}

void PvalueDlg::OnBnClickedButton3()
{
	unsigned int x, y;
	unsigned int shifted_box_num;
	if (h0_box_num < 5) {
		x = H0_BOX_START1X;
		y = H0_BOX_START1Y;
		shifted_box_num = h0_box_num;
	}
	else {
		x = H0_BOX_START2X;
		y = H0_BOX_START2Y;
		shifted_box_num = h0_box_num - 5;
		CWnd* freq_text = GetDlgItem(IDC_STATIC5);
		freq_text->ShowWindow(SW_SHOW);
		CWnd* value_text = GetDlgItem(IDC_STATIC6);
		value_text->ShowWindow(SW_SHOW);
	}
	h0_edit_freq_vector.push_back(new CEdit);
	h0_edit_freq_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
	CRect(x + BOX_WIDTH * shifted_box_num, y, x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT), this, 1);
	h0_edit_val_vector.push_back(new CEdit);
	h0_edit_val_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(x + BOX_WIDTH * shifted_box_num, y + BOX_HEIGHT,
			x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT + BOX_HEIGHT), this, 1);

	h0_edit_val_vector[h0_box_num]->SetFont(box_font, 1);
	h0_edit_freq_vector[h0_box_num]->SetFont(box_font, 1);


	if (!init_mode) {
		if (h0_box_num == 0)
			m_h0_delete_box.EnableWindow(1);
		++h0_box_num;
		if (h0_box_num == 11)
			m_h0_add_box.EnableWindow(0);
	}
}


void PvalueDlg::OnBnClickedButton4()
{
	h0_edit_freq_vector.back()->Clear();
	delete h0_edit_freq_vector.back();
	h0_edit_freq_vector.pop_back();
	h0_edit_val_vector.back()->Clear();
	delete h0_edit_val_vector.back();
	h0_edit_val_vector.pop_back();
	if (h0_box_num == 11)
		m_h0_add_box.EnableWindow(1);
	if (h0_box_num == 6) {
		CWnd* freq_text = GetDlgItem(IDC_STATIC5);
		freq_text->ShowWindow(SW_HIDE);
		CWnd* value_text = GetDlgItem(IDC_STATIC6);
		value_text->ShowWindow(SW_HIDE);
	}
	--h0_box_num;
	if (h0_box_num == 0)
		m_h0_delete_box.EnableWindow(0);
}


void PvalueDlg::OnBnClickedButton5()
{
	unsigned int x, y;
	unsigned int shifted_box_num;
	if (h1_box_num < 5) {
		x = H1_BOX_START1X;
		y = H1_BOX_START1Y;
		shifted_box_num = h1_box_num;
	}
	else {
		x = H1_BOX_START2X;
		y = H1_BOX_START2Y;
		shifted_box_num = h1_box_num - 5;
		CWnd* freq_text = GetDlgItem(IDC_STATIC7);
		freq_text->ShowWindow(SW_SHOW);
		CWnd* value_text = GetDlgItem(IDC_STATIC8);
		value_text->ShowWindow(SW_SHOW);
	}
	h1_edit_freq_vector.push_back(new CEdit);
	h1_edit_freq_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(x + BOX_WIDTH * shifted_box_num, y, x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT), this, 1);
	h1_edit_val_vector.push_back(new CEdit);
	h1_edit_val_vector.back()->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(x + BOX_WIDTH * shifted_box_num, y + BOX_HEIGHT,
			x + BOX_WIDTH * (1 + shifted_box_num), y + BOX_HEIGHT + BOX_HEIGHT), this, 1);

	h1_edit_val_vector[h1_box_num]->SetFont(box_font, 1);
	h1_edit_freq_vector[h1_box_num]->SetFont(box_font, 1);


	if (!init_mode) {
		if (h1_box_num == 0)
			m_h1_delete_box.EnableWindow(1);
		++h1_box_num;
		if (h1_box_num == 11)
			m_h1_add_box.EnableWindow(0);
	}
}


void PvalueDlg::OnBnClickedButton6()
{
	h1_edit_freq_vector.back()->Clear();
	delete h1_edit_freq_vector.back();
	h1_edit_freq_vector.pop_back();
	h1_edit_val_vector.back()->Clear();
	delete h1_edit_val_vector.back();
	h1_edit_val_vector.pop_back();
	if (h1_box_num == 11)
		m_h1_add_box.EnableWindow(1);
	if (h1_box_num == 6) {
		CWnd* freq_text = GetDlgItem(IDC_STATIC7);
		freq_text->ShowWindow(SW_HIDE);
		CWnd* value_text = GetDlgItem(IDC_STATIC8);
		value_text->ShowWindow(SW_HIDE);
	}
	--h1_box_num;
	if (h1_box_num == 0)
		m_h1_delete_box.EnableWindow(0);
}

BOOL PvalueDlg::OnInitDialog() {
	CString tmp;

	CEdit* sample_size_box = (CEdit*)GetDlgItem(IDC_EDIT9);
	sample_size_box->SetFont(box_font, 1);
	sample_size_box->SetLimitText(6);

	CEdit* pvalue_sample_size_box = (CEdit*)GetDlgItem(IDC_EDIT8);
	pvalue_sample_size_box->SetFont(box_font, 1);
	pvalue_sample_size_box->SetLimitText(6);

	if (m_method_type == 0) {
		GetDlgItem(IDC_M_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_M_TEXT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_M_FRAME2)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_M_EDIT2)->SetFont(box_font, 1);

	if (h0_box_num == -1) {
		h0_box_num = 0;
	}
	else {
		CString tmp_text;

		CEdit* first_freq_box = (CEdit*)GetDlgItem(IDC_EDIT4);
		CEdit* first_val_box = (CEdit*)GetDlgItem(IDC_EDIT5);

		tmp.Format(L"%d", h0_abs_freqs[0]);
		first_freq_box->SetWindowText(tmp);
		first_freq_box->SetFont(box_font, 1);
		tmp.Format(L"%.3f", h0_values[0]);
		first_val_box->SetWindowText(tmp);
		first_val_box->SetFont(box_font, 1);

		first_val_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_freq_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_val_box->SetLimitText(5);
		first_freq_box->SetLimitText(5);


		int tmp_box_num = h0_box_num;
		for (int i = 0; i < tmp_box_num; ++i) {
			h0_box_num = i;
			OnBnClickedButton3();
			tmp.Format(L"%d", h0_abs_freqs[i + 1]);
			h0_edit_freq_vector[i]->SetWindowText(tmp);
			tmp.Format(L"%.3f", h0_values[i + 1]);
			h0_edit_val_vector[i]->SetWindowText(tmp);
		}
		h0_box_num = tmp_box_num;
	}

	if (h1_box_num == -1) {
		h1_box_num = 0;
	}
	else {
		CString tmp_text;

		CEdit* first_freq_box = (CEdit*)GetDlgItem(IDC_EDIT6);
		CEdit* first_val_box = (CEdit*)GetDlgItem(IDC_EDIT7);

		tmp.Format(L"%d", h1_abs_freqs[0]);
		first_freq_box->SetWindowText(tmp);
		first_freq_box->SetFont(box_font, 1);
		tmp.Format(L"%.3f", h1_values[0]);
		first_val_box->SetWindowText(tmp);
		first_val_box->SetFont(box_font, 1);

		first_val_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_freq_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_val_box->SetLimitText(5);
		first_freq_box->SetLimitText(5);


		int tmp_box_num = h1_box_num;
		for (int i = 0; i < tmp_box_num; ++i) {
			h1_box_num = i;
			OnBnClickedButton5();
			tmp.Format(L"%d", h1_abs_freqs[i + 1]);
			h1_edit_freq_vector[i]->SetWindowText(tmp);
			tmp.Format(L"%.3f", h1_values[i + 1]);
			h1_edit_val_vector[i]->SetWindowText(tmp);
		}
		h1_box_num = tmp_box_num;
	}

	init_mode = 0;
	UpdateData(0);
	return 1;
}

void PvalueDlg::ProcessBoxData(CEdit* edit_box, int mode, int hyp_num, int index) {
	/*Input: edit_box_id - id of edit box,
	* mode - 0 for absolute frequency box, 1 for value box, 2 for sample size box, 3 for pvalue sample size box
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
		if (mode == 1) {
			if (hyp_num)
				h1_values[index] = _wtof(buff);
			else
				h0_values[index] = _wtof(buff);
		}
		else {
			int freq_val = _wtoi(buff);
			if (freq_val <= 0) {
				error_found = 1;
				if (mode == 0) {
					if (error_type_status[INVALID_FREQ] == 0) {
						error_type_status[INVALID_FREQ] = 1;
						error_message += GetErrorMessage(INVALID_FREQ);
					}
				}
				else if (mode == 2){
					if (error_type_status[INVALID_SAMPLE_SIZE] == 0) {
						error_type_status[INVALID_SAMPLE_SIZE] = 1;
						error_message += GetErrorMessage(INVALID_SAMPLE_SIZE);
					}
				}
				else {
					if (error_type_status[TOO_SMALL_PVALUE_SAMPLE_SIZE] == 0) {
						error_type_status[TOO_SMALL_PVALUE_SAMPLE_SIZE] = 1;
						error_message += GetErrorMessage(TOO_SMALL_PVALUE_SAMPLE_SIZE);
					}
				}
			}
			else if ((freq_val > 10000) && (mode == 3)) {
				error_found = 1;
				if (error_type_status[TOO_BIG_PVALUE_SAMPLE_SIZE] == 0) {
					error_type_status[TOO_BIG_PVALUE_SAMPLE_SIZE] = 1;
					error_message += GetErrorMessage(TOO_BIG_PVALUE_SAMPLE_SIZE);
				}
			}
			else if (mode == 0) {
				if (hyp_num)
					h1_abs_freqs[index] = freq_val;
				else
					h0_abs_freqs[index] = freq_val;
			}
		}
	}
}

void PvalueDlg::OnBnClickedOk()
{

	error_found = 0;
	error_message = L"";
	for (int i = 0; i < 10; ++i)
		error_type_status[i] = 0;

	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT4), 0, 0, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT5), 1, 0, 0);
	for (int i = 0; i < h0_box_num; ++i) {
		ProcessBoxData(h0_edit_freq_vector[i], 0, 0, i + 1);
		ProcessBoxData(h0_edit_val_vector[i], 1, 0, i + 1);
	}

	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT6), 0, 1, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT7), 1, 1, 0);
	for (int i = 0; i < h1_box_num; ++i) {
		ProcessBoxData(h1_edit_freq_vector[i], 0, 1, i + 1);
		ProcessBoxData(h1_edit_val_vector[i], 1, 1, i + 1);
	}

	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT9), 2, 0, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT8), 3, 0, 0);

	if (error_found)
		AfxMessageBox(error_message);
	else {
		bool match = 0;
		for (int i = 0; i < h0_box_num + 1; ++i)
			for (int j = i + 1; j < h0_box_num + 1; ++j) {
				if (h0_values[i] == h0_values[j])
					match = 1;
			}
		for (int i = 0; i < h1_box_num + 1; ++i)
			for (int j = i + 1; j < h1_box_num + 1; ++j) {
				if (h1_values[i] == h1_values[j])
					match = 1;
			}

		if (!match)
			CDialog::OnOK();
		else
			AfxMessageBox(error_message + GetErrorMessage(COINCIDING_VALUES));
	}
}


void PvalueDlg::OnBnClickedRadio3()
{
	m_method_type = 0;
	GetDlgItem(IDC_M_EDIT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_M_TEXT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_M_FRAME2)->ShowWindow(SW_HIDE);
}




void PvalueDlg::OnBnClickedRadio4()
{
	m_method_type = 1;
	GetDlgItem(IDC_M_EDIT2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_M_TEXT2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_M_FRAME2)->ShowWindow(SW_SHOW);
}
