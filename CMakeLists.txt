cmake_minimum_required(VERSION 3.5)
project(KenoRun VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
# set ( CMAKE_CXX_FLAGS "-Wall" )

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 14)
#--------------------------------

# configura o diretório contendo os .h, assim você pode incluílos apenas com include "arquivo.h"
include_directories( include )

# Cria um executável com nome "KenoRun", adiciona neste executável os arquivos OtherFunctions, KenoBet e o seu main.cpp
add_executable( KenoRun
                src/KenoBet.cpp
                src/OtherFunctions.cpp
                src/KenoMain.cpp )

# The end