#!/bin/bash
# Setup verification script for Atari 800XL LLVM-MOS project

echo "========================================="
echo "Atari 800XL LLVM-MOS Setup Check"
echo "========================================="
echo ""

# Check for llvm-mos compiler
echo "Checking for LLVM-MOS compiler..."
if command -v mos-atari8-clang >/dev/null 2>&1; then
    echo "✓ mos-atari8-clang found at: $(which mos-atari8-clang)"
    mos-atari8-clang --version 2>/dev/null | head -n 1
else
    echo "✗ mos-atari8-clang NOT FOUND"
    echo "  Please install LLVM-MOS SDK from:"
    echo "  https://github.com/llvm-mos/llvm-mos-sdk/releases"
fi
echo ""

# Check for Atari emulator
echo "Checking for Atari 800 emulator..."
if command -v atari800 >/dev/null 2>&1; then
    echo "✓ atari800 emulator found at: $(which atari800)"
else
    echo "✗ atari800 emulator NOT FOUND"
    echo "  Install with: brew install atari800"
    echo "  Or download from: https://atari800.github.io/"
fi
echo ""

# Check for ATR tools
echo "Checking for ATR disk image tools..."
if command -v dir2atr >/dev/null 2>&1; then
    echo "✓ dir2atr found at: $(which dir2atr)"
elif command -v atr >/dev/null 2>&1; then
    echo "✓ atr tool found at: $(which atr)"
else
    echo "⚠ ATR creation tools NOT FOUND (optional)"
    echo "  XEX files work fine without ATR images"
    echo "  Install dir2atr from: https://github.com/jhallen/dir2atr"
fi
echo ""

# Check for make
echo "Checking for build tools..."
if command -v make >/dev/null 2>&1; then
    echo "✓ make found at: $(which make)"
else
    echo "✗ make NOT FOUND"
    echo "  Install Xcode Command Line Tools:"
    echo "  xcode-select --install"
fi
echo ""

echo "========================================="
echo "Setup check complete!"
echo ""

if command -v mos-atari8-clang >/dev/null 2>&1 && command -v make >/dev/null 2>&1; then
    echo "You're ready to build! Run: make"
else
    echo "Please install missing components above."
fi
echo "========================================="
