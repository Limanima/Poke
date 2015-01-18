package limanima.FatCatsAndMice.app;
import com.google.android.gms.ads.*;
import android.util.Log;;

// Manager para um anuncio AdView da API do google
public class PKaAdBanner extends PKaCObject 
{
	private AdView _adView;
	private boolean _visible;
	private boolean _requesting;
	private String _adId;
	private String [] _testDevicesIds;
	native void AdRequestError(long cObjAddress);
	native void AdRequestSuccess(long cObjAddress);
	
	public PKaAdBanner(long cObjAddress)
	{
		super(cObjAddress);
		_adView = null;
		_visible = false;
}
	
	public static PKaAdBanner CreateInstance(long cObjAddress)
	{
		return new PKaAdBanner(cObjAddress);
	}

	public void SetAdId(String id)
	{
		_adId = id;
	}

	public void SetTestDevices(String testDevices) // Separados por ;
	{
		_testDevicesIds = testDevices.split(";");
	}
	
	public void Show()
	{
		try
		{
			if (_visible == true)
			{
				return;
			}
			
			if (_adView == null)
			{
			    // Create an ad.
				_adView = new AdView(FatCatsAndMiceActivity.GetInstance());
				_adView.setAdSize(AdSize.BANNER);
				_adView.setAdUnitId(_adId);
				_adView.setAdListener(new AdListener() {
					  @Override
					  public void onAdLoaded() 
					  {
						  super.onAdLoaded();
						  
						  FatCatsAndMiceActivity.GetInstance().runOnUiThread(new Runnable() {
					            @Override
					            public void run() {
					            	FatCatsAndMiceActivity.GetInstance().GetLayout().requestLayout();
					            }
					        });
						  AdRequestSuccess(GetCObject());

					  }
					  
					  @Override
					  public void onAdFailedToLoad(int errorCode)
					  {
						  super.onAdFailedToLoad(errorCode);
						  _requesting = false;
						  Hide();
						  AdRequestError(GetCObject());
					  }
					});	
				
				FatCatsAndMiceActivity.GetInstance().runOnUiThread(new Runnable()
				{
					public void run()
					{
						FatCatsAndMiceActivity.GetInstance().GetLayout().addView(_adView);
						AdRequest adRequest = new AdRequest.Builder()
				        	.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
				        	.build();

					    _adView.loadAd(adRequest);
					}
				});
			}
			
		    _visible = true;
			FatCatsAndMiceActivity.GetInstance().runOnUiThread(new Runnable()
			{
				public void run()
				{
					_adView.setVisibility(android.view.View.VISIBLE);
			}
			});
		    
		}
		catch(Exception ex)
		{
			Log.v(PKaConsts.PK_LOG_TAG, "Error in PKa_AdBanner.Show()", ex);
		}
	}
	
  //
	public void Hide()
	{
		_visible = false;
		FatCatsAndMiceActivity.GetInstance().runOnUiThread(new Runnable()
		{
			public void run()
			{
			    _adView.setVisibility(android.view.View.INVISIBLE);
			}
		});
	}

}
