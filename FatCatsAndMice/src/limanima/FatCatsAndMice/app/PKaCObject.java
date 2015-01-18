package limanima.FatCatsAndMice.app;

import android.util.Log;

// 
public class PKaCObject 
{
	private long _cObjAddress;

	public PKaCObject(long cObjAddress)
	{
		_cObjAddress = cObjAddress;
}
	
	public long GetCObject()
	{
		return _cObjAddress;
	}

}
