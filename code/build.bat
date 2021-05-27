@echo off

mkdir ..\build
pushd ..\build
cl -Zi X:\code\win32_handmade.cpp
popd