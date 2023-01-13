using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class StringIsPresentToVisibilityConverterTest : StringConverterTestSupport<StringIsPresentToVisibilityConverter, Visibility>
	{
		[TestMethod]
		public void ConvertNullptr()
		{
			var retValue = Convert(null);
			Assert.AreEqual(Visibility.Collapsed, retValue);
		}

		[TestMethod]
		public void ConvertEmpty()
		{
			var retValue = Convert("");
			Assert.AreEqual(Visibility.Collapsed, retValue);
		}

		[TestMethod]
		public void ConvertPresent()
		{
			var retValue = Convert("string");
			Assert.AreEqual(Visibility.Visible, retValue);
		}

		[TestMethod]
		public void ConvertBackNotImplemented()
		{
			Assert.ThrowsException<NotImplementedException>(() => ConvertBackUnsetValue());
		}
	}
}