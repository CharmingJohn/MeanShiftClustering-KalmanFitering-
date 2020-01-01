//Edited by github.com/charmingjohn


// Mean shift clusteringDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Mean shift clustering.h"
#include "Mean shift clusteringDlg.h"
#include "afxdialogex.h"

#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMeanshiftclusteringDlg ��ȭ ����
TCHAR imagefolder[MAX_PATH];
TCHAR imagefiles[20000][MAX_PATH];
int   imagecount = 0;
int   imageindex = 0;
int   show_images = 0;

void load_unicode_image(TCHAR *imgfn, Mat& img);

CMeanshiftclusteringDlg::CMeanshiftclusteringDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeanshiftclusteringDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeanshiftclusteringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_folder);
}

BEGIN_MESSAGE_MAP(CMeanshiftclusteringDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMeanshiftclusteringDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMeanshiftclusteringDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMeanshiftclusteringDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK3, &CMeanshiftclusteringDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK2, &CMeanshiftclusteringDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMeanshiftclusteringDlg �޽��� ó����

BOOL CMeanshiftclusteringDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTimer(1, 50, NULL);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMeanshiftclusteringDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMeanshiftclusteringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int _main(int argc, const char** argv);

Mat image_t;

void InitTrace();
void Track(Mat& image);
void proc_init(Mat& frame);

int tracker_type = 1; // ����Ʈ Ʈ��Ŀ 1

void CMeanshiftclusteringDlg::OnBnClickedOk()
{
	namedWindow("test", 0);
	tracker_type = 1; // ����Ʈ Ʈ��Ŀ 1

	if (imagecount > 0) {
//		InitTrace();
		load_unicode_image(imagefiles[0], image_t);
		proc_init(image_t);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		show_images = 1;
//	_main(1, NULL);
	}

	//CDialogEx::OnOK();
}

void proc_loop(Mat& frame);
void kalman_loop(Mat& frame);

void load_unicode_image(TCHAR *imgfn, Mat& img)
{
	char imgname[MAX_PATH];
	// opencv�� unicode�� �� �д´�. �׷��� ��ȯ�Ѵ�.
	WideCharToMultiByte(CP_ACP, 0, imagefiles[imageindex], lstrlen(imagefiles[imageindex]) + 1, imgname, MAX_PATH, NULL, NULL);
	img = imread(imgname);
}

void CMeanshiftclusteringDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (!show_images)
		return;

	load_unicode_image(imagefiles[imageindex], image_t);
/*	if (!image_t.empty()) {
		imshow("test", image_t);
	}*/
//	Track(image_t);
	if (tracker_type == 1) // mean shift loop
		proc_loop(image_t);
	else {
		kalman_loop(image_t);
	}

	imageindex++;
	if(imageindex >= imagecount)
		imageindex = 0;

	CDialogEx::OnTimer(nIDEvent);
}

// �ʱ� ���� �� '���'�� ������ ������ �ҷ���
int CALLBACK BICallBackFunc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		if (lpData)
			::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);      // lpData �� ���
		break;
	}
	return 0;
}
BOOL BrowseFolder(HWND hWnd, TCHAR *pszPathname, LPARAM lParam, DWORD flag)
{
	ITEMIDLIST*  pildBrowse;
	BROWSEINFO  bInfo;
	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.hwndOwner = hWnd;
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = pszPathname;
	bInfo.lpszTitle = _T("���丮�� �����ϼ���");             // dialog title
	bInfo.ulFlags = flag;                 // �������� �ɼ��� �����մϴ�.. msdn�� �����غ�����.
	bInfo.lpfn = BICallBackFunc;                        // �ɼ�? �Դϴ�.. �ʱ� ��� �������� �Ҷ��� ���⿡ �߰��ϼ���.
	bInfo.lParam = (LPARAM)(LPCTSTR)lParam;
	pildBrowse = ::SHBrowseForFolder(&bInfo);
	if (!pildBrowse)
		return FALSE;
	SHGetPathFromIDList(pildBrowse, pszPathname);
	return TRUE;
}

int ShowFolderDialog(HWND hWnd, TCHAR* buf)
{
	TCHAR   pszPathname[MAX_PATH];
	if (BrowseFolder(hWnd, pszPathname, (LPARAM)buf, BIF_RETURNONLYFSDIRS | BIF_VALIDATE)) {
		lstrcpy(buf, (LPCTSTR)pszPathname);                                // => ���� ������ ������ ��ü ��η� ���ɴϴ�.
		return TRUE;
	}
	return FALSE;
}

// ���� �̸��� 00�� �� �پ���ϱ� �� ����� ��������
void sort_image()
{
	for (int i = 0; i < imagecount - 1; i++) {
		for (int j = i + 1; j < imagecount; j++) {
			int ix0 = StrToInt(imagefiles[i]);
			int ix1 = StrToInt(imagefiles[j]);
			if(ix0 > ix1) {
				TCHAR ft[MAX_PATH];
				lstrcpy(ft, imagefiles[i]);
				lstrcpy(imagefiles[i], imagefiles[j]);
				lstrcpy(imagefiles[j], ft);
			}
		}
	}
}

void CMeanshiftclusteringDlg::OnBnClickedButton1()
{
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowFolderDialog(this->m_hWnd, imagefolder);
	SetDlgItemText(IDC_EDIT1, imagefolder);

	// ������ ������ �̹��� �̸��� ��� �����´�
	WIN32_FIND_DATA wfd;
	TCHAR srchfolder[MAX_PATH];
	lstrcpy(srchfolder, imagefolder);
	lstrcat(srchfolder, L"\\*.jpg");
	imagecount = 0;
	imageindex = 0;
	HANDLE hfind = FindFirstFile(srchfolder, &wfd);
	while (hfind != INVALID_HANDLE_VALUE) {
		lstrcat(imagefiles[imagecount], wfd.cFileName);
		imagecount++; // ���� ���� ����
		if (!FindNextFile(hfind, &wfd)) {
			FindClose(hfind);
			break;
		}
	}
	sort_image();
	// ���� ���̱�~ ^^
	TCHAR ft[MAX_PATH];
	for (int i = 0; i < imagecount; i++) {
		lstrcpy(ft, imagefolder);
		lstrcat(ft, L"\\");
		lstrcat(ft, imagefiles[i]);
		lstrcpy(imagefiles[i], ft);
	}

	if (imagecount == 0) {
		MessageBox(L"�̹��� ������ �����ϴ�");
	} else {
		TCHAR msg[256];
		wsprintf(msg, L"�̹��� ������ %d�� �Դϴ�", imagecount);
		MessageBox(msg);
	}

}


void CMeanshiftclusteringDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShowFolderDialog(this->m_hWnd, imagefolder);
	SetDlgItemText(IDC_EDIT2, imagefolder);

	// ������ ������ �̹��� �̸��� ��� �����´�
	WIN32_FIND_DATA wfd;
	TCHAR srchfolder[MAX_PATH];
	lstrcpy(srchfolder, imagefolder);
	lstrcat(srchfolder, L"\\*.jpg");
	imagecount = 0;
	imageindex = 0;
	HANDLE hfind = FindFirstFile(srchfolder, &wfd);
	while (hfind != INVALID_HANDLE_VALUE) {
		lstrcat(imagefiles[imagecount], wfd.cFileName);
		imagecount++; // ���� ���� ����
		if (!FindNextFile(hfind, &wfd)) {
			FindClose(hfind);
			break;
		}
	}
	sort_image();
	// ���� ���̱�~ ^^
	TCHAR ft[MAX_PATH];
	for (int i = 0; i < imagecount; i++) {
		lstrcpy(ft, imagefolder);
		lstrcat(ft, L"\\");
		lstrcat(ft, imagefiles[i]);
		lstrcpy(imagefiles[i], ft);
	}

	if (imagecount == 0) {
		MessageBox(L"�̹��� ������ �����ϴ�");
	}
	else {
		TCHAR msg[256];
		wsprintf(msg, L"�̹��� ������ %d�� �Դϴ�", imagecount);
		MessageBox(msg);
	}
}

void kalman_capture(TCHAR *folder);

void CMeanshiftclusteringDlg::OnBnClickedOk3()
{
	kalman_capture(imagefolder);
}

void kalman_init();
void kalman_loop(Mat& frame);

void CMeanshiftclusteringDlg::OnBnClickedOk2()
{
	if (imagecount > 0) {
		//		InitTrace();
		load_unicode_image(imagefiles[0], image_t);
		kalman_init();

		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		show_images = 1;
		//	_main(1, NULL);
		tracker_type = 2; // ����Ʈ Ʈ��Ŀ 1
	}
}
