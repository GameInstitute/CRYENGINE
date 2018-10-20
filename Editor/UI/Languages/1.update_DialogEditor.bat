 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\DialogEditor\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\DialogEditor.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\DialogEditor -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt