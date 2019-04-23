`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/04/05 13:21:24
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [31:0] int1,
    input [31:0] int2,
    input [3:0] ALUctr,
    output  reg [31:0] Res,
    output  reg   zero
    );
    always@(int1 or int2 or ALUctr)
           begin
              case (ALUctr)
              4'b0000://and
              Res= int1 & int2;
              
               4'b0001://or
               Res= int1 | int2;
                            
              4 'b0010://add
              Res=int1+int2;
                
                4'b0110://sub
               begin
                Res=int1-int2;
              zero=(Res==0)?1:0;
              end
              
               4'b0111://slt
               Res=(int1<int2)?1:0;
                
               default: //others
               Res=0;
              endcase
              end
             
endmodule
