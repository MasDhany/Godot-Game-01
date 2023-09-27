:: Usage: call update_output <extension>

cd $(TargetDir)

set lib_ext=%1%
set lib_name=

set lib_current=%lib_name%%lib_ext%
set lib_old=%lib_name%_old%lib_ext%

if exist "%lib_old%" (
	erase "%lib_old%"
)

if not exist "%lib_old%" (
	if exist "%lib_current%" (
		rename "%lib_current%" "%lib_old%"
		rename "%lib_old%" "%lib_current%"
	)
)