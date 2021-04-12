CC=sdcc 
AS=sdasz80
LD=sdldz80
BINTAP=./bin2tap
CFLAGS=-mz80 --no-std-crt0 --opt-code-speed --nostdlib 
CODELOC=32768
DATALOC=0x6000
LDSCR=zx.lk

default:
	if [ ! -d 'out' ]; then mkdir out; fi 
	${CC} ${CFLAGS} --code-loc ${CODELOC} --data-loc ${DATALOC} -S -o out/main.s src/main.c
	${AS} -o out/main.rel out/main.s 
	${LD} -f ${LDSCR} out/main.ihx out/main.rel 
	python hex2bin.py out/main.ihx out/main.bin
	${BINTAP} -b out/main.bin -e ${CODELOC} -o app.tap 
#	rm -rf out/*.ihx out/*.lk out/*.noi out/*.rel out/*.lst out/*.map out/*.sym 

run: default
	fuse app.tap

deps:
#	sdasz80 -xlos -g sound.rel sound.s
#	sdasz80 -xlos -g crt0_zx.rel crt0_zx.s


clean:
	rm -rf out *.tap 
