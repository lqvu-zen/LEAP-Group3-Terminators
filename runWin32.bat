@echo off

call config.bat

cocos run -s .\%PROJECT_NAME% -p win32 -m release

pause