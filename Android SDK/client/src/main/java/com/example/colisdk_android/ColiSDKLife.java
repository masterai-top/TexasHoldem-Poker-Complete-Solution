package com.example.colisdk_android;

import android.content.Intent;

import com.example.DeviceID.DeviceIdGet;
import com.example.Permission.PermissionsSet;
import com.example.SelectImage.SelectImage;

import org.json.JSONException;


class  ColiSDKLife
{
    public static ColiSDKLife instance;

    public static ColiSDKLife getInstance() {
        if (instance == null)
            instance = new ColiSDKLife();
        return instance;
    }

    public void onCreate() throws JSONException {
        DeviceIdGet.Instance().OnCreat();
    }

    public void onDestroy()
    {
        SelectImage.Instance().OnDestroy();
        DeviceIdGet.Instance().OnDestroy();
        PermissionsSet.Instance().OnDestroy();
    }

    public void onStart()
    {

    }
    public void onResume()
    {

    }

    public void onStop()
    {

    }

    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        SelectImage.Instance().onActivityResult(requestCode, resultCode, data);
    }
}