
// ReNet_OCRDlg.h : ͷ�ļ�
//
#include <opencv2/opencv.hpp>
#pragma once


// CReNet_OCRDlg �Ի���
class CReNet_OCRDlg : public CDialogEx
{
// ����
public:
	CReNet_OCRDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENET_OCR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int MatToCImage(cv::Mat* mat, CImage& cImage);
	void printToExcel(std::vector<std::string> contentOfImage);
	void ProccessPic(const CString &CstrPath);
	bool EnImageNeedProccess(const CString &CstrPath);
	cv::Mat imageClean(cv::Mat rawImage);
	cv::Mat imageAddBlackGround(cv::Mat lineImage);
	cv::Mat cleanImageOther(cv::Mat rawImage);
	std::vector<std::string> fileSearch(std::string path, std::string mode);
	std::string Trim(std::string s);
	std::string TrimSpace(std::string s);
	std::string changecodeTowide(std::string contant);
	std::vector<cv::Mat> wordSpiltLine(cv::Mat rawImage, cv::Mat cleanedImage);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit5();
};
