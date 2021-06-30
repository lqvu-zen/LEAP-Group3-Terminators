@echo off

set "dir=D:\GameLoft\Project\LEAP-Group3-Terminators\ForgottenMemoriae\Resources\sprites\Warrior"
set "pfx=Warrior-"

setlocal enabledelayedexpansion
for /r "%dir%" %%A in (*.png) do (
    set "txt=%%~nA"
    if not "!txt:~0,13!"=="%pfx%" ren "%%A" "%pfx%%%~nxA"
)

pause