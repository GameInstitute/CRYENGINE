// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "Plugin.h"
#include "Menu/AbstractMenu.h"
#include <AssetSystem/AssetManager.h>
#include <CryCore/Platform/platform_impl.inl>
#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>	

// Plugin instance
static CDependencyGraph* g_pInstance = nullptr;

REGISTER_PLUGIN(CDependencyGraph);

CDependencyGraph::CDependencyGraph()
{
	CRY_ASSERT(g_pInstance == nullptr);
	g_pInstance = this;

	GetIEditor()->GetAssetManager()->signalContextMenuRequested.Connect([](CAbstractMenu& menu, const std::vector<CAsset*>& assets, std::shared_ptr<IUIContext> context)
	{
		if (assets.size() == 1)
		{
			auto action = menu.CreateAction(QObject::tr("Show Dependency Graph"), menu.FindSectionByName("Assets"));
			QObject::connect(action, &QAction::triggered, [asset = assets.front()]()
			{ 
				GetIEditor()->ExecuteCommand("asset.show_dependency_graph '%s'", asset->GetMetadataFile());
			});
		}
	}, (uintptr_t)this);

	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);
	QString translationFile = "DependencyGraph.qm";
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

CDependencyGraph::~CDependencyGraph()
{
	GetIEditor()->GetAssetManager()->signalContextMenuRequested.DisconnectById((uintptr_t)this);
	CRY_ASSERT(g_pInstance == this);
	g_pInstance = nullptr;
}

CDependencyGraph* CDependencyGraph::GetInstance()
{
	return g_pInstance;
}

void CDependencyGraph::SetPersonalizationProperty(const QString& propName, const QVariant& value)
{
	GetIEditor()->GetPersonalizationManager()->SetProperty(GetPluginName(), propName, value);
}

const QVariant& CDependencyGraph::GetPersonalizationProperty(const QString& propName)
{
	return GetIEditor()->GetPersonalizationManager()->GetProperty(GetPluginName(), propName);
}

