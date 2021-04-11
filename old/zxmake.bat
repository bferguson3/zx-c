@ECHO OFF
del *.bin
del *.tap
sdasz80 -xlos -g sound.rel sound.s
sdasz80 -xlos -g crt0_zx.rel crt0_zx.s
sdcc -c -o app.rel main.c -mz80 --no-std-crt0 --opt-code-speed
sdcc -mz80 --no-std-crt0 --opt-code-speed --nostdlib --code-loc 0x6032 --data-loc 0xc000 -Wl -b_HEADER=0x6000 crt0_zx.rel app.rel sound.rel
hex2bin crt0_zx.ihx
del *.lst
del *.sym
del *.ihx
del *.lk
del *.map
del *.noi
rename crt0_zx.bin app.bin
appmake +zx --binfile app.bin --org 24576
REM speccy app.tap
@ECHO ON
