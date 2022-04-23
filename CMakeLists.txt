cmake_minimum_required (VERSION 3.9)

project (llbuilder)
#project (luaide)

#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${llbuilder_SOURCE_DIR}/bin)
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(PkgConfig REQUIRED)

if (PKG_CONFIG_FOUND)
	set(llbuilder_INCLUDE_DIRS
		${CMAKE_SOURCE_DIR}/src/inc
		
	)
	add_executable("llbuilder"
						"src/mini-pacman.cpp" 
						
						# C++ Main modules 
						"src/inc/m_builder.cpp"
						"src/inc/m_lpac.cpp"
						"src/inc/m_helper.cpp"

						# C++ Helper Classes
						"src/inc/cpp_fs.cpp"
						"src/inc/cpp_inet.cpp"
						
						# LUA functions
						"src/inc/lua_filesystem.cpp"
						"src/inc/lua_loop.cpp"
						"src/inc/lua_envs.cpp"
						"src/inc/lua_child_process.cpp"
						
						# 3th party functions to decrease app dependency
						"src/inc_3th/sha256.cpp"
	)
	pkg_check_modules(LUA REQUIRED lua)
	if (LUA_FOUND)
		SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
		add_compile_options(
 				"-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  				"$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-fsanitize=address;-fstack-protector-all;-lSegFault>"
		)
		target_link_libraries(llbuilder 	PRIVATE ${LUA_LIBRARIES} SegFault)
		execute_process (
		    COMMAND bash -c ${llbuilder_SOURCE_DIR}"/lcompile.sh"
		    OUTPUT_VARIABLE outVar
		)
	endif()
	
	
	# file(COPY ${mini-pacman_SOURCE_DIR}/lua/ DESTINATION ${mini-pacman_BINARY_DIR}bin/)
	#file(COPY ${llbuilder_SOURCE_DIR}/lua/ DESTINATION ${llbuilder_BINARY_DIR}bin/)
	
endif()


#[[
if (PKG_CONFIG_FOUND)
	pkg_check_modules(GTK REQUIRED gtk+-3.0 gdk-3.0 gtksourceview-3.0)
	if (GTK_FOUND)  
		add_executable("mini-pacman-gtk"
							"src/gui-gtk/luaide.cpp"
							# "src/gui-gtk/sourceview.cpp"
		)
		target_link_libraries(mini-pacman-gtk ${GTK_LIBRARIES})
    	add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
	endif()
endif()
]]





