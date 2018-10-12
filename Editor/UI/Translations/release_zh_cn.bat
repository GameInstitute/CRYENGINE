@IF "%QTDIR%" == "" (
    echo QTDIR environment variable is not set!
    EXIT /B 1
)

%QTDIR%\lrelease .\zh_cn\editor.ts
%QTDIR%\lrelease .\zh_cn\CryDesigner.ts
%QTDIR%\lrelease .\zh_cn\DependencyGraph.ts
%QTDIR%\lrelease .\zh_cn\DialogEditor.ts
%QTDIR%\lrelease .\zh_cn\EditorAnimation.ts
%QTDIR%\lrelease .\zh_cn\EditorCommon.ts
%QTDIR%\lrelease .\zh_cn\EditorConsole.ts
%QTDIR%\lrelease .\zh_cn\EditorCSharp.ts
%QTDIR%\lrelease .\zh_cn\EditorDynamicResponseSystem.ts
%QTDIR%\lrelease .\zh_cn\EditorEnvironment.ts
%QTDIR%\lrelease .\zh_cn\EditorGameSDK.ts
%QTDIR%\lrelease .\zh_cn\EditorParticle.ts
%QTDIR%\lrelease .\zh_cn\EditorSchematyc.ts
%QTDIR%\lrelease .\zh_cn\EditorSchematyc2.ts
%QTDIR%\lrelease .\zh_cn\EditorSubstance.ts
%QTDIR%\lrelease .\zh_cn\EditorTrackView.ts
%QTDIR%\lrelease .\zh_cn\FacialEditorPlugin.ts
%QTDIR%\lrelease .\zh_cn\FBXPlugin.ts
%QTDIR%\lrelease .\zh_cn\LodGeneratorPlugin.ts
%QTDIR%\lrelease .\zh_cn\MaterialEditorPlugin.ts
%QTDIR%\lrelease .\zh_cn\MeshImporter.ts
%QTDIR%\lrelease .\zh_cn\MFCToolsPlugin.ts
%QTDIR%\lrelease .\zh_cn\SamplePlugin.ts
%QTDIR%\lrelease .\zh_cn\SchematycEditor.ts
%QTDIR%\lrelease .\zh_cn\SmartObjectEditor.ts
%QTDIR%\lrelease .\zh_cn\VehicleEditor.ts 