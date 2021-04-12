const unsigned char str[] = "Hello World!\x00";
unsigned char b;

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