workspace "UCI-connector"
    configurations { "Debug", "Release" }
    language "C++"
    cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Core/Build-Core.lua"
group ""

project "Connector"
    kind "ConsoleApp"
    location "UCI-connector"
    files { "UCI-connector/**.cpp", "UCI-connector.h" }
    includedirs { "Core", "Core/Game", "Core/Engine" }
    links { "Chess-Core" }

filter "configurations:Debug"
  symbols "On"
  optimize "Off"