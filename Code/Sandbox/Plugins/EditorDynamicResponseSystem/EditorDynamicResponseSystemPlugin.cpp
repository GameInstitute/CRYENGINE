// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"

#include "EditorDynamicResponseSystemPlugin.h"
#include "DrsEditorMainWindow.h"

#include <IResourceSelectorHost.h>

#include <CrySerialization/IArchiveHost.h>
#include <CrySerialization/STL.h>

#include <CryCore/Platform/platform_impl.inl>
#include <IEditor.h>
#include <CrySystem/ISystem.h>
#include <CryDynamicResponseSystem/IDynamicResponseSystem.h>
#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

REGISTER_PLUGIN(CEditorDynamicResponseSystemPlugin);

CEditorDynamicResponseSystemPlugin::CEditorDynamicResponseSystemPlugin()
{
	CRY_ASSERT(gEnv->pDynamicResponseSystem->GetResponseManager());
	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "EditorDynamicResponseSystem.qm";
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
