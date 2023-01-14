using Microsoft.UI.Xaml.Controls;
using Microsoft.VisualStudio.TestTools.UnitTesting.AppContainer;
using Mntone.AngelUmbrella.Controls;

namespace Mntone.AngelUmbrella.Tests.Controls
{
	[TestClass]
	public sealed class SettingsPanelPropertiesTest
	{
		private readonly Lazy<SettingsPanel> _control = new Lazy<SettingsPanel>(() => new SettingsPanel());

		private SettingsPanel Control => _control.Value;

		[UITestMethod]
		public void Description_DefaultIsNull()
		{
			var propValue = Control.Description;
			Assert.IsNull(propValue);
		}

		[UITestMethod]
		public void HeaderIcon_DefaultIsNull()
		{
			var propValue = Control.HeaderIcon;
			Assert.IsNull(propValue);
		}

		[UITestMethod]
		public void Header_DefaultIsNull()
		{
			var propValue = Control.Header as string;
			Assert.AreEqual(null, propValue);
		}

		[UITestMethod]
		public void Orientation_DefaultIsHorizontal()
		{
			var propValue = Control.Orientation;
			Assert.AreEqual(Orientation.Horizontal, propValue);
		}
	}
}
