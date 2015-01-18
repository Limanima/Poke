package limanima.FatCatsAndMice.app;
import java.net.*;
import android.content.Intent;
import android.net.Uri;

// 
public class PKaWeb 
{
	//
	public static boolean WithInternetConnection() 
	{
		try 
		{
			URLConnection urlConnection = new URL("http://www.google.com").openConnection();
			urlConnection.setConnectTimeout(400);
			urlConnection.connect();
			return true;
		} 
		catch (Exception e) 
		{
			PKaLog.WriteError("Error in PKaWeb.WithInternetConnection()." + e.getMessage());
			return false;
		}
	}
	
	//
	public static void OpenURL(String url) 
	{
		try
		{
			PKaLog.WriteInfo("Going to open URL " + url + " on android browser.");	
			Intent i = new Intent(android.content.Intent.ACTION_VIEW);
			i.setData(Uri.parse(url));
			FatCatsAndMiceActivity.GetInstance().startActivity(i);
		} 
		catch (Exception e) 
		{
			PKaLog.WriteError("Error in PKaWeb.OpenURL()." + e.getMessage());	
		}
	}
}
