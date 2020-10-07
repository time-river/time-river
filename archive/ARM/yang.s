;--------------------------------------------------------
;整个程序完成的功能:
;1.常量定义
;2.堆栈初始化
;3.异常向量表初始化(Reset_Handler):
;  (1).初始化堆栈
;  (2).控制 IOPA，配置输出 PA0 -- PA7, 并确定初始输出值
;  (3).为异常向量分配存储空间，定义异常向量值
;4.初始化完成后，ENTRY 定义了程序入口，并进入 Reset_Handler 函数
;5.进入 Loop 函数，无限循环。Loop 函数触发中断 IRQ0
;6.怎么使用中断向量表？我不知道......!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
;7.处理中断函数: IRQ0_Handler，完成的功能看 C 语言
;--------------------------------------------------------

;-----------------------------
; RCC_APB2ENR -- APB2外设时钟使能寄存器，偏移地址 0x18
;   GPIO 的时钟统一挂接在 APB2 总线上，具体使能寄存器为 RCC_APB2ENR
; RCC_PIOA_EN EQU 0x4 -- 此比特控制 IOPA 参考 http://www.cnblogs.com/funny-xiaomao/archive/2012/06/20/2556098.html
;-----------------------------
; GPIOA_BASE -- GPIOA 基址
; GPIOx_IDR  -- 端口输入寄存器地址偏移量
; GPIOx_ODR  -- 端口输出
; GPIOx_CRH  -- 端口配置高位寄存器
; GPIOx_CRL  --         低

RCC_BASE    EQU     0x40021000
RCC_APB2ENR EQU     0x18
RCC_PIOA_EN EQU     (0x1<<2)
GPIOA_BASE  EQU     0x40010800
GPIOx_CRL   EQU     0x00
GPIOx_CRH   EQU     0x04
GPIOx_IDR   EQU     0x08
GPIOx_ODR   EQU     0x0c

Stack_Size  EQU     0x00000400
            AREA    STACK, NOINIT, READWRITE, ALIGN=3 ; 在 FLASH 或 RAM 内分配一块区域用于存放代码或数据；参考 http://limian539.com/2016/03/12/MDK-Start/
Stack_Men   SPACE   Stack_Size
__initial_sp ; 初始化 SP 寄存器

; AREA / SPACE / EXPORT 语法参考 http://m.blog.csdn.net/article/details?id=50470484

            AREA    RESET, CODE ;RESET 有点特殊，是系统复位时的位置。具体是什么我也没搞懂
            EXPORT  __Vectors ;声明一个可全局引用的标号 __Vectors

__Vectors
            DEC     __initial_sp
            DEC     Reset_Handler ;
            SPACE   14*4 ; PPT 倒数第5页，异常想量表作用有提，不明白
            DEC     IRQ0_Handler
number      DEC     0xFE, 0xF6, 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0
;                      8     9     0     1     2     3     4     5     6     7
;number 是数码管的输入；比对数码管可知，这些十六进制输入后，在数码管上显示的内容（其中Q0始终为0）

            ENTRYI ;程序入口
            EXPORT  Reset_Handler ;声明一个可全局引用的标号 Reset_Handler，置中断向量

Reset_Handler PROC
            LDR     R0, =0xE000E100 ; 0xE000E100 使能与除能寄存器中 SETENA0 地址（书61页）
            MOV     R1, #1
            STR     R1, [R0] ;使能中断

            ;---------
            LDR     R2, =RCC_BASE
            LDR     R3, =(1<<2)
            STR     R3, [R2, #RCC_APB2ENR]
            ;--------- 完成的功能：使能，控制 IOPA

            LDR     R2, =GPIOA_BASE
            LDR     R3, =0x33333333
            STR     R3, [R2, +GPIOx_CRL]
            ;--------- 完成的功能：将 GPIOA 的 PA0 -- PA7 配置为输出

            ;---------
            LDR     R6, =number
            LDR     R8, 0xE0
            STR     R8, [R2, #GPIOx_ODR]
            ;--------- 完成的功能：初始化数码管，显示为 7

            MOV     R7, #0

Loop
            LDR     R0, =0xE000EF00 ;软件触发中断寄存器地址。书第 65 页
            MOV     R1, #0
            STR     R1, [R0] ;产生 IRQ0（为啥？不知，你书上这么写的）
            B       Loop ; 无条件跳转指令 B，参考书第 49 页
            ENDP

;----------------
IRQ0_Handler PROC
            CMP     R7, #10
            BHS     Putzero ; 相当于: if ([R7] >= 10) { Putzero }; Putzero 完成的功能：置 R7 为 0，跳转 Return
Return
            LDR     R6, =x
            LDR     R8, [R6, R7, LSL #2] ; [] 内地址计算： addr = [R6] + ([R7] << 2)
            STR     R8, [R2, #GPIOx_ODR] ; 输出 R8 的内容至 数码管
            ADD     R7, #1 ; R7 = R7 + 1

            BX      LR ; LR(又叫R14)，连接寄存器，LR 用于在调用子程序的时候存储返回地址(书第 18 页)。BX reg，无条件跳转指令，跳转到寄存器 reg 给出的地址
            ENDP

Putzero
            MOV     R7, #0
            B Return

            END
;--------------
; 上一段翻译成 C
;
;        if (R7 >= 10) { // R7 值为其存储的变量置，下同
;          Putzero();
;        } 
;        else {
;          R7 = 0;
;        }
;        R6 = {8, 9, 0, 1, 2, 3, 4, 5, 6, 7}; // 为了便于理解，把十六进制值映射为其含义，比如 0xFE 映射为 8
;        index = R7 << 2;
;        R8 = R6[index];
;        GPIOA->ODR = R8;
;        R7 += 1;
;        return;
