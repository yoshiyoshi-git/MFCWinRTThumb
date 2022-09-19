
// MFCWinRTThumbView.h : CMFCWinRTThumbView クラスのインターフェイス
//

#pragma once


class CMFCWinRTThumbView : public CView
{
	//ここにWinRT関連のメンバを追加
	winrt::ThumbView::App hostApp{ nullptr };
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource _desktopWindowXamlSource{ nullptr };
	winrt::ThumbView::MainControl _mainControl{ nullptr };
	winrt::impl::com_ref<IDesktopWindowXamlSourceNative> interop;

protected: // シリアル化からのみ作成します。
	CMFCWinRTThumbView() noexcept;
	DECLARE_DYNCREATE(CMFCWinRTThumbView)

// 属性
public:
	CMFCWinRTThumbDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CMFCWinRTThumbView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // MFCWinRTThumbView.cpp のデバッグ バージョン
inline CMFCWinRTThumbDoc* CMFCWinRTThumbView::GetDocument() const
   { return reinterpret_cast<CMFCWinRTThumbDoc*>(m_pDocument); }
#endif

