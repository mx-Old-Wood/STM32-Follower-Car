# 从车固件

从车固件面向 STM32F103C8T6，基于 STM32F10x Standard Peripheral Library 开发，并使用 Keil ARM Compiler 5 构建。控制程序同时处理红外循迹、超声波测距、串口通信、距离控制和双电机速度闭环。

## 执行流程

```text
串口接收与显示
      ↓
停车条件与距离控制
      ↓
循迹模式选择
      ↓
运动指令与轮速设定
      ↓
TIM4 周期执行双电机 PI
```

## 模块划分

| 路径 | 功能 |
| --- | --- |
| `follower/User/main.c` | 外设初始化与主循环 |
| `follower/User/Mode.c` | 数据解析、距离源切换、距离控制与停车判断 |
| `follower/Hardware/Infrared.c` | 五路红外循迹、标志线和阶段计数 |
| `follower/Hardware/Ultrasound.c` | 本车超声波触发与距离计算 |
| `follower/Hardware/Serial.c` | USART1 固定帧收发 |
| `follower/Hardware/Encoder.c` | 双路编码器脉冲计数 |
| `follower/System/PID/` | 双电机增量式 PI |
| `follower/System/Timer/Timer.c` | 测距计时、轮速计算和速度环调度 |

## 工程配置

固件工程文件为 `follower/Project.uvprojx`，目标器件为 STM32F103C8，构建目标为 `Target 1`。当前公开版本的全量构建结果为 `0 Error(s), 0 Warning(s)`。
