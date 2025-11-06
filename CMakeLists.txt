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

option(APPOUT_BUILD_TESTS "Build Test Executable" ON)

# if (NOT MSVC)
#	    message(FATAL_ERROR "Non MSVC compilers are not currently supported (but are planned)")
# endif()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "32-bit executables only support loading 32-bit libraries. (CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P})")
endif ()
set(CMAKE_SIZEOF_VOID_P 4)

add_library(Appout STATIC 
	"src/Assembler/AssemblerBase.cpp"
	"src/Assembler/x86Assembler.cpp"
	"src/MemoryPool/MemoryBlock.cpp"
	"src/MemoryPool/MemoryPoolBase.cpp"
	"src/MemoryPool/Win32MemoryPool.cpp"
	
	"src/HookData.cpp"
	"src/HookManager.cpp"
	"src/OpCode.cpp"
	"src/Process.cpp"
	"src/Trampoline.cpp"
	"src/HookInfo.cpp" 
	"src/CallingConvention.cpp" 
	"src/Instance.cpp" "src/Log.cpp" "src/Debug.cpp")


target_include_directories(Appout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

CPMAddPackage("gh:rotweaver/mhde#master")
target_link_libraries(Appout PUBLIC mhde_lib)

if (mhde_ADDED STREQUAL YES)
    target_include_directories(Appout PUBLIC ${mhde_SOURCE_DIR}/include)
    message(STATUS "MHDE ADDED!")
else()
	message(FATAL_ERROR "mhde is a required dependency for Appout")
endif()


if (${APPOUT_BUILD_TESTS})
	message(STATUS "Build Appout Tests is ON")
	project(APPOUT_TESTS VERSION 1.0.0 LANGUAGES C CXX)
	add_executable(APPOUT_TESTS "src/Test/main.cpp" "src/Test/TestEnviroment.cpp" "src/Test/Platform/x86Test.cpp")

	target_compile_definitions(APPOUT_TESTS PUBLIC -DAPPOUT_BUILD_TESTS)

	target_compile_definitions(APPOUT_TESTS PUBLIC -DAPPOUT_TEST_ARCH_X86) # temp

	target_link_libraries(APPOUT_TESTS PUBLIC Appout)
	target_link_directories(APPOUT_TESTS PRIVATE $<TARGET_PROPERTY:Appout,INTERFACE_INCLUDE_DIRECTORIES>)
endif()