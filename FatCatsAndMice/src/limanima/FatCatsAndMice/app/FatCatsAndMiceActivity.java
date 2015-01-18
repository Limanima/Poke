package limanima.FatCatsAndMice.app;
import org.libsdl.app.SDLActivity; 

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.example.games.basegameutils.GameHelper;

public class FatCatsAndMiceActivity extends SDLActivity 
	implements GameHelper.GameHelperListener 
{
	// BaseGameActivity
	protected GameHelper mHelper;
    // We expose these constants here because we don't want users of this class
    // to have to know about GameHelper at all.
    public static final int CLIENT_GAMES = GameHelper.CLIENT_GAMES;
    public static final int CLIENT_APPSTATE = GameHelper.CLIENT_APPSTATE;
    public static final int CLIENT_PLUS = GameHelper.CLIENT_PLUS;
    public static final int CLIENT_ALL = GameHelper.CLIENT_ALL;
    
    // Requested clients. By default, that's just the games client.
    protected int mRequestedClients = CLIENT_GAMES;
    protected boolean mDebugLog = false;
    // BaseGameActivity end
    
	private static FatCatsAndMiceActivity _instance;
	public static FatCatsAndMiceActivity GetInstance()
	{
		return _instance;
	}
	
	public FatCatsAndMiceActivity()
	{
		_instance = this;
	}
	
	public String GetPackageName()
	{
		return getPackageName();
	}
	 
	public ViewGroup GetLayout()
	{
		return mLayout;
	}
	
	public void onSignInSucceeded()
	{
		PKaPlayer.GamerServicesLogin(true);
	}
	
	public void onSignInFailed()
	{
		PKaPlayer.GamerServicesLogin(false);
		
	}
	// BaseGameActivity
    /**
     * Sets the requested clients. The preferred way to set the requested clients is
     * via the constructor, but this method is available if for some reason your code
     * cannot do this in the constructor. This must be called before onCreate or getGameHelper()
     * in order to have any effect. If called after onCreate()/getGameHelper(), this method
     * is a no-op.
     *
     * @param requestedClients A combination of the flags CLIENT_GAMES, CLIENT_PLUS
     *         and CLIENT_APPSTATE, or CLIENT_ALL to request all available clients.
     */
    protected void setRequestedClients(int requestedClients) 
    {
        mRequestedClients = requestedClients;
    }

    public GameHelper getGameHelper() 
    {
        if (mHelper == null) {
            mHelper = new GameHelper(this, mRequestedClients);
            mHelper.enableDebugLog(mDebugLog);
        }
        return mHelper;
    }

    @Override
    protected void onCreate(Bundle b) 
    {
        super.onCreate(b);
        if (mHelper == null) {
            getGameHelper();
        }
        mHelper.setup(this);
        mHelper.setConnectOnStart(false);
    }

    @Override
    protected void onStart() 
    {
        super.onStart();
        mHelper.onStart(this);
    }

    @Override
    protected void onStop() 
    {
        super.onStop();
        mHelper.onStop();
    }

    @Override
    protected void onActivityResult(int request, int response, Intent data) 
    {
        super.onActivityResult(request, response, data);
        mHelper.onActivityResult(request, response, data);
    }

    public GoogleApiClient getApiClient() 
    {
        return mHelper.getApiClient();
    }

    protected boolean isSignedIn() 
    {
        return mHelper.isSignedIn();
    }

    protected void beginUserInitiatedSignIn() 
    {
        mHelper.beginUserInitiatedSignIn();
    }

    protected void signOut() 
    {
        mHelper.signOut();
    }

    protected void showAlert(String message) 
    {
        mHelper.makeSimpleDialog(message).show();
    }

    protected void showAlert(String title, String message) 
    {
        mHelper.makeSimpleDialog(title, message).show();
    }

    protected void enableDebugLog(boolean enabled) 
    {
        mDebugLog = true;
        if (mHelper != null) {
            mHelper.enableDebugLog(enabled);
        }
    }

    protected String getInvitationId() 
    {
        return mHelper.getInvitationId();
    }

    protected void reconnectClient() 
    {
        mHelper.reconnectClient();
    }

    protected boolean hasSignInError() 
    {
        return mHelper.hasSignInError();
    }

    protected GameHelper.SignInFailureReason getSignInError() 
    {
        return mHelper.getSignInError();
    }
    // BaseGameActivity end
}