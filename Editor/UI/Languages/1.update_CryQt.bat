 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Libs\CryQt\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\CryQt.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Libs\CryQt -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt