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

### Install the qemu emulator
> sudo apt install qemu-system

## How to use these tools for building the kernel?  
- The kernel or any OS is started by going through a boot process.  
- Ater the computer is turned ON the computer jumps to specific memory location.  
- And in that location lives the BIOS.  
- The BIOS runs some tests and looks for a bootloader and transfers control to it.  
- And the bootloader then looks for our kernel, loads it into memory and jumps to its entry point.  

```ascii
        ┌─────────────────┐      ┌─────────────────┐      ┌─────────────────┐
        │      BIOS       │─────>│   Bootloader    │─────>│     Kernel      │
        └─────────────────┘      └─────────────────┘      └─────────────────┘
```

- To run a kernel we have to provide a bootloader and a kernel binary.  
- We use GRUB as a bootloader. So we then pack GRUB and our kernel into a bootable ISO file.  
- After that we can use the emulator to boot from this ISO file.  
- Our installed emulator is Bochs.  

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

## Memory layout of the kernel binary

### kernel.elf

```ascii
        0x00000000  ┌───────────────────┐
                    │   Reserved        │   (reserved space for CPU's personal workspace)
        0x00100000  ├───────────────────┤
                    │   .multiboot      │   (in this header our kernel tells grub how to start it)
        0x00101000  ├───────────────────┤
                    │   .text           │   (actual kernel code goes here)
        0x00105000  ├───────────────────┤
                    │   .rodata         │   (read only data: usually for string constants and stuff)
        0x0010A000  ├───────────────────┤
                    │   .data           │   (section for initialized variables)
        0x00210000  ├───────────────────┤
                    │   .bss            │   (section for uninitialized variables)
                    └───────────────────┘
```

### Compile the assembly file
```
nasm -f elf32 loader.s -o loader.o
```

### Use linker to build kernel binary
```
ld -T link.ld -melf_i386 loader.o -o kernel.elf
```

### Use grub to build the ISO file
```
mv kernel.elf iso/boot
grub-mkrescue -o ritamOS.iso iso -d /usr/lib/grub/i386-pc
```

### Run bootable ISO in the bochs emulator
```
bochs -f bochsrc.txt
```

### Run bootable ISO in the qemu emulator
```
qemu-system-i386 -cdrom ritamOS.iso
```

## Setup the kernel stack

### .bss

- Reserve some memory in .bss (say 4KB).
- To initialize the stack, we only need to setup the stack pointer to the beginning of the reserved region.
- Use push instructions to push values on the stack.
- The stack pointer then increases automatically.       *(push dword 0x00000008) (doubleword = 4 bytes)*
- When we pop values, the stack pointer decreases automatically.        *(pop eax)*

```ascii
                          ┌───────────────────┐
                          │                   │
                          │                   │ 
                          │                   │ 
                          │                   │ 
        esp=kernel_stack  ├───────────────────┤  kernel_stack
                          │                   │
                          ├───────────────────┤  kernel_stack + 4096 bytes
                          │                   │ 
                          │                   │ 
                          │                   │ 
                          └───────────────────┘
```

### Why we need the stack for function calls ?
**_cdecl calling convention_** (Function calling convention)  

```
test_func(arg1, arg2, arg3);
```
> To call a function with 3 arguments (4 byte each)   
  The convention requires that we push each argument into the stack in opposite order.  
  After we push the arguments in the stack, we call the function.  
  And the call then also pushes return address on the stack and maybe some other stuff.

```ascii
          esp=kernel_stack      ┌────────────────────┐  kernel_stack
                                │       arg3         │
          esp=kernel_stack + 4  ├────────────────────┤
                                │       arg2         │
          esp=kernel_stack + 8  ├────────────────────┤
                                │       arg1         │
                                ├────────────────────┤
                                │   return address   │
                                ├────────────────────┤
                                │   local variables  │
                                ├────────────────────┤
                                │                    │
                                ├────────────────────┤
                                │                    │
                                ├────────────────────┤
                                │                    │
                                └────────────────────┘  kernel_stack + 4096 bytes
```

## Framebuffer

Framebuffer is a memory region within the reserved section in kernal memory.  
It is located at this fixed address and has a size of about 32 kilobytes.  
To display something on the screen, we can write entries with a specific structure into this region.  

Text-based framebuffer that can only display text.  
The idea behind the text-based framebuffer is to divide the screen into 80 columns and 25 rows.  
Each entry in the framebuffer fills one of these cells with a letter.  
Each entry has a size of 2 bytes (16 bits).  

```ascii
    Example: letter X in green with a white background

        ┌─────┐      ┌───────────┐      ┌──────────────┐      ┌────────────────────────────┐
        │  1  │      │  1  1  1  │      │  0  0  1  0  │      │  0  1  0  1    1  0  0  0  │
        └─────┘      └───────────┘      └──────────────┘      └────────────────────────────┘
         blink          bg color           text color                   ASCII code
```

Depending on the mode setup, attribute bit 7 may be either the blink bit  
or the fourth background color bit (which allows all 16 colors to be used as background colors).  
Bit 3 is the bright bit, which turns, for example, blue into light blue.  
For the background color, this bit is repurposed as the blink bit in Bochs.

> Flickering issue in Bochs  
Default Behavior (Blinking Enabled): Bits 0–2 determine the background color,  
and Bit 7 toggles blinking. High-intensity backgrounds are impossible.

These entries are continuously read by the hardware and transformed on the screen.  
Pixel-mode framebuffer is more versatile.

## Cursor and Scrolling

To move the cursor or scroll up and down we send commands to the CRT controller.  
The CRT controller is a chip which manages how text is rendered on the screen.  
It has several registers to control the cursor position, the cursor shape or the display offset.  

To access these registers we have two ports: the command port and the data port.  
The command port takes the index of the register that we want to access.  
The data port takes the value we want to write to that register.  
And to do that we can use CPU's out instruction.  

Suppose, if we want to move the cursor in row 2 and column 5.
The cursor offset would be 0x00A5 (2 * 80 + 5 = 165).  

The data port is only 8 bits wide and we need to write 16 bits, we have to split the value and send the high and low bytes separately.
We first send the index of the cursor postion high byte register to the command port and then the high byte value to the data port.  
The controller then automatically writes values to the register.

> out 0x3D4, 0x0E  
  out 0x3D5, 0x00  
  out 0x3D4, 0x0F  
  out 0x3D5, 0xA5  

Suppose we want to scroll 3 lines, the offset would be 0x00F0 (2 * 80 = 160)
> out 0x3D4, 0x0C  
  out 0x3D5, 0x00  
  out 0x3D4, 0x0D  
  out 0x3D5, 0xA0  

```ascii
                                ┌────────────────────┐
                                │       0x0D         │  0x3D4   Command Port
                                └────────────────────┘
                                ┌────────────────────┐
                                │       0xA0         │  0x3D5   Data Port
                                └────────────────────┘

                                ┌────────────────────┐
                                │       0x00         │  0x0E    Cursor High Byte
                                ├────────────────────┤
                                │       0xA5         │  0x0F    Cursor Low Byte
                                └────────────────────┘

                                ┌────────────────────┐
                                │       0x00         │  0x0C    Scroll Offset High
                                ├────────────────────┤
                                │       0xA0         │  0x0D    Scroll Offset Low
                                └────────────────────┘
```

