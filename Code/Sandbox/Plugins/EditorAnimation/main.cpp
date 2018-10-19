// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "stdafx.h"

#include <CryCore/Platform/platform_impl.inl>
#include "IEditorClassFactory.h"
#include "ICommandManager.h"
#include "IPlugin.h"
#include "IResourceSelectorHost.h"
#include "AnimationCompressionManager.h"
#include "CharacterTool/CharacterToolForm.h"
#include "QtViewPane.h"

// just for CGFContent:
#include <CryRenderer/VertexFormats.h>
#include <CryMath/Cry_Geo.h>
#include <CryCore/TypeInfo_impl.h>
#include <CryCore/Common_TypeInfo.h>
#include <Cry3DEngine/IIndexedMesh_info.h>
#include <Cry3DEngine/CGF/CGFContent_info.h>
// ^^^

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

#include "Serialization.h"

#include "CharacterTool/CharacterToolForm.h"
#include "CharacterTool/CharacterToolSystem.h"


void Log(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	GetIEditor()->GetSystem()->GetILog()->LogV(ILog::eAlways, format, args);
	va_end(args);
}


CharacterTool::System* g_pCharacterToolSystem;

// ---------------------------------------------------------------------------

class CEditorAnimationPlugin : public IPlugin
{
public:
	CEditorAnimationPlugin()
	{
		g_pCharacterToolSystem = new CharacterTool::System();
		g_pCharacterToolSystem->Initialize();

		const ICVar* pUseImgCafCVar = gEnv->pConsole->GetCVar("ca_UseIMG_CAF");
		const bool useImgCafSet = (pUseImgCafCVar && pUseImgCafCVar->GetIVal());
		if (useImgCafSet)
		{
			CryWarning(VALIDATOR_MODULE_EDITOR, VALIDATOR_WARNING, "[EditorAnimation] Animation compilation disabled: 'ca_UseIMG_CAF' should be set to zero at load time for compilation to work.");
		}
		else
		{
			g_pCharacterToolSystem->animationCompressionManager.reset(new CAnimationCompressionManager());
		}

		char szEngineRootDir[_MAX_PATH];
		CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
		string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
		QString translationFile = "EditorAnimation.qm";
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

	~CEditorAnimationPlugin()
	{
		if (g_pCharacterToolSystem)
		{
			delete g_pCharacterToolSystem;
			g_pCharacterToolSystem = 0;
		}
	}

	// implements IPlugin
	int32       GetPluginVersion()                        { return 0x01; }
	const char* GetPluginName()                           { return "Editor Animation"; }
	const char* GetPluginDescription()					  { return "Animation tools and Character Tool"; }
};

//////////////////////////////////////////////////////////////////////////-

REGISTER_PLUGIN(CEditorAnimationPlugin);
