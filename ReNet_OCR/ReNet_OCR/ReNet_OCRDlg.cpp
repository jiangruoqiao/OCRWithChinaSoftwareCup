
// ReNet_OCRDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReNet_OCR.h"
#include "ReNet_OCRDlg.h"
#include "afxdialogex.h"
#include "aboutV.h"
#include "helpV.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <leptonica\allheaders.h>  
#include <capi.h> 
#include <stdio.h>  
#include "saveData.h"
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <atlconv.h>
#include <Windows.h>
#include <urlmon.h>
#include <tchar.h>
#include <WinBase.h>
#include <afx.h>
#include <io.h>
#include <stdio.h>  
#include <capi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ȫ�ֱ���
std::vector<std::string> fileName;
std::vector<std::string> filePath;
CString strDir = L" ";
CString savefilePath = L"C:\\Users\\ly\\Desktop\\scoresheet.csv";
CString saveExcelPath;
std::ofstream oFile;
bool OnlineFlag;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReNet_OCRDlg �Ի���



CReNet_OCRDlg::CReNet_OCRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENET_OCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReNet_OCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReNet_OCRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CReNet_OCRDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CReNet_OCRDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CReNet_OCRDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CReNet_OCRDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDCANCEL, &CReNet_OCRDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CReNet_OCRDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CReNet_OCRDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CReNet_OCRDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT5, &CReNet_OCRDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CReNet_OCRDlg ��Ϣ�������

