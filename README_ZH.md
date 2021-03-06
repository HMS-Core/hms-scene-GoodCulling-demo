# HMS Core Scene Kit Good Culling示例代码

[English](README.md) | 中文

## 目录

* [简介](#简介)
* [开发环境](#开发环境)
* [场景展示](#场景展示)
* [运行结果](#运行结果)
* [技术支持](#技术支持)
* [许可证](#许可证)

## 简介

Good Culling 是华为公司 HMS Core 组件 Scene Kit 的一个组成部分，本示例代码演示如何调用libCoreCulling.so对外接口进行遮挡剔除计算。


## 开发环境

* Android Stuido 3.6.1及以上版本
* JDK 1.8及以上版本
* Gradle 4.0及以上版本
* NDK 21.0.6113669及以上版本
* HMS Core (APK) 4.0.2.300及以上版本
* EMUI 10.0及以上版本

## 场景展示
本示例代码中的场景中共有4个物体，运行时场景图如下：

![scene_front.jpg](image/scene_front.jpg)

同时，场景的侧面图如下：

![scene_side.jpg](image/scene_side.jpg)

## 运行结果

输出android log:

![log.PNG](image/log.PNG)

说明：1表示未被遮挡，0表示被遮挡。

##  技术支持

如果您对HMS Core还处于评估阶段，可在[Reddit社区](https://www.reddit.com/r/HuaweiDevelopers/)获取关于HMS Core的最新讯息，并与其他开发者交流见解。

如果您对使用HMS示例代码有疑问，请尝试：

- 开发过程遇到问题上[Stack Overflow](https://stackoverflow.com/questions/tagged/huawei-mobile-services?tab=Votes)，在\[huawei-mobile-services]标签下提问，有华为研发专家在线一对一解决您的问题。
- 到[华为开发者论坛](https://developer.huawei.com/consumer/cn/forum/blockdisplay?fid=18) HMS Core板块与其他开发者进行交流。

如果您在尝试示例代码中遇到问题，请向仓库提交[issue](https://github.com/HMS-Core/hms-scene-GoodCulling-demo/issues)，也欢迎您提交[Pull Request](https://github.com/HMS-Core/hms-scene-GoodCulling-demo/pulls)。

## 许可证

本示例代码采用的许可证为[Apache License, version 2.0](http://www.apache.org/licenses/LICENSE-2.0)。
