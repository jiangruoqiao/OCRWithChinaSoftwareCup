#pragma once


// helpV �Ի���

class helpV : public CDialogEx
{
	DECLARE_DYNAMIC(helpV)

public:
	helpV(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~helpV();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
