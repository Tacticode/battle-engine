# Battle Engine

[Coding Style](CODING_STYLE.md)

# Dependency

## V8
We use v8 from google as script engine
### Unix/Linux with make support
Please use command line
```
$> 3rdparty/install.sh
$> make -C 3rdparty/v8 x64.release -j8
```
Where the x64.release is the target architecture. Note: for now FindV8.cmake has this x64.release hard coded, so just got with x64.release for now (tested by Wilko and Hengrui)

To install 3rdparty dependencies. Windows portability not fully automatically supported without cygwin.
You may have to build the project through extra command line.

### Windows Command line
The below is tested on my epi computer, no-cygwin environment
- [instruction](https://www.chromium.org/developers/how-tos/install-depot-tools), or direct download link [here](https://storage.googleapis.com/chrome-infra/depot_tools.zip)
- Unzip it into a folder, let's say PATH_DEPOT_TOOLS (eg. d:\somepath\ ), be sure that the full path is accessible without any space!, that is, "Program Files/depot_tools" for example, won't work
- Go to your configuration panel, by right clicking your computer and select property -> advanced configuration -> environment variables; Then add an entry, PATH, set it to be the folder where you extracted your depot_tools.
- Now open up a cmd terminal, validate previous step by typing gclient. You should be able to see gclient fetching some dependencies such as windows git, svn, etc. don't worry, let it run for a while
- cd to a directory (eg. d:\somepath\ ) where you would like to download v8. Just any arbitrary place outside of the battle-engine project directory.
```
> set DEPOT_TOOLS_WIN_TOOLCHAIN=0
> fetch v8
> gclient sync
```
- `fetch v8`, this could take quite a while. You can see the folder size of v8 grow overtime, don't worry for it... around 20 minutes
- `gclient sync`, this will make some update to gyp files, used to generate build of project, then you should see a line `Updating gypfiles` upon succed. Could take a while around 10 min.
-You should also set variable for your version of visual studio, if you are not using default 2013. `set GYP_MSVS_VERSION=2015`.
- `python.exe v8\gypfiles\gyp_v8 -Dtarget_arch=ia32`, where ia32 can be replaced by `x64` depends on your architecture. (I tested only ia32)
- Now you should be able to find an all.sln or similar under gypfiles
- There is just maybe one more thing to do. Take a look for presence of `cygwin` under third_party of folder v8. You should find a setup_env.bat, you may need to add your path and python_path to that of `python_276` under `depot_tools`. Come back to this step if you see any error message like `bash: python command not found`.
example of my setup_env.bat
```
...
set "PATH=%PATH%;E:\programmation\depot_tools\python276_bin\"
set "PYTHONPATH=E:\programmation\depot_tools\python276_bin\"
```
- Open the file using visual studio. Select the projects under folder `src`, including (v8, v8_base0) etc, so that you avoid compiling test cases. 
- Everything compile just fine under Debug for now (tested). tho some issues remain to compile under Release.
- Now you should find `v8/include`, `v8/build/Debug/`, where under debug you would find the following libs that are necessary
```
lib/v8_base_[0-3].lib, lib/v8_libbase.lib
lib/v8_nosnapshot.lib, lib/icuuc.lib, lib/icui18n.lib
lib/v8_libsampler.lib, lib/v8_libplatform.lib
```
- Copy paste those under `3rdparty/v8`, battle-engine looks for the following files under`3rdparty/v8`
```
lib/
include/
natives_blob.bin
snapshot_blob.bin
```

Use Cmake-gui or any ccmake to configure battle-engine.
Check the box for V8, and configure
All lib files should have a path except for the two binary blob files which are optional.
Generate the project
Open it with visual studio
Compile and chill :D

Note on 10/June: I am not sure yet but you may run into thread library problem upon compilation, then you may go to properties, find a option which you may choose for MD/MDT. and change it to whats unmatched in error message

Edit 11/June: Last tested with paul-maxime, this actually works, GG!