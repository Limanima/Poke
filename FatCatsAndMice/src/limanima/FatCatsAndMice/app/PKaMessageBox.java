package limanima.FatCatsAndMice.app;
import android.app.AlertDialog;
import android.content.DialogInterface;

// 
public class PKaMessageBox
{
	static String m_caption;
	static String m_message;
	static String m_button1Text;
	static String m_button2Text;
	static String m_button3Text;
	
	static native void Button1Clicked();
	static native void Button2Clicked();
	static native void Button3Clicked();
	
	public static void Show(String caption, String message, String button1Text, String button2Text, String button3Text)
	{
		m_caption = caption;
		m_message = message; 
		m_button1Text = button1Text; 
		m_button2Text = button2Text; 
		m_button3Text = button3Text;
		FatCatsAndMiceActivity.GetInstance().runOnUiThread(new Runnable() {
            @Override
            public void run() 
            {
            	PKaMessageBox.InternalShow();
            }
        });
	}
    //
	public static void InternalShow()
	{
		AlertDialog.Builder builder = new AlertDialog.Builder(FatCatsAndMiceActivity.GetInstance());
		builder.setTitle(m_caption);
		builder.setMessage(m_message);
		builder.setPositiveButton(m_button1Text, 
				new DialogInterface.OnClickListener() 
					{
	        			public void onClick(DialogInterface dialog, int which) 
	        			{ 
	        				PKaMessageBox.Button1Clicked();
	        			}
	        		}
					);
		if (m_button2Text!= null && m_button2Text.length() != 0)
		{
			builder.setNeutralButton(m_button2Text, 
					new DialogInterface.OnClickListener() 
						{
		        			public void onClick(DialogInterface dialog, int which) 
		        			{ 
		        				PKaMessageBox.Button2Clicked();
		        			}
		        		}
						);
		}
		
		if (m_button3Text!= null && m_button3Text.length() != 0)
		{
			builder.setNegativeButton(m_button3Text, 
					new DialogInterface.OnClickListener() 
						{
		        			public void onClick(DialogInterface dialog, int which) 
		        			{ 
		        				PKaMessageBox.Button3Clicked();
		        			}
		        		}
						);
		}		
		
		AlertDialog alertDialog = builder.create();
		alertDialog.show();
	
	}
}
