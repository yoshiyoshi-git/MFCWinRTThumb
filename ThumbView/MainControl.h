#pragma once

#include "MainControl.g.h"

#include "thumbViewModel.h"

namespace winrt::ThumbView::implementation
{
    struct MainControl : MainControlT<MainControl>
    {
        MainControl();

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ThumbViewModelVec() const
        {
            return thumbViewModelVec;
        }

        //ここで、StorageFile、サムネイル画像、ファイル名を集めるよ static
        static Windows::Foundation::IAsyncAction AppendViewModelAsync();

        //サムネイル画像を取得するよ static
        static Windows::Foundation::IAsyncOperation<Windows::UI::Xaml::Media::Imaging::BitmapImage> GetThumbnailAsync(Windows::Storage::StorageFile m_imageFile);


    private:
        //サムネイル等の保存用だよ static
        static  Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> thumbViewModelVec;
    };

    
}

namespace winrt::ThumbView::factory_implementation
{
    struct MainControl : MainControlT<MainControl, implementation::MainControl>
    {
    };
}
