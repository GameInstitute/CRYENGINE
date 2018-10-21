// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#include <StdAfx.h>
#include "MannPreferences.h"

#include <CrySerialization/yasli/decorators/Range.h>

SMannequinGeneralPreferences gMannequinPreferences;
REGISTER_PREFERENCES_PAGE_PTR(SMannequinGeneralPreferences, &gMannequinPreferences)

SMannequinGeneralPreferences::SMannequinGeneralPreferences()
	: SPreferencePage("General", "Mannequin/General")
	, defaultPreviewFile("Animations/Mannequin/Preview/SDK_playerPreview1P.xml")
	, trackSize(32)
	, timelineWheelZoomSpeed(1.f)
	, bCtrlForScrubSnapping(false)
{
}

bool SMannequinGeneralPreferences::Serialize(yasli::Archive& ar)
{
	const int kMannequinTrackSizeMin = 14;
	const int kMannequinTrackSizeMax = 32;

	ar.openBlock("general", gettext("General"));
	ar(defaultPreviewFile, "defaultPreviewFile", gettext("Default Preview File")); //file
	ar(yasli::Range(trackSize, kMannequinTrackSizeMin, kMannequinTrackSizeMax), "trackSize", gettext("Size of tracks"));
	ar(bCtrlForScrubSnapping, "bCtrlForScrubSnapping", gettext("Hold Ctrl to Snap Scrubbing"));
	ar(yasli::Range(timelineWheelZoomSpeed, 0.1f, 5.f), "timelineWheelZoomSpeed", gettext("Timeline Wheel Zoom Speed"));
	ar.closeBlock();

	return true;
}

