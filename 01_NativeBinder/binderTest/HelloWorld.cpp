#define LOG_TAG "HelloWorld"

#include "IHelloWorld.h"
#include <utils/Log.h>

namespace android {

// ----------------------------------------------------------------------
// 4. Client 端实现 (Proxy)
// ----------------------------------------------------------------------

// Bp = Binder Proxy
class BpHelloWorld : public BpInterface<IHelloWorld> {
public:
  // 构造函数，传入远端的 IBinder 句柄（impl）
  explicit BpHelloWorld(const sp<IBinder> &impl)
      : BpInterface<IHelloWorld>(impl) {}

  virtual void hello(const char *name) {
    Parcel data, reply;
    // 写入 Interface Token，用于校验，防止恶意调用
    data.writeInterfaceToken(IHelloWorld::getInterfaceDescriptor());
    // 写入参数
    data.writeCString(name);

    // 发送给远端！
    // HELLO 是我们自定义的 Transaction ID (通常建议用 enum)
    // remote() 获取的就是远端的 IBinder 句柄
    remote()->transact(IBinder::FIRST_CALL_TRANSACTION, data, &reply);

    // 如果有返回值，可以从 reply 里读取
    // int32_t result = reply.readInt32();
    ALOGI("BpHelloWorld::hello calls, name=%s", name);
  }
};

// 3. 实现 Meta Interface 魔法
// "android.demo.IHelloWorld" 是这个服务的唯一标识 ID
// IMPLEMENT_META_INTERFACE(HelloWorld, "android.demo.IHelloWorld");

// 手动展开宏，为了避开 static_assert 检查并在 BpHelloWorld 定义后使用
const android::String16 IHelloWorld::descriptor("android.demo.IHelloWorld");

const android::String16 &IHelloWorld::getInterfaceDescriptor() const {
  return IHelloWorld::descriptor;
}

android::sp<IHelloWorld>
IHelloWorld::asInterface(const android::sp<android::IBinder> &obj) {
  android::sp<IHelloWorld> intr;
  if (obj != nullptr) {
    intr = static_cast<IHelloWorld *>(
        obj->queryLocalInterface(IHelloWorld::descriptor).get());
    if (intr == nullptr) {
      intr = new BpHelloWorld(obj);
    }
  }
  return intr;
}

IHelloWorld::IHelloWorld() {}
IHelloWorld::~IHelloWorld() {}

// ----------------------------------------------------------------------
// 5. Server 端实现 (Stub)
// ----------------------------------------------------------------------

status_t BnHelloWorld::onTransact(uint32_t code, const Parcel &data,
                                  Parcel *reply, uint32_t flags) {
  switch (code) {
  case IBinder::FIRST_CALL_TRANSACTION: {
    // 校验 Token
    CHECK_INTERFACE(IHelloWorld, data, reply);

    // 读取参数
    const char *name = data.readCString();

    // 调用真正的业务实现 (这个由子类实现，BnHelloWorld 只是个骨架)
    hello(name);

    // 我们的 hello 是 void，不需要写入返回值
    return NO_ERROR;
  }
  }
  // 默认处理 (处理 ping, dump 等基础命令)
  return BBinder::onTransact(code, data, reply, flags);
}

} // namespace android
