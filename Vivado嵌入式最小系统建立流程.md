## Vivado嵌入式最小系统建立流程

1.首先File->New project建立新工程，名字和位置自己随意设

2.之后就是一直next,直到Default part这一项要选择自己要用的实验板--我们实验用到的是Nexys4 DDR,找不到自己要的板子的型号，可以在网上查找并下载

3.选好板子后点击Finish,new project就创建成功

4.在新建立好的窗口左侧的IP Integrator下点击Create Block Design,弹出界面照默认设置直接点OK

5.之后在工作窗口区的Diagram窗口下点击"＋"添加IP核，在弹出界面输出Micro，双击列表中的MicroBlaze.

6.双击刚产生的MicroBlaze微处理器，在弹出界面中勾选Enable MicroBlaze Debug Module Interface启用调试接口，再点击2次下一步，将Debug中的Number of PC Breakpoints设置为4，再点击下一步并OK完成设置

7.单击IP核集成器设计助手运行模块自动配置-Run Block Automation,在弹出界面中将Local Memory设置为64kB并勾选Interrupt Controller,点击OK完成配置

8.双击框图中的Clocking Wizard模块,要设置3个东西。一是Clocking Options的最下面的Primary条框的Source设置为Single ended clock capable pin.二是Output clocks中的Reset type设为Active Low.三是Board中的CLK_IN1与EXT_RESET_IN的Board Interference分别设为sys clock和reset.之后点击OK完成设置

9.双击框图中Process System Reset模块，设置Board中的Ext_Reset为reset,点击OK完成设置

10.点击Run Connection Automation并勾选左侧所有模块，单击OK会自动完成连线。

11.单击IP核集成器设计界面中的"＋"，在弹出界面中输入UART并双击AXI Uartlite

12.双击生成的AXI Uartlite模块，将Board设为usb uart,并将IP Configuration中的Baud Rate设为115200，点击OK完成设置

13.点击Run Connection Automation并勾选左侧所有模块，单击OK会自动完成连线。

14.至此，基于MicroBlaze微处理器的最小计算机硬件系统搭建完成，紧接着保存设计并生成硬件比特流

15.具体来说，保存设计之后，先单击"＋"旁边的有一个勾的校验快捷键进行校验

16.之后在Sources窗口右键单击Design Sources下面的条目，选择Create HDL Wrapper,弹出界面直接OK

17.在左侧工作流窗口直接点击Generate Bitstream开始生成硬件比特流，大概要10来分钟，完成后弹出界面点击Cancel

18.单击File菜单下Export->Export Hardware并勾选弹出界面中的Include bitstream，点击OK

19.单击File菜单下的Launch SDK启动SDK