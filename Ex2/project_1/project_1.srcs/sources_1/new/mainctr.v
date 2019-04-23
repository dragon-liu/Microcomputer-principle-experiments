`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 13:37:34
// Design Name: 
// Module Name: mainctr
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


module mainctr(
    input [5:0] opCode,
    output [1:0] ALUop,
    output RtDst,
    output regwr,
    output Imm,
    output memwr,
    output B,
    output J,
    output M2R
    );
    reg[8:0] outputtemp;
    assign RtDst=outputtemp[8];
    assign Imm=outputtemp[7];
    assign M2R=outputtemp[6];
    assign regwr=outputtemp[5];
    assign memwr=outputtemp[4];
    assign B=outputtemp[3];
    assign J=outputtemp[2];
    assign ALUop=outputtemp[1:0]; 

always@(opCode)
   case(opCode)
   6'b000010:outputtemp=9'bxxx0_001_xx;//jmp
   6'b000000:outputtemp=9'b1001_000_10;//R
   6'b100011:outputtemp=9'b0111_000_00;//lw
   6'b101011:outputtemp=9'bx1x0_100_00;//sw
   6'b000100:outputtemp=9'bx0x0_010_01;//beq
   6'b001000:outputtemp=9'b0101_000_00;//addi
   default:outputtemp=9'b0000000000;
   
   endcase
 
endmodule
