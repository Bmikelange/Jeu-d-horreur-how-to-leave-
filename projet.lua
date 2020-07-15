
no_project = true
dofile "./premake4.lua"

gfx_projet_dir = path.getabsolute(".")

master_projet_files = {	gfx_projet_dir .. "/src/Projet-synthese/*.cpp", 
							gfx_projet_dir .. "/libs/soloud20200207/src/core/*.cpp",
							gfx_projet_dir .. "/libs/soloud20200207/src/audiosource/wav/*.cpp",
							gfx_projet_dir .. "/libs/soloud20200207/src/audiosource/wav/*.c",
							gfx_projet_dir .. "/libs/soloud20200207/src/backend/sdl2_static/*.cpp",
							gfx_projet_dir .. "/src/Projet-synthese/*.h",
							gfx_projet_dir .. "/libs/soloud20200207/include/*.h",
							gfx_projet_dir .. "/libs/imgui-master/*.cpp",
							gfx_projet_dir .. "/libs/imgui-master/*.h",	
							gfx_projet_dir .. "/libs/imgui-master/examples/imgui_impl_sdl.h",
							gfx_projet_dir .. "/libs/imgui-master/examples/imgui_impl_sdl.cpp",
							gfx_projet_dir .. "/libs/imgui-master/examples/imgui_impl_opengl3.h",
							gfx_projet_dir .. "/libs/imgui-master/examples/imgui_impl_opengl3.cpp"
	}
	
project("Projet-synthese")
    language "C++"
    kind "ConsoleApp"
    targetdir ( gfx_projet_dir .. "/bin" )
    includedirs { gfx_projet_dir .. "/src/Projet-synthese/",gfx_projet_dir .. "/libs/soloud20200207/include/"}
    files ( gkit_files )
    files ( master_projet_files )
    links { "GLEW", "SDL2", "SDL2_image", "GL","GLU","pthread" }
    defines {"WITH_SDL2_STATIC"}
