# Atari 800XL LLVM-MOS Test Project

A test project demonstrating 6502 development for the Atari 800XL using the llvm-mos compiler toolchain.

## Project Description

This project contains a simple test application that:
- Displays text on the Atari 800XL screen
- Shows a counter that increments continuously
- Cycles through background colors
- Demonstrates basic screen memory manipulation

## Prerequisites

### 1. LLVM-MOS Compiler

Install llvm-mos from the official repository:

```bash
# On macOS, you can build from source or use a prebuilt release
# Download the latest release from:
# https://github.com/llvm-mos/llvm-mos-sdk/releases

# Example installation (adjust for your system):
cd ~/Downloads
wget https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-macos.tar.xz
tar xf llvm-mos-macos.tar.xz
sudo mv llvm-mos /opt/
export PATH="/opt/llvm-mos/bin:$PATH"
```

Add the export line to your `~/.zshrc` or `~/.bash_profile` to make it permanent:

```bash
echo 'export PATH="/opt/llvm-mos/bin:$PATH"' >> ~/.zshrc
```

### 2. Atari Emulator

Install an Atari 800 emulator to test your programs:

```bash
# On macOS with Homebrew:
brew install atari800
```

Alternative emulators:
- **Altirra** (Windows, excellent debugger)
- **Atari800MacX** (macOS native)
- **Atari++** (Cross-platform)

### 3. ATR Disk Image Tools (Optional)

To create ATR disk images:

```bash
# dir2atr tool
git clone https://github.com/jhallen/dir2atr.git
cd dir2atr
make
sudo cp dir2atr /usr/local/bin/
```

## Building the Project

### Quick Build

```bash
make
```

This will:
1. Compile the C source files
2. Link them into an ELF executable
3. Convert to Atari XEX format
4. Attempt to create an ATR disk image (if tools are available)

### Build Targets

- `make all` - Build everything (default)
- `make clean` - Remove all build artifacts
- `make rebuild` - Clean and rebuild
- `make info` - Display build information
- `make run` - Build and run in emulator (requires atari800)

## Output Files

- `build/atari-test.elf` - ELF executable (intermediate format)
- `dist/atari-test.xex` - Atari executable format (load this in emulator)
- `dist/atari-test.atr` - ATR disk image (optional)

## Running the Program

### Method 1: Direct XEX Loading

```bash
# If you have atari800 emulator installed:
make run

# Or manually:
atari800 -xl -nobasic dist/atari-test.xex
```

### Method 2: Using ATR Disk Image

1. Load your emulator
2. Boot with the ATR image as disk 1
3. The program should auto-run, or use the DOS menu to load it

### Method 3: Manual Emulator Loading

1. Start your Atari emulator
2. Configure it for Atari 800XL mode
3. Load the XEX file from the File menu
4. The program should start automatically

## Project Structure

```
atari-llvm-mos-test/
├── src/
│   └── main.c          # Main test application
├── build/              # Build artifacts (generated)
├── dist/               # Distribution files (generated)
├── Makefile            # Build system
└── README.md           # This file
```

## How It Works

The test program demonstrates:

1. **Screen Memory Access**: Direct manipulation of Atari screen memory at $3C00
2. **ATASCII Conversion**: Converting ASCII text to Atari screen codes
3. **Color Registers**: Setting background and border colors via hardware registers
4. **PEEK/POKE Operations**: Direct memory read/write operations
5. **Main Loop**: Continuous counter display with color cycling

## Customization

### Changing Colors

Edit the `set_colors()` call in `main.c`:

```c
set_colors(0x84, 0x7C);  // bg, border
```

Atari color values range from 0x00 to 0xFF (hue and luminance).

### Modifying Text

Edit the `print_at()` calls:

```c
print_at(x, y, "Your text here");
```

Screen coordinates: x (0-39), y (0-23) for text mode.

## Troubleshooting

### Compiler Not Found

```
make: mos-atari8-clang: No such file or directory
```

**Solution**: Ensure llvm-mos is installed and in your PATH.

### Blank Screen in Emulator

**Possible causes**:
- Program crashed or hung
- Wrong emulator settings (try XL mode with BASIC disabled)
- Check emulator console for error messages

### ATR Creation Failed

**Solution**: The XEX file works fine in emulators. ATR creation is optional. Install `dir2atr` if you need ATR images.

## Resources

- [LLVM-MOS Documentation](https://llvm-mos.org/)
- [LLVM-MOS SDK GitHub](https://github.com/llvm-mos/llvm-mos-sdk)
- [Atari 8-bit Memory Map](https://www.atariarchives.org/mapping/)
- [Atari800 Emulator](https://atari800.github.io/)
- [Altirra Emulator](https://www.virtualdub.org/altirra.html)

## Next Steps

- Explore joystick input
- Add sound (POKEY chip programming)
- Implement graphics modes
- Create more complex programs
- Study the llvm-mos SDK examples

## License

This is a test/demo project. Feel free to use and modify as needed.
