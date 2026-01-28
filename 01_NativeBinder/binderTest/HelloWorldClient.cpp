#define LOG_TAG "HelloWorldClient"

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Log.h>


#include "IHelloWorld.h"

using namespace android;

int main(int /*argc*/, char ** /*argv*/) {
  // 12. 同样需要简单的初始化
  sp<ProcessState> proc(ProcessState::self());

  // 13. 获取 ServiceManager
  sp<IServiceManager> sm = defaultServiceManager();

  // 14. 查找名为 "hello" 的服务
  // 返回的是一个通用的 IBinder 句柄
  sp<IBinder> binder = sm->getService(String16("hello"));

  if (binder == nullptr) {
    ALOGE("Can not find hello service!");
    return -1;
  }

  // 15. 核心魔法再次出现！
  // 把通用的 IBinder 转成我们的 IHelloWorld 接口
  // 如果是远程服务，这里会创建 BpHelloWorld
  sp<IHelloWorld> hello = interface_cast<IHelloWorld>(binder);

  // 16. 发起调用
  // 就像调用本地对象一样简单
  hello->hello("World");

  ALOGI("Done.");
  return 0;
}
