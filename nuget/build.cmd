@echo off
set MSBUILD=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\msbuild
set SOLUTION_FILE=../AngelUmbrella.sln
set NATIVE_PROJECTS=AngelUmbrella
set PROJECTION_PROJECTS=AngelUmbrella_projection
set TARGET_PLATFORMS=x86 x64 ARM64
set TARGET_CONFIGURATION=Release
set CLEAN_AFTER_BUILD=true

goto MAIN

:ERROR
	echo "Error"
	exit /b %!%errorlevel%

:MAIN
	REM Build Native DLL
	for %%p in (%TARGET_PLATFORMS%) do (
		for %%f in (%NATIVE_PROJECTS%) do (
			echo +-------------------------------------------
			echo ^| Build %%f (native^)
			echo +-------------------------------------------
			"%MSBUILD%" "%SOLUTION_FILE%" -fl -flp:logfile=msbuild_native_%%p.log -m -t:"%%f":Clean;"%%f":Rebuild -p:Configuration=%TARGET_CONFIGURATION%;Platform=%%p
			if errorlevel 1 goto ERROR
			if "%CLEAN_AFTER_BUILD%" == "true" (
				if "%%p" == "x86" (
					rd /s /q "../obj/Win32-%TARGET_CONFIGURATION%/%%f"
				) else (
					rd /s /q "../obj/%%p-%TARGET_CONFIGURATION%/%%f"
				)
			)
		)
	)

	REM Build Projection DLL
	for %%f in (%PROJECTION_PROJECTS%) do (
		echo +-------------------------------------------
		echo ^| Build %%f (projection^)
		echo +-------------------------------------------
		"%MSBUILD%" "%SOLUTION_FILE%" -fl -flp:logfile=msbuild_projection.log -m -t:"%%f":Clean;"%%f":Rebuild -p:Configuration=%TARGET_CONFIGURATION%;Platform=x86
		if errorlevel 1 goto ERROR
		if "%CLEAN_AFTER_BUILD%" == "true" (
			rd /s /q "../obj/AnyCPU-%TARGET_CONFIGURATION%/%%f"
		)
	)

	REM Pack NuGet
	echo Pack NuGet package
	./pack.cmd
