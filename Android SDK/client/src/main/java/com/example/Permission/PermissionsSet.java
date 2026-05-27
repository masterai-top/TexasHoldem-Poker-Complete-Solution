package com.example.Permission;

import android.content.pm.PackageManager;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.example.colisdk_android.SDKClass;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

public class PermissionsSet extends SDKClass {
    private static  PermissionsSet instance;
    private Message onlyMsg;

    public static  PermissionsSet Instance()
    {
        if (instance == null)
        {
            instance = new PermissionsSet();
            instance.init();
        }

        return instance;
    }
    private final android.os.Handler mhandler = new Handler(new Handler.Callback() {
        @Override
        public boolean handleMessage(@NonNull Message msg) {
            Log.w("分享或邀请","执行回调"+msg);
            if (callbacks != null)
            {
                if (msg.what == 0)
                {
                    callbacks.onPermissionsGranted(msg.obj.toString());
                }
                else
                {
                    callbacks.onPermissionsDenied(msg.obj.toString());
                }
            }
            return false;
        }
    });

    public  PermissionCallbacks callbacks;
    private static final int permissionResoult = 177;

    public void OnDestroy()
    {
        mhandler.removeCallbacksAndMessages(null);
    }

    /**
     * 通过str解析出有需要请求的权限
     * @param str  需要请求权限的json数据
     * @param _callbacks 请求权限对应的c#回调
     */
    public void RequestPermission(String str ,PermissionCallbacks _callbacks)
    {
        callbacks =_callbacks;
        ArrayList<String> havePermiss = new ArrayList<String>();
        ArrayList<String> notHavePermiss = new ArrayList<String>();
        JSONArray jsonDate = null;
        try {
            jsonDate = new JSONArray(str);
            int num = jsonDate.length();
            for (int i = 0; i < num; i++)
            {
                String permiss =  jsonDate.getString(i);
                if (hasPermissions(permiss))
                {
                    havePermiss.add(permiss);
                }
                else
                {
                    notHavePermiss.add(permiss);
                }
            }
            if (notHavePermiss.size() == 0) // 所有权限都有
            {

                SendMsg(1,"");
                SendMsg(0,"");
                return;
            }
            String[] a = new String[notHavePermiss.size()];
            for(int i = 0 ;i< a.length ;i++)
            {
                a[i]= notHavePermiss.get(i);
            }
            executePermissionsRequest(a,permissionResoult);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    void SendMsg(int what , String obj)
    {
        onlyMsg = Message.obtain();
        onlyMsg.what = what;
        onlyMsg.obj = obj;
        mhandler.sendMessage(onlyMsg);
    }
    /**
     * Check if the calling context has a set of permissions.
     *
     * @return true if all permissions are already granted, false if at least one permission
     * is not yet granted.
     */
    public  boolean hasPermissions( String perm) {
        return  (ContextCompat.checkSelfPermission(context, perm) == PackageManager.PERMISSION_GRANTED);
    }
    /**
     * 安卓权限请求
     * @param perms 请求的权限
     * @param requestCode  结果码
     */
    private  void executePermissionsRequest( String[] perms, int requestCode) {
        try
        {
            ActivityCompat.requestPermissions(context, perms, requestCode);
        }
        catch (Exception e) {
            Log.w("请求权限出错",e.getMessage());
        }
    }



    /**
     * Handle the result of a permission request, should be called from the calling Activity's
     * {@link ActivityCompat.OnRequestPermissionsResultCallback#onRequestPermissionsResult(int, String[], int[])}
     * method.
     * <p/>
     * If any permissions were granted or denied, the Activity will receive the appropriate

     *
     * @param requestCode  requestCode argument to permission result callback.
     * @param permissions  permissions argument to permission result callback.
     * @param grantResults grantResults argument to permission result callback.
     * @throws IllegalArgumentException if the calling Activity does not implement
     *                                  {@link PermissionCallbacks}.
     */
    public  void onRequestPermissionsResult(int requestCode, String[] permissions,
                                            int[] grantResults) {

        if (callbacks == null && permissionResoult  != requestCode)
            return;
        // Make a collection of granted and denied permissions from the request.


        JSONObject granted = new JSONObject();
        JSONObject  denied = new JSONObject();
        try {
            for(int i = 0; i< permissions.length; i++)
            {
                String perm = permissions[i];
                if (grantResults[i] == PackageManager.PERMISSION_GRANTED) {
                    granted.put(granted.length()+"",perm);
                } else {
                    denied.put(granted.length()+"",perm);
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        // Report granted permissions, if any.
        if (granted.length()>0) {
            SendMsg(0,granted.toString());
        }
        else
        {
            SendMsg(0,"");
        }

        // Report denied permissions, if any.
        if (denied.length()>0) {
            SendMsg(1,denied.toString());
        }
        else
        {
            SendMsg(1,"");
        }
    }

}
