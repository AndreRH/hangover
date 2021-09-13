# Benchmarks

## box64

So according to some tests box64+dynarec is about 31 times faster than without dynarec.
Wine refuses to run in box64 without dynarec, so there's no direct comparison between Hangover and pure box64.
This is Hangover (f3fa090ccd795ad72d71b4bdb45de72790b30860) compared to box64 (c3ef6380a7baa6457974fe2eca1652dff6808cca) on a Raspberry Pi 400:

![dhry164int64.exe benchmark][dhry1]
![dhry264int64.exe benchmark][dhry2]
![linpack64.exe benchmark][linpa]

[dhry1]: dhry164int64.exe.png
[dhry2]: dhry264int64.exe.png
[linpa]: linpack64.exe.png