#define LOG_TAG "HelloWorldService"

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Log.h>

#include "IHelloWorld.h"

using namespace android;

// 6. 实现具体的 Server 业务逻辑
// 必须继承自 BnHelloWorld
class HelloWorldService : public BnHelloWorld {
public:
  // 实现接口中定义的 pure method
  virtual void hello(const char *name) {
    ALOGI("HelloWorldService: Hello, %s! (I am running in pid=%d)", name,
          getpid());
  }
};

int main(int /*argc*/, char ** /*argv*/) {
  // 7. 初始化 Binder 驱动 (调用 open("/dev/binder"))
  // 设定最大线程数，通常默认就够用了
  sp<ProcessState> proc(ProcessState::self());

  // 8. 获取 ServiceManager (大管家)
  sp<IServiceManager> sm = defaultServiceManager();

  // 9. 注册服务
  // 参数1: 服务名 "hello" (客户端要用这个名字来找)
  // 参数2: 我们的服务实体
  sm->addService(String16("hello"), new HelloWorldService());
  ALOGI("HelloWorldService is registered and ready to serve.");

  // 10. 启动线程池
  // 服务端通常需要开启线程池来处理并发请求
  ProcessState::self()->startThreadPool();

  // 11. 加入线程池循环
  // 主线程也加入进去，一起干活，永不退出
  IPCThreadState::self()->joinThreadPool();

  return 0;
}
