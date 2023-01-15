using Microsoft.UI.Composition.SystemBackdrops;

namespace Mntone.AngelUmbrella.Composition.SystemBackdrops
{
	public static class DesktopAcrylicControllerExtensions
	{
		public static void SetColors(this DesktopAcrylicController controller, DesktopAcrylicTheme theme)
			=> DesktopAcrylicHelper.SetColors(controller, theme);

		public static void SetColors(this DesktopAcrylicController controller, SystemBackdropTheme theme)
			=> DesktopAcrylicHelper.SetColors(controller, theme);

		public static void SetColors(this DesktopAcrylicController controller, DesktopAcrylicTheme theme, DesktopAcrylicKind kind)
			=> DesktopAcrylicHelper.SetColors(controller, theme, kind);

		public static void SetColors(this DesktopAcrylicController controller, SystemBackdropTheme theme, DesktopAcrylicKind kind)
			=> DesktopAcrylicHelper.SetColors(controller, theme, kind);
	}
}
