clone windows_v8 depot from gitlab into 3rdparty/v8/
You should find a lib and a include directory

Now if you configure with cmake, it will generate sln file

Open it, and goto property of BattleEngine, change its platform from WIN32 to x64
//may be confusing to change

compile BattleEngine

You can find the binary in x64\Debug\BattleEngine.exe in build
If some dll is missing, copy paste them from 3rdparty/v8/lib into where the exe is

under folder build, you should be able to launch:
```
x64\Debug\BattleEngine.exe < ..\assets\sample.json
```

