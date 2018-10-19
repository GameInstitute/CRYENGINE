// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include <CryCore/Platform/platform_impl.inl>
#include "IPlugin.h"
#include "Objects/DesignerObject.h"
#include "Objects/AreaSolidObject.h"
#include "Objects/ClipVolumeObject.h"
#include "Tools/AreaSolidTool.h"
#include "DesignerEditor.h"
#include "Tools/ClipVolumeTool.h"
#include "Util/Converter.h"
#include "Util/Exporter.h"
#include "GameExporter.h"
#include "Util/BoostPythonHelpers.h"
#include "Core/Helper.h"
#include "UVMappingEditor/UVMappingEditor.h"
#include <CrySerialization/Enum.h>
#include "QtViewPane.h"
#include "UIs/DesignerDockable.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

DECLARE_PYTHON_MODULE(designer);
DECLARE_PYTHON_MODULE(uvmapping);

using namespace Designer;

namespace Designer
{
namespace UVMapping
{
REGISTER_VIEWPANE_FACTORY_AND_MENU(UVMappingEditor, "UV Mapping", "Designer Tool", true, "Designer Tool")
REGISTER_VIEWPANE_FACTORY_AND_MENU(DesignerDockable, "Modeling", "Designer Tool", true, "Designer Tool")
}
}

class EditorDesigner : public IPlugin, public IAutoEditorNotifyListener
{
public:
	EditorDesigner()
	{
		char szEngineRootDir[_MAX_PATH];
		CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
		string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
		QString translationFile = "CryDesigner.qm";
		QString translationFilesPath;
		QString editorSettingsFile = engineRootDir.c_str() + QString("/editor.ini");
		QSettings *pEditorSetting = new QSettings(editorSettingsFile, QSettings::IniFormat);
		QString editorLang = pEditorSetting->value("/Sandbox/Language").toString();
		if (!editorLang.isNull())
		{
			translationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + editorLang + QString("/");
		}
		else
		{
			translationFilesPath = engineRootDir.c_str() + QString("/Editor/UI/Translations/") + QLocale::system().name().toLower() + QString("/");
		}
		QTranslator translator;
		translator.load(translationFile, translationFilesPath);
		QCoreApplication::installTranslator(&translator);
	}
	int32       GetPluginVersion() override { return 1; }
	const char* GetPluginName() override    { return "CryDesigner"; }
	const char* GetPluginDescription() override { return "Cryengine modeling and UV mapping tool"; }

	void        OnEditorNotifyEvent(EEditorNotifyEvent aEventId) override
	{
		// Notify the session and tool
		DesignerSession::GetInstance()->OnEditorNotifyEvent(aEventId);
		if (GetDesigner())
			GetDesigner()->OnEditorNotifyEvent(aEventId);

		switch (aEventId)
		{
		case eNotify_OnBeginExportToGame:
		case eNotify_OnBeginSceneSave:
			{
				DesignerSession::GetInstance()->EndSession();
				RemoveAllEmptyDesignerObjects();
			}
			break;

		case eNotify_OnExportBrushes:
			{
				CGameExporter* pGameExporter = CGameExporter::GetCurrentExporter();
				if (pGameExporter)
				{
					Exporter designerExporter;
					string path = PathUtil::RemoveSlash(PathUtil::GetPathWithoutFilename(pGameExporter->GetLevelPack().m_sPath)).c_str();
					designerExporter.ExportBrushes(path, pGameExporter->GetLevelPack().m_pakFile);
				}
			}
			break;
		}
	}
};


REGISTER_PLUGIN(EditorDesigner);

