using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	public class ConverterTestSupport<T, TIn, TOut>
		where T : Microsoft.UI.Xaml.Data.IValueConverter, new()
		where TIn : struct
		where TOut : struct
	{
		public T Converter { get; }

		protected ConverterTestSupport()
		{
			Converter = new T();
		}

		protected TOut? Convert(TIn? value, string? language = null)
			=> Converter.Convert(value, typeof(TOut), null, language) as TOut?;

		protected TOut? ConvertNull(string? language = null)
			=> Converter.Convert(null, typeof(TOut), null, language) as TOut?;

		protected TIn? ConvertBack(TOut? value, string? language = null)
			=> Converter.ConvertBack(value, typeof(TIn), null, language) as TIn?;

		protected TIn? ConvertBackUnsetValue(string? language = null)
			=> Converter.ConvertBack(DependencyProperty.UnsetValue, typeof(TIn), null, language) as TIn?;
	}
}
