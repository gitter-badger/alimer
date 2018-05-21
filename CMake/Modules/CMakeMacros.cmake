cmake_minimum_required(VERSION 3.5)

# Replace compilation flags, configuration type is optional
macro(replace_compile_flags pSearch pReplace)
	set(MacroArgs "${ARGN}")
	if( NOT MacroArgs )
		string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
		string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		foreach(MacroArg IN LISTS MacroArgs)
			if( MacroArg STREQUAL "debug" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
			elseif( MacroArg STREQUAL "dev" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_C_FLAGS_DEV "${CMAKE_C_FLAGS_DEV}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_CXX_FLAGS_DEV "${CMAKE_CXX_FLAGS_DEV}")
			elseif( MacroArg STREQUAL "release" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
			else()
				message(FATAL_ERROR "Unknown configuration, cannot replace compile flags!")
			endif()
		endforeach()
	endif()
endmacro()

# Add linker flags, configuration type is optional
macro(add_linker_flags pFlags)
	set(MacroArgs "${ARGN}")
	if( NOT MacroArgs )
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${pFlags}")
		set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${pFlags}")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${pFlags}")
	else()
		foreach(MacroArg IN LISTS MacroArgs)
			if( MacroArg STREQUAL "debug" )
				set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${pFlags}")
				set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} ${pFlags}")
				set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} ${pFlags}")
			elseif( MacroArg STREQUAL "dev" )
				set(CMAKE_EXE_LINKER_FLAGS_DEV "${CMAKE_EXE_LINKER_FLAGS_DEV} ${pFlags}")
				set(CMAKE_STATIC_LINKER_FLAGS_DEV "${CMAKE_STATIC_LINKER_FLAGS_DEV} ${pFlags}")
				set(CMAKE_SHARED_LINKER_FLAGS_DEV "${CMAKE_SHARED_LINKER_FLAGS_DEV} ${pFlags}")
			elseif( MacroArg STREQUAL "release" )
				set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${pFlags}")
				set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} ${pFlags}")
				set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} ${pFlags}")
			else()
				message(FATAL_ERROR "Unknown configuration, cannot add linker flags!")
			endif()
		endforeach()
	endif()
endmacro()

# Replace linker flags, configuration type is optional
macro(replace_linker_flags pSearch pReplace)
	set(MacroArgs "${ARGN}")
	if( NOT MacroArgs )
		string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
		string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
		string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")
	else()
		foreach(MacroArg IN LISTS MacroArgs)
			if( MacroArg STREQUAL "debug" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}")
			elseif( MacroArg STREQUAL "dev" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_EXE_LINKER_FLAGS_DEV "${CMAKE_EXE_LINKER_FLAGS_DEV}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_SHARED_LINKER_FLAGS_DEV "${CMAKE_SHARED_LINKER_FLAGS_DEV}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_MODULE_LINKER_FLAGS_DEV "${CMAKE_MODULE_LINKER_FLAGS_DEV}")
			elseif( MacroArg STREQUAL "release" )
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
				string(REGEX REPLACE "${pSearch}" "${pReplace}" CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}")
			else()
				message(FATAL_ERROR "Unknown configuration, cannot replace linker flags!")
			endif()
		endforeach()
	endif()
endmacro()

# build compile flags.
function(copy_release_build_flags BUILD_TYPE)
    set(CMAKE_C_FLAGS_${BUILD_TYPE} ${CMAKE_C_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_${BUILD_TYPE} ${CMAKE_CXX_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_SHARED_LINKER_FLAGS_${BUILD_TYPE} ${CMAKE_SHARED_LINKER_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_MODULE_LINKER_FLAGS_${BUILD_TYPE} ${CMAKE_MODULE_LINKER_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_EXE_LINKER_FLAGS_${BUILD_TYPE} ${CMAKE_EXE_LINKER_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_STATIC_LINKER_FLAGS_${BUILD_TYPE} ${CMAKE_STATIC_LINKER_FLAGS_RELEASE} PARENT_SCOPE)
endfunction()

# Groups sources into subfolders.
macro(group_sources)
    file (GLOB_RECURSE children LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/**)
    foreach (child ${children})
        if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
            string(REPLACE "/" "\\" groupname "${child}")
            file (GLOB files LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/${child}/*)
            source_group(${groupname} FILES ${files})
        endif ()
    endforeach ()
endmacro()

macro (add_alimer_executable TARGET)
    file (GLOB SOURCE_FILES *.cpp *.h)
    if (NOT ALIMER_WIN32_CONSOLE)
        set (TARGET_TYPE WIN32)
    endif ()

    if (PLATFORM_ANDROID)
        add_library(${TARGET} SHARED ${ARGN})
    else ()
        add_executable (${TARGET} ${TARGET_TYPE} ${ARGN})
    endif ()
    target_link_libraries (${TARGET} libAlimer)
endmacro ()
