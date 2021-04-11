default:
#	sdasz80 -xlos -g sound.rel sound.s
#	sdasz80 -xlos -g crt0_zx.rel crt0_zx.s
	if [ ! -d 'out' ]; then mkdir out; fi 
	sdcc -c -o out/app.rel src/main.c -mz80 --no-std-crt0 --opt-code-speed
	sdcc -mz80 --no-std-crt0 --opt-code-speed --nostdlib --code-loc 0x6032 --data-loc 0xc000 out/app.rel -o out/app.ihx
#	sdcc -mz80 --no-std-crt0 --opt-code-speed --nostdlib -Wl crt0_zx.rel app.rel sound.rel -o app.ihx
	python hex2bin.py out/app.ihx out/app.bin
	./bin2tap -b out/app.bin -e 24626 -o app.tap 
	rm -rf *.ihx 
	rm -rf *.lk 
	rm -rf *.noi 
	rm -rf *.rel 

clean:
	rm -rf out
	rm -rf *.tap 
