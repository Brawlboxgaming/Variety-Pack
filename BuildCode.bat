@echo off
SETLOCAL EnableDelayedExpansion

cls

:: Destination (change as necessary)
SET "SOURCE=VP"

:: CPP compilation settings
SET CC="../Common/cw/mwcceppc.exe"
SET CFLAGS=-I- -i "../Common/engine" -i "../Common/source" -i "../Common/source/game" -i "../Common/source/core" -i "../Common/Pulsar" -i "../Common" -i code -O2,p^
  -opt loop,peep,schedule  -inline auto -enum int -proc 750 -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1 -func_align 4 -rtti off 
SET DEFINE=

:: CPP Sources
SET CPPFILES=
for /R "../Common/Pulsar" %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"
for /R code %%f in (*.cpp) do SET "CPPFILES=%%f !CPPFILES!"

:: Compile CPP
%CC% %CFLAGS% -c -o "build/kamek.o" "..\Common\engine\kamek.cpp"

SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    ::echo "Compiling %%H..."
    %CC% %CFLAGS% %DEFINE% -c -o "build/%%~nH.o" "%%H"
    SET "OBJECTS=build/%%~nH.o !OBJECTS!"
)

:: Link
echo Linking... %time%
"../Common/KamekSource/bin/Debug/Kamek" "build/kamek.o" %OBJECTS% -dynamic -externals="../Common/source/symbols.txt" -versions="../Common/source/versions.txt" -output-kamek=build\$KV$.bin >nul

del build\*.o

echo Copying Files...
xcopy /y build\* "C:\Users\James\AppData\Roaming\Dolphin Emulator\Load\Riivolution\vpv3\Binaries"

:end
ENDLOCAL