package com.example.DeviceID;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.bun.miitmdid.core.ErrorCode;
import com.bun.miitmdid.core.JLibrary;
import com.bun.miitmdid.core.MdidSdk;
import com.bun.miitmdid.core.MdidSdkHelper;
import com.bun.supplier.IIdentifierListener;
import com.bun.supplier.IdSupplier;
import com.example.colisdk_android.SDKClass;
import com.unity3d.player.UnityPlayer;

import org.json.JSONException;
import org.json.JSONObject;


public class NewVersionGetDrviceId  extends SDKClass implements IIdentifierListener {
    android.os.Handler hander;
    public Integer GetOAID(){
        int nres = CallFromReflect(context);
        Log.w("Unity", "get OAID return code" + nres);
        Log.d(getClass().getSimpleName(),"return value: " + String.valueOf(nres));
        switch (nres)
        {
            case ErrorCode.INIT_ERROR_DEVICE_NOSUPPORT://不支持的设备
            case ErrorCode.INIT_ERROR_LOAD_CONFIGFILE://加载配置文件出错
            case ErrorCode.INIT_ERROR_MANUFACTURER_NOSUPPORT://不支持的设备厂商
            case ErrorCode.INIT_HELPER_CALL_ERROR://反射调用出错
                this.SendMsg("");
                break;
        }
        return nres;
    }
    public void GetDeviceId(android.os.Handler hander)
    {
        this.hander = hander;
        GetOAID();
    }

    /*
     * 通过反射调用，解决android 9以后的类加载升级，导至找不到so中的方法
     *
     * */
    private int CallFromReflect(Context cxt){

        return MdidSdkHelper.InitSdk( UnityPlayer.currentActivity,true,this);
    }

    @Override
    public void OnSupport(boolean isSupport, IdSupplier _supplier) {
        JSONObject jsonData = new JSONObject();
        if(_supplier==null) {
            this.SendMsg("");
            return;
        }
        String oaid=_supplier.getOAID();
        String vaid=_supplier.getVAID();
        String aaid=_supplier.getAAID();

        try {
            jsonData.put("support", isSupport?"true":"false");
            jsonData.put("OAID", oaid);
            jsonData.put("VAID", vaid);
            jsonData.put("AAID", aaid);
        } catch (JSONException e) {
            Log.w("unity get oaid error", e.getMessage());
        }
        this.SendMsg(jsonData.toString());
    }
    void SendMsg(String msg)
    {
        Message message = new Message();
        message.obj = msg;
        if (hander != null)
            hander.sendMessage(message);
        else
            Log.w("unity", "not find hander on getDeviceID");
    }
}

