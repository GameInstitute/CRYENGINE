@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)

%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\EditorQt                             -ts .\zh_cn\editor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\CryDesigner                  -ts .\zh_cn\CryDesigner.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\DependencyGraph              -ts .\zh_cn\DependencyGraph.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\DialogEditor                 -ts .\zh_cn\DialogEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorAnimation              -ts .\zh_cn\EditorAnimation.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorCommon                 -ts .\zh_cn\EditorCommon.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorConsole                -ts .\zh_cn\EditorConsole.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorCSharp                 -ts .\zh_cn\EditorCSharp.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorDynamicResponseSystem  -ts .\zh_cn\EditorDynamicResponseSystem.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorEnvironment            -ts .\zh_cn\EditorEnvironment.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorGameSDK                -ts .\zh_cn\EditorGameSDK.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorParticle               -ts .\zh_cn\EditorParticle.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorSchematyc              -ts .\zh_cn\EditorSchematyc.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorSchematyc2             -ts .\zh_cn\EditorSchematyc2.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorSubstance              -ts .\zh_cn\EditorSubstance.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\EditorTrackView              -ts .\zh_cn\EditorTrackView.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\FacialEditorPlugin           -ts .\zh_cn\FacialEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\FBXPlugin                    -ts .\zh_cn\FBXPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\LodGeneratorPlugin           -ts .\zh_cn\LodGeneratorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\MaterialEditorPlugin         -ts .\zh_cn\MaterialEditorPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\MeshImporter                 -ts .\zh_cn\MeshImporter.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\MFCToolsPlugin               -ts .\zh_cn\MFCToolsPlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\SamplePlugin                 -ts .\zh_cn\SamplePlugin.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\SchematycEditor              -ts .\zh_cn\SchematycEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\SmartObjectEditor            -ts .\zh_cn\SmartObjectEditor.ts
%QTDIR%\lupdate -noobsolete ..\..\..\Code\Sandbox\Plugins\VehicleEditor                -ts .\zh_cn\VehicleEditor.ts 