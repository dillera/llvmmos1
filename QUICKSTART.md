# Quick Start Guide

## 1. Check Your Setup

Run the setup check script:

```bash
./check-setup.sh
```

This will verify that you have all necessary tools installed.

## 2. Install LLVM-MOS (if needed)

If you don't have llvm-mos installed:

```bash
# Download the latest macOS release
cd ~/Downloads
curl -LO https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-macos.tar.xz

# Extract and install
tar xf llvm-mos-macos.tar.xz
sudo mv llvm-mos /opt/

# Add to your PATH (for zsh)
echo 'export PATH="/opt/llvm-mos/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc

# Verify installation
mos-atari8-clang --version
```

## 3. Build the Test Program

```bash
make
```

This creates:
- `dist/atari-test.xex` - Atari executable file
- `dist/atari-test.atr` - ATR disk image (if tools available)

## 4. Run in Emulator

### Option A: Using the included run target

```bash
make run
```

### Option B: Manual emulator launch

If you have atari800 installed:

```bash
atari800 -xl -nobasic dist/atari-test.xex
```

### Option C: Using your preferred emulator

1. Open your Atari emulator
2. Set it to **Atari 800XL** mode
3. Disable BASIC (if option available)
4. Load `dist/atari-test.xex`

## What You Should See

When the program runs, you'll see:
- A title "LLVM-MOS TEST PROGRAM"
- Text indicating it's built with llvm-mos compiler
- A counter that increments continuously
- The background color cycling through different hues

## Troubleshooting

**Problem**: `mos-atari8-clang: command not found`
- **Solution**: Install llvm-mos and add it to your PATH (see step 2)

**Problem**: Blank screen in emulator
- **Solution**: Make sure you're in 800XL mode with BASIC disabled

**Problem**: ATR creation failed
- **Solution**: This is optional. The XEX file works fine in all emulators

## Next Steps

- Edit `src/main.c` to modify the program
- Run `make rebuild` to clean and rebuild
- Explore the llvm-mos SDK documentation
- Try adding joystick input, sounds, or graphics

## Emulator Recommendations

- **macOS**: atari800 (via Homebrew) or Atari800MacX
- **Windows**: Altirra (best debugger)
- **Linux**: atari800
- **All Platforms**: Atari++ or online emulators

Enjoy retro computing!
