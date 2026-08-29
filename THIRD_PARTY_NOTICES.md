# 第三方内容声明

本仓库包含来自第三方固件发行包和通用 STM32 教学示例的代码。相关文件保留其原始版权声明，并继续受原权利人的许可条款约束。

## STMicroelectronics 与 ARM

以下目录和文件包含 STM32F10x Standard Peripheral Library、CMSIS、设备支持、启动文件或工程模板内容：

- `firmware/follower/Library/`
- `firmware/follower/Start/`
- `firmware/follower/User/stm32f10x_conf.h`
- `firmware/follower/User/stm32f10x_it.c`
- `firmware/follower/User/stm32f10x_it.h`

上述内容的版权归 STMicroelectronics、ARM 或相应权利人所有，不因收录于本仓库而改变授权方式。

## 外设驱动代码

部分基础外设驱动源于常见 STM32 教学示例。仓库未对这些第三方内容进行统一再授权。带有额外限制声明且未被当前工程使用的 `System/Sys` 和 `System/Usart` 已从公开副本中移除。

项目自编控制逻辑与第三方基础库在目录结构中保持分离，便于识别各自来源与适用许可。
