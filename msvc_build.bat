@echo off

REM please execute this file in msvc x86 native compiler shell in current directory

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"

call msbuild -consoleLoggerParameters:PerformanceSummary;Summary;ShowTimestamp -maxCpuCount:2 ab\ab\ab.vcxproj
