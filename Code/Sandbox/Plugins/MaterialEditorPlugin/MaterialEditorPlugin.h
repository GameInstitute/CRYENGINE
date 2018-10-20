// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once
#include "IPlugin.h"
#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>

class CMaterialEditorPlugin : public IPlugin
{
public:
	CMaterialEditorPlugin()
	{
		InitialTranslator("MaterialEditorPlugin", "MaterialEditorPlugin.qm");
	}
	~CMaterialEditorPlugin() { /* exit point of the plugin, perform cleanup */ }

	int32       GetPluginVersion() { return 1; };
	const char* GetPluginName() { return "Material Editor Plugin"; };
	const char* GetPluginDescription() { return "New material editor integrated with the asset system"; };

private:
};
