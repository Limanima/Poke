package limanima.FatCatsAndMice.app;

import android.util.Log;

// 
public class PKaPlayer extends PKaCObject
{
	static native void GamerServicesLogin(boolean success);
	static native void GamerServicesLogout();

	public PKaPlayer(long cObjAddress)
	{
		super(cObjAddress);
}
	
	public static PKaPlayer CreateInstance(long cObjAddress)
	{
		return new PKaPlayer(cObjAddress);
	}
	
	public boolean IsSignedIn()
	{
		return FatCatsAndMiceActivity.GetInstance().isSignedIn();
	}
	
	public void DoSignIn()
	{
		FatCatsAndMiceActivity.GetInstance().beginUserInitiatedSignIn();
	}
	
	public void DoSignOut()
	{
		FatCatsAndMiceActivity.GetInstance().signOut();
	}
}