BOOL CReNet_OCRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CReNet_OCRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReNet_OCRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReNet_OCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**���ܴ��뺯������**/
/***���ַ���***/
std::vector<cv::Mat> CReNet_OCRDlg::wordSpiltLine(cv::Mat rawImage, cv::Mat cleanedImage)
{
	int perPixelValue;
	int width = cleanedImage.cols;
	int height = cleanedImage.rows;
	int* projectValArry = new int[width];
	memset(projectValArry, 0, width * 4);
	for (int col = 0; col < height; col++)
	{
		for (int row = 0; row < width; row++)
		{
			perPixelValue = cleanedImage.at<uchar>(col, row);
			if (perPixelValue == 255)
			{
				projectValArry[col]++;
			}
		}
	}
	/*�½�һ��Mat���ڴ���ͶӰֱ��ͼ����������Ϊ��ɫ*/
	cv::Mat verticalProjectionMat(height, width, CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			perPixelValue = 255;  //��������Ϊ��ɫ��
			verticalProjectionMat.at<uchar>(i, j) = perPixelValue;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < projectValArry[i]; j++)
		{
			perPixelValue = 0;  //ֱ��ͼ����Ϊ��ɫ
			verticalProjectionMat.at<uchar>(i, j) = perPixelValue;
		}
	}
	std::vector<cv::Mat> roiList;
	int startIndex = 0;
	int endIndex = 0;
	bool inBlock = false;
	for (int i = 0; i < cleanedImage.rows; ++i)
	{
		if (!inBlock && projectValArry[i] != 0)     //�����ַ�����
		{
			inBlock = true;
			startIndex = i;
		}
		else if (projectValArry[i] == 0 && inBlock) //����հ�����
		{
			endIndex = i;
			inBlock = false;
			cv::Mat roiImg = rawImage(cv::Range(startIndex, endIndex), cv::Range(0, cleanedImage.cols));
			roiList.push_back(roiImg);
		}
	}
	std::cout << roiList.size() << std::endl;
	delete[] projectValArry;//��Ҫ����ɾ������ռ�
	return roiList;
}
/***ȥ�ո�***/
std::string CReNet_OCRDlg::TrimSpace(std::string s)
{
	int index = 0;
	if (!s.empty())
	{
		while ((index = s.find('/n', index)) != std::string::npos)
		{
			s.erase(index, 1);
		}
	}
	return s;
}
/***Mat��ʽת����CImage***/
int CReNet_OCRDlg::MatToCImage(cv::Mat* mat, CImage& img)
{
	if (!mat || mat->empty())
		return -1;
	int nBPP = mat->channels() * 8;
	img.Create(mat->cols, mat->rows, nBPP);
	if (nBPP == 8)
	{
		static RGBQUAD pRGB[256];
		for (int i = 0; i < 256; i++)
		{
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
		}
		img.SetColorTable(0, 256, pRGB);
	}
	uchar* psrc = mat->data;
	uchar* pdst = (uchar*)img.GetBits();
	int imgPitch = img.GetPitch();
	for (int y = 0; y < mat->rows; y++)
	{
		memcpy(pdst, psrc, mat->cols *mat->channels());
		psrc += mat->step;
		pdst += imgPitch;
	}
	return 0;
}
/***�����Excel�����***/
void CReNet_OCRDlg::printToExcel(std::vector<std::string> contentOfImage)
{
	dataText dataText;
	dataText.dataOfJson = contentOfImage.at(0);
	CString CgetCompanyNumber(dataText.getCompanyNumber().c_str()); // ��stringתΪcstring ��ҵע���
	dataText.dataOfJson = contentOfImage.at(1);
	CString CgetCompanyName(dataText.getCompanyName().c_str()); // ��stringתΪcstring ��ҵ����
	dataText.dataOfJson = contentOfImage.at(2);

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->ReplaceSel(CgetCompanyNumber + "   " + CgetCompanyName + "\r\n");
	//SetDlgItemText(IDC_EDIT4, CgetCompanyName + " " + CgetCompanyNumber + " " + CgetCompanySytle + " " + CgetCompanyAdress + " " + CgetCompanyHoster + " " + CgetCompanyBuildTime + " " + CgetCompanyBuildMomey + " " + CgetCompanyRunTime+ " " + CgetCompanyRunRange + " " + CgetCompanySignIn + " " + CgetCompanyCheckTime+"\r\n"); //��ʾ��IDΪIDC_EDIT1�����ֿؼ���
	//MessageBoxEx(NULL, CgetCompanyRunTime, L"Alert", MB_OKCANCEL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	// �����ͺ����׵����һ����Ҫ��excel �ļ�
	oFile << dataText.getCompanyName() << "," << "'" << dataText.getCompanyNumber() << std::endl;
	//oFile << dataText.getCompanyName() << "," << dataText.getCompanyNumber()  << std::endl;
}
/***�����ı�ͼ��***/
void CReNet_OCRDlg::ProccessPic(const CString &CstrPath)
{
	std::string strPath = CT2A(CstrPath);   //Cstringתstring
	std::string comtent = " ";
	cv::Mat rawImage = cv::imread(strPath, CV_LOAD_IMAGE_UNCHANGED); //strPathΪͼƬ��·��
	bool enImage = TRUE;
	bool enType1 = FALSE;
	bool enType2 = FALSE;
	if (!rawImage.data)
	{
		CString errorImage = L"ͼ�������޷����룡";
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
		pEdit->ReplaceSel(errorImage + "\r\n");
		enImage = FALSE;
	}
	else
	{
		int widthOfImage = rawImage.cols;
		int heightOfImage = rawImage.rows;
		int channelsOfImage = rawImage.channels();	
		if (channelsOfImage != 4)
		{
			enImage = FALSE;
			if (widthOfImage < heightOfImage)
			{
				enImage = FALSE;
				enType1 = TRUE;
			}
			else
			{
				cv::Mat cleanedImageTpye2 = imageClean(rawImage);//������ͼƬ���д���ȥ��ˮӡ
				std::vector<cv::Mat> wordLineTpye2;
				wordLineTpye2 = wordSpiltLine(cleanedImageTpye2, cleanedImageTpye2);
				if (0 == wordLineTpye2.size())
				{
					enType2 = TRUE;
				}
			}
		}
	}

	if (enType2)
	{
		SetDlgItemText(IDC_STATIC, L"������㡶��ҵ����Ӫҵִ�ա�");
		cv::Mat image = cv::imread(strPath);
		int widthImage = image.cols;
		int heigthImage = image.rows;
		cv::Mat grayImage;
		//cvtColor(image, grayImage, CV_BGR2GRAY);
		grayImage = cleanImageOther(image);
		cv::Mat clean = grayImage(cv::Range((int)heigthImage / 8, (int)heigthImage / 2), cv::Range((int)widthImage / 10, (int)widthImage / 2));
		cv::Mat cleanRawImage = image(cv::Range((int)heigthImage / 8, (int)heigthImage / 2), cv::Range((int)widthImage / 10, (int)widthImage / 2));
		
		CRect rect;
		GetDlgItem(IDC_STATIC_Image)->GetClientRect(&rect);
		cv::Size winSize(rect.right, rect.bottom);
		cv::Mat cvImgTmp(winSize, CV_8UC3);
		if (cleanRawImage.size() != winSize)
		{
			cv::resize(cleanRawImage, cvImgTmp, winSize);
		}
		else
		{
			cvImgTmp = cleanRawImage;
		}
		CImage imgDst;
		MatToCImage(&cleanRawImage, imgDst);
		imgDst.Draw(GetDlgItem(IDC_STATIC_Image)->GetDC()->GetSafeHdc(), rect);
		
		std::vector<cv::Mat> word;
		word = wordSpiltLine(cleanRawImage, clean);
		std::cout << word.size() << std::endl;
		cv::Mat input;
		cv::Mat input1;
		input = imageAddBlackGround(word.at(3));
		imwrite("r.png", input);
		input1 = imageAddBlackGround(word.at(2));
		imwrite("r1.png",input1);
		TessBaseAPI *handle;

		PIX *img;
		char *text;
		handle = TessBaseAPICreate();
		TessBaseAPIInit3(handle, NULL, "chi_sim_1");
		img = pixRead("r.png");
		handle = TessBaseAPICreate();
		TessBaseAPIInit3(handle, NULL, "chi_sim_1");
		TessBaseAPISetImage2(handle, img);
		TessBaseAPIRecognize(handle, NULL);
		text = TessBaseAPIGetUTF8Text(handle);
		std::cout << text << std::endl;
		std::string s = text;
		std::cout << s << std::endl;
		s = changecodeTowide(s);
		s = Trim(s);
		TessDeleteText(text);
		TessBaseAPIEnd(handle);
		TessBaseAPIDelete(handle);
		pixDestroy(&img);

		TessBaseAPI *handle1;
		PIX *img1;
		char *text1;
		handle1 = TessBaseAPICreate();
		TessBaseAPIInit3(handle1, NULL, "chi_sim_1");
		img1 = pixRead("r1.png");
		handle1 = TessBaseAPICreate();
		TessBaseAPIInit3(handle1, NULL, "chi_sim_1");
		TessBaseAPISetImage2(handle1, img1);
		TessBaseAPIRecognize(handle1, NULL);
		text1 = TessBaseAPIGetUTF8Text(handle1);
		std::cout << text1 << std::endl;
		std::string s1 = text1;
		std::cout << s1 << std::endl;
		s1 = changecodeTowide(s1);
		s1 = Trim(s1);
		TessDeleteText(text1);
		TessBaseAPIEnd(handle1);
		TessBaseAPIDelete(handle1);
		pixDestroy(&img1);

		dataText dataText;
		dataText.dataOfJson = s1;
		CString CgetCompanyNumber(dataText.getCompanyNumberT1().c_str()); // ��stringתΪcstring ��ҵע���
		dataText.dataOfJson = s;
		CString CgetCompanyName(dataText.getCompanyNameT1().c_str()); // ��stringתΪcstring ��ҵ����

		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
		if (!CgetCompanyNumber.IsEmpty())
		{
			pEdit->ReplaceSel(CgetCompanyNumber + "   " + CgetCompanyName + "\r\n");
			// �����ͺ����׵����һ����Ҫ��excel �ļ�
			oFile << dataText.getCompanyNameT1() << "," << "'" << dataText.getCompanyNumberT1() << std::endl;
		}
		else
		{
			CString errorImage = L"ͼ�����ģ�����޷�ʶ��";
			pEdit->ReplaceSel(errorImage + "\r\n");
		}
	}

	if (enType1)
	{
		SetDlgItemText(IDC_STATIC, L"���������Ӫҵִ�ա�");
		CString errorImage = L"�ݲ�֧�ָ�ͼƬ��ʽ";
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
		pEdit->ReplaceSel(errorImage + "\r\n");
	}

	if (enImage) 
	{
		SetDlgItemText(IDC_STATIC, L"��׼��ˮӡͼ��");
		
		int widthOfImage = rawImage.cols;
		int heightOfImage = rawImage.rows;
		int channelsOfImage = rawImage.channels();
		cv::Mat cleanedImage = imageClean(rawImage);//������ͼƬ���д���ȥ��ˮӡ
		TessBaseAPI *handle;
		PIX *img;
		char *text;
		handle = TessBaseAPICreate();
		TessBaseAPIInit3(handle, NULL, "chi_sim_1");
		cv::Mat out;
		cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2)); //��
		erode(cleanedImage, out, element);
		cv::Mat lineOne;
		//���ɿհ�ͼ�񱳾�
		cv::Mat proessImage(heightOfImage, widthOfImage, CV_8UC1);
		for (int i = 0; i < widthOfImage; i++)
		{
			for (int j = 0; j < heightOfImage; j++)
			{
				proessImage.at<uchar>(j, i) = rawImage.at<cv::Vec4b>(j, i)[3];
				if ((rawImage.at<cv::Vec4b>(j, i)[2] == 229) && (rawImage.at<cv::Vec4b>(j, i)[0] == 229) && (rawImage.at<cv::Vec4b>(j, i)[1] == 229))
				{
					rawImage.at<cv::Vec4b>(j, i)[3] = 255;
					rawImage.at<cv::Vec4b>(j, i)[0] = 0;
					rawImage.at<cv::Vec4b>(j, i)[1] = 0;
					rawImage.at<cv::Vec4b>(j, i)[2] = 0;
					proessImage.at<uchar>(j, i) = 0;
				}
			}
		}
		/**��ʾͼƬ**/
		CRect rect;
		GetDlgItem(IDC_STATIC_Image)->GetClientRect(&rect);
		cv::Size winSize(rect.right, rect.bottom);
		cv::Mat cvImgTmp(winSize, CV_8UC3);
		if (proessImage.size() != winSize)
		{
			cv::resize(proessImage, cvImgTmp, winSize);
		}
		else
		{
			cvImgTmp = proessImage;
		}
		CImage imgDst;
		MatToCImage(&proessImage, imgDst);
		imgDst.Draw(GetDlgItem(IDC_STATIC_Image)->GetDC()->GetSafeHdc(), rect);
		/**�ַ��ָ�**/
		std::vector<cv::Mat> wordLine;
		std::vector<std::string> wordLineString;
		wordLine = wordSpiltLine(proessImage, out);
		std::string contentOfImage = " ";
		std::string tempString = " ";
		cv::Mat lineP;
		for (int i = 0; i < 3; i++)
		{
			lineOne = wordLine.at(i);
			lineP = imageAddBlackGround(lineOne);
			imwrite("1.jpg", lineP);
			img = pixRead("1.jpg");
			TessBaseAPISetImage2(handle, img);
			TessBaseAPIRecognize(handle, NULL);
			text = TessBaseAPIGetUTF8Text(handle);
			tempString = text;
			tempString = changecodeTowide(tempString);
			tempString = Trim(tempString); //ȥ���ո�/
			wordLineString.push_back(tempString);
			contentOfImage = tempString + contentOfImage;
		}
		TessDeleteText(text);
		TessBaseAPIEnd(handle);
		TessBaseAPIDelete(handle);
		contentOfImage = Trim(contentOfImage); //ȥ���ո�
		contentOfImage = changecodeTowide(contentOfImage);  //�����ʽת��
		printToExcel(wordLineString);
	}
}

