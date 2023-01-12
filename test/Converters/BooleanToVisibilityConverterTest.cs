using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class BooleanToVisibilityConverterTest : ConverterTestSupport<BooleanToVisibilityConverter, bool, Visibility>
	{
		[TestMethod]
		public void ConvertNullptr()
		{
			var retValue = Convert(null);
			Assert.AreEqual(retValue, null);
		}

		[TestMethod]
		public void ConvertFalse()
		{
			var retValue = Convert(false);
			Assert.AreEqual(Visibility.Collapsed, retValue);
		}

		[TestMethod]
		public void ConvertTrue()
		{
			var retValue = Convert(true);
			Assert.AreEqual(Visibility.Visible, retValue);
		}

		[TestMethod]
		public void ConvertBackDependencyPropertyUnsetValue()
		{
			var retValue = ConvertBackUnsetValue();
			Assert.AreEqual(null, retValue);
		}

		[TestMethod]
		public void ConvertBackCollapsed()
		{
			var retValue = ConvertBack(Visibility.Collapsed);
			Assert.AreEqual(false, retValue);
		}

		[TestMethod]
		public void ConvertBackVisible()
		{
			var retValue = ConvertBack(Visibility.Visible);
			Assert.AreEqual(true, retValue);
		}
	}
}
