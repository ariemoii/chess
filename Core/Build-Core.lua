project "Chess-Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Game/**.h", "Game/**.cpp", "Engine/**.h", "Engine/**.cpp", "ChessGame/**.cpp", "ChessGame/**.h" }

   includedirs
   {
    "Game",
    "Engine",
    "ChessGame"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "system:linux"
       buildoptions {"-lsfml-graphics", "-lsfml-window", "-lsfml-system"}

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"