// package com.example.aidl;

// 1. 定义接口
// AIDL (Android Interface Definition Language)
// 这个文件会被 aidl 工具处理，自动生成 IMyAidlInterface.java
// 里面包含了我们上节课手写的 Stub 和 Proxy 逻辑
interface IMyAidlInterface {
    /**
     * 计算两个数的和
     */
    int add(int a, int b);
    
    /**
     * 一个带方向标记的示例
     * in: 数据从客户端流向服务端
     * out: 数据从服务端流向客户端
     * inout: 双向流动
     */
    void connect(in String clientName);
}
