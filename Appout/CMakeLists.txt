cmake_minimum_required(VERSION 3.8)

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

add_library(${PROJECT_NAME} SHARED 
	"Assembler/AssemblerBase.cpp"
	"Assembler/x86Assembler.cpp"
	"MemoryPool/MemoryBlock.cpp"
	"MemoryPool/MemoryPoolBase.cpp"
	"MemoryPool/Win32MemoryPool.cpp"
	"CConv.cpp"
	"HookData.cpp"
	"HookManager.cpp"
	"OpCode.cpp"
	"Process.cpp"
	"Trampoline.cpp"
	)
	
target_include_directories(${PROJECT_NAME} PUBLIC "include")