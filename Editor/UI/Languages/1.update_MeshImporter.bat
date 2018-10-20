 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\MeshImporter\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\MeshImporter.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\MeshImporter -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt