@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"

call msbuild -consoleLoggerParameters:PerformanceSummary;Summary;ShowTimestamp -maxCpuCount:2 -property:Configuration=%BUILD_CONFIG% Bubblebobble_Termproject_28\Bubblebobble_Termproject_28.vcxproj
