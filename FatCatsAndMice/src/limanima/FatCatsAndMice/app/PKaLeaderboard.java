package limanima.FatCatsAndMice.app;
import android.util.Log;

import com.google.android.gms.games.*;

// 
public class PKaLeaderboard extends PKaCObject
{
	String _leaderboardId;
	
	public PKaLeaderboard(long cObjAddress)
	{
		super(cObjAddress);
}
	
	public static PKaLeaderboard CreateInstance(long cObjAddress, String leaderboardId)
	{
		PKaLeaderboard leaderboard = new PKaLeaderboard(cObjAddress);
		leaderboard._leaderboardId = leaderboardId; 
		return leaderboard;
	}
	
	public boolean SubmitScore(int iScore)
	{
		Games.Leaderboards.submitScore(FatCatsAndMiceActivity.GetInstance().getApiClient(), _leaderboardId, iScore);
		return true;
	}
	
	public boolean Show()
	{
		FatCatsAndMiceActivity.GetInstance().startActivityForResult(Games.Leaderboards.getLeaderboardIntent(FatCatsAndMiceActivity.GetInstance().getApiClient(),
										_leaderboardId), 0);
		return true;
	}
}
