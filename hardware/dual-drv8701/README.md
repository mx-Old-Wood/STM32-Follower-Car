# 双路 DRV8701 电机驱动板

电机驱动板为从车左右直流电机提供独立功率通道。每路通道以 DRV8701E 作为栅极驱动器，配合外置功率 MOSFET 构成电机功率级，并通过逻辑缓冲与控制板连接。

## 电路组成

- 双路 DRV8701E 栅极驱动器。
- 外置功率 MOSFET 电机桥。
- PWM、方向和使能控制接口。
- 逻辑缓冲与信号整形。
- 电机电源输入、板载稳压和状态指示。

## 设计文件

| 类型 | 文件 |
| --- | --- |
| Altium 工程 | `source/DRV8701E.PrjPcb` |
| 原理图 | `source/DRV8901E.SchDoc` |
| PCB | `source/DRV8901E.PcbDoc` |
| 原理图库 | `source/DRV8701_DualMotorDriver.SCHLIB` |
| PCB 库 | `source/DRV8701_DualMotorDriver V1.1.PcbLib` |

源文件中的 `DRV8901E` 为历史文件名，板卡实际采用的核心驱动器为 DRV8701E。文件名保持不变，以维持 Altium 工程内部引用关系。

## PDF 视图

- [驱动板原理图](../../docs/images/驱动板原理图.pdf)
- [驱动板布线图](../../docs/images/驱动板布线图.pdf)
- [驱动板丝印图](../../docs/images/驱动板丝印图.pdf)
