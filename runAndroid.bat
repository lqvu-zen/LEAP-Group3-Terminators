@echo off

call config.bat

cocos run -s .\%PROJECT_NAME% -p android -m release --ap android-28 --app-abi armeabi-v7a:x86

pause
