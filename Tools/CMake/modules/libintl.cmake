if(WIN64)
	add_library(libintl SHARED IMPORTED GLOBAL)
	set_target_properties(libintl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SDK_DIR}/libintl/include")

	set_property(TARGET libintl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_target_properties(libintl PROPERTIES IMPORTED_LOCATION_DEBUG "${SDK_DIR}/libintl/bin/x64/libintl_debug.dll")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_DEBUG "${SDK_DIR}/libintl/lib/x64/libintl_debug.lib")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_DEBUG "${SDK_DIR}/libintl/lib/x64/libintl_a_debug.lib")

	set_property(TARGET libintl APPEND PROPERTY IMPORTED_CONFIGURATIONS PROFILE)
	set_target_properties(libintl PROPERTIES IMPORTED_LOCATION_PROFILE "${SDK_DIR}/libintl/bin/x64/libintl.dll")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_PROFILE "${SDK_DIR}/libintl/lib/x64/libintl.lib")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_PROFILE "${SDK_DIR}/libintl/lib/x64/libintl_a.lib")

	set_property(TARGET libintl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
	set_target_properties(libintl PROPERTIES IMPORTED_LOCATION_RELEASE "${SDK_DIR}/libintl/bin/x64/libintl.dll")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_RELEASE "${SDK_DIR}/libintl/lib/x64/libintl.lib")
	set_target_properties(libintl PROPERTIES IMPORTED_IMPLIB_RELEASE "${SDK_DIR}/libintl/lib/x64/libintl_a.lib")

	deploy_runtime_files("${SDK_DIR}/libintl/bin/x64/libintl.dll")
	
endif()
