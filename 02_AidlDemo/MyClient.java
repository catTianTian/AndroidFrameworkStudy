// package com.example.aidl;

import android.os.IBinder;
import android.os.ServiceManager;
import android.util.Log;

public class MyClient {
    private static final String TAG = "MyClient";

    public static void main(String[] args) {
        try {
            // 5. 查找服务
            // 依然是通过 ServiceManager 找
            IBinder binder = ServiceManager.getService("myservice");
            if (binder == null) {
                Log.e(TAG, "Can not find 'myservice'!");
                return;
            }

            // 6. 核心魔法 (asInterface)
            // 调用 AIDL 自动生成的 Stub.asInterface 方法
            // 它会自动判断是返回 Proxy 还是 Stub
            IMyAidlInterface service = IMyAidlInterface.Stub.asInterface(binder);

            // 7. 像调用本地对象一样调用远程方法
            service.connect("Client-A");
            int result = service.add(10, 20);
            
            Log.i(TAG, "10 + 20 = " + result);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
