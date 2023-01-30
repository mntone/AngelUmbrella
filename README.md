# Angel Umbrella - Mntone WinUI 3 Library

"Angel Umbrella" is small WinUI 3 Library for C++/WinRT.

https://user-images.githubusercontent.com/901816/211709015-77fee141-17b7-45e6-a96a-4a98e6a9d14b.mp4

## Classes

- *Mntone.AngelUmbrella.Composition.SystemBackdrops*
  - **DesktopAcrylicHelper** (C++) / **DesktopAcrylicControllerExtensions** (C#) - Provide to set acrylic colors (Choose assets from `Theme` and `Kind`).
- *Mntone.AngelUmbrella.Converters*
  - **BooleanToVisibilityConverter** - Convert from *bool* to *Microsoft.UI.Xaml.Visibility* (TwoWay).
  - **DateTimeToStringConverter** - Convert from *DateTime* (C++) / *DateTimeOffset* (C#) to *hstring* (OneWay).
  - **InvertedBooleanConverterTest** - Convert from *bool* to inverted *bool* (TwoWay).
  - **StringIsPresentToVisibilityConverter** - Convert from *hstring* to *Microsoft.UI.Xaml.Visibility* (OneWay only).
- *Mntone.AngelUmbrella.Controls*
  - **OddEvenStyleSelector** - Provide to choose the odd/even style.
  - **SettingsCard** - Provide basic settings card.
  - **SettingsExpander** - Provide settings card with expander.
  - **SettingsPanel** - Provide settings layout in items control, such as `ListView` or `GridView`, with the style `CardListViewItemStyle`.
  - **SizeSpecifiedWrapPanelPage** - Provide flow layout panel with item size.
  - **WrapPanel** - Provide flow layout panel.
- *Mntone.AngelUmbrella.Navigation*
  - **NavigationProperties** - Provide xaml-friendly navigation data.
- *Mntone.AngelUmbrella.Triggers*
  - **ControlSizeTrigger** - Provide control size based trigger.
  - **ControlWidthTrigger** - Provide control <u>width</u> based trigger. This is triggered by width only.

## Requirements

Angel Umbrella have the following system requirements:

- Windows App SDK Version 1.2 or later

## Usages

1. Install the package from the NuGet:<br>
   https://www.nuget.org/packages/Mntone.AngelUmbrella
2. Set `Generic.xaml` as your Application resources in App.xaml:
   ```xml
   <Application>
     <Application.Resources>
       <!-- WinUI 3 -->
       <XamlControlsResources xmlns="using:Microsoft.UI.Xaml.Controls" />
       <ResourceDictionary Source="/Mntone.AngelUmbrella/Themes/Generic.xaml" />
     </Application.Resources>
   </Application>
   ```
3. *(C++/WinRT)* Include `winrt/Mntone.AngelUmbrella.UI.Controls.h` in App.xaml.h or pch.h.
   ```c
   // Sample code for pch.h
   #pragma once

   #include <iterator>
   #include <vector>
   // Other header files of C++ STL

   #define WIN32_LEAN_AND_MEAN
   #define WINRT_LEAN_AND_MEAN
   #define NOMINMAX
   #include <windows.h>

   #include <unknwn.h>
   #include <inspectable.h>
   #include <restrictederrorinfo.h>
   #include <hstring.h>

   #include <winrt/base.h>
   #include <winrt/Windows.Foundation.h>
   #include <winrt/Windows.Foundation.Collections.h>
   // Other header files in namespace Windows

   #include <winrt/Microsoft.UI.Xaml.h>
   #include <winrt/Microsoft.UI.Xaml.Controls.h>
   // Other header files in namespace Microsoft

   #include <winrt/Mntone.AngelUmbrella.Controls.h> // <- HERE!
   ```

## Development

It runs on Windows 10 version 1809 or later.

You'll need the following software:

- Visual Studio 2022 Version 17.4 or later (no test in earlier version)
  - Desktop development with C++
  - .NET SDK (Use the build for DesktopBridge app; this option includes .NET 6 & 7 Runtime)
- Windows 10 SDK, version 1809 (10.0.17763.0)<br>
  https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/

1. Clone the repository:

   ```sh
   git clone https://github.com/mntone/AngelUmbrella.git
   ```
2. Open the `AngelUmbrella.sln` file.

## Authors

- mntone - Initial work.

## License

Angel Umbrella is licensed under the GPLv3 license - see the [LICENSE.txt](https://github.com/mntone/AngelUmbrella/blob/master/LICENSE.txt) file for details.
