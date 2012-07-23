/* file name: 	ex07.java
 * purpose: 	it's a demo application, will call the "jni native code" from the *.so
 * author: 		guangwei jiang
 * create date: Jan25'10
 * notes:		Make sure this application has right to access the /dev/xx
 * 
 *  History:
 * 
 */
package com.wistron.ex07;



import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class ex07 extends Activity {
	protected Button mButton01;
	protected Button mButton02;
	protected Button mButton03;
	protected Button mButton04;
	protected Button mButton05;

	/*jni native codes interface*/
	public native int ex07Test();
	public native int ex07Set(int test_val);
	public native int ex07Get();

	/* this is used to load the 'ex_07' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.wistron.ex07/lib/libex_07.so at
     * installation time by the package manager.
     */
    static {
        System.loadLibrary("ex_07");
    }
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        mButton01 = (Button)findViewById(R.id.Button01);        
        mButton02 = (Button)findViewById(R.id.Button02);        
        mButton03 = (Button)findViewById(R.id.Button03);
        mButton04 = (Button)findViewById(R.id.Button04);
        mButton05 = (Button)findViewById(R.id.Button05);
        
        
        //will call ex07Test (jni native interface), then call EX04_IOCTL_TEST
        mButton01.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				int rc = 0;
				
				rc = ex07Test();				
				Toast.makeText(ex07.this, String.format("ex07Test, rc=%d", rc), Toast.LENGTH_LONG).show();
			}
		});
        
        
        //will call ex07Set (jni native interface), then call EX04_IOCTL_SET_VAL
        mButton02.setOnClickListener(new View.OnClickListener() {
			
        	public void onClick(View v) {
				int rc = 0;
				int test_val = 22;
				
				rc = ex07Set(test_val);
				Toast.makeText(ex07.this, String.format("ex07Set-set to %d, rc=%d", test_val, rc), Toast.LENGTH_LONG).show();
			}
		});


      //will call ex07Set (jni native interface), then call EX04_IOCTL_SET_VAL
        mButton03.setOnClickListener(new View.OnClickListener() {
	
        	public void onClick(View v) {
				int rc = 0;
				int test_val = 44;
				
				rc = ex07Set(test_val);
				Toast.makeText(ex07.this, String.format("ex07Set-set to %d, rc=%d", test_val, rc), Toast.LENGTH_LONG).show();
			}
        });


      //will call ex07Set (jni native interface), then call EX04_IOCTL_SET_VAL
        mButton04.setOnClickListener(new View.OnClickListener() {
	
        	public void onClick(View v) {
				int rc = 0;
				int test_val = 66;
				
				rc = ex07Set(test_val);
				Toast.makeText(ex07.this, String.format("ex07Set-set to %d, rc=%d", test_val, rc), Toast.LENGTH_LONG).show();
			}
        });


      //will call ex07Get (jni native interface), then call EX04_IOCTL_GET_VAL
        mButton05.setOnClickListener(new View.OnClickListener() {
	
        	public void onClick(View v) {
        		int rc = 0;
		
        		rc = ex07Get();
        		Toast.makeText(ex07.this, String.format("ex07Get, rc=%d", rc), Toast.LENGTH_LONG).show();
        	}
        });
    }
}