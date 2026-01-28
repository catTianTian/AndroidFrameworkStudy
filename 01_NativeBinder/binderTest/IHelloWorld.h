#ifndef IHELLOWORLD_H
#define IHELLOWORLD_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

// 1. 定义接口
// 必须继承自 IInterface
class IHelloWorld : public IInterface {
public:
    // 这是一个宏，替我们声明了 asInterface(), getInterfaceDescriptor() 等标准方法
    DECLARE_META_INTERFACE(HelloWorld);

    // 定义我们自己的业务方法
    virtual void hello(const char* name) = 0;
};

// 2. 定义 Server 端的 Stub (桩)
// Bn = Binder Native
// 继承自 BnInterface<IHelloWorld>，这样它即是 Binder 对象，又是 IHelloWorld 接口
class BnHelloWorld : public BnInterface<IHelloWorld> {
public:
    // 也就是 onTransact
    // code: 区分调用哪个函数
    // data: 也就是参数包裹
    // reply: 返回结果包裹
    // flags: 是否是单向调用等
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

} // namespace android

#endif // IHELLOWORLD_H
