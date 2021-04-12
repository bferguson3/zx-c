typedef const unsigned char String[];
typedef unsigned char u8;
typedef unsigned int u16;

#define FLASH (1<<7)
#define BRIGHT (1<<6)
#define PAPER(n) (n<<3)
#define INK(n) n 
#define VRAM_BASE 0x4000
#define CRAM_BASE 0x5800

String str = "Hello World!\x00";
unsigned char b;
u16 temp;

u16 GetVRAMPos(u8 x, u8 y);

void main()
{
    inits();
    
    volatile u8* p;
    // Draw a line 
    p = (u8*)(VRAM_BASE + 3);
    *p = 255;
    // Draw a dotted line
    temp = GetVRAMPos(15, 30);
    p = (u8*)temp;
    *p = 0b10101010;
    // Set color to red on pink
    p = (u8*)CRAM_BASE + 3;
    *p = BRIGHT|PAPER(3)|INK(2);
    
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
        
        ld      a, b 
        and     #0b00000111
        or      #0b01000000
        ld      h, a 
        ld      a, b 
        rra 
        rra 
        rra 
        and     #0b00011000
        or      h 
        ld      h, a 
        ld      a, b 
        rla 
        rla 
        and     #0b11100000 
        ld      l, a 
        ld      a, c 
        rra     
        rra     
        rra     
        and     #0b00011111
        or      l 
        ld      l, a 
    
        pop	    ix
        ret
    __endasm;
    // Return in HL
}