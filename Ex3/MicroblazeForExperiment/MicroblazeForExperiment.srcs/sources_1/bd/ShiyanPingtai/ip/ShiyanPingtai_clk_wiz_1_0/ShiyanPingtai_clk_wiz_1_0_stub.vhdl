-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
-- Date        : Tue Jun 18 13:45:27 2019
-- Host        : DESKTOP-6E4H686 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               H:/MicroComputerPrinciple/MicroblazeForExperiment/MicroblazeForExperiment.srcs/sources_1/bd/ShiyanPingtai/ip/ShiyanPingtai_clk_wiz_1_0/ShiyanPingtai_clk_wiz_1_0_stub.vhdl
-- Design      : ShiyanPingtai_clk_wiz_1_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ShiyanPingtai_clk_wiz_1_0 is
  Port ( 
    clk_out1 : out STD_LOGIC;
    resetn : in STD_LOGIC;
    locked : out STD_LOGIC;
    clk_in1 : in STD_LOGIC
  );

end ShiyanPingtai_clk_wiz_1_0;

architecture stub of ShiyanPingtai_clk_wiz_1_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk_out1,resetn,locked,clk_in1";
begin
end;
