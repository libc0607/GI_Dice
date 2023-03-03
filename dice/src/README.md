# BLE_Dice demo 

与 CH573EVT V2.2 版本一同测试通过  
代码参考了 CH573EVT V2.2 中的 BLE_UART Demo  
下文截图使用了沁恒的 BLE 调试助手 APP  

## 使用 BLE 和打牌中控进行交互  
如果你正试图实现打牌中控，那么目前支持通过两种方式经 BLE 获取骰子的状态信息，分别为监听广播包（一对多）和配对后（一对一）  
![image](https://user-images.githubusercontent.com/8705034/222700474-fc90bcaa-f36f-4afb-9436-ae7814d4eb67.png)


### 从广播包中获取信息   
![image](https://user-images.githubusercontent.com/8705034/222694336-d8461e77-7ef5-4a51-9ada-0b136faa1467.png)  

| 长度 | 类型 | 数据 | 数据在 advert/scan_rsp 包中 | 备注 |
|---|---|---|---|---|
| 2 | GAP_ADTYPE_FLAGS | DEFAULT_DISCOVERABLE_MODE \| GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED | advert | 默认 | 
| 3 | GAP_ADTYPE_16BIT_MORE | 16bit 短 Service UUID，fff0 | advert | 修改自 BLE_UART，默认 |
| 5 | GAP_ADTYPE_MANUFACTURER_SPECIFIC | “制造商数据”：'G'(0x47), 'I'(0x49), (uint8)((电池电压mV-3200)/4), ([lis_dice_8d_t](https://github.com/libc0607/GI_Dice/blob/a4a67a805def9365946631231ff4620e6b9b3964/dice/src/BLE_Dice/APP/include/lis2dw12_glue.h#L44))朝向 | advert | 只解析这个即可 |
| 9 | GAP_ADTYPE_LOCAL_NAME_COMPLETE | 骰子显示的名称：Dice8AA1，前4固定，后4字节是MAC地址末尾且大写 | scan_rsp | 可用于判定&配对检查 | 
  
### BLE 配对后进行交互 
这部分本质上是直接使用了 BLE_UART 示例中提供的虚拟串口来发送与接收数据   
Service UUID 为 0xfff0  
![image](https://user-images.githubusercontent.com/8705034/222698269-3cb4fb84-fd10-4d7a-9f41-67c45f251e31.png)  

Characteristic 0xfff1 为 骰子->中控，接收骰子发来的数据时，打开 Notify，然后接收就行   
数据格式为：
'#'，电池电压mV，温度（但是好像Bug了），([lis_dice_8d_t](https://github.com/libc0607/GI_Dice/blob/a4a67a805def9365946631231ff4620e6b9b3964/dice/src/BLE_Dice/APP/include/lis2dw12_glue.h#L44))朝向，加速度[0]，加速度[1]，加速度[2]  
其中加速度范围为 [-2000, 2000]，单位为 mg  
![image](https://user-images.githubusercontent.com/8705034/222698630-5f67ac4c-09da-40ec-85eb-2883e30e98c2.png)   

Characteristic 0xfff2 为 中控->骰子，这坨代码目前只能接收一种数据，即在接收到字符 'F' 后点亮全部 LED 约一秒，用于实现初次与中控配对时在一堆骰子里找到对应的骰子  
![image](https://user-images.githubusercontent.com/8705034/222700094-8f4fe3e0-ed33-4985-ab34-9c227b9fe8c4.png)

