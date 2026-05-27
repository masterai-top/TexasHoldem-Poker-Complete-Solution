package com.example.DeviceID;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import androidx.annotation.NonNull;

import com.bun.miitmdid.core.JLibrary;
import com.bun.supplier.IIdentifierListener;
import com.bun.supplier.IdSupplier;
import com.example.colisdk_android.SDKClass;

import org.json.JSONException;
import org.json.JSONObject;

public class DeviceIdGet extends SDKClass  {
    public OAIDEvent onIdGet;
    static DeviceIdGet instance = new DeviceIdGet();
    OldVersionGetDrviceID oldVersionGet = new OldVersionGetDrviceID();
    NewVersionGetDrviceId newVersionGet = new NewVersionGetDrviceId();

    private final android.os.Handler mhandler = new Handler(new Handler.Callback() {
        @Override
        public boolean handleMessage(@NonNull Message msg) {
            Log.w("Unity", "Get msg deviceid" + msg.obj.toString());
            onIdGet.OnIdsAvalid(msg.obj.toString());
            return false;
        }
    });

    public static DeviceIdGet Instance()
    {
        return  instance;
    }

    public void OnDestroy()
    {
        mhandler.removeCallbacksAndMessages(null);
    }

    public void getDeviceID(OAIDEvent oaidEvent)
    {
        Log.w("Unity", "get deviceid");
        if ( Build.VERSION.SDK_INT < 29)
        {
            oaidEvent.OnIdsAvalid(GetReturn(oldVersionGet.getDeviceId(context)));
        }
        else
        {
            onIdGet = oaidEvent;
            newVersionGet.GetDeviceId(mhandler);
        }
    }

    public String GetReturn(String msg)
    {
        JSONObject data = new JSONObject();
        try{
            data.put("type", "DeviceID");
            data.put("data", msg);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return  data.toString();
    }

    // OAID获取的初始化
    public void OnCreat()
    {
        this.init();
        try {
            JLibrary.InitEntry(context);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
