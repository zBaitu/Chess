#pragma once


// CInitializeDlg dialog

class CInitializeDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitializeDlg)

public:
	CInitializeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInitializeDlg();

// Dialog Data
	enum { IDD = IDD_INITIALIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	// �����ؼ�����
	int m_iAnswer;
	int m_iAnswer1;

public:
	virtual BOOL OnInitDialog();	// ��ʼ���Ի���ʱ�Ĵ�����
	// �ؼ���Ӧ����
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedJiugongqi();
	afx_msg void OnBnClickedJiugongqiRj();
	afx_msg void OnBnClickedOthello();
	afx_msg void OnBnClickedOthelloRj();
};
