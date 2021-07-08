@echo off

call config.bat

cocos new %PROJECT_NAME% -p com.leap2021.%PROJECT_NAME% -l cpp -d .

pause