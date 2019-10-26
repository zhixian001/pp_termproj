outfile = new ActiveXObject("Scripting.FileSystemObject");
out_f = outfile.CreateTextFile("buildscript2.bat", true);

out_f.WriteLine("@echo off");
out_f.WriteLine("echo Start build!");
out_f.WriteLine("@echo on");

src_dir = "src\\";
build_dir = "build\\";
names = ["WireShape3D", "WireSphere", "WireTeapot", "WireTorus"];

tmp = "";



for (i = 0 ; i < names.length ; i++) {
    tmp = "g++ -Iinclude\\ -I\"C:\\MinGW\\freeglut\\include\" -L\"C:\\MinGW\\freeglut\\lib\" -Lsrc -c " + src_dir + names[i] + ".cpp" + " -o build\\" + names[i] + ".o" + " -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows";
    // tmp += " &&^";
    out_f.WriteLine(tmp);
    // WScript.Echo(tmp);
}


out_f.WriteLine("g++ -I\"C:\\MinGW\\freeglut\\include\" -I\"include\" -Lsrc -L\"C:\\MinGW\\freeglut\\lib\" \"src\\run.cpp\" -g \"build\\WireSphere.o\" -g \"build\\WireTorus.o\" -g \"build\\WireTeapot.o\" -g \"build\\WireShape3D.o\" -o run.exe -Wall -lopengl32 -lfreeglut -lglu32 -Wl,--subsystem,windows");

out_f.WriteLine("@echo off");
out_f.WriteLine("echo End of Build Script");
out_f.WriteLine("@echo on");

out_f.close();
