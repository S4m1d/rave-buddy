#!/bin/bash

cat > .clangd << EOF
CompileFlags:
  CompilationDatabase: .
  Remove:
    - "-fzero-init-padding-bits=all"
    - "-fno-shrink-wrap"
    - "-fno-tree-switch-conversion"
    - "-fstrict-volatile-bitfields"
    - "-mlongcalls"
    - "-fno-*"
    - "-W*"
  Add:
    - "--sysroot=$HOME/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf"
    - "--target=xtensa-esp32-elf"
    - "-nostdinc"
    - "-isystem$HOME/.platformio/packages/toolchain-xtensa-esp-elf/xtensa-esp-elf/include"
    - "-isystem$HOME/.platformio/packages/toolchain-xtensa-esp-elf/lib/gcc/xtensa-esp-elf/15.2.0/include"
    - "-I$HOME/.platformio/packages/framework-espidf/components/newlib/include"
    - "-I$HOME/.platformio/packages/framework-espidf/components/esp_common/include"
    - "-I$HOME/.platformio/packages/framework-espidf/components/esp_hw_support/include"
    - "-I.pio/build/esp32dev/config"
    - "-I./src"
Diagnostics:
  Suppress:
    - unknown_typename
    - drv_unknown_argument
    - pp_including_mainfile_in_preamble
    - redefinition_different_typedef
EOF
