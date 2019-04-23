`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 15:40:35
// Design Name: 
// Module Name: top
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


module top(      
input clk,
input reset
);
reg[31:0]PC;
wire J,B,Bzero,zero,M2R,memwr,Imm,regwr,RtDst;
wire[1:0]ALUop;
wire[3:0]ALUctr;
wire[31:0]  NewPC ,JMPPC, BranPC, Imm32L2, Imm32, NotJMPPC ,TempPC;
wire[31:0]Instr,WriteData, DataOut,Res, RsData,RtData,in2;
wire[4:0]WriteAddr;
assign Imm32={{16{Instr[15]}},Instr[15:0]};//·ûºÅÊýÀ©Õ¹
assign WriteAddr = RtDst ? Instr[15:11] :Instr[20:16];//
assign in2= Imm? Imm32:RtData;//
assign WriteData=M2R?DataOut:Res;//
assign NotJMPPC=Bzero? BranPC:NewPC;//
assign TempPC=J? JMPPC: NotJMPPC;//
assign Bzero=B&zero;//
assign Imm32L2=Imm32<<2;//
assign JMPPC={NewPC[31:28],Instr[25:0],2'b00};//
assign BranPC=NewPC+Imm32L2;//
assign NewPC =PC+4;//
always @(posedge clk)
if(!reset)
PC=TempPC;
else
PC=32'b0;
    
mainctr mainctr(Instr[31:26],ALUop,RtDst,regwr,Imm,memwr,B,J,M2R);
ALU alu(RsData,in2,ALUctr,Res,zero);
aluctr Aluctr(.ALUop(ALUop),.func(Instr[5:0]),.ALUctr(ALUctr));
DataROM dram(.a(Res[7:2]),.d(RtData),.clk(!clk),.we(memwr),.spo(DataOut));
InstrROM irom(.a(PC[8:2]),.spo(Instr));
regfile regfile (clk,reset,regwr,Instr[25:21],Instr[20:16],WriteAddr,WriteData,RsData,RtData);       

endmodule