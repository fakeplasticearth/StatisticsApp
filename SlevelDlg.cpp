// SlevelDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "SlevelDlg.h"
#include "afxdialogex.h"


// Диалоговое окно SlevelDlg

IMPLEMENT_DYNAMIC(SlevelDlg, CDialog)

SlevelDlg::SlevelDlg(CWnd* pParent /*=nullptr*/)
	: ParameterDlg(IDD_DIALOG4, pParent), m_parameter(0)
	, m_method_type(0)
	, m_pvalue_sample_size(0)
	, m_max_sample_size(0)
	, m_alpha(0)
{
	for (int i = 0; i < 12; ++i) {
		values[i] = 0.;
		abs_freqs[i] = 0;
	}
}

SlevelDlg::~SlevelDlg()
{
}

void SlevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON7, m_add_box);
	DDX_Control(pDX, IDC_BUTTON8, m_delete_box);
	DDX_Radio(pDX, IDC_RADIO5, m_method_type);
	DDX_Text(pDX, IDC_M_EDIT3, m_parameter);
	DDV_MinMaxInt(pDX, m_parameter, 1, 20);
	DDX_Text(pDX, IDC_EDIT12, m_pvalue_sample_size);
	DDV_MinMaxInt(pDX, m_pvalue_sample_size, 1, 999999);
	DDX_Text(pDX, IDC_EDIT13, m_max_sample_size);
	DDV_MinMaxInt(pDX, m_max_sample_size, 1, 999999);
	DDX_Text(pDX, IDC_EDIT14, m_alpha);
}


BEGIN_MESSAGE_MAP(SlevelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON7, &SlevelDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &SlevelDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_RADIO5, &SlevelDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &SlevelDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDOK, &SlevelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений SlevelDlg


void SlevelDlg::OnBnClickedButton7()
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
		CWnd* freq_text = GetDlgItem(IDC_STATIC9);
		freq_text->ShowWindow(SW_SHOW);
		CWnd* value_text = GetDlgItem(IDC_STATIC10);
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


void SlevelDlg::OnBnClickedButton8()
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
		CWnd* freq_text = GetDlgItem(IDC_STATIC9);
		freq_text->ShowWindow(SW_HIDE);
		CWnd* value_text = GetDlgItem(IDC_STATIC10);
		value_text->ShowWindow(SW_HIDE);
	}
	--box_num;
	if (box_num == 0)
		m_delete_box.EnableWindow(0);
}


void SlevelDlg::OnBnClickedRadio5()
{
	m_method_type = 0;
	GetDlgItem(IDC_M_EDIT3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_M_TEXT3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_M_FRAME3)->ShowWindow(SW_HIDE);
}


void SlevelDlg::OnBnClickedRadio6()
{
	m_method_type = 1;
	GetDlgItem(IDC_M_EDIT3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_M_TEXT3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_M_FRAME3)->ShowWindow(SW_SHOW);
}

