![Amir Mohammad Jahani - MyOS Creator](docs/author/amir-developer.jpg)

# 🚀 MyOS v1.0 - Open Source Operating System

## 👨‍💻 Creator: Amir Mohammad Jahani
**Age: 14 years old**

---

## 🏆 Historic Achievement

**🌟 First Person to Build an Operating System and Kernel on Mobile Phone using Termux**

A groundbreaking achievement in mobile development history. At just 14 years old, Amir Mohammad Jahani has created a fully functional operating system entirely from a mobile phone using only Termux terminal.

---

## 📱 Platform & Tools

### Development Environment
- **Primary Tool**: Termux (Android Terminal)
- **Text Editor**: Vim/Nano
- **Compiler**: GCC
- **Assembler**: GAS (GNU Assembler)
- **Shell**: Bash
- **Version Control**: Git

### System Requirements
- Android Phone
- Termux App
- Internet Connection (for package installation)
- No GUI IDE needed
- Command Line Only

---

## ✨ Features

### MyOS v1.0 Includes:
- ✅ Custom Bootloader (Assembly)
- ✅ Kernel Implementation (C & Assembly)
- ✅ VGA Text Driver
- ✅ Keyboard Driver (Polling)
- ✅ Interactive Shell
- ✅ Command System
- ✅ Memory Management
- ✅ Process Management
- ✅ Open Source (Free to modify and fork)

---

## 🎯 Available Commands

```bash
help     - Show available commands
about    - About MyOS
clear    - Clear the screen
echo X   - Print text to screen
reboot   - Restart the system
halt     - Stop the CPU
```

---

## 📦 Project Structure

```
MyOS/
├── kernel/
│   ├── boot_sect.S       # Bootloader (Real Mode → Protected Mode)
│   ├── kernel_entry.S    # Kernel entry point
│   ├── kernel.c          # Main kernel with drivers
│   └── kernel.ld         # Linker script
├── build.sh              # Build script
├── os-image.bin          # Compiled OS image
└── README.md             # This file
```

---

## 🔧 Building MyOS

### Prerequisites
```bash
# Install required tools in Termux
pkg install build-essential
pkg install binutils
pkg install gcc
pkg install git
```

### Compile
```bash
chmod +x build.sh
./build.sh
```

### Run on Emulator
```bash
qemu-system-i386 -drive format=raw,file=os-image.bin
```

---

## 💡 What Makes This Special

1. **Age**: 14 years old - one of the youngest OS developers
2. **Platform**: Built entirely on mobile phone (Termux)
3. **No IDE**: Pure command-line development
4. **Open Source**: Free for anyone to learn from and improve
5. **Educational**: Perfect learning resource for OS development
6. **Complete**: Full bootloader, kernel, and shell implementation

---

## 🌍 About the Developer

**Amir Mohammad Jahani**
- 🎓 Age: 14 years old
- 💻 Self-taught programmer
- 🔧 OS & Systems developer
- 📱 Mobile development pioneer
- 🏆 Historic achievement holder

### Skills:
- Assembly Language (x86)
- C Programming
- Bash Scripting
- Operating System Design
- Kernel Development
- Hardware-level Programming

### Development Setup:
- **Dual Monitor Setup** (as seen in photo)
- **Termux Terminal** on Android
- **Professional coding environment** on mobile

---

## 📸 Meet the Creator

*Amir Mohammad Jahani (14 years old) developing MyOS using Termux on Android with dual-monitor professional setup.*

---

## 🚀 Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/amirmohammadjahani04-collab/MyOS
   cd MyOS
   ```

2. **Install dependencies**
   ```bash
   pkg install build-essential binutils gcc
   ```

3. **Build the OS**
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

4. **Run on QEMU**
   ```bash
   qemu-system-i386 -drive format=raw,file=os-image.bin
   ```

---

## 📚 Learning Resources

This project is perfect for learning:
- **Bootloader Development**
- **Protected Mode Switching**
- **Kernel Programming**
- **Driver Development**
- **Shell Implementation**
- **Assembly Language**
- **Operating System Design**

---

## 📝 License

**Open Source** - Free to modify, fork, and improve

Anyone can:
- ✅ Use the code
- ✅ Modify it
- ✅ Learn from it
- ✅ Improve it
- ✅ Share it

---

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Fork the project
- Make improvements
- Submit pull requests
- Report issues
- Suggest features

---

## 📞 Contact & Social

- **GitHub**: [@amirmohammadjahani04-collab](https://github.com/amirmohammadjahani04-collab)
- **Project**: MyOS v1.0 Open Source

---

## 🎉 Acknowledgments

Special thanks to:
- The Termux community
- Open source software enthusiasts
- All learners and developers who use this project

---

## 🌟 Star History

If you found this project interesting, please consider starring it! ⭐

---

**Last Updated**: June 19, 2026

**Status**: Active Development

**Version**: 1.0 (Stable)

---

### 💪 Built with passion on mobile. Built to inspire millions.

**MyOS - Bringing OS Development to Everyone's Pocket** 📱🔥

---

## 🎯 Why This Project Matters

- **Breaks barriers**: Shows what's possible with just a mobile phone
- **Inspires youth**: Proves age is no limit to becoming a developer
- **Educational**: Perfect resource for learning OS development
- **Open for all**: Anyone can learn from and improve this project
- **Historic**: First OS built entirely on mobile with Termux

**Thank you for supporting MyOS!** 🚀⭐
