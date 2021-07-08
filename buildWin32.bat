@echo off

call config.bat

if NOT EXIST .\%PROJECT_NAME%\win32-build\ (
	mkdir .\%PROJECT_NAME%\win32-build

	pushd .\%PROJECT_NAME%\win32-build
		cmake .. -G "Visual Studio 15 2017" -AWin32
	popd
)

cocos compile -s .\%PROJECT_NAME% -p win32 -m release -o .\%PROJECT_NAME%\bin --vs 2017

pause