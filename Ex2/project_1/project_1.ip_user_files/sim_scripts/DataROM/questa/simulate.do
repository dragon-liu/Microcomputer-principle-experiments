onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib DataROM_opt

do {wave.do}

view wave
view structure
view signals

do {DataROM.udo}

run -all

quit -force
