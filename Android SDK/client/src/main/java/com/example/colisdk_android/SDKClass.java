package com.example.colisdk_android;

import android.app.Activity;
import android.view.View;

import com.unity3d.player.UnityPlayer;

public class SDKClass {

   protected View view = null;
   protected Activity context; // Unity的Active
    public void init()
    {
        view = UnityPlayer.currentActivity.getWindow().getCurrentFocus();
        context =  UnityPlayer.currentActivity;
    }
}
