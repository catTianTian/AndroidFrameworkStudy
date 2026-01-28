// package com.example.aidl;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

// 2. 实现 Service (Server端)
// 这里的 "Stub" 是 AIDL 自动生成的内部抽象类，它继承了 Binder 并实现了 IMyAidlInterface 这个接口
// 所以我们只需要继承它，然后填空(实现具体方法)即可
public class MyService extends IMyAidlInterface.Stub {
    private static final String TAG = "MyService";

    @Override
    public int add(int a, int b) throws RemoteException {
        // 具体的业务逻辑
        Log.i(TAG, "Remote called add: " + a + " + " + b);
        return a + b;
    }

    @Override
    public void connect(String clientName) throws RemoteException {
        Log.i(TAG, "Client connected: " + clientName);
    }

    // ----------------------------------------------------
    // 下面是程序的 main 函数，负责启动服务
    // 这和写普通的 appService 不一样，因为我们是作为一个独立进程跑在 shell 里的
    // ----------------------------------------------------
    public static void main(String[] args) {
        // 3. 注册服务
        // 在 Java 层，ServiceManager.addService 是一个隐藏 API (Hidden API)
        // 但我们在源码环境下编译，是可以直接调用的
        try {
            Log.i(TAG, "Registering service 'myservice'...");
            ServiceManager.addService("myservice", new MyService());
            Log.i(TAG, "Service registered! Waiting for requests...");
            
            // 4. 阻塞主线程，保持存活
            // 对于 Java 进程，只要有 Binder 线程在跑，主线程怎么处理是个学问
            // 这里我们用一个基于 Looper 的经典死循环写法
            android.os.Looper.prepare();
            android.os.Looper.loop();
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