/**��Ӻڱ�**/
cv::Mat CReNet_OCRDlg::imageAddBlackGround(cv::Mat lineImage)
{
	cv::Mat proessImage;
	cv::Scalar value;
	proessImage = lineImage;
	copyMakeBorder(lineImage, proessImage, 10, 10, 10, 10, cv::BORDER_CONSTANT, value);
	return proessImage;
}

/***ȥ�ո�***/
std::string CReNet_OCRDlg::Trim(std::string s)
{
	int index = 0;
	if (!s.empty())
	{
		while ((index = s.find(' ', index)) != std::string::npos)
		{
			s.erase(index, 1);
		}
	}
	return s;
}
/****ͼ��ȥ��ˮӡ****/
cv::Mat CReNet_OCRDlg::imageClean(cv::Mat rawImage)
{
	cv::Mat grayImage;
	cvtColor(rawImage, grayImage, CV_BGR2GRAY);
	int heightOfImage = grayImage.rows; //height of image
	int widthOfImage = grayImage.cols;  //width of image
	for (int i1 = 0; i1 < heightOfImage; i1++)
	{
		for (int j1 = 0; j1 < widthOfImage; j1++)
		{
			if (grayImage.at<uchar>(i1, j1)>200)
			{
				grayImage.at<uchar>(i1, j1) = 0;
			}
		}
	}
	for (int i2 = 0; i2 < heightOfImage; i2++)
	{
		for (int j2 = 0; j2 < widthOfImage; j2++)
		{
			if (grayImage.at<uchar>(i2, j2)>0)
			{
				grayImage.at<uchar>(i2, j2) = 255;
			}
		}
	}
	return grayImage;
}
/**�����ļ�����**/
std::vector<std::string> CReNet_OCRDlg::fileSearch(std::string path, std::string mode)
{
	struct _finddata_t filefind;
	if (path[path.size() - 1] == '\\')
	{
		path.resize(path.size() - 1);
	}
	std::string curr = path + "\\*.*";
	int done = 0, handle;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)
	{
		return fileName;
	}
	int i = 0;
	while (!(done = _findnext(handle, &filefind)))
	{
		if (!strcmp(filefind.name, ".."))
			continue;
		curr = path + "\\" + filefind.name;
		std::string filePathObject = path;
		if (strstr(filefind.name, mode.c_str()))
		{
			fileName.push_back(curr);
			filePath.push_back(filePathObject);
		}
		if (_A_SUBDIR == filefind.attrib)
			fileSearch(curr, mode);
	}
	_findclose(handle);
	return fileName;
}
/****�����ʽת��****/
std::string CReNet_OCRDlg::changecodeTowide(std::string contant)
{
	//�ı�����ʽ
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, contant.c_str(), -1, NULL, 0);
	wchar_t *pUnicode = new  wchar_t[unicodeLen];
	memset(pUnicode, 0, unicodeLen * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, contant.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring rt = pUnicode;

	std::string strLocale = setlocale(LC_ALL, "");
	const wchar_t* wchSrc = rt.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char *chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	std::string strResult = chDest;
	delete[]chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;
}

/***�ж�ͼƬ�Ƿ�Ϊ��Ҫ�����ͼ��***/
bool CReNet_OCRDlg::EnImageNeedProccess(const CString &CstrPath)
{
	BOOL enCheckImage = false;
	std::string strPath = CT2A(CstrPath);   //Cstringתstring
	std::string comtent = " ";
	cv::Mat rawImage = cv::imread(strPath, CV_LOAD_IMAGE_UNCHANGED); //strPathΪͼƬ��·��
	cv::Mat channelsImage = cv::imread(strPath);
	int widthOfImage = rawImage.cols;
	int heightOfImage = rawImage.rows;
	if (enCheckImage == false)
	{
		cv::Mat cleanedImage = imageClean(rawImage);//������ͼƬ���д���ȥ��ˮӡ
		cv::Mat out;
		cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2)); //��
		erode(cleanedImage, out, element);
		cv::Mat lineOne;
		//STRING text_out;

		//���ɿհ�ͼ�񱳾�
		cv::Mat proessImage(heightOfImage, widthOfImage, CV_8UC1);
		for (int i = 0; i < widthOfImage; i++)
		{
			for (int j = 0; j < heightOfImage; j++)
			{
				proessImage.at<uchar>(j, i) = rawImage.at<cv::Vec4b>(j, i)[3];
				//if ((rawImage.at<cv::Vec4b>(j, i)[2] == 229) && (rawImage.at<cv::Vec4b>(j, i)[0] == 229) && (rawImage.at<cv::Vec4b>(j, i)[1] == 229))
				if ((rawImage.at<cv::Vec4b>(j, i)[2]) > 150)
				{
					rawImage.at<cv::Vec4b>(j, i)[3] = 255;
					rawImage.at<cv::Vec4b>(j, i)[0] = 0;
					rawImage.at<cv::Vec4b>(j, i)[1] = 0;
					rawImage.at<cv::Vec4b>(j, i)[2] = 0;
					proessImage.at<uchar>(j, i) = 0;
				}
			}
		}
		/**�ַ��ָ�**/
		std::vector<cv::Mat> wordLine;
		std::vector<std::string> wordLineString;
		wordLine = wordSpiltLine(proessImage, out);
		std::string contentOfImage = " ";
		std::string tempString = " ";
		TessBaseAPI *handle;
		PIX *img;
		char *text=NULL;
		handle = TessBaseAPICreate();
		TessBaseAPIInit3(handle, NULL, "chi_sim");
		cv::Mat lineOut;
		for (int i = 0; i < wordLine.size(); i++)
		{
			lineOne = wordLine.at(i);
			lineOut = imageAddBlackGround(lineOne);
			imwrite("1.jpg", lineOut);
			img = pixRead("1.jpg");
			TessBaseAPISetImage2(handle, img);
			TessBaseAPIRecognize(handle, NULL);
			text = TessBaseAPIGetUTF8Text(handle);
			tempString = text;
			tempString = changecodeTowide(tempString);
			tempString = Trim(tempString); //ȥ���ո�/
			wordLineString.push_back(tempString);
			contentOfImage = tempString + contentOfImage;
		}
		TessDeleteText(text);
		TessBaseAPIEnd(handle);
		TessBaseAPIDelete(handle);
		pixDestroy(&img);

		contentOfImage = Trim(contentOfImage); //ȥ���ո�
		contentOfImage = changecodeTowide(contentOfImage);  //�����ʽת��
		dataText dataTextAuto;
		dataTextAuto.dataOfJson = wordLineString.at(0);
		CString CgetCompanyNumber(dataTextAuto.getCompanyNumber().c_str());
		if (CgetCompanyNumber.IsEmpty())
		{
			enCheckImage = true;
		}
	}
	return enCheckImage;
}

/*��ʼ���*/
void CReNet_OCRDlg::OnBnClickedOk()
{
	int radiStateLocalImage = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	int radiStateNetwortImage = ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck();
	int atuoFindFile = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	int handleFindFile = ((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();

	if (1 == radiStateLocalImage) //�ж��Ƿ�����б���ͼƬ��ʶ��
	{
		//�ֶ�����·��ʶ��
		if (saveExcelPath.IsEmpty()) 
		{
			CString newsErrorOfInputBox;
			newsErrorOfInputBox.Format(_T("����ѡ�����Ŀ¼��"));
			MessageBox(newsErrorOfInputBox, _T("OCR����ʶ��ϵͳ"), MB_OK);
		}
		else
		{
			if (1 == handleFindFile)
			{
				BOOL m_Radio1NetworkImage = TRUE;
				//��ָ���ļ��е�ͼƬ���ݱ���
				CString fdPath;
				CString strDataPath = strDir + "\\*.*";
				CString strTmp;
				USES_CONVERSION;
				//�����ʽΪconst char* []
				char *saveCsvFile = T2A(saveExcelPath);
				oFile.open(saveCsvFile, std::ios::out | std::ios::trunc);
				oFile << "��ҵ����" << "," << "��ҵע���" << std::endl;

				CFileFind find;//MFC���ļ�������
				BOOL enFindFileNumber = find.FindFile(strDataPath);
				while (enFindFileNumber)//ѭ�������ļ����µ��ļ�
				{
					enFindFileNumber = find.FindNextFile();
					if (!find.IsDots() && enFindFileNumber == 1)
					{
						fdPath = find.GetFilePath();
						strTmp = fdPath.Right(4);//CString�ܷ���
						strTmp.MakeLower();

						if (".png" == strTmp)//ָ����ʽ��׺
						{
							ProccessPic(fdPath);
						}
					}
				}
				oFile.close();  //�ر�����ļ�
				find.Close();
			}

			//�Զ�����·��ʶ��
			if (1 == atuoFindFile)
			{
				/***�Զ������ı�***/
				std::string fileNameAutoSearch;
				std::string filePathAutoSearch;
				fileName = fileSearch("D:\\", "1.png");
				std::cout << fileName.size() << std::endl;
				bool enCheckImage = true;
				for (size_t i = 0; i < 4; i++)
				{
					std::cout << fileName.at(i) << std::endl;
					std::cout << filePath.at(i) << std::endl;
					CString CfilePath(fileName.at(i).c_str());
					enCheckImage = EnImageNeedProccess(CfilePath);
					if (enCheckImage == false)
					{
						filePathAutoSearch = filePath.at(i);
						break;
					}
				}

				if (false == enCheckImage)
				{
					CString strAutoDir(filePathAutoSearch.c_str());
					CWnd::SetDlgItemText(IDC_EDIT1, strAutoDir); //��ʾ·��
					BOOL m_Radio1NetworkImage = TRUE;
					//��ָ���ļ��е�ͼƬ���ݱ���
					CString fdPath;
					CString strDataPath = strAutoDir + "\\*.*";
					CString strTmp;
					USES_CONVERSION;
					char *saveCsvFileAuto = T2A(saveExcelPath);
					oFile.open(saveCsvFileAuto, std::ios::out | std::ios::trunc);  //��Ҫ������ļ�
					oFile << "��ҵ����" << "," << "��ҵע���" << std::endl;
					CFileFind find;//MFC���ļ�������
					BOOL enFindFileNumber = find.FindFile(strDataPath);
					while (enFindFileNumber)//ѭ�������ļ����µ��ļ�
					{
						enFindFileNumber = find.FindNextFile();
						if (!find.IsDots() && enFindFileNumber == 1)
						{
							fdPath = find.GetFilePath();
							strTmp = fdPath.Right(4);//CString�ܷ���
							strTmp.MakeLower();
							if (".png" == strTmp)//ָ����ʽ��׺
							{
								ProccessPic(fdPath);
							}
						}
					}
					oFile.close();  //�ر�����ļ�
					find.Close();
				}
				if (true == enCheckImage)
				{
					CString newsErrorOfAutoImage;
					newsErrorOfAutoImage.Format(_T("û���ҵ�ͼƬ��"));
					MessageBox(newsErrorOfAutoImage, _T("OCR����ʶ��ϵͳ"), MB_OK);
				}
			}
		}

		if ((0 == handleFindFile) && (0 == atuoFindFile))
		{
			CString newsErrorOfCheckBox;
			newsErrorOfCheckBox.Format(_T("����ѡ�񱾵��ļ��������ͣ�"));
			MessageBox(newsErrorOfCheckBox, _T("OCR����ʶ��ϵͳ"), MB_OK);
		}
	}
	if (1 == radiStateNetwortImage)
	{
		CEdit* pBoxUrl;
		pBoxUrl = (CEdit*)GetDlgItem(IDC_EDIT3);
		CString urlBox;
		pBoxUrl->GetWindowText(urlBox);
		//����ͼƬ����url��ַ
		if (urlBox.IsEmpty())
		{
			CString newsErrorOfNetworkImageUrl;
			newsErrorOfNetworkImageUrl.Format(_T("Url��ַ����Ϊ�գ�"));
			MessageBox(newsErrorOfNetworkImageUrl, _T("OCR����ʶ��ϵͳ"), MB_OK);
		}
		else
		{
			//std::string url = "http://imglf3.nosdn.127.net/img/SjhqbjhCMTNNT2dGdnBUTmVSR0NVc2RqZVd6S0w4dVpObDh2VXdHMTJTZENvYmxyNHhZbUpRPT0.png?imageView&thumbnail=1680x0&quality=96&stripmeta=0";
			std::string url = CT2A(urlBox);
			std::string fileNetworkImage = "C:\\Users\\ly\\Desktop\\temp.png";
			size_t len = url.length();//��ȡ�ַ�������
			int nmlen = MultiByteToWideChar(CP_ACP, 0, url.c_str(), len + 1, NULL, 0);
			wchar_t* buffer = new wchar_t[nmlen];
			MultiByteToWideChar(CP_ACP, 0, url.c_str(), len + 1, buffer, nmlen);
			HRESULT hr = URLDownloadToFile(NULL, (LPCTSTR)buffer, _T("C:\\Users\\ly\\Desktop\\temp.png"), 0, NULL); //
			if (hr == S_OK)
			{
				CString imageLoaded;
				imageLoaded.Format(_T("�������"));
				MessageBox(imageLoaded, _T("OCR����ʶ��ϵͳ"), MB_OK);
				CString CfileNetworkImage(fileNetworkImage.c_str());
				ProccessPic(CfileNetworkImage); //����ͼ������ʶ�� �����ַΪCString
			}
			else
			{
				CString newsErrorOfNetworkImage;
				newsErrorOfNetworkImage.Format(_T("����ʧ�ܣ���������״����URL��ַ����"));
				MessageBox(newsErrorOfNetworkImage, _T("OCR����ʶ��ϵͳ"), MB_OK);
			}
		}
	}
	if ((0 == radiStateLocalImage) && (0 == radiStateNetwortImage))
	{
		CString newsError;
		newsError.Format(_T("��ѡ��ʶ��ģʽ"));
		MessageBox(newsError, _T("OCR����ʶ��ϵͳ"), MB_OK);
	}
}


void CReNet_OCRDlg::OnBnClickedButton1()
{
	CString strfilePath;
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"C:\\Users\\ly\\Desktop\\22";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  	
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_READONLY, NULL, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result == IDOK)
	{
		strfilePath = openFileDlg.GetPathName();
		strDir = strfilePath.Left(strfilePath.ReverseFind('\\'));
		CWnd::SetDlgItemText(IDC_EDIT1, strDir); //��ʾ·��
	}
}


void CReNet_OCRDlg::OnBnClickedRadio1()
{
	CString newsOfLocalImage;
	newsOfLocalImage.Format(_T("��ѡ��ͼƬ�ļ�·��"));
	MessageBox(newsOfLocalImage, _T("OCR����ʶ��ϵͳ"), MB_OK);
	BOOL m_Radio1NetworkImage = TRUE;
}


void CReNet_OCRDlg::OnBnClickedRadio2()
{
	CString newsOfNetworkImage;
	newsOfNetworkImage.Format(_T("��������Ҫʶ��ͼƬ��URL"));
	MessageBox(newsOfNetworkImage, _T("OCR����ʶ��ϵͳ"), MB_OK);
	BOOL m_RadioLocalImage = TRUE;
}


void CReNet_OCRDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CReNet_OCRDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isOpen = FALSE;        //�Ƿ��(����Ϊ����)  
	//CString defaultDir = L"C:\\Users\\ly\\Desktop\\scoresheet.csv";   //Ĭ�ϴ򿪵��ļ�·�� 
	
	CString opensavefile;
	CString csvPath = L"\\������Ϣ����.csv";
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL);
	INT_PTR result = openFileDlg.DoModal();

	if (result == IDOK) 
	{
		opensavefile = openFileDlg.GetPathName();
		savefilePath = opensavefile.Left(opensavefile.ReverseFind('\\'));
		saveExcelPath = savefilePath + csvPath;
	}
	
	CWnd::SetDlgItemText(IDC_EDIT2, saveExcelPath);
}

