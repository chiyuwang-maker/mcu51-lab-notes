# mcu51-lab-notes

51 单片机实验源码整理仓库（**干净树**）。从本机 `D:\experiment\` **只抽取用户自己写的实验主逻辑**（各目录下的 `main.c` / `main1.c`），**禁止混入**开发板厂商 / 板厂提供的驱动与模板代码。

## 本次整理策略

1. **默认丢弃**（无论出现在哪个实验）：`XPT2046.c/.h`、`lcd.c/.h`、`i2c.c/.h`、`key.c/.h`、`KeyScan.*`、`public.c/.h`、板厂风格的 `temp.c/.h`（DS18B20 例程）、`4-2Motor.*` / `42Motor.*` 及一切电机 demo，以及与多目录字节级相同的驱动副本。
2. **默认保留**：各实验目录中的 `main.c`、`main1.c`（用户入口）。
3. `smart-temp-control`、`07-lcd1602-temp`：除 `main.c` 外其余均为板厂模块 → **只保留 `main.c`**；编译需自行搭配开发板例程中的 LCD / DS18B20 / I2C / 按键等驱动。
4. `coding*` / `xue_ya_ji` / `21-adc` 各子目录：各自只留 `main.c` 或 `main1.c`。
5. **不收录** Keil 工程与中间产物（`.hex` / `.obj` / `.lst` / `.uvproj` 等）、图片、`截图.doc`、根目录日志原文。
6. **严禁**收录 μC/OS-II / UCOS / UCOSII 等相关工程（本次扫描 `D:\experiment\` 未发现此类路径）。
7. 原路径 `D:\experiment\` **未删除、未移动、未覆盖**；本仓库为覆盖重建的拷贝整理。**未执行** `git push`。

## 目录一览

| 目录 | 说明 | 入库文件 |
|------|------|----------|
| `01-led` | 点亮第一个 LED | `main.c` |
| `01-digital-stopwatch` | 数字秒表（动态数码管） | `main.c` |
| `05-dynamic-nixie` | 动态数码管显示 0–7 | `main.c` |
| `07-lcd1602-temp` | LCD1602 显示温度 + 串口输出 | **仅** `main.c`（`lcd`/`temp` 板厂驱动未入库） |
| `21-uart` | 串口通信（接收中断，波特率 4800） | `main.c` |
| `21-adc/potentiometer` | 电位器 AD 值显示 | **仅** `main.c`（依赖 `XPT2046` 需自备） |
| `21-adc/photoresistor` | 光敏电阻 AD 值显示 | **仅** `main.c` |
| `21-adc/thermistor` | 热敏电阻 AD 值显示 | **仅** `main.c` |
| `21-adc/external-input` | 外部输入 AIN3 AD 值 | **仅** `main.c` |
| `coding1`～`coding5` | 练习工程 | 各目录仅 `main.c`（`coding4` 为 `main1.c`） |
| `xue_ya_ji` | 目录名意为血压计相关；源码为 AIN3 AD 演示 | **仅** `main.c` |
| `smart-temp-control` | 智能温度检测控制系统主逻辑 | **仅** `main.c`（LCD/按键/I2C/DS18B20/`public` 等板厂模块未入库） |
| `root-snippets` | 原 `D:\experiment\` 根目录片段 | `main.c`、`main1.c` |

## 未收录（原因）

| 原路径 / 文件 | 原因 |
|---------------|------|
| 各处 `XPT2046.c` / `XPT2046.h` | 板厂 AD/触摸 SPI 驱动，多目录字节级相同副本 |
| `07-lcd1602-temp` 的 `lcd.c/.h`、`temp.c/.h` | 板厂 LCD1602 / DS18B20 例程风格驱动 |
| `smart-temp-control` 的 `i2c.*`、`key.*`、`lcd.*`、`public.*`、`temp.*` | 板厂模块；策略规定该实验只留用户 `main.c` |
| `21-adc/photoresistor` 的 `4-2Motor.*`、`42Motor.*`、`i2c.*`、`key.*`、`KeyScan.*`、`lcd.*` | 电机 demo / 板厂按键 I2C LCD；与 AD 主逻辑无关且曾致冲突 |
| `coding1/4/5`、`xue_ya_ji`、各 AD 子目录的 `XPT2046.*` | 同上，厂商驱动 |
| 根目录 `截图.doc`、`日志2023.6.6.txt` | 非用户源码；日志仅作整理参考不整文件入库 |
| 全部 Keil 产物与工程文件 | 中间产物，不入库 |
| 空壳目录 | 剔除后无用户文件则不建目录（本次各收录目录均有 `main`） |

日志摘要（原 `日志2023.6.6.txt`）：改模数转换程序后曾无法正常工作，因混入电机相关源码、出现重复主函数，单片机实际跑的是电机程序——故本次从 AD「光敏电阻」等路径坚决剔除电机 / 按键 / I2C / LCD 板厂残留。

## 如何自行搭配板厂驱动编译

1. 用 Keil μVision 新建 8051 / C51 工程，把对应目录下的 `main.c`（或 `main1.c`）加入工程。
2. 从你自己的开发板例程包中，按 `main` 里的 `#include` 补齐缺失驱动，例如：
   - AD 类：`XPT2046.c` / `XPT2046.h`
   - 温度显示类：`lcd.c` / `lcd.h`、`temp.c` / `temp.h`
   - 智能温控：`lcd` / `temp` / `i2c` / `key` / `public` 等
3. 管脚与晶振以开发攻略 / 例程说明为准；本仓库**不**附带厂商驱动，避免版权与重复副本问题。
4. 仓库 `.gitignore` 已忽略常见 Keil 产物。

## 来源说明

- 源目录：`D:\experiment\`（保持原样，未改动）
- 输出目录：`D:\repos\mcu51-lab-notes\`（本次清空后覆盖重建）
- 复制方式：字节级拷贝（保留原文件编码）