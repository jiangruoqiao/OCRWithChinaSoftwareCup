#pragma once


// aboutV �Ի���

class aboutV : public CDialogEx
{
	DECLARE_DYNAMIC(aboutV)

public:
	aboutV(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~aboutV();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
