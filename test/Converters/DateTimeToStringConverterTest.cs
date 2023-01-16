namespace Mntone.AngelUmbrella.Tests.Converters
{
	[TestClass]
	public sealed class DateTimeToStringConverterTest : StringOutputConverterTestSupport<DateTimeToStringConverter, DateTimeOffset>
	{
		private const string DEFAULT_FORMAT = "longdate longtime";

		[TestMethod]
		public void ConvertDefault()
		{
			var datetime = new DateTimeOffset(2023, 1, 2, 3, 4, 5, TimeSpan.Zero);
			var retValue = Convert(datetime);
			Assert.AreEqual("Monday, January 2, 2023 3:04:05 AM", retValue.Replace("\u200E", ""));
		}

		[TestMethod]
		public void ConvertFormat()
		{
			try
			{
				Converter.Format = "shortdate longtime";

				var datetime = new DateTimeOffset(2023, 1, 2, 3, 4, 5, TimeSpan.Zero);
				var retValue = Convert(datetime);
				Assert.AreEqual("1/2/2023 3:04:05 AM", retValue.Replace("\u200E", ""));
			}
			finally
			{
				Converter.Format = DEFAULT_FORMAT;
			}
		}

		[TestMethod]
		public void ConvertJapanese()
		{
			var datetime = new DateTimeOffset(2023, 1, 2, 3, 4, 5, TimeSpan.Zero);
			var retValue = Convert(datetime, language: "ja-JP");
			Assert.AreEqual("2023年1月2日 3:04:05", retValue.Replace("\u200E", ""));
		}
	}
}
