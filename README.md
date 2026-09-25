# mcu51-lab-notes

**8051（reg52/reg51）单片机实验：仅用户编写的 `main` / `main1` 源文件。**

来源（本机只读拷贝）：`D:\experiment\`  
整理原则（按用户要求）：**去掉全部厂商驱动**（如 XPT2046、lcd、temp、i2c、key、public、电机等），每个实验目录只保留 `main.c` 或 `main1.c`。

建议 GitHub 仓名：`chiyuwang-maker/mcu51-lab-notes`

## 说明

- 这些 `main` 在去掉驱动后，**多数无法直接单独编译通过**（原工程依赖已剔除的板厂 `.c/.h`）。本仓用途是保存你自己的实验主程序逻辑与笔记，不是完整可烧录工程。
- 原目录 `D:\experiment\` 未被修改或删除。
- 不含 Keil 工程、`Debug`、截图 doc、二进制。

## 目录

| 目录 | 原意 | 保留文件 |
|------|------|----------|
| `labs/01-led` | 点亮 LED | `main.c` |
| `labs/02-digital-stopwatch` | 数字秒表 | `main.c` |
| `labs/03-dynamic-digit-display` | 动态数码管 | `main.c` |
| `labs/04-uart` | 串口通信 | `main.c` |
| `labs/05a-adc-photoresistor` | AD 光敏 | `main.c` |
| `labs/05b-adc-external-ain` | AD 外部输入 | `main.c` |
| `labs/05c-adc-thermistor` | AD 热敏 | `main.c` |
| `labs/05d-adc-potentiometer` | AD 电位器 | `main.c` |
| `labs/06-lcd1602-temp-uart` | LCD + 温度 + 串口 | `main.c` |
| `labs/07-smart-temp-control` | 智能温控 | `main.c` |
| `labs/08-blood-pressure-adc` | 血压计相关 AD | `main.c` |
| `labs/scratch-coding1`…`5` | 练习副本 | `main.c` / `main1.c` |
| `labs/00-root-loose` | 根目录散落 | `main.c`, `main1.c` |
