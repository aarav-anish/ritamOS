# Kernel

It tells hardware what to do.  
It tells CPU what process to run.  
It decides where in memory the data is stored.  
It talks to devices like keyboard.

This schemantic is somewhat misleading as kernel itself lives in memory.

The kernel provides instructions that the CPU executes.  
And there are ways to display letters on the screen.  
And there are also ways to receive input.

## Installing the tools that we need for development (build tools, bootloader and an emulator):  
> sudo apt install 
    build-essential
    binutils
    nasm
    bochs
    bochs-sdl
    grub-pc-bin
    grub-common
    xorriso
    vgabios

## How to use these tools for building the kernel?  
- The kernel or any OS is started by going through a boot process.  
- Ater the computer is turned ON the computer jumps to specific memory location.  
- And in that location lives the BIOS.  
- The BIOS runs some tests and looks for a bootloader and transfers control to it.  
- And the bootloader then looks for our kernel, loads it into memory and jumps to its entry point.  

```mermaid
flowchart LR
    A[BIOS] --> B[Bootloader] --> C[Kernel]
```

- To run a kernel we have to provide a bootloader and a kernel binary.  
- We use GRUB as a bootloader. So we then pack GRUB and our kernel into a bootable ISO file.  
- After that we can use and emulator to boot from this ISO file.  
- Our insatlled emulator is Bochs.

```ascii
┌──────────────────────────────────────────────────────┐
│                                                      │
│                       Bochs                          │
│                                                      │
│    ┌────────────────────────────────────────────┐    │
│    │                                            │    │
│    │  ┌─────────────────┐  ┌─────────────────┐  │    │
│    │  │      GRUB       │  │      Kernel     │  │    │
│    │  └─────────────────┘  └─────────────────┘  │    │
│    │                                            │    │
│    │                  OS.iso                    │    │
│    │                                            │    │
│    └────────────────────────────────────────────┘    │
│                                                      │
└──────────────────────────────────────────────────────┘
```
