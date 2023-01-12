using Microsoft.UI.Xaml;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Mntone.AngelUmbrella.Test
{
	public sealed partial class App : Application
	{
		//private Window? _window;

		public App()
		{
			InitializeComponent();
		}

		protected override void OnLaunched(LaunchActivatedEventArgs args)
		{
			Microsoft.VisualStudio.TestPlatform.TestExecutor.UnitTestClient.CreateDefaultUI();

			//_window = new MainWindow();
			//_window.Activate();

			//UITestMethodAttribute.DispatcherQueue = _window.DispatcherQueue;

			// Replace back with args.Arguments when https://github.com/microsoft/microsoft-ui-xaml/issues/3368 is fixed
			Microsoft.VisualStudio.TestPlatform.TestExecutor.UnitTestClient.Run(Environment.CommandLine);
		}
	}
}
