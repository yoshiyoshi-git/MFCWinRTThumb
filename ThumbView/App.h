#pragma once
#include "App.g.h"
#include "App.base.h"

namespace winrt::ThumbView::implementation
{
    class App : public AppT2<App>
    {
    public:
        App();
        ~App();

        //ここ追加
        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
    };
}
namespace winrt::ThumbView::factory_implementation
{
    class App : public AppT<App, implementation::App>
    {
    };
}