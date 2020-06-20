# LoRaWAN-STM32L072-RT-Thread
# 1 简介
LoRaWAN-STM32L072-RT-Thread工程是基于RT-Thread封装的LoRaWAN工程，可用于快速搭建基于LoRa等通信的应用产品。<br />LoRa-Radio-Driver软件包在LoRaWAN开源协议栈[LoRaMAC-Node中的radio]()基础上，进一步封装实现。
> LoRaMac\Radio
> [https://github.com/Lora-net/LoRaMac-node/tree/master/src/radio](https://github.com/Lora-net/LoRaMac-node/tree/master/src/radio)

- 主要特点:
   - 当前支持的调制方式
      - 支持调制方式
         - [x] LoRa
         - [ ] FSK
- 当前支持LoRa 模块\芯片
   - LoRa Transceiver (SPI)
      - SX126X
        - [x] ASR6500S ( SX1262 )
# 2 使用方法
采用RT-Thread Studio直接导入工程即可，暂未配置Finsh，由Main函数直接启动线程。