cv::Mat CReNet_OCRDlg::cleanImageOther(cv::Mat rawImage)
{
	cv::Mat grayImage;
	cvtColor(rawImage, grayImage, CV_BGR2GRAY);
	int heightOfImage = grayImage.rows; //height of image
	int widthOfImage = grayImage.cols;  //width of image
	for (int i1 = 0; i1 < heightOfImage; i1++)
	{
		for (int j1 = 0; j1 < widthOfImage; j1++)
		{
			if (grayImage.at<uchar>(i1, j1)>100)
			{
				grayImage.at<uchar>(i1, j1) = 0;
			}
		}
	}
	for (int i2 = 0; i2 < heightOfImage; i2++)
	{
		for (int j2 = 0; j2 < widthOfImage; j2++)
		{
			if (grayImage.at<uchar>(i2, j2)!=0)
			{
				grayImage.at<uchar>(i2, j2) = 255;
			}
		}
	}
	return grayImage;
}


void CReNet_OCRDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	cv::Mat image = cv::imread("C:\\Users\\ly\\Desktop\\22\\0.png");
	int widthImage = image.cols;
	int heigthImage = image.rows;
	cv::Mat grayImage;
	//cvtColor(image, grayImage, CV_BGR2GRAY);
	grayImage = cleanImageOther(image);
	cv::Mat clean = grayImage(cv::Range((int)heigthImage / 8, (int)heigthImage / 2), cv::Range((int)widthImage / 10, (int)widthImage / 2));
	cv::Mat cleanRawImage = image(cv::Range((int)heigthImage / 8, (int)heigthImage / 2), cv::Range((int)widthImage / 10, (int)widthImage / 2));
	imshow("fdfd", clean);
	cv::waitKey(100);
	std::vector<cv::Mat> word;
	word = wordSpiltLine(cleanRawImage, clean);
	std::cout << word.size() << std::endl;
	cv::Mat input;
	input = imageAddBlackGround(word.at(3));
	imwrite("r.png", input);
	TessBaseAPI *handle;
	PIX *img;
	char *text;
	handle = TessBaseAPICreate();
	TessBaseAPIInit3(handle, NULL, "chi_sim_1");
	img = pixRead("r.png");
	handle = TessBaseAPICreate();
	TessBaseAPIInit3(handle, NULL, "chi_sim_1");
	TessBaseAPISetImage2(handle, img);
	TessBaseAPIRecognize(handle, NULL);
	text = TessBaseAPIGetUTF8Text(handle);
	std::cout << text << std::endl;
	std::string s = text;
	std::cout << s << std::endl;
	s = changecodeTowide(s); 
	CString CgetCompanyNumber(s.c_str());
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit->ReplaceSel(CgetCompanyNumber + "\r\n");
	TessDeleteText(text);
	TessBaseAPIEnd(handle);
	TessBaseAPIDelete(handle);
	pixDestroy(&img);
	*/

	
	INT_PTR nRes;
	aboutV aboutDlg;
	nRes = aboutDlg.DoModal();
	if (IDCANCEL == nRes)
		return;
    
}


void CReNet_OCRDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nHelp;
    helpV helpDlg;
	nHelp = helpDlg.DoModal();
	if (IDCANCEL == nHelp)
		return;
}


void CReNet_OCRDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
