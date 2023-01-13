using Microsoft.UI.Xaml.Controls;
using Microsoft.VisualStudio.TestTools.UnitTesting.AppContainer;
using Mntone.AngelUmbrella.UI.Controls;

namespace Mntone.AngelUmbrella.Tests.Controls
{
	[TestClass]
	public sealed class SettingsCardPropertiesTest
	{
		private readonly Lazy<SettingsCard> _control = new Lazy<SettingsCard>(() => new SettingsCard());

		private SettingsCard Control => _control.Value;

		[UITestMethod]
		public void ActionIconTooltip_DefaultIsNull()
		{
			var propValue = Control.ActionIconTooltip;
			Assert.AreEqual("More", propValue);
		}

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
		public void IsClickEnabled_DefaultIsNull()
		{
			var propValue = Control.IsClickEnabled;
			Assert.IsFalse(propValue);
		}

		[UITestMethod]
		public void Orientation_DefaultIsHorizontal()
		{
			var propValue = Control.Orientation;
			Assert.AreEqual(Orientation.Horizontal, propValue);
		}
	}
}
