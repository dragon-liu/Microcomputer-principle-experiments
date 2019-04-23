`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 13:52:48
// Design Name: 
// Module Name: aluctr
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


module aluctr(
    input [1:0] ALUop,
    input [5:0] func,
    output reg  [3:0] ALUctr
    );
    
    always@(ALUop or func)
    casex({ALUop,func})
    8'b00xxxxxx:ALUctr = 4'b0010;//lw,sw
    8'b01xxxxxx:ALUctr = 4'b0110;//beq
    8'b10xx0000:ALUctr = 4'b0010;//add
    8'b10xx0010:ALUctr = 4'b0110;//sub
    8'b10xx0100:ALUctr = 4'b0000;//and
    8'b10xx0101:ALUctr = 4'b0001;//or
    8'b10xx1010:ALUctr = 4'b0111;//slt
    default: ALUctr  = 4'b0000;
    endcase
endmodule
