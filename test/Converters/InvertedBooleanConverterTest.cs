namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class InvertedBooleanConverterTest : ConverterTestSupport<InvertedBooleanConverter, bool, bool>
	{
		[TestMethod]
		public void ConvertNullptr()
		{
			var retValue = Convert(null);
			Assert.AreEqual(null, retValue);
		}

		[TestMethod]
		public void ConvertFalse()
		{
			var retValue = Convert(false);
			Assert.AreEqual(true, retValue);
		}

		[TestMethod]
		public void ConvertTrue()
		{
			var retValue = Convert(true);
			Assert.AreEqual(false, retValue);
		}

		[TestMethod]
		public void ConvertBackDependencyPropertyUnsetValue()
		{
			var retValue = ConvertBackUnsetValue();
			Assert.AreEqual(null, retValue);
		}

		[TestMethod]
		public void ConvertBackFalse()
		{
			var retValue = ConvertBack(false);
			Assert.AreEqual(true, retValue);
		}

		[TestMethod]
		public void ConvertBackTrue()
		{
			var retValue = ConvertBack(true);
			Assert.AreEqual(false, retValue);
		}
	}
}