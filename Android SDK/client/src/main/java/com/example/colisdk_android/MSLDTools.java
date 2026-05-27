package com.example.colisdk_android;

import static android.content.Context.SENSOR_SERVICE;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.util.Log;
import com.msld.tools.SimulatorTool;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class MSLDTools {
    public static final String ErrorAgency = "ErrorAgency";
    public static String agencyInfo = "";

    /**
     * 传感器数量小于18判断为 模拟器这个可能会误杀低端机
     * 测试小米手机40+传感器数量
     * 华为mate p 20+
     * 其他 30+
     * 夜神模拟器 12
     */
    public static  boolean isSimulator(Context context) {
        SensorManager sm = (SensorManager) context.getSystemService(SENSOR_SERVICE);
        int num = sm.getSensorList(Sensor.TYPE_ALL).size();
//        Log.e("unity", "传感器数量：" + num);
        return num < 18;
    }

    public static void CrashSimulator(Context context){
        if( isSimulator(context) ){
            SimulatorTool.DoNothing();
        }
    }

//*************************************** 代理相关 *******************************************
    private static int bytes2int(byte[] bytes, int offset) {
        ByteBuffer buffer = ByteBuffer.allocate(8);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.put(bytes[offset]);
        buffer.put(bytes[offset + 1]);
        buffer.put(bytes[offset + 2]);
        buffer.put(bytes[offset + 3]);
        return buffer.getInt(0);
    }

    private static long bytes2Long(byte[] bytes, int offset) {
        ByteBuffer buffer = ByteBuffer.allocate(8);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.put(bytes[offset]);
        buffer.put(bytes[offset + 1]);
        buffer.put(bytes[offset + 2]);
        buffer.put(bytes[offset + 3]);
        buffer.put(bytes[offset + 4]);
        buffer.put(bytes[offset + 5]);
        buffer.put(bytes[offset + 6]);
        buffer.put(bytes[offset + 7]);
        return buffer.getLong(0);
    }

    public static String readApkv2(String path) {
        byte[] eocdMagic = {0x50 ,0x4b,0x05 ,0x06};
        byte[] bytes = null;
        int channelSign = 100910;
        int eocdMaxLen = 0xffff;
        try {
            File file = new File(path);
            RandomAccessFile accessFile = new RandomAccessFile(file, "r");
            long fileLen = accessFile.length();
            // 文件最后两个字节代表了comment的长度
            bytes = new byte[eocdMaxLen];
            accessFile.seek(fileLen-eocdMaxLen);
            accessFile.readFully(bytes);
            int pos = -1;
            for (int i=0;i<bytes.length;i++){
                if(pos >=0){
                    break;
                }
                for(int n = 0;n<eocdMagic.length;n++){
                    if(eocdMagic[n]!=bytes[i+n]){
                        break;
                    }
                    if(n==eocdMagic.length-1){
                        pos = i;
                    }
                }
            }
            if(pos == -1){
                Log.e("Unity ", "Error Length");
                return ErrorAgency;
            }

            int offset =  bytes2int(bytes, pos+16);
            bytes = new byte[8];
            accessFile.seek(offset-16-8);
            accessFile.readFully(bytes);
            long contentLength = bytes2Long(bytes,0);

            long start = offset - contentLength ;
            long kvLength = contentLength-16-8;
            bytes = new byte[(int)kvLength];
            accessFile.seek(start);
            accessFile.readFully(bytes);
            String r = "";
            for (int i=0;i<kvLength;){
                int kvlen = (int)bytes2Long(bytes, i);
                int sign = bytes2int(bytes,i+8);
                if(sign==channelSign){
                    byte[] s= new byte[kvlen-4];
                    System.arraycopy(bytes,i+12,s,0,kvlen-4);
                    r = new String(s, "utf-8");
                    break;
                }
                i+=kvlen+8;
            }
//            Log.e("Unity ", "r: " + r);
            return r;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Log.e("Unity ", "agency is null");
        return null;
    }

}

