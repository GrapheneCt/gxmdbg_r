cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "$ENV{SCE_PSP2_SDK_DIR}/host_tools/build/cmake/psp2-snc-toolchain.cmake")

project(gxmdbg_r LANGUAGES C)

include(VitaDevelopmentSuite)
enable_language(EMD)
set(CMAKE_C_STANDARD 99)

include_directories(SYSTEM
  ${VDSUITE_KERNEL_INCLUDE_DIRECTORIES}
)

link_directories(
  ${VDSUITE_LIBRARY_DIRECTORIES}
)

add_compile_options(
  -Xdiag=0 -Xquit=2
)

add_link_options(
  --prx-no-runtime-support
  --strip-unused-data
  --strip-duplicates
)

set(ELF "${PROJECT_NAME}.elf")
set(SELF "${PROJECT_NAME}.skprx")

add_library("${PROJECT_NAME}.elf" MODULE
  gxmdbg_r.emd
  main.c
)

target_link_libraries("${PROJECT_NAME}.elf"
  SceSysclibForDriver_stub
  SceIofilemgrForDriver_stub
  taihenForKernel_stub
  taihenModuleUtils_stub
)

VDSuiteSignElf("${PROJECT_NAME}.skprx" "${PROJECT_NAME}.elf")
