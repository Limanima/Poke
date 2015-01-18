package limanima.FatCatsAndMice.app;
import java.net.*;
import android.content.Intent;
import android.net.Uri;

// 
public class PKaAppStore
{
	
	//
	public static void OpenAppPage(String packageName) 
	{
		try
		{
			Intent i = new Intent(android.content.Intent.ACTION_VIEW);
			
			PKaLog.WriteInfo("Going to open App (package '" + packageName + "') in Google Play Store.");	
			try 
			{
				i.setData(Uri.parse("market://details?id=" + packageName));
				FatCatsAndMiceActivity.GetInstance().startActivity(i);
			} 
			catch (android.content.ActivityNotFoundException anfe) 
			{
				i.setData(Uri.parse("http://play.google.com/store/apps/details?id=" + packageName));
				FatCatsAndMiceActivity.GetInstance().startActivity(i);
			}
		} 
		catch (Exception e) 
		{
			PKaLog.WriteError("Error in PKaAppStore.OpenAppPage()." + e.getMessage());	
		}
	}
}
