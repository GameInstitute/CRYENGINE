if(WIN64)
	add_library(libiconv SHARED IMPORTED GLOBAL)
	set_target_properties(libiconv PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SDK_DIR}/libiconv/include")

	set_property(TARGET libiconv APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
	set_target_properties(libiconv PROPERTIES IMPORTED_LOCATION_DEBUG "${SDK_DIR}/libiconv/bin/x64/libiconv_debug.dll")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_DEBUG "${SDK_DIR}/libiconv/lib/x64/libiconv_debug.lib")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_DEBUG "${SDK_DIR}/libiconv/lib/x64/libiconv_a_debug.lib")

	set_property(TARGET libiconv APPEND PROPERTY IMPORTED_CONFIGURATIONS PROFILE)
	set_target_properties(libiconv PROPERTIES IMPORTED_LOCATION_PROFILE "${SDK_DIR}/libiconv/bin/x64/libiconv.dll")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_PROFILE "${SDK_DIR}/libiconv/lib/x64/libiconv.lib")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_PROFILE "${SDK_DIR}/libiconv/lib/x64/libiconv_a.lib")

	set_property(TARGET libiconv APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
	set_target_properties(libiconv PROPERTIES IMPORTED_LOCATION_RELEASE "${SDK_DIR}/libiconv/bin/x64/libiconv.dll")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_RELEASE "${SDK_DIR}/libiconv/lib/x64/libiconv.lib")
	set_target_properties(libiconv PROPERTIES IMPORTED_IMPLIB_RELEASE "${SDK_DIR}/libiconv/lib/x64/libiconv_a.lib")

	deploy_runtime_files("${SDK_DIR}/libiconv/bin/x64/libiconv.dll")
	
endif()
