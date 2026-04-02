# FN Base - Fortnite External Cheat Base

**Educational Project Only**

FN Base is a clean external Fortnite cheat base written in C++ for educational and learning purposes only. It demonstrates modern external game hacking techniques using a custom kernel driver.

> ⚠️ Important: This project is strictly for educational purposes. Using cheats in online games violates Fortnite's Terms of Service and can result in permanent account or hardware bans. Use responsibly and only for learning or in offline environments.

---

## Features

### 🎯 Aimbot
- Smooth aimbot with adjustable smoothness
- Customizable FOV with optional circle display
- Multiple aim keys (Left Mouse / Right Mouse)
- Triggerbot support

### 👁️ Visuals (ESP)
- Box ESP (Normal & Cornered styles)
- Filled box option
- Skeleton ESP with proper bone connections
- Snaplines
- Distance display
- Visibility check (white = visible, red = not visible)

### ⚡ Exploits / Misc
- FOV Changer
- Spinbot
- Player Size Changer
- Car Fly (hold Space)
- Rapid Fire

### 💾 Configuration System
- Save and load multiple configs
- Easy config management directly in the menu
- Persistent settings

### 🎨 Menu & Overlay
- Clean ImGui-based menu with custom dark theme
- DirectX 9 overlay
- Embedded custom fonts and icons
- Watermark with FPS and real-time clock
- Insert key to toggle menu

---

## Technical Overview

- Fully external cheat (no DLL injection)
- Custom kernel driver communication (\\\\.\\0XploitUD)
- Physical memory read/write
- CR3 fetching and base address resolution
- World decryption support
- Bone matrix reading & World-to-Screen projection
- Direct memory writes for exploits

---

## Project Structure

FN Base/
├── driver/                 # Kernel driver interface
├── game/
│   ├── aim/                # Aimbot logic
│   ├── esp/                # ESP drawing functions
│   └── exploits/           # Feature exploits
├── render/                 # ImGui + D3D9 rendering
├── sdk and offsets/        # Game structures, offsets & decryption
├── other/                  # Config system, settings, input
├── includes.hpp
└── main.cpp

---

## Disclaimer

**This project is for educational purposes only.**

It is intended to help developers learn:
- Kernel-user mode communication
- External memory manipulation
- Game reverse engineering
- Overlay rendering with ImGui
- Math behind ESP and aimbot systems

The author is not responsible for any bans or damage caused by misuse of this project.

---

## Credits

- Developed as an educational project by **0Xploit**
- ImGui library for the menu
- STB TrueType for font rendering
- KDmapper for the mapper

---

**Made with ❤️ for the reverse engineering and game hacking learning community.**
