target remote | openocd -f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg -f openocd/gdb-pipe.cfg
monitor reset halt
