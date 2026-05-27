package com.example.Permission;

import java.util.ArrayList;

public interface  PermissionCallbacks
{
  public void  onPermissionsGranted(String strs);
  public void onPermissionsDenied(String strs);
}
