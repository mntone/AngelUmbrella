using System.Numerics;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class SingleToVector3AsXConverterTest : ConverterTestSupport<SingleToVector3AsXConverter, float, Vector3>
	{
		[TestMethod]
		public void ConvertNullptr()
		{
			var retValue = Convert(null);
			Assert.AreEqual(retValue, null);
		}

		[DataTestMethod]
		[DataRow(float.NegativeZero)]
		[DataRow(0)]
		[DataRow(1)]
		[DataRow(float.NaN)]
		[DataRow(float.MinValue)]
		[DataRow(float.MaxValue)]
		[DataRow(float.PositiveInfinity)]
		[DataRow(float.NegativeInfinity)]
		public void ConvertValue(float value)
		{
			var retValue = Convert(value);
			Assert.AreEqual(new Vector3(value, 0, 0), retValue);
		}

		[TestMethod]
		public void ConvertBackDependencyPropertyUnsetValue()
		{
			var retValue = ConvertBackUnsetValue();
			Assert.AreEqual(null, retValue);
		}

		[DataTestMethod]
		[DataRow(float.NegativeZero)]
		[DataRow(0)]
		[DataRow(1)]
		[DataRow(float.NaN)]
		[DataRow(float.MinValue)]
		[DataRow(float.MaxValue)]
		[DataRow(float.PositiveInfinity)]
		[DataRow(float.NegativeInfinity)]
		public void ConvertValueBack(float value)
		{
			var retValue = ConvertBack(new Vector3(value, 0, 0));
			Assert.AreEqual(value, retValue);
		}
	}
}
