cmake_minimum_required(VERSION 3.20)

project(Plasmacoin_Crypto VERSION 0.1.0)
configure_file(PCConfig.h.in PCConfig.h)

add_executable(Plasmacoin_Crypto src/qt/plasmacoin-ui/main.cpp)

target_include_directories(Plasmacoin_Crypto PUBLIC "src/qt/build-plasmacoin-ui-Desktop-Debug/plasmacoin-ui")

include(ExternalProject)
ExternalProject_Add(cryptopp
	GIT_REPOSITORY	git@github.com:weidai11/cryptopp
	GIT_TAG			CRYPTOPP_8_5_0
)