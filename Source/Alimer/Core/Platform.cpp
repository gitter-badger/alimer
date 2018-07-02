//
// Copyright (c) 2018 Amer Koleci and contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Core/Platform.h"
#include "../Core/Log.h"

namespace Alimer
{
	PlatformId GetPlatformId()
	{
#if __ANDROID__
		return PlatformId::Android;
#elif ALIMER_PLATFORM_APPLE_IOS
		return PlatformId::iOS;
#elif ALIMER_PLATFORM_APPLE_TV
		return PlatformId::AppleTV;
#elif ALIMER_PLATFORM_APPLE_OSX
		return PlatformId::MacOS;
#elif ALIMER_PLATFORM_WINDOWS
		return PlatformId::Windows;
#elif ALIMER_PLATFORM_UWP
		return PlatformId::WindowsUniversal;
#elif ALIMER_PLATFORM_WEB
		return PlatformId::Web;
#elif ALIMER_PLATFORM_LINUX
		return PlatformId::Linux;
#else
		return PlatformId::Unknown;
#endif
	}

	PlatformFamily GetPlatformFamily()
	{
#if ALIMER_PLATFORM_ANDROID || ALIMER_PLATFORM_APPLE_IOS || ALIMER_PLATFORM_APPLE_TV
		return PlatformFamily::Mobile;
#elif ALIMER_PLATFORM_WINDOWS || ALIMER_PLATFORM_LINUX || ALIMER_PLATFORM_APPLE_OSX
		return PlatformFamily::Desktop;
#elif ALIMER_PLATFORM_UWP
		Windows::System::Profile::AnalyticsVersionInfo^ versionInfo = Windows::System::Profile::AnalyticsInfo::VersionInfo;
		Platform::String^ DeviceFamily = versionInfo->DeviceFamily;
		if (DeviceFamily->Equals("Windows.Desktop"))
		{
			return PlatformFamily::Desktop;
		}
		else if (DeviceFamily->Equals("Windows.Mobile"))
		{
			return PlatformFamily::Mobile;
		}
		else if (DeviceFamily->Equals("Windows.Xbox"))
		{
			return PlatformFamily::Console;
		}

		return PlatformFamily::Unknown;
#elif ALIMER_PLATFORM_WEB
		return PlatformFamily::Console;
#else
		return PlatformFamily::Unknown;
#endif
	}

	const char* GetPlatformName()
	{
		PlatformId platform = GetPlatformId();
		switch (platform)
		{
			case PlatformId::Windows:
				return "Windows";
			case PlatformId::WindowsUniversal:
				return "UWP";
			case PlatformId::Linux:
				return "Linux";
			case PlatformId::MacOS:
				return "MacOS";
			case PlatformId::Android:
				return "Android";
			case PlatformId::iOS:
				return "iOS";
			case PlatformId::AppleTV:
				return "AppleTV";
			case PlatformId::Web:
				return "Web";
			default:
				return "Unknown";
		}
	}
}