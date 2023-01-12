using System.Numerics;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class SingleToVector3AsZConverterTest : ConverterTestSupport<SingleToVector3AsZConverter, float, Vector3>
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
			Assert.AreEqual(new Vector3(0, 0, value), retValue);
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
			var retValue = ConvertBack(new Vector3(0, 0, value));
			Assert.AreEqual(value, retValue);
		}
	}
}
