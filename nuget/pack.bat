@echo off
REM Thanks to https://stackoverflow.com/a/25850626
setlocal enableextensions disabledelayedexpansion

set "major="
for /f "tokens=3 delims=<>" %%a in (
	'find /i "<AngelVersionMajor>" ^< "../src/version.props"'
) do set "major=%%a"

set "minor="
for /f "tokens=3 delims=<>" %%a in (
	'find /i "<AngelVersionMinor>" ^< "../src/version.props"'
) do set "minor=%%a"

set "patch="
for /f "tokens=3 delims=<>" %%a in (
	'find /i "<AngelVersionPatch>" ^< "../src/version.props"'
) do set "patch=%%a"

set version=%major%.%minor%.%patch%

echo Detect Angel Umbrella version: %version%
nuget pack Mntone.AngelUmbrella.nuspec -Version %version% -OutputDirectory "../BuildNugetPackages/"
