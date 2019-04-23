`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 14:09:29
// Design Name: 
// Module Name: regSim
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


module regSim(

    );
    reg clk;
    reg reset;
    reg regwr;
    reg [4:0] RsAddr;
    reg [4:0] RtAddr;
    reg [4:0] WriteAddr;
    reg [31:0] WriteData;
    wire [31:0] RsData;
    wire [31:0] RtData;
    regfile uut (clk,reset,regwr,RsAddr,RtAddr,WriteAddr,WriteDaya,RsData,RtData);
    parameter PERIOD=10;//clk period 10ns
    always begin
    clk=1'b0;
    #(PERIOD/2) clk=1'b1;//rieing edge
    #(PERIOD/2);//falling edge
    end
    initial begin
    reset=1;//reset 14ns
    RsAddr=3;
    RtAddr=0;
    WriteAddr=5;
    WriteData=8;
    regwr=1;
    #14 reset=0;//20ns writedata stored in writeaddr $5=8
    #20 RsAddr=5;//34ns RsData=8
    end
    
endmodule
