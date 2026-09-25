# mcu51-lab-notes

51 单片机**初学者练习优化稿**（非厂家 SDK / 开发攻略拷贝）。

从早期实验目录里筛出「自己拼的」小实验，去掉「实验现象 / 接线说明 / 开发攻略」套话与缺失的板厂驱动依赖，改成只用 `reg52.h`（必要时把极小辅助逻辑内联进同一文件）的可读示例。

## 保留的实验

| 目录 | 说明 |
|------|------|
| `01-led` | 点亮 P2.0 上一颗 LED |
| `02-motor` | 直流电机约转 5 秒后停止 |
| `05-dynamic-nixie` | 动态数码管显示 0～7 |
| `01-digital-stopwatch` | 定时器 0 + 数码管数字秒表（mm-ss-xx） |
| `21-uart` | 串口 4800 回显 |
| `21-adc` | 电位器 AD（内联 XPT2046 位带 SPI）+ 数码管显示 |
| `bp-meter-practice` | 血压计练习稿：AIN3 采样、粗换算显示、按键切 LED/电机 |

每个目录一个 `main.c`，用 Keil C51 / 兼容工具打开即可；晶振按常见 12MHz 例程取值，管脚按普中类实验板习惯（可按自己板子改 `sbit`）。

## 已删除（原因）

| 原路径 | 原因 |
|--------|------|
| `07-lcd1602-temp` | 依赖仓内不存在的 `lcd.h` / `temp.h`，正文多为厂家 LCD1602 + DS18B20 攻略 |
| `smart-temp-control` | 依赖 `public.h` / `lcd.h` / `temp.h` / `i2c.h`，整段厂家智能温控模板 |
| `coding1`～`coding4`、`root-snippets`、`xue_ya_ji` | 基本是 AD + 数码管厂家模板，或与保留实验重复；`coding5` 中有自写痕迹的已并入 `bp-meter-practice` |
| `21-adc/photoresistor`、`thermistor`、`external-input`、`potentiometer` 旧副本 | 通道号不同的同一套厂家 AD 模板；`external-input` 曾误粘电机代码，电机意图已收进 `02-motor`，AD 收进 `21-adc` |

本仓**不**附带板厂 `XPT2046` / `lcd` / `temp` / `i2c` / `key` / `public` 等驱动源文件。

## 编译提示

1. Keil μVision 新建 8051/C51 工程，加入对应目录的 `main.c`。
2. 头文件选编译器自带的 `reg52.h` 即可。
3. `.gitignore` 已忽略常见 Keil 产物。
