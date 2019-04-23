`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/09 20:45:33
// Design Name: 
// Module Name: topsim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module topsim();
reg clk;
reg reset;
top u1(.clk(clk),.reset(reset));
parameter PERIOD=10;
always begin
   clk=1'b0;
   #(PERIOD/2)clk=1'b1;
    #(PERIOD/2);
    end
    initial begin
    reset = 1'b1;
    #14
    reset = 1'b0;
    end

endmodule
