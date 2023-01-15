using Microsoft.UI.Xaml.Automation.Peers;
using Microsoft.VisualStudio.TestTools.UnitTesting.AppContainer;
using Mntone.AngelUmbrella.Controls;

namespace Mntone.AngelUmbrella.Tests.Controls
{
	[TestClass]
	public sealed class SettingsCardAutomationPropertiesTest
	{
		private readonly Lazy<SettingsCard> _control = new Lazy<SettingsCard>(() =>
		{
			var card = new SettingsCard()
			{
				Description = nameof(SettingsCard.Description),
				Header = nameof(SettingsCard.Header),
			};
			return card;
		});

		private SettingsCard Control => _control.Value;

		[UITestMethod]
		public void Description()
		{
			var peer = FrameworkElementAutomationPeer.FromElement(Control);
			var propValue = peer.GetHelpText();
			Assert.AreEqual(nameof(SettingsCard.Description), propValue);
		}

		[UITestMethod]
		public void Header()
		{
			var peer = FrameworkElementAutomationPeer.FromElement(Control);
			var propValue = peer.GetName();
			Assert.AreEqual(nameof(SettingsCard.Header), propValue);
		}
	}
}
