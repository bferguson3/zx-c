typedef const unsigned char String[];
typedef unsigned char u8;
typedef unsigned int u16;

const unsigned char str[] = "Hello World!\x00";
unsigned char b;

u16 GetVRAMPos(u8 x, u8 y);

void main()
{
    inits();
    volatile unsigned char* p;
    p = (unsigned char*)(0x4000 + 3);
    *p = 255;
    while(1){ }
    return;
}

static void inits()
{
    b = 22;
    return;
}

u16 GetVRAMPos(u8 x, u8 y) __naked
{
    __asm 
    	push	ix
        ld	    ix,#0
        add	    ix,sp
        
        ld	    b, 4 (ix)
        ld	    c, 5 (ix)
        
      /*  
        push	ix
        ld	ix,#0
        add	ix,sp
    ;src/main.c:28: return x + y;
        ld	c, 4 (ix)
        ld	b, #0x00
        ld	l, 5 (ix)
        ld	h, #0x00
        add	hl, bc
    ;src/main.c:30: __endasm;
    ;src/main.c:31: }
        pop	ix
        ret
    */
        pop	    ix
        ret
    __endasm;
    // Return in HL
}