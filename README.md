# Battle Engine

[Coding Style](CODING_STYLE.md)

# Dependency

## V8
We use v8 from google as script engine
### 1st step
Please use command line
```
$> 3rdparty/install.sh
```
To install 3rdparty dependencies. Windows portability not fully automatically supported without cygwin.
You may have to build the project through extra command line.


### 2nd step
Build v8

If you are on linux or mac with a make support
```
make -C 3rdparty/v8 x64.release -j8
```

If you are on Windows, hopefully type this in your command line will generate a visual studio project file so that then you can open it up and compile the lib
```
python.exe 3rdparty\v8\build\gyp_v8 -Dtarget_arch=x64
```
Where python.exe is probably under ```3rdparty\depot_tools\third_party```