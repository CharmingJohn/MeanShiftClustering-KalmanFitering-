//Edited by github.com/charmingjohn


// Mean shift clusteringDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMeanshiftclusteringDlg ��ȭ ����
class CMeanshiftclusteringDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMeanshiftclusteringDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MEANSHIFTCLUSTERING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_folder;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk2();
};
