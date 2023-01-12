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

		protected TOut? Convert(TIn? value)
			=> Converter.Convert(value, typeof(TOut), null, null) as TOut?;

		protected TOut? ConvertNull()
			=> Converter.Convert(null, typeof(TOut), null, null) as TOut?;

		protected TIn? ConvertBack(TOut? value)
			=> Converter.ConvertBack(value, typeof(TIn), null, null) as TIn?;

		protected TIn? ConvertBackUnsetValue()
			=> Converter.ConvertBack(DependencyProperty.UnsetValue, typeof(TIn), null, null) as TIn?;
	}
}
