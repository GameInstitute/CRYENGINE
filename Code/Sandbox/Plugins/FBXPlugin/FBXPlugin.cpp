// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "FBXPlugin.h"

#include <CryCore/Platform/platform_impl.inl>

#include "FBXExporter.h"

#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

REGISTER_PLUGIN(CFBXPlugin);

namespace PluginInfo
{
const char* kName = "FBX Exporter";
const char* kDesc = "FBX Exporter plugin";
const int kVersion = 1;
}

CFBXPlugin::CFBXPlugin()
{
	IExportManager* pExportManager = GetIEditor()->GetExportManager();
	if (pExportManager)
	{
		pExportManager->RegisterExporter(new CFBXExporter());
	}

	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "FBXPlugin.qm";
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

CFBXPlugin::~CFBXPlugin()
{
	CryWarning(VALIDATOR_MODULE_EDITOR, VALIDATOR_ERROR, "CFBXPlugin cannot be unloaded as FBX exporter cannot be unregistered");
}

int32 CFBXPlugin::GetPluginVersion()
{
	return PluginInfo::kVersion;
}

const char* CFBXPlugin::GetPluginName()
{
	return PluginInfo::kName;
}

const char* CFBXPlugin::GetPluginDescription()
{
	return PluginInfo::kDesc;
}

