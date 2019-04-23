`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 08:42:07
// Design Name: 
// Module Name: regFile
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


module regfile(
    input clk,
    input reset,
    input regwr,
    input [4:0] RsAddr,
    input [4:0] RtAddr,
    input [4:0] WriteAddr,
    input [31:0] WriteData,
   output [31:0] RsData,
    output [31:0] RtData
    );
    reg[31:0]           regs[1:31];
    assign RsData = (RsAddr==5'h0) ? 32'h0 : regs[RsAddr];
    assign RtData = (RtAddr==5'h0) ? 32'h0 : regs[RtAddr];   
    integer i;
    always@(negedge clk or posedge reset)
    if(reset)
       for(i=1;i<32;i=i+1)
       regs[i]<=0;
    else if (regwr)
        regs[WriteAddr]<=  WriteData;
endmodule
