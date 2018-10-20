 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\PerforcePlugin\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\PerforcePlugin.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\PerforcePlugin -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt