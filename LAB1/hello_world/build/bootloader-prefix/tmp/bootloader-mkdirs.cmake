# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/Espressif/frameworks/esp-idf-v5.0.2/components/bootloader/subproject"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/tmp"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/src"
  "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Users/PC/VY/HCMUT/HK231/ES/LAB/LAB1/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
