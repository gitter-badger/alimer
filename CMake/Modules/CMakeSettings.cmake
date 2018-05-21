cmake_minimum_required(VERSION 3.5)

if( _SETTINGS_GUARD )
	return()
endif()
set(_SETTINGS_GUARD 1)

include(CMakePlatforms)
include(CMakeMacros)

# Graphics backends
if (NOT ALIMER_DISABLE_D3D12)
	if (PLATFORM_WINDOWS OR PLATFORM_UWP)
		set (ALIMER_D3D12_DEFAULT ON)
	else ()
		set (ALIMER_D3D12_DEFAULT OFF)
	endif ()
endif ()

# Tools
if (NOT ALIMER_DISABLE_ASSET_PIPELINE)
	if (PLATFORM_DESKTOP)
		set (ALIMER_ASSET_PIPELINE_DEFAULT ON)
	else ()
		set (ALIMER_ASSET_PIPELINE_DEFAULT OFF)
	endif()
endif ()

option (ALIMER_D3D12 "Enable D3D12 backend" ${ALIMER_D3D12_DEFAULT})
option (ALIMER_ASSET_PIPELINE "Enable AssetPipeline" ${ALIMER_ASSET_PIPELINE_DEFAULT})