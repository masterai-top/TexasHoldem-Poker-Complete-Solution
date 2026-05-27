package com.example.DeviceID;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Build;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.Log;

import static android.content.Context.TELEPHONY_SERVICE;

public class OldVersionGetDrviceID
{
    public  String getDeviceIdentifier(Context ctx) {
        if (getDeviceId(ctx) ==  "")
        {
            return getAndroidId(ctx);
        }
        else
        {
            return  getDeviceId(ctx);
        }
    }
    public  String getDeviceId(Context ctx) {
        String str = "";
        try
        {
            TelephonyManager TelephonyMgr = (TelephonyManager)ctx.getSystemService(TELEPHONY_SERVICE);
            @SuppressLint("MissingPermission") String szImei = TelephonyMgr.getDeviceId();
            str =szImei;
        }
        catch (Exception e)
        {
            Log.w("error","没有权限");
        }
        return str;
    }

    public  String getAndroidId(Context ctx) {
        if (Build.VERSION.SDK_INT <= 14) {
            return Settings.System.getString(ctx.getContentResolver(), Settings.System.ANDROID_ID);
        } else {
            return Settings.System.getString(ctx.getContentResolver(), Settings.Secure.ANDROID_ID);
        }
    }
}
