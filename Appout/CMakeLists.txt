cmake_minimum_required(VERSION 3.8)

include(cmake/get_cpm.cmake)

if (NOT DEFINED CPM_SOURCE_CACHE)
    message(NOTICE "Not using CPM cache (CPM_SOURCE_CACHE). "
        "It is recommended to use it to improve configure times.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

project(Appout VERSION 1.0.0 LANGUAGES C CXX)

# if (NOT MSVC)
#	    message(FATAL_ERROR "Non MSVC compilers are not currently supported (but are planned)")
# endif()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "32-bit executables only support loading 32-bit libraries. (CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P})")
endif ()
set(CMAKE_SIZEOF_VOID_P 4)

add_library(${PROJECT_NAME} STATIC 
	"src/Assembler/AssemblerBase.cpp"
	"src/Assembler/x86Assembler.cpp"
	"src/MemoryPool/MemoryBlock.cpp"
	"src/MemoryPool/MemoryPoolBase.cpp"
	"src/MemoryPool/Win32MemoryPool.cpp"
	"src/CConv.cpp"
	"src/HookData.cpp"
	"src/HookManager.cpp"
	"src/OpCode.cpp"
	"src/Process.cpp"
	"src/Trampoline.cpp"
	)
	
target_include_directories(${PROJECT_NAME} PUBLIC "include")


CPMAddPackage("gh:rotweaver/mhde#master")
target_link_libraries(${PROJECT_NAME} mhde_lib)

if (mhde_ADDED)
    target_include_directories(${PROJECT_NAME} PUBLIC ${mhde_SOURCE_DIR}/include)
    message("MHDE ADDED!")
endif()
