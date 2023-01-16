using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	public class StringInputConverterTestSupport<T, TOut>
		where T : Microsoft.UI.Xaml.Data.IValueConverter, new()
		where TOut : struct
	{
		public T Converter { get; }

		protected StringInputConverterTestSupport()
		{
			Converter = new T();
		}

		protected TOut? Convert(string? value, string? language = null)
			=> Converter.Convert(value, typeof(TOut), null, language) as TOut?;

		protected TOut? ConvertNull(string? language = null)
			=> Converter.Convert(null, typeof(TOut), null, language) as TOut?;

		protected string? ConvertBack(TOut? value, string? language = null)
			=> Converter.ConvertBack(value, typeof(string), null, language) as string;

		protected string? ConvertBackUnsetValue(string? language = null)
			=> Converter.ConvertBack(DependencyProperty.UnsetValue, typeof(string), null, language) as string;
	}
}
