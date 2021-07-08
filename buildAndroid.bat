@echo off

call config.bat

cocos compile -s .\%PROJECT_NAME% -p android -m release -o .\%PROJECT_NAME%\bin --ap android-28 --app-abi armeabi-v7a:x86 --no-sign

pause