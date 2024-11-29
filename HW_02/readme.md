# Homework 2

视频地址：[UE-第二次作业_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1nPzqYVEdM/?vd_source=69b4485adcb7b0d8d2c1f9e475b82e1e)

本次作业过程主要由C++编写逻辑，混搭了一点蓝图用作参数配置。

实现：

- 开局随机选择 M 个方块变成红色，并分数翻 N 倍。
- 在 T 秒后游戏结束，输出并打印每个玩家的分数。
- 实现网络 & UI。

## GameMode

- 方块随机选择逻辑。
- Timer 倒计时逻辑。

## TP_WeaponComponent

修改了开火逻辑，client 调用 server rpc 生成子弹。

## CubeActor

受击逻辑主要在这里，添加了一些 Replicated 变量保证状态同步。

## PlayerController

添加了 client rpc，游戏时间到达后由服务器调用，本地禁止输入并且打印分数。