 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\EditorAudioControlsEditor\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\EditorAudioControlsEditor.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\EditorAudioControlsEditor -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt