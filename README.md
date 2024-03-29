# GI Dice
这是一种原神七圣召唤中的元素骰子的可低成本 DIY 的实现  
本设计中，除了外壳、元素图标及 PCB 需要给 JLC 氪点之外，其余全部使用立创商城或淘宝零售可买到的全新部件实现，无需额外定制  
关于使用效果，你可以看看 [BV1Gs4y1t7k7](https://www.bilibili.com/video/BV1Gs4y1t7k7)  
![image](https://user-images.githubusercontent.com/8705034/222403405-049926f7-dd81-42ee-9be6-d858ec9ba666.png)  

## 特性
 - CH573F 主控，通过蓝牙广播实现多个骰子同时向中控传输骰子朝向及电量信息
 - 打牌计分中控我没打算做，但给出了在 ESP32-S3 上做接收的例程，想做中控的可以直接对接
 - LIS2DW12 三轴加速度传感器
 - 8 个 APA102 (SK9822) RGB LED，支持关断 LED 电源以省电（*见下文续航）
 - LIR1240 55mAh 锂电池，以及正经的充电管理和电池保护 IC
 - 使用无线充电，同样开源了配套的充电盒
 - 霍尔传感器实现放入充电盒后关断电源
 - 正八面体，边长 22mm

续航与电池电压、温度、元件及使用场景等多种因素有关，没有全面地测量过，这里只给出我的一次测量的结果用于粗略估计  
|  工作状态   | 电池的输出电流  |
|  ----  | ----  |
| 正常工作，蓝牙广播，1灯亮  | ~7.5mA |
| 正常工作，蓝牙配对，1灯亮  | ~9.5mA |
| 正常工作，蓝牙广播，灯灭  | ~2.5mA |
| 正常工作，蓝牙配对，灯灭  | ~4.5mA |
| 十分钟（默认）无动作后休眠  | ~数十uA |
| 放入充电盒盖上盖子  | ~8uA |


## TO-DOs 
写完各个 README 

## 开源协议  
本仓库内全部的 原理图、PCB、外壳，适用于 CERN-OHL-S v2 或任何之后的版本  
其中，霍尔开关和无线充电的部分设计有参考 [jeansimonet/Pixels](https://github.com/jeansimonet/Pixels) 项目，该项目基于 MIT 协议开源  
  
dice/src 下包含的软件中，我自己写的部分基于 GPL v3 开源（反正加一起也没写几行还写得那么烂不会真的有人想在这上面改吧x   
其他需要作出声明的包括：
 - lis2dw12 驱动来自 [STMicroelectronics/lis2dw12-pid](https://github.com/STMicroelectronics/lis2dw12-pid)，原代码基于 BSD 3-Clause 协议开源
 - 代码主体修改自 [CH573EVT](https://www.wch.cn/downloads/CH573EVT_ZIP.html) 的 BLE_UART 示例，原代码基于 Apache-2.0 协议开源  
 - esp32_dice_scanner 修改于 [espressif/arduino-esp32](https://github.com/espressif/arduino-esp32) 中提供的 BLE_Beacon_Scanner 示例，由于基于 LGPL-2.1 开源，这部分就跟着用相同的   

作者不对 dice/panel 目录下带有元素图标的面板打印文件声明任何协议，作者也没有把这个文件商用，总之就是先放这    
其中图纸来自 [B站 @芒果小强DY：教你如何实现元素骰子自由](https://www.bilibili.com/video/BV1S14y1K7hi)，但其中的美术素材（元素 Logo）版权归属于自由的 mhy  
如果认为这部分有侵权的话，请联系删除  

禁止拿去做毕设，你也不想被你的答辩老师知道你平日其实都在原神里打牌吧（  
