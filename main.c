
int main(void)
{
    volatile unsigned char* p;
    p = (unsigned char*)(0x4000 + 3);
    *p = 255;
    return 0;
}
