cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

message("\n================= Start configure project [${PROJECT_NAME}] ==================")

project("fmtlog" 
    VERSION 1.0.0.0
    LANGUAGES CXX C
    DESCRIPTION "something about this project"
    HOMEPAGE_URL "project site"
    )

message("PROJECT_NAME: " ${PROJECT_NAME})
message("CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME})

if(NOT DEFINED META_NAME)
    set(META_NAME ${PROJECT_NAME})

    include(cmake/DetectEnvironment.cmake)
    include(cmake/AddLibrary.cmake)
    include(cmake/CompileOptions.cmake)
    include(cmake/InstallFunc.cmake)

    set(CMAKE_C_STANDARD 11)                    # 设置整个项目的默认 C 标准
    set(CMAKE_CXX_STANDARD 17)                  # 设置整个项目的默认 C++ 标准
    set(CMAKE_CXX_EXTENSIONS OFF)               # 只启用ISO C++标准的编译器标志，而不使用特定编译器的扩展
    set(CMAKE_CXX_STANDARD_REQUIRED ON)         # 开启防止编译器回退到支持的低版本的C++标准
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)     # 默认为开启，代码位置无关，避免使用动态链接库时需要重定位
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)    # 在 Windows 上导出所有库符号
    set(CMAKE_MACOSX_RPATH ON)                  # macOS上动态库使用相对路径
    set(CMAKE_DEBUG_POSTFIX "_d")

    # 设置默认输出路径
    set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

    option(IS_BUILD_TEST "option for build test" ON)
    option(IS_BUILD_INSTALL "option for build install" ON)
    
    if(IS_BUILD_TEST)
        add_subdirectory(test)
    endif()
    
endif()

include(FetchContent)
FetchContent_Declare(spdlog
        GIT_REPOSITORY git@github.com:gabime/spdlog.git
        # GIT_TAG ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36
        GIT_TAG v1.11.0

        # URL      https://intranet.mycompany.com/assets/iconset_1.12.tar.gz
        # URL_HASH MD5=5588a7b18261c20068beabfb4f530b87

        # SVN_REPOSITORY svn+ssh://svn.mycompany.com/srv/svn/trunk/certs
        # SVN_REVISION   -r12345
        
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext
        )
FetchContent_MakeAvailable(spdlog)

project("fmtlog" 
    VERSION 1.0.0.0
    LANGUAGES CXX C
    DESCRIPTION "something about this project"
    HOMEPAGE_URL "project site"
    )

add_subdirectory(src)

add_subdirectory(bench)

# 安装目标
if(IS_BUILD_INSTALL)
    InstallFunc(${PROJECT_NAME})
endif()    

message("================== Stop configure project [${PROJECT_NAME}] ==================\n")