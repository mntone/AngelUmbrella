using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	public class StringOutputConverterTestSupport<T, TIn>
		where T : Microsoft.UI.Xaml.Data.IValueConverter, new()
		where TIn : struct
	{
		public T Converter { get; }

		protected StringOutputConverterTestSupport()
		{
			Converter = new T();
		}

		protected string? Convert(TIn? value, string? language = null)
			=> Converter.Convert(value, typeof(string), null, language) as string;

		protected string? ConvertNull(string? language = null)
			=> Converter.Convert(null, typeof(string), null, language) as string;

		protected TIn? ConvertBack(string value, string? language = null)
			=> Converter.ConvertBack(value, typeof(TIn), null, language) as TIn?;

		protected TIn? ConvertBackUnsetValue(string? language = null)
			=> Converter.ConvertBack(DependencyProperty.UnsetValue, typeof(TIn), null, language) as TIn?;
	}
}
