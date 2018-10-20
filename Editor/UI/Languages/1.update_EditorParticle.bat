 @echo off
echo Generating file list..
dir ..\..\..\Code\Sandbox\Plugins\EditorParticle\*.cpp /L /B /S > %TEMP%\listfile.txt
echo Generating .POT file...
xgettext -k_e -k__ --from-code utf-8  -o .\EditorParticle.pot -L C++ --no-wrap -D ..\..\..\Code\Sandbox\Plugins\EditorParticle -f %TEMP%\listfile.txt
echo Done.
del %TEMP%\listfile.txt