//Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2018.1 (win64) Build 2188600 Wed Apr  4 18:40:38 MDT 2018
//Date        : Tue Jun 18 13:59:34 2019
//Host        : DESKTOP-6E4H686 running 64-bit major release  (build 9200)
//Command     : generate_target ShiyanPingtai_wrapper.bd
//Design      : ShiyanPingtai_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module ShiyanPingtai_wrapper
   (dual_seven_seg_led_disp_tri_i,
    reset,
    seven_seg_led_an_tri_io,
    sys_clock,
    usb_uart_rxd,
    usb_uart_txd);
  input [15:0]dual_seven_seg_led_disp_tri_i;
  input reset;
  inout [7:0]seven_seg_led_an_tri_io;
  input sys_clock;
  input usb_uart_rxd;
  output usb_uart_txd;

  wire [15:0]dual_seven_seg_led_disp_tri_i;
  wire reset;
  wire [0:0]seven_seg_led_an_tri_i_0;
  wire [1:1]seven_seg_led_an_tri_i_1;
  wire [2:2]seven_seg_led_an_tri_i_2;
  wire [3:3]seven_seg_led_an_tri_i_3;
  wire [4:4]seven_seg_led_an_tri_i_4;
  wire [5:5]seven_seg_led_an_tri_i_5;
  wire [6:6]seven_seg_led_an_tri_i_6;
  wire [7:7]seven_seg_led_an_tri_i_7;
  wire [0:0]seven_seg_led_an_tri_io_0;
  wire [1:1]seven_seg_led_an_tri_io_1;
  wire [2:2]seven_seg_led_an_tri_io_2;
  wire [3:3]seven_seg_led_an_tri_io_3;
  wire [4:4]seven_seg_led_an_tri_io_4;
  wire [5:5]seven_seg_led_an_tri_io_5;
  wire [6:6]seven_seg_led_an_tri_io_6;
  wire [7:7]seven_seg_led_an_tri_io_7;
  wire [0:0]seven_seg_led_an_tri_o_0;
  wire [1:1]seven_seg_led_an_tri_o_1;
  wire [2:2]seven_seg_led_an_tri_o_2;
  wire [3:3]seven_seg_led_an_tri_o_3;
  wire [4:4]seven_seg_led_an_tri_o_4;
  wire [5:5]seven_seg_led_an_tri_o_5;
  wire [6:6]seven_seg_led_an_tri_o_6;
  wire [7:7]seven_seg_led_an_tri_o_7;
  wire [0:0]seven_seg_led_an_tri_t_0;
  wire [1:1]seven_seg_led_an_tri_t_1;
  wire [2:2]seven_seg_led_an_tri_t_2;
  wire [3:3]seven_seg_led_an_tri_t_3;
  wire [4:4]seven_seg_led_an_tri_t_4;
  wire [5:5]seven_seg_led_an_tri_t_5;
  wire [6:6]seven_seg_led_an_tri_t_6;
  wire [7:7]seven_seg_led_an_tri_t_7;
  wire sys_clock;
  wire usb_uart_rxd;
  wire usb_uart_txd;

  ShiyanPingtai ShiyanPingtai_i
       (.dual_seven_seg_led_disp_tri_i(dual_seven_seg_led_disp_tri_i),
        .reset(reset),
        .seven_seg_led_an_tri_i({seven_seg_led_an_tri_i_7,seven_seg_led_an_tri_i_6,seven_seg_led_an_tri_i_5,seven_seg_led_an_tri_i_4,seven_seg_led_an_tri_i_3,seven_seg_led_an_tri_i_2,seven_seg_led_an_tri_i_1,seven_seg_led_an_tri_i_0}),
        .seven_seg_led_an_tri_o({seven_seg_led_an_tri_o_7,seven_seg_led_an_tri_o_6,seven_seg_led_an_tri_o_5,seven_seg_led_an_tri_o_4,seven_seg_led_an_tri_o_3,seven_seg_led_an_tri_o_2,seven_seg_led_an_tri_o_1,seven_seg_led_an_tri_o_0}),
        .seven_seg_led_an_tri_t({seven_seg_led_an_tri_t_7,seven_seg_led_an_tri_t_6,seven_seg_led_an_tri_t_5,seven_seg_led_an_tri_t_4,seven_seg_led_an_tri_t_3,seven_seg_led_an_tri_t_2,seven_seg_led_an_tri_t_1,seven_seg_led_an_tri_t_0}),
        .sys_clock(sys_clock),
        .usb_uart_rxd(usb_uart_rxd),
        .usb_uart_txd(usb_uart_txd));
  IOBUF seven_seg_led_an_tri_iobuf_0
       (.I(seven_seg_led_an_tri_o_0),
        .IO(seven_seg_led_an_tri_io[0]),
        .O(seven_seg_led_an_tri_i_0),
        .T(seven_seg_led_an_tri_t_0));
  IOBUF seven_seg_led_an_tri_iobuf_1
       (.I(seven_seg_led_an_tri_o_1),
        .IO(seven_seg_led_an_tri_io[1]),
        .O(seven_seg_led_an_tri_i_1),
        .T(seven_seg_led_an_tri_t_1));
  IOBUF seven_seg_led_an_tri_iobuf_2
       (.I(seven_seg_led_an_tri_o_2),
        .IO(seven_seg_led_an_tri_io[2]),
        .O(seven_seg_led_an_tri_i_2),
        .T(seven_seg_led_an_tri_t_2));
  IOBUF seven_seg_led_an_tri_iobuf_3
       (.I(seven_seg_led_an_tri_o_3),
        .IO(seven_seg_led_an_tri_io[3]),
        .O(seven_seg_led_an_tri_i_3),
        .T(seven_seg_led_an_tri_t_3));
  IOBUF seven_seg_led_an_tri_iobuf_4
       (.I(seven_seg_led_an_tri_o_4),
        .IO(seven_seg_led_an_tri_io[4]),
        .O(seven_seg_led_an_tri_i_4),
        .T(seven_seg_led_an_tri_t_4));
  IOBUF seven_seg_led_an_tri_iobuf_5
       (.I(seven_seg_led_an_tri_o_5),
        .IO(seven_seg_led_an_tri_io[5]),
        .O(seven_seg_led_an_tri_i_5),
        .T(seven_seg_led_an_tri_t_5));
  IOBUF seven_seg_led_an_tri_iobuf_6
       (.I(seven_seg_led_an_tri_o_6),
        .IO(seven_seg_led_an_tri_io[6]),
        .O(seven_seg_led_an_tri_i_6),
        .T(seven_seg_led_an_tri_t_6));
  IOBUF seven_seg_led_an_tri_iobuf_7
       (.I(seven_seg_led_an_tri_o_7),
        .IO(seven_seg_led_an_tri_io[7]),
        .O(seven_seg_led_an_tri_i_7),
        .T(seven_seg_led_an_tri_t_7));
endmodule
