using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.VisualStudio.TestTools.UnitTesting.AppContainer;
using Windows.Graphics;
using WinRT.Interop;

namespace Mntone.AngelUmbrella.Test
{
	public sealed partial class App : Application
	{
		private Window? _window;

		public App()
		{
			InitializeComponent();
		}

		protected override void OnLaunched(LaunchActivatedEventArgs args)
		{
			Microsoft.VisualStudio.TestPlatform.TestExecutor.UnitTestClient.CreateDefaultUI();

			_window = new MainWindow();
			var hWnd = WindowNative.GetWindowHandle(_window);
			var windowId = Win32Interop.GetWindowIdFromWindow(hWnd);
			var appWindow = AppWindow.GetFromWindowId(windowId);
			appWindow.ResizeClient(new SizeInt32(1, 1));
			appWindow.Show();

			UITestMethodAttribute.DispatcherQueue = _window.DispatcherQueue;

			// Replace back with args.Arguments when https://github.com/microsoft/microsoft-ui-xaml/issues/3368 is fixed
			Microsoft.VisualStudio.TestPlatform.TestExecutor.UnitTestClient.Run(Environment.CommandLine);
		}
	}
}
