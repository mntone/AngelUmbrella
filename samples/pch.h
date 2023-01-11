#pragma once

// Unused definition
// windef.h
// - minwindef.h
#define NOMINMAX

// winbase.h
// - interlockedapi.h
#define NOWINBASEINTERLOCK

// wingdi.h
#define NORASTEROPS
#define NOMETAFILE
#define NOTEXTMETRIC
#define NOGDICAPMASKS

// WinUser.h
#define NOAPISET
#define NORESOURCE
#define NOSCROLL
#define NOSHOWWINDOW
#define NOVIRTUALKEYCODES
#define NOWH
#define NODESKTOP
#define NOWINDOWSTATION
#define NOSECURITY
#define NOWINSTYLES
#define NOCLIPBOARD
#define NODEFERWINDOWPOS
#define NOSYSMETRICS
#define NOMENUS
#define NODRAWTEXT
#define NOMB
#define NOCOLOR
#define NOICONS
#define NOMDI
#define NOHELP
#define NOSYSPARAMSINFO
#define NOWINABLE
#define NO_STATE_FLAGS

// WinNls.h
#define NONLS

#include <windows.h>
#include <Unknwn.h>
#include <winrt/base.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

#include <winrt/Microsoft.UI.Input.h>

#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>

#include <winrt/Mntone.AngelUmbrella.UI.Controls.h>
