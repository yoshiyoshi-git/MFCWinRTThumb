
// MFCWinRTThumbView.cpp : CMFCWinRTThumbView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MFCWinRTThumb.h"
#endif

#include "MFCWinRTThumbDoc.h"
#include "MFCWinRTThumbView.h"

#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWinRTThumbView

IMPLEMENT_DYNCREATE(CMFCWinRTThumbView, CView)

BEGIN_MESSAGE_MAP(CMFCWinRTThumbView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCWinRTThumbView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCWinRTThumbView コンストラクション/デストラクション

CMFCWinRTThumbView::CMFCWinRTThumbView() noexcept
{
	// TODO: 構築コードをここに追加します。
}

CMFCWinRTThumbView::~CMFCWinRTThumbView()
{
}

BOOL CMFCWinRTThumbView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。


	return CView::PreCreateWindow(cs);
}

// CMFCWinRTThumbView 描画

void CMFCWinRTThumbView::OnDraw(CDC* /*pDC*/)
{
	CMFCWinRTThumbDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。	

	HWND hWndXamlIsland = nullptr;
	interop->get_WindowHandle(&hWndXamlIsland);
	RECT windowRect;
	::GetWindowRect(this->m_hWnd, &windowRect);
	::SetWindowPos(hWndXamlIsland, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);

	_desktopWindowXamlSource.Content(_mainControl);		
}


// CMFCWinRTThumbView の印刷


void CMFCWinRTThumbView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCWinRTThumbView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMFCWinRTThumbView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMFCWinRTThumbView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CMFCWinRTThumbView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCWinRTThumbView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCWinRTThumbView の診断

#ifdef _DEBUG
void CMFCWinRTThumbView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCWinRTThumbView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCWinRTThumbDoc* CMFCWinRTThumbView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWinRTThumbDoc)));
	return (CMFCWinRTThumbDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCWinRTThumbView メッセージ ハンドラー


int CMFCWinRTThumbView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。

	//ここでWinRTの初期化～ウインドウのアタッチまで
	winrt::init_apartment(winrt::apartment_type::single_threaded);
	hostApp = winrt::ThumbView::App{};
	_desktopWindowXamlSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{};		

	if (_desktopWindowXamlSource != nullptr)
	{
		interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
		check_hresult(interop->AttachToWindow(this->m_hWnd));
		_mainControl = winrt::ThumbView::MainControl();
		
	}	
	
	return 0;
}