void SlevelDlg::ProcessBoxData(CEdit* edit_box, int mode, int index) {
	/*Input: edit_box_id - id of edit box,
	* mode - 0 for absolute frequency box, 1 for value box, 3 for pvalue sample size box, 4 for max sample size, 5 for significance level
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
				values[index] = _wtof(buff);
		}
		else if (mode == 5) {
			double val = _wtof(buff);
			if (val <= 0.) {
				error_type_status[SMALL_ALPHA] = 1;
				error_message += GetErrorMessage(SMALL_ALPHA);
				error_found = 1;
			}
			if (val >= 1.) {
				error_type_status[BIG_ALPHA] = 1;
				error_message += GetErrorMessage(BIG_ALPHA);
				error_found = 1;
			}
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
				else if (mode == 3){
					if (error_type_status[TOO_SMALL_PVALUE_SAMPLE_SIZE] == 0) {
						error_type_status[TOO_SMALL_PVALUE_SAMPLE_SIZE] = 1;
						error_message += GetErrorMessage(TOO_SMALL_PVALUE_SAMPLE_SIZE);
					}
				}
				else {
					if (error_type_status[TOO_SMALL_MAX_SAMPLE_SIZE] == 0) {
						error_type_status[TOO_SMALL_MAX_SAMPLE_SIZE] = 1;
						error_message += GetErrorMessage(TOO_SMALL_MAX_SAMPLE_SIZE);
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
				abs_freqs[index] = freq_val;
			}
		}
	}
}

afx_msg void SlevelDlg::OnBnClickedOk() {
	error_found = 0;
	error_message = L"";
	for (int i = 0; i < 10; ++i)
		error_type_status[i] = 0;

	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT10), 0, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT11), 1, 0);
	for (int i = 0; i < box_num; ++i) {
		ProcessBoxData(edit_freq_vector[i], 0, i + 1);
		ProcessBoxData(edit_val_vector[i], 1, i + 1);
	}

	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT12), 3, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT13), 4, 0);
	ProcessBoxData((CEdit*)GetDlgItem(IDC_EDIT14), 5, 0);

	if (error_found)
		AfxMessageBox(error_message);
	else {
		bool match = 0;
		for (int i = 0; i < box_num + 1; ++i)
			for (int j = i + 1; j < box_num + 1; ++j) {
				if (values[i] == values[j])
					match = 1;
			}

		if (!match) {
			int sum_freqs = 0;
			for (int i = 0; i < box_num + 1; ++i)
				sum_freqs += abs_freqs[i];


			CString buff;
			int len = ((CEdit*)GetDlgItem(IDC_EDIT13))->LineLength();
			((CEdit*)GetDlgItem(IDC_EDIT13))->GetLine(0, buff.GetBuffer(len), len);
			buff.ReleaseBuffer(len);
			int tmp_max_sample_size = _wtoi(buff);

			bool df_less_than_one = 1;
			int n = 0;

			int* th_freqs_merged = new int[box_num + 3];

			point_th* th_points_sorted = new point_th[box_num + 3];

			for (int i = 0; i < box_num + 1; ++i) {
				th_points_sorted[i] = { 1. * abs_freqs[i], values[i] };
			}
			std::sort(th_points_sorted, th_points_sorted + box_num + 1, [](const point_th& lval, const point_th& rval) {
				return lval.value < rval.value;
				});

			while (df_less_than_one) {
				++n;

				int df = 0;

				for (int i = 0; i < box_num + 1; ++i) {
					th_freqs_merged[df] = 0;
					for (; (i < box_num + 1) && (th_freqs_merged[df] * n / sum_freqs < 5); ++i) {
						th_freqs_merged[df] += th_points_sorted[i].freq;
					}
					if (th_freqs_merged[df] * n / sum_freqs < 5 && df >= 1) {
						th_freqs_merged[df - 1] += th_freqs_merged[df];
						--df;
					}
					--i;
					++df;
				}
				--df;

				df_less_than_one = df < 1;
			}
			min_sample_size = n;

			delete[]th_freqs_merged;
			delete[]th_points_sorted;

			if (tmp_max_sample_size < min_sample_size) {
				CString tmp;
				tmp.Format(L"%d", min_sample_size);
				AfxMessageBox(error_message + L"Max sample size must be greater or equal than " + tmp + L"\n");
			}
			else
			{
				CDialog::OnOK();
			}
		}
		else
			AfxMessageBox(error_message + GetErrorMessage(COINCIDING_VALUES));
	}
}

void SlevelDlg::fill_values(CBPv1Doc* doc) {
	box_num = doc->d0.get_size() - 1;
	m_method_type = doc->method_type;
	box_font = doc->box_font;
	m_sample_size = doc->sample_size;
	m_parameter = doc->chen_parameter;
	m_max_sample_size = doc->max_sample_size;
	m_pvalue_sample_size = doc->pvalue_sample_size;
	m_alpha = doc->alpha;
	if ((int)box_num > -1) {
		for (int i = 0; i < box_num + 1; ++i) {
			values[i] = doc->d0.get_ith_value(i);
			abs_freqs[i] = doc->sum_freqs_h0 * doc->d0.get_ith_freq(i);
		}
	}

}

BOOL SlevelDlg::OnInitDialog() {
	CString tmp;
	GetDlgItem(IDC_EDIT12)->SetWindowText(tmp);
	if (m_method_type == 0) {
		GetDlgItem(IDC_M_EDIT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_M_TEXT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_M_FRAME3)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_M_EDIT3)->SetFont(box_font, 1);
	GetDlgItem(IDC_EDIT13)->SetFont(box_font, 1);
	GetDlgItem(IDC_EDIT14)->SetFont(box_font, 1);
	((CEdit*)GetDlgItem(IDC_EDIT14))->SetLimitText(6);

	if (box_num == -1) {
		box_num = 0;
	}
	else {
		CString tmp_text;

		CEdit* first_freq_box = (CEdit*)GetDlgItem(IDC_EDIT10);
		CEdit* first_val_box = (CEdit*)GetDlgItem(IDC_EDIT11);

		tmp.Format(L"%d", abs_freqs[0]);
		first_freq_box->SetWindowText(tmp);
		first_freq_box->SetFont(box_font, 1);
		tmp.Format(L"%.3f", values[0]);
		first_val_box->SetWindowText(tmp);
		first_val_box->SetFont(box_font, 1);

		CEdit* pvalue_sample_size_box = (CEdit*)GetDlgItem(IDC_EDIT12);
		pvalue_sample_size_box->SetFont(box_font, 1);
		pvalue_sample_size_box->SetLimitText(6);

		first_val_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_freq_box->ModifyStyle(0, ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP, SWP_FRAMECHANGED);
		first_val_box->SetLimitText(5);
		first_freq_box->SetLimitText(5);


		int tmp_box_num = box_num;
		for (int i = 0; i < tmp_box_num; ++i) {
			box_num = i;
			OnBnClickedButton7();
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