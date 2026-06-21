/* kernel.c - minimal freestanding kernel with VGA text driver, keyboard
 * polling driver, and a tiny command shell. No libc, no OS underneath. */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/* ---------------- low-level port I/O ---------------- */
static inline u8 inb(u16 port) {
    u8 ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(u16 port, u8 val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

/* ---------------- VGA text mode driver ---------------- */
#define VGA_ADDRESS   0xb8000
#define VGA_WIDTH     80
#define VGA_HEIGHT    25
#define WHITE_ON_BLACK 0x0f

static u16 *vga_buffer = (u16 *) VGA_ADDRESS;
static int cursor_row = 0;
static int cursor_col = 0;

static void update_hw_cursor(void) {
    u16 pos = cursor_row * VGA_WIDTH + cursor_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((pos >> 8) & 0xFF));
}

static void scroll_if_needed(void) {
    if (cursor_row < VGA_HEIGHT) return;
    for (int row = 1; row < VGA_HEIGHT; row++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            vga_buffer[(row - 1) * VGA_WIDTH + col] = vga_buffer[row * VGA_WIDTH + col];
        }
    }
    for (int col = 0; col < VGA_WIDTH; col++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = (u16)(' ' | (WHITE_ON_BLACK << 8));
    }
    cursor_row = VGA_HEIGHT - 1;
}

static void clear_screen(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = (u16)(' ' | (WHITE_ON_BLACK << 8));
    }
    cursor_row = 0;
    cursor_col = 0;
    update_hw_cursor();
}

static void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            vga_buffer[cursor_row * VGA_WIDTH + cursor_col] = (u16)(' ' | (WHITE_ON_BLACK << 8));
        }
    } else {
        vga_buffer[cursor_row * VGA_WIDTH + cursor_col] = (u16)(c | (WHITE_ON_BLACK << 8));
        cursor_col++;
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }
    scroll_if_needed();
    update_hw_cursor();
}

static void print_string(const char *s) {
    while (*s) {
        print_char(*s);
        s++;
    }
}

/* ---------------- tiny string helpers (no libc available) ---------------- */
static int str_eq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

static int str_starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s != *prefix) return 0;
        s++; prefix++;
    }
    return 1;
}

static int str_len(const char *s) {
    int n = 0;
    while (s[n]) n++;
    return n;
}

/* ---------------- keyboard driver (polling, US layout, scancode set 1) ---------------- */
#define KBD_DATA_PORT   0x60
#define KBD_STATUS_PORT 0x64

static const char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0, 'a','s','d','f','g','h','j','k','l',';','\'','`',
    0, '\\','z','x','c','v','b','n','m',',','.','/', 0,
    '*', 0, ' ', 0,
    /* rest unused for this minimal shell */
};

static char read_char_blocking(void) {
    while (1) {
        /* wait until the keyboard controller's output buffer is full */
        if (inb(KBD_STATUS_PORT) & 0x01) {
            u8 scancode = inb(KBD_DATA_PORT);
            if (scancode & 0x80) {
                continue; /* key release, ignore */
            }
            if (scancode < 128) {
                char c = scancode_to_ascii[scancode];
                if (c) return c;
            }
        }
    }
}

/* ---------------- shell ---------------- */
#define LINE_MAX 128

static void reboot(void) {
    print_string("\nRebooting...\n");
    u8 good = 0x02;
    while (good & 0x02) good = inb(0x64);
    outb(0x64, 0xFE);
    __asm__ volatile ("hlt");
}

static void halt_system(void) {
    print_string("\nSystem halted. You can close the emulator now.\n");
    __asm__ volatile ("cli");
    while (1) { __asm__ volatile ("hlt"); }
}

static void print_prompt(void) {
    print_string("minios> ");
}

static void handle_command(char *line) {
    if (str_len(line) == 0) {
        return;
    } else if (str_eq(line, "help")) {
        print_string("Available commands:\n");
        print_string("  help    - show this message\n");
        print_string("  about   - about this mini OS\n");
        print_string("  clear   - clear the screen\n");
        print_string("  echo X  - print X back to the screen\n");
        print_string("  reboot  - restart the machine\n");
        print_string("  halt    - stop the CPU\n");
    } else if (str_eq(line, "about")) {
        print_string("Mini-OS - a minimal educational kernel.\n");
        print_string("Built with a hand-written bootloader, a tiny\n");
        print_string("protected-mode switch, and a polling keyboard driver.\n");
    } else if (str_eq(line, "clear")) {
        clear_screen();
    } else if (str_starts_with(line, "echo ")) {
        print_string(line + 5);
        print_string("\n");
    } else if (str_eq(line, "echo")) {
        print_string("\n");
    } else if (str_eq(line, "reboot")) {
        reboot();
    } else if (str_eq(line, "halt")) {
        halt_system();
    } else {
        print_string("Unknown command: ");
        print_string(line);
        print_string("\n");
        print_string("Type 'help' for a list of commands.\n");
    }
}

static void shell_loop(void) {
    char line[LINE_MAX];
    int pos;

    while (1) {
        print_prompt();
        pos = 0;
        line[0] = 0;

        while (1) {
            char c = read_char_blocking();
            if (c == '\n') {
                line[pos] = 0;
                print_char('\n');
                break;
            } else if (c == '\b') {
                if (pos > 0) {
                    pos--;
                    print_char('\b');
                }
            } else if (pos < LINE_MAX - 1) {
                line[pos++] = c;
                print_char(c);
            }
        }

        handle_command(line);
    }
}

/* ---------------- kernel entry point (called from kernel_entry.S) ---------------- */
void kmain(void) {
    clear_screen();
    print_string("Mini-OS booted successfully!\n");
    print_string("Type 'help' to see available commands.\n\n");
    shell_loop();
}
