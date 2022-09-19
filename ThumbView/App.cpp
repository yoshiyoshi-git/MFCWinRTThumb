#include "pch.h"
#include "App.h"
#include "App.g.cpp"

#include "MainControl.h"


using namespace winrt;
using namespace Windows::UI::Xaml;


using namespace ThumbView::implementation;

namespace winrt::ThumbView::implementation
{
    App::App()
    {
        Initialize();
        AddRef();
        m_inner.as<::IUnknown>()->Release();
    }
    App::~App()
    {
        Close();
    }

    void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e)
    {
        //呼び出すよ～～
        MainControl::AppendViewModelAsync();
    }
}