# Benchmarks

## Hangover
### Hangover Preview (2023-10-12, 32-Bit)

I finally made some new benchmarks. This time with [y-cruncher](http://numberworld.org/y-cruncher/), as Hangover currently only supports 32-bit applications. Under the full diagram I added a "zoom" on fexcore.dll and box64cpu.dll. Values are the average of 3 runs. The diagrams are in seconds, so less is better.

Setup:

- Wine: Hangover 8.17 + fixes/improvements + updated Box64 to b9ea4983f93b93c5b72d6cbb14269cecc54eb8aa (this and more will be part of the next release)
- Box64: b9ea4983f93b93c5b72d6cbb14269cecc54eb8aa
- FEXCore: FEX-2310 + Hangover modifications (same as Hangover 8.17)

y-cruncher v0.8.1.9317 settings:

- 0 "Benchmark Pi  (all in ram)"
- 0 "Single-Threaded"
- 1 "25,000,000" (Decimal Digits)

Note: "box64+wine" means Wine 8.17 running under Box64

![y-cruncher benchmark][2023-10-12-p4p1]
![y-cruncher benchmark zoomed][2023-10-12-p4p2]

[2023-10-12-p4p1]: 2023-10-12/04-P4P.exe.1.png
[2023-10-12-p4p2]: 2023-10-12/04-P4P.exe.2.png

The y-cruncher benchmark is calculating a lot but doesn't touch the win32 API so much. To show the benefit of combining an emulator with Wine the Hangover way I used yquake2 with timedemo. Here box64cpu.dll performed best, likely because Wine is native and only the application needs to be emulated. The diagram is in FPS, so more is better.

Yamagi Quake II 8.20 settings:

- Map: q2demo1.dm2
- Resolution: 1920x1080
- Renderer: OpenGL 1.4
- VSync: Off
- Multisampling: Off
- Native Fullscreen

Note: "box64+wine" means Wine 8.17 running under Box64

![yquake2 benchmark][2023-10-12-yquake2]

[2023-10-12-yquake2]: 2023-10-12/yquake2.exe.png

This result is special, it proofs that only emulating the application is faster than emulating wine+application.

### System changed!

So while the new benchmarks are also done on the same Pi400 and I turned off overclocking to at least mimic the same foundation as 2021, it now runs a newer OS, Box64, Wine, compiler and so on. So let's compare what happened to put Hangover benchmarks into context.

![dhry164int64.exe benchmark][2021-2023-dhry1]
![dhry264int64.exe benchmark][2021-2023-dhry2]
![linpack64.exe benchmark][2021-2023-linpa]

[2021-2023-dhry1]: 2021-2023/dhry164int64.exe.png
[2021-2023-dhry2]: 2021-2023/dhry264int64.exe.png
[2021-2023-linpa]: 2021-2023/linpack64.exe.png

## Hangover-Classic
### Box64 (2021-09-13, 64-Bit)

This is Hangover (f3fa090ccd795ad72d71b4bdb45de72790b30860) compared to Box64 (c3ef6380a7baa6457974fe2eca1652dff6808cca) on a Raspberry Pi400:

![dhry164int64.exe benchmark][2021-09-13-dhry1]
![dhry264int64.exe benchmark][2021-09-13-dhry2]
![linpack64.exe benchmark][2021-09-13-linpa]

[2021-09-13-dhry1]: 2021-09-13/dhry164int64.exe.png
[2021-09-13-dhry2]: 2021-09-13/dhry264int64.exe.png
[2021-09-13-linpa]: 2021-09-13/linpack64.exe.png
