// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "MFCToolsPlugin.h"

#include "IPlugin.h"
#include <CryCore/Platform/platform_impl.inl>

static IEditor* g_editor = nullptr;
IEditor* GetIEditor() { return g_editor; }

void InitialTranslator(const char* domain)
{
	char szEngineRootDir[_MAX_PATH];
	CryFindEngineRootFolder(CRY_ARRAY_COUNT(szEngineRootDir), szEngineRootDir);
	string engineRootDir = PathUtil::RemoveSlash(szEngineRootDir);

	string domainTranslationFilesPath;
	domainTranslationFilesPath = engineRootDir + "/Editor/UI/Languages/";

	setlocale(LC_ALL, "");
	bindtextdomain(domain, domainTranslationFilesPath.c_str());
	textdomain(domain);
}

PLUGIN_API void MFCToolsPlugin::SetEditor(IEditor* editor)
{
	g_editor = editor;
	auto system = GetIEditor()->GetSystem();
	gEnv = system->GetGlobalEnvironment();
}

PLUGIN_API void MFCToolsPlugin::Initialize()
{
	ModuleInitISystem(GetIEditor()->GetSystem(), "MFCToolsPlugin");
	RegisterPlugin();

	InitialTranslator("MFCToolsPlugin");
}

PLUGIN_API void MFCToolsPlugin::Deinitialize()
{
	UnregisterPlugin();
	g_editor = nullptr;
	gEnv = nullptr;
}

