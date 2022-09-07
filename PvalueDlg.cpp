// PvalueDlg.cpp: файл реализации
//

#include "pch.h"
#include "BPv1.h"
#include "PvalueDlg.h"
#include "afxdialogex.h"


// Диалоговое окно PvalueDlg

IMPLEMENT_DYNAMIC(PvalueDlg, CDialog)

PvalueDlg::PvalueDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

PvalueDlg::~PvalueDlg()
{
}

void PvalueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PvalueDlg, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений PvalueDlg
