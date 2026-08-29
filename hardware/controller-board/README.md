# STM32 从车控制板

控制板承担传感器接入、双车通信、执行器控制和电源分配，是从车控制系统的信号汇聚节点。板卡通过 STM32F103C8 核心板接口连接主控，并将电机驱动、循迹、测距和人机显示模块集中到统一硬件平台。

## 电路组成

- STM32F103C8 核心板与调试接口。
- 红外循迹、超声波和编码器接口。
- USART 双车通信接口。
- 双路电机驱动控制信号接口。
- 舵机、OLED、蜂鸣器和 LED 接口。
- 板载稳压与电源输入电路。

## 设计文件

| 类型 | 文件 |
| --- | --- |
| Altium 工程 | `source/Control board from the owner_Project.PrjPcb` |
| 原理图 | `source/STM32 Core board.SchDoc` |
| PCB | `source/STM32 Core board.PcbDoc` |
| 原理图库 | `source/STM32 Core board.SCHLIB` |
| PCB 库 | `source/STM32 Core board.PcbLib` |

## PDF 视图

- [控制板原理图](../../docs/images/主控板原理图.pdf)
- [控制板布线图](../../docs/images/主控板布线图.pdf)
- [控制板丝印图](../../docs/images/主控板丝印图.pdf)
