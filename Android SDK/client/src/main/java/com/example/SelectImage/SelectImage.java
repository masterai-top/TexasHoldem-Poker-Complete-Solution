package com.example.SelectImage;

import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.provider.MediaStore;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;

import com.example.colisdk_android.SDKClass;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;

import static android.app.Activity.RESULT_OK;
import static androidx.core.app.ActivityCompat.startActivityForResult;

public class SelectImage extends SDKClass {
    private static SelectImage instance;

    public static SelectImage Instance() {
        if (instance == null) {
            instance = new SelectImage();
            instance.init();;
        }
        return instance;
    }

    private final String MSG_SELECT_IMAGE = "Unity SelectImage";
    private Message onlyMsg;

    public static final int IMAGE_REQUEST_CODE = 0x198663;
    GetImageCallback callback;
    Integer quality = 100;
    private final Handler mhandler = new Handler(new Handler.Callback() {
        @Override
        public boolean handleMessage(@NonNull Message msg) {
            switch (msg.what) {
                case 0:
                    Log.w(MSG_SELECT_IMAGE, "选择相片执行回调" + msg);
                    if (callback != null) {
                        JSONObject jsonData = (JSONObject) msg.obj;
                        try {
                            String result = jsonData.getString("resoult");
                            int width = jsonData.getInt("bitmapWidth");
                            int height = jsonData.getInt("bitmapHeight");
                            callback.onGetImage(result, width, height);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                    break;
                case 1:
                    Log.w(MSG_SELECT_IMAGE, "保存相片回调" + msg);
                    if (callback != null) {
                        int resultCode = (int) msg.obj;
                        callback.onSaveImageCallback(resultCode);
                    }
                    break;
                default:
                    Log.w(MSG_SELECT_IMAGE, "msg.what???" + msg);
                    break;
            }
            return false;
        }
    });

    public void OnDestroy()
    {
         mhandler.removeCallbacksAndMessages(null);
    }

    private void SendMsg(int what, Object obj)
    {
        onlyMsg = Message.obtain();
        onlyMsg.what = what;
        onlyMsg.obj = obj;
        mhandler.sendMessage(onlyMsg);
    }

    // 选择相册图像
    public void select(String unityQuality, GetImageCallback unityCallback) {
        callback = unityCallback;
        Log.w(MSG_SELECT_IMAGE,"图片的质量为" + unityQuality);
        quality = Integer.parseInt( unityQuality);
        Bundle bundle = new Bundle();
        //在这里跳转到手机系统相册里面
        Intent intent = new Intent(
                Intent.ACTION_PICK,
                android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(context, intent, IMAGE_REQUEST_CODE, bundle);
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        //在相册里面选择好相片之后调回到现在的这个activity中
        switch (requestCode) {
            case IMAGE_REQUEST_CODE://这里的requestCode是我自己设置的，就是确定返回到那个Activity的标志
                if (resultCode == RESULT_OK) {//resultcode是setResult里面设置的code值
                    try {
                        Uri selectedImage = data.getData(); //获取系统返回的照片的Uri
                        String[] filePathColumn = {MediaStore.Images.Media.DATA};
                        Cursor cursor = context.getContentResolver().query(selectedImage,
                                filePathColumn, null, null, null);//从系统表中查询指定Uri对应的照片
                        cursor.moveToFirst();
                        int columnIndex = cursor.getColumnIndex(filePathColumn[0]);

                        String  path = cursor.getString(columnIndex);  //获取照片路径
                        cursor.close();
                        fileBase64String(path);
                        Bitmap bitmap = BitmapFactory.decodeFile(path);
                        SendMsg(0, getImageInfo(bitmap));
                    } catch (Exception e) {
                        Log.w(MSG_SELECT_IMAGE,"执行出错" + e.getMessage());
                        e.printStackTrace();
                    }
                }
                break;
            default:
                break;
        }
    }

    JSONObject getImageInfo(Bitmap bitmap) throws JSONException {
        String resoult =  bitmapToBase64(bitmap);
        int bitmapHeight = bitmap.getHeight();
        int bitmapWidth = bitmap.getWidth();
        JSONObject dates = new JSONObject();
        dates.put("resoult",resoult);
        dates.put("bitmapHeight",bitmapHeight); // 谷歌内购标示
        dates.put("bitmapWidth",bitmapWidth);
        return  dates;
    }

    // 将Bitmap转换成Base64字符串
    private String bitmapToBase64(Bitmap bitmap ) {
        String result = null;
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try {
            if (bitmap != null) {
                bitmap.compress(Bitmap.CompressFormat.JPEG, quality, baos);
                baos.flush();
                baos.close();

                byte[] bitmapBytes = baos.toByteArray();


                result = Base64.encodeToString(bitmapBytes, Base64.NO_WRAP);
            }
        } catch (IOException e) {
            Log.w(MSG_SELECT_IMAGE, e.getMessage());
            e.printStackTrace();
        } finally {
            try {
                if (baos != null) {
                    baos.flush();
                    baos.close();
                }
            } catch (IOException e) {
                Log.w(MSG_SELECT_IMAGE, e.getMessage());
            }
        }
        return result;
    }

    // 将Base64字符串转换成Bitmap
    private Bitmap Base64ToBitmap(String base64Str)
    {
        if(TextUtils.isEmpty(base64Str)){
            return null;
        }
        Bitmap bitmap = null;
        byte[] btimapArray = new byte[0];
        try{
            Log.w(MSG_SELECT_IMAGE,"Base64ToBitmap: " + base64Str.length());
            btimapArray = Base64.decode(base64Str, Base64.DEFAULT);
            bitmap = BitmapFactory.decodeByteArray(btimapArray, 0, btimapArray.length);
        }catch (Exception e){
            Log.w(MSG_SELECT_IMAGE,"Base64ToBitmap Exception: " + e.getMessage());
        }
        return bitmap;
    }

    // 图片文件转Base64字符串
    private String fileBase64String(String path){
        try {
            FileInputStream fis = new FileInputStream(path);//转换成输入流
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int count = 0;
            while((count = fis.read(buffer)) >= 0){
                baos.write(buffer, 0, count);//读取输入流并写入输出字节流中
            }
            fis.close();//关闭文件输入流
            String uploadBuffer = new String(Base64.encodeToString(baos.toByteArray(),Base64.DEFAULT));  //进行Base64编码
            return uploadBuffer;
        } catch (Exception e) {
            return null;
        }
    }

    // 保存bitmap到相册
    public void saveImage(final String base64Str, String fileName, GetImageCallback unityCallback)
    {
        Log.w(MSG_SELECT_IMAGE,"saveImage call");
        callback = unityCallback;

        //获取要保存的图片的位图
        //Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.image1);
        //API 29之前可用. API29之后该方法已经被弃用了
        //MediaStore 相当于管理媒体资源的一个管理器，类似于一个数据库，对媒体资源的一个索引(包括图片 音频 视频)，在里面都有索引
        //if (MediaStore.Images.Media.insertImage(getContentResolver(), bitmap, "", "") == null) {
        //      Toast.makeText(this, "保存失败！", Toast.LENGTH_SHORT).show();
        //} else {
        //      Toast.makeText(this, "保存成功！", Toast.LENGTH_SHORT).show();
        //}

        //创建一个子线程，将耗时任务在子线程中完成，防止主线程被阻塞
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    //创建一个保存的Uri
                    Uri saveUri = context.getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, new ContentValues());
                    if (TextUtils.isEmpty(saveUri.toString())) {
                        Looper.prepare();
                        Log.w(MSG_SELECT_IMAGE,"save failed saveUri is null");
                        SendMsg(1, -1);
                        Looper.loop();
                        return;
                    }
                    OutputStream outputStream = context.getContentResolver().openOutputStream(saveUri);
                    //将位图写出到指定的位置
                    //第一个参数：格式JPEG 是可以压缩的一个格式 PNG 是一个无损的格式
                    //第二个参数：保留原图像90%的品质，压缩10% 这里压缩的是存储大小
                    //第三个参数：具体的输出流

                    Bitmap bitmap = Base64ToBitmap(base64Str);
                    if(bitmap != null){
                        if (bitmap.compress(Bitmap.CompressFormat.JPEG, 90, outputStream)) {
                            Looper.prepare();
                            Log.w(MSG_SELECT_IMAGE,"save success");
                            SendMsg(1, 0);
                            Looper.loop();
                        } else {
                            Looper.prepare();
                            Log.w(MSG_SELECT_IMAGE,"save failed compress");
                            SendMsg(1, -2);
                            Looper.loop();
                        }
                    }
                    else{
                        Looper.prepare();
                        Log.w(MSG_SELECT_IMAGE,"save failed bitmap is null");
                        SendMsg(1, -3);
                        Looper.loop();
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
