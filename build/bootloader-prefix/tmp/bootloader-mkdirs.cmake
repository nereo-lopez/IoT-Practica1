# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/ESP32/v5.2/esp-idf/components/bootloader/subproject"
  "F:/Github/IoT-Practica1/build/bootloader"
  "F:/Github/IoT-Practica1/build/bootloader-prefix"
  "F:/Github/IoT-Practica1/build/bootloader-prefix/tmp"
  "F:/Github/IoT-Practica1/build/bootloader-prefix/src/bootloader-stamp"
  "F:/Github/IoT-Practica1/build/bootloader-prefix/src"
  "F:/Github/IoT-Practica1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/Github/IoT-Practica1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/Github/IoT-Practica1/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
