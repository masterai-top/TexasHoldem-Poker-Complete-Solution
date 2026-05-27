package com.example.SelectImage;

public interface  GetImageCallback
{
    public void onGetImage(String path, int width, int height);
    public void onSaveImageCallback(int resultCode);
}
