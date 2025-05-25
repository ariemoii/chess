workspace "Testing"
    configurations { "Debug", "Release" }
    language "C++"
    cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Core/Build-Core.lua"
group ""

project "Tester"
    kind "ConsoleApp"
    location "Testing"
    files { "Testing/**.cpp", "Testing.h" }
    includedirs { "Core", "Core/Game", "Core/Engine" }
    links { "Chess-Core" }

filter "configurations:Debug"
  symbols "On"
  optimize "Off"