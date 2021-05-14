cmake_minimum_required(VERSION 3.20)
project(Plasmacoin Cryptocurrency)

include(ExternalProject)
ExternalProject_Add(cryptopp
	GIT_REPOSITORY	git@github.com:weidai11/cryptopp
	GIT_TAG			CRYPTOPP_8_5_0
)

add_executable(PlasmacoinUI src/qt/build-plasmacoin-ui-Desktop-Debug/plasmacoin-ui)
