#!/bin/bash

cat > .clangd << EOF
CompileFlags:
  CompilationDatabase: .
  Remove:
    - "-fno-shrink-wrap"
    - "-fno-tree-switch-conversion"
    - "-fstrict-volatile-bitfields"
    - "-mlongcalls"
    - "-fno-*"
  Add:
    - "-I./src"
    - "--sysroot=$HOME/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf"
    - "-I$HOME/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include"
    - "-I$HOME/.platformio/packages/framework-espidf/components/riscv/include"
    - "-I$HOME/.platformio/packages/framework-espidf/components/soc/esp32c5/include"
EOF
