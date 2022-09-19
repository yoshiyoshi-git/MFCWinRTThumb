#include "pch.h"
#include "MainControl.h"
#if __has_include("MainControl.g.cpp")
#include "MainControl.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Storage.Search.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::ThumbView::implementation
{
    //staticなので初期化を追加
    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> MainControl::thumbViewModelVec{ nullptr };

    MainControl::MainControl()
    {
        thumbViewModelVec = winrt::single_threaded_observable_vector<IInspectable>();
        InitializeComponent();

    }

    Windows::Foundation::IAsyncAction MainControl::AppendViewModelAsync()
    {
        //サーチするのは「jpg」「png」「gif」
        Windows::Storage::Search::QueryOptions searchoptions{};

        searchoptions.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);

        searchoptions.FileTypeFilter().Append(L".jpg");
        searchoptions.FileTypeFilter().Append(L".png");
        searchoptions.FileTypeFilter().Append(L".gif");

        //ピクチャーフォルダをサーチ
        Windows::Storage::StorageFolder picturesfolder = Windows::Storage::KnownFolders::PicturesLibrary();

        //上記の条件に合うのを探す
        auto searchresult = picturesfolder.CreateFileQueryWithOptions(searchoptions);
        auto imagefiles = co_await searchresult.GetFilesAsync();

        if (thumbViewModelVec.Size() != 0)
            co_return;

        //StorageFileからサムネイル画像とファイル名を取得して、ThumbViewModelを作成し、ThumbViewModelVecへAppend（追加）
        for (auto&& file : imagefiles)
        {
            if (file.Provider().Id() == L"computer")
            {
                auto thumbimage = co_await GetThumbnailAsync(file);
                auto thumbview = winrt::make<thumbViewModel>(file, thumbimage, file.DisplayName());
                thumbViewModelVec.Append(thumbview);
            }
        }
    }

    Windows::Foundation::IAsyncOperation<Windows::UI::Xaml::Media::Imaging::BitmapImage> MainControl::GetThumbnailAsync(Windows::Storage::StorageFile imagefile)
    {
        auto thumbnail = co_await imagefile.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
        Windows::UI::Xaml::Media::Imaging::BitmapImage thumbnailimage{};
        thumbnailimage.SetSource(thumbnail);
        thumbnail.Close();

        co_return thumbnailimage;
    }

}
