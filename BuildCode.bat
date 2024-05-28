
SETLOCAL EnableDelayedExpansion
@echo off
cls
del build\*.o

SET "debug="
SET "cwDWARF="
if "%1" equ "-d" SET "debug=-debug -map=^"%APPDATA%\Dolphin Emulator\Maps\RMCP01.map^" -readelf=^"C:\MinGW\bin\readelf.exe^""
if "%1" equ "-d" SET "cwDWARF=-g"


:: Destination (change as necessary)
SET "SOURCE=VP"
SET "RIIVO=C:\Users\James\AppData\Roaming\Dolphin Emulator\Load\Riivolution\vpv3"
SET "ENGINE=C:\Users\James\Wii\MKW\Kamek\Common\KamekInclude"
echo %RIIVO%


:: CPP compilation settings
SET CC="../Common/cw/mwcceppc.exe"
SET CFLAGS=-I- -i "../Common/KamekInclude" -i "../Common/GameSource" -i "../Common/GameSource/MarioKartWii" -i "../Common/GameSource/core" -i "../Common/PulsarEngine" -i "../Common" -i "code" ^
  -opt all -inline auto -enum int -proc gekko -fp hard -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 %cwDWARF%
SET DEFINE=

:: CPP Sources
SET CPPFILES=
for /R "../Common/PulsarEngine" %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"
for /R code %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"

:: Compile CPP
%CC% %CFLAGS% -c -o "build/kamek.o" "%ENGINE%\kamek.cpp"

SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
    SET "OBJECTS=build/%%~nH.o !OBJECTS!"
)

:: Link
echo Linking... %time%
"../Common/KamekLinker/Kamek" "build/kamek.o" %OBJECTS% %debug% -dynamic -externals="../Common/GameSource/symbols.txt" -versions="../Common/GameSource/versions.txt" -output-combined=build\Code.pul

if %ErrorLevel% equ 0 (
    xcopy /Y build\*.pul "%RIIVO%\Binaries" >nul
    del build\*.o
    echo Binaries copied
)

:end
ENDLOCAL