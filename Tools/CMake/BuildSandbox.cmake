if(NOT EXISTS "${SDK_DIR}/FbxSdk")
	message(WARNING "FBX SDK (2016) is required to build Sandbox. Download it from https://www.autodesk.com.")
	return()
endif()

set(CMAKE_AUTOMOC_RELAXED_MODE TRUE)

#modules
include("${TOOLS_CMAKE_DIR}/modules/FbxSdk.cmake")
include("${TOOLS_CMAKE_DIR}/modules/libiconv.cmake")
include("${TOOLS_CMAKE_DIR}/modules/libintl.cmake")
#---

add_subdirectory("Code/Sandbox/Libs/CryQt")

set(EDITOR_DIR "Code/Sandbox/EditorQt" )
add_subdirectory("Code/Sandbox/EditorQt")
add_subdirectory("Code/Sandbox/Plugins/3DConnexionPlugin")
add_subdirectory("Code/Sandbox/Plugins/EditorConsole")

add_subdirectory("Code/Sandbox/Plugins/EditorCommon")
add_subdirectory("Code/Sandbox/EditorInterface")

add_subdirectory("Code/Sandbox/Plugins/CryDesigner")
add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor")
add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor/common")
if(AUDIO_FMOD)
	add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor/EditorFmod")
endif()
if(AUDIO_SDL_MIXER)
	add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor/EditorSDLMixer")
endif()
if(AUDIO_PORTAUDIO)
	add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor/EditorPortAudio")
endif()
if (AUDIO_WWISE)
	add_subdirectory("Code/Sandbox/Plugins/EditorAudioControlsEditor/EditorWwise")
endif()
add_subdirectory("Code/Sandbox/Plugins/EditorAnimation")
add_subdirectory("Code/Sandbox/Plugins/EditorDynamicResponseSystem")
add_subdirectory("Code/Sandbox/Plugins/EditorEnvironment")
add_subdirectory("Code/Sandbox/Plugins/EditorParticle")
if (PLUGIN_SCHEMATYC)
	add_subdirectory("Code/Sandbox/Plugins/EditorSchematyc")
endif()
add_subdirectory("Code/Sandbox/Plugins/EditorTrackView")
add_subdirectory("Code/Sandbox/Plugins/EditorGameSDK")
add_subdirectory("Code/Sandbox/Plugins/FbxPlugin")
add_subdirectory("Code/Sandbox/Plugins/MeshImporter")
if (EXISTS "${SDK_DIR}/p4api")
	add_subdirectory("Code/Sandbox/Plugins/PerforcePlugin")
else()
	message(INFO "Perforce SDK 2015.1 not found at ${SDK_DIR}/p4api, disabling legacy Sandbox plugin.")
endif()
add_subdirectory("Code/Sandbox/Plugins/SandboxPythonBridge")
add_subdirectory("Code/Sandbox/Plugins/SamplePlugin")
add_subdirectory("Code/Sandbox/Plugins/VehicleEditor")
add_subdirectory("Code/Sandbox/Plugins/SmartObjectEditor")
add_subdirectory("Code/Sandbox/Plugins/DialogEditor")
add_subdirectory("Code/Sandbox/Plugins/MFCToolsPlugin")
add_subdirectory("Code/Sandbox/Plugins/FacialEditorPlugin")
add_subdirectory("Code/Sandbox/Plugins/DependencyGraph")
add_subdirectory("Code/Sandbox/Plugins/MaterialEditorPlugin")
if(OPTION_SANDBOX_SUBSTANCE)
	include("${CRYENGINE_DIR}/Tools/CMake/modules/Substance.cmake")
	add_subdirectory("Code/Sandbox/Libs/CrySubstance")
	add_subdirectory("Code/Sandbox/Plugins/EditorSubstance")
endif()
if(OPTION_CRYMONO)
	add_subdirectory("Code/Sandbox/Plugins/EditorCSharp")
endif()
#libs
add_subdirectory ("Code/Libs/prt")
add_subdirectory ("Code/Libs/python")
