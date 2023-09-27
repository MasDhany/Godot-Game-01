@echo off

copy dev.vcxitems build.files.vcxitems /y

setlocal enableextensions disabledelayedexpansion

set "filename=build.files.vcxitems"

set "search="$(MSBuildThisFileDirectory)"
set "replace=""

for /f "delims=" %%i in ('type "%filename%" ^& break ^> "%filename%" ') do (
	set "line=%%i"

	setlocal enabledelayedexpansion

	if "!line:<ClInclude=!"=="!line!" (
	if "!line:</ClInclude>=!"=="!line!" (
	if "!line:<None=!"=="!line!" (
	if "!line:</None>=!"=="!line!" (
	if "!line:<ItemsProjectGuid>=!"=="!line!" (
	if "!line:UniqueIdentifier>=!"=="!line!" (
		>>"%filename%" echo(!line:%search%=%replace%!
	))))))
		
	endlocal
)

endlocal