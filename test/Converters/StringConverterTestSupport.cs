using Microsoft.UI.Xaml;

namespace Mntone.AngelUmbrella.Tests.Converters
{
	public class StringConverterTestSupport<T, TOut>
		where T : Microsoft.UI.Xaml.Data.IValueConverter, new()
		where TOut : struct
	{
		public T Converter { get; }

		protected StringConverterTestSupport()
		{
			Converter = new T();
		}

		protected TOut? Convert(string? value)
			=> Converter.Convert(value, typeof(TOut), null, null) as TOut?;

		protected TOut? ConvertNull()
			=> Converter.Convert(null, typeof(TOut), null, null) as TOut?;

		protected string? ConvertBack(TOut? value)
			=> Converter.ConvertBack(value, typeof(string), null, null) as string;

		protected string? ConvertBackUnsetValue()
			=> Converter.ConvertBack(DependencyProperty.UnsetValue, typeof(string), null, null) as string;
	}
}
