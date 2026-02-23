// kernel.c
//  -ffreestanding -m32

void kernel_main(void) {
    char* video = (char*)0xB8000; // VGA text mode
    const char* msg = "Slay game from Floptropica 😎";

    for (int i = 0; msg[i] != '\0'; i++) {
        video[i * 2] = msg[i];      // symbols
        video[i * 2 + 1] = 0x0F;    // white
    }

    while (1) {
        // slaying game:0
    }
}
void kernel_sencond(void) {
    char* video = (char*)0xB8000; 
    const char* msg = "Kernel sencond"

    for (int i=1; msg[i] != '\0'; i++) {
        video[i * 6] =msg[i];
        video[i * 9 + 1] = 0x0F; 

    }
}