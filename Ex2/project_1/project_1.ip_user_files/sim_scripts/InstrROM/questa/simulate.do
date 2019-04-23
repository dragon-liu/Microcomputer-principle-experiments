onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib InstrROM_opt

do {wave.do}

view wave
view structure
view signals

do {InstrROM.udo}

run -all

quit -force
