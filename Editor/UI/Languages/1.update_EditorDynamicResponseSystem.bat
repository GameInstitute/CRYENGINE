 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\EditorDynamicResponseSystem\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\EditorDynamicResponseSystem.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\EditorDynamicResponseSystem -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt