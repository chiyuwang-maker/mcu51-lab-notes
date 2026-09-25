# mcu51-lab-notes

**8051（reg52/reg51）单片机实验源码笔记**，从课设/开发板实验目录整理，仅保留 `.c` / `.h`。

来源（用户本机，只读拷贝）：`D:\experiment\`  
建议 GitHub 仓名（**尚未创建/推送**）：`chiyuwang-maker/mcu51-lab-notes`

## 硬件与工具假定

- 典型 51 开发板（LED、动态数码管、XPT2046 ADC、LCD1602、DS18B20、串口等）
- Keil C51 / 同类环境；本仓不含工程文件与 `Debug` 产物

## 实验目录一览

| 目录 | 原文件夹含义 | 内容摘要 |
|------|----------------|----------|
| `01-led` | 实验1：点亮第一个LED | `P2.0` 置低点亮 D1 |
| `02-digital-stopwatch` | 实验1. 数字秒表设计 | 定时器 + 动态数码管显示分/秒 |
| `03-dynamic-digit-display` | 实验5：动态数码管显示 | 左至右显示 0–7 |
| `04-uart` | 实验21：串口通信 | 波特率约 4800，串口回显 |
| `05a-adc-photoresistor` | AD：光敏电阻 | XPT2046 + 数码管/电机等相关驱动 |
| `05b-adc-external-ain` | AD：外部输入 AIN | 外部模拟量 → 数码管显示 |
| `05c-adc-thermistor` | AD：热敏电阻 | 热敏通道采样显示 |
| `05d-adc-potentiometer` | AD：电位器 | 电位器采样显示 |
| `06-lcd1602-temp-uart` | 实验7：LCD1602+温度+串口 | DS18B20 + LCD + 串口输出温度 |
| `07-smart-temp-control` | 智能温度检测控制系统 | 阈值、EEPROM(AT24C02)、蜂鸣器/继电器/电机联动 |
| `08-blood-pressure-adc` | `xue_ya_ji` | 基于 XPT2046 的 AD 显示（血压计相关实验草稿） |
| `scratch-coding1`…`5` | coding1–5 | 与正式实验相近的练习副本（LED/数码管/AD 等） |
| `00-root-loose` | `D:\experiment\` 根目录散落 | `main.c` / `main1.c`（偏 AD+数码管） |

## 当前文件树

- `00-root-loose/` — `main.c`, `main1.c`
- `01-led/` — `main.c`
- `02-digital-stopwatch/` — `main.c`
- `03-dynamic-digit-display/` — `main.c`
- `04-uart/` — `main.c`
- `05a-adc-photoresistor/` — `4-2Motor.c`, `4-2Motor.h`, `42Motor.c`, `42Motor.h`, `KeyScan.c`, `KeyScan.h`, `XPT2046.c`, `XPT2046.h`, `i2c.c`, `i2c.h`, `key.c`, `key.h`, `lcd.c`, `lcd.h`, `main.c`
- `05b-adc-external-ain/` — `XPT2046.c`, `XPT2046.h`, `main.c`
- `05c-adc-thermistor/` — `XPT2046.c`, `XPT2046.h`, `main.c`
- `05d-adc-potentiometer/` — `XPT2046.c`, `XPT2046.h`, `main.c`
- `06-lcd1602-temp-uart/` — `lcd.c`, `lcd.h`, `main.c`, `temp.c`, `temp.h`
- `07-smart-temp-control/` — `i2c.c`, `i2c.h`, `key.c`, `key.h`, `lcd.c`, `lcd.h`, `main.c`, `public.c`, `public.h`, `temp.c`, `temp.h`
- `08-blood-pressure-adc/` — `XPT2046.c`, `XPT2046.h`, `main.c`
- `scratch-coding1/` — `XPT2046.c`, `XPT2046.h`, `main.c`
- `scratch-coding2/` — `main.c`
- `scratch-coding3/` — `main.c`
- `scratch-coding4/` — `XPT2046.c`, `XPT2046.h`, `main1.c`
- `scratch-coding5/` — `XPT2046.c`, `XPT2046.h`, `main.c`

## 整理说明

- 原中文路径已映射为 ASCII 目录名，含义见上表；**未删除**用户磁盘原件
- 排除：`.vs`、`Debug`、`.exe`、Word 截图/日志等
- 源码已转为 UTF-8，便于 GitHub 显示中文注释
- `05a` 目录混有电机/`i2c`/`lcd` 等文件，可能是实验包整体拷贝，入库前可再拆模块

## 建议后续

1. 为每个 `labs/*` 补一句「接线要点」短 `NOTES.md`（可选）
2. 去掉与主实验重复的 `scratch-coding*`（或标明为历史草稿）
3. 主代理确认后再 `gh repo create` 并 push
