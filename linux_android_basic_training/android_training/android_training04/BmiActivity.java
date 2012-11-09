package com.xing.bmi;

import java.text.DecimalFormat;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;//弹出消息框
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;




public class BmiActivity extends Activity {
	
	private static final String TAG = "aBmi";

	
		
	private Button button_calc;
	private Button button_clear;
	private Button button_advice;
	private EditText field_height;
	private EditText field_weight;
	private TextView view_result;
	private TextView view_suggest;
	private TextView view_tvsex;
	private TextView view_setsex;
	private RadioGroup group;

	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bmi);
        findViews();
        setListeners();

    }
		
	private void findViews()
	{
		Log.d(TAG,"find views");
		button_calc = (Button) findViewById(R.id.submit);
		button_clear = (Button)findViewById(R.id.clear);
		button_advice = (Button)findViewById(R.id.ha);
		group = (RadioGroup)findViewById(R.id.radioGroup);
		field_height = (EditText) findViewById(R.id.height);
		field_weight = (EditText) findViewById(R.id.weight);
		view_result = (TextView) findViewById(R.id.result);
		view_suggest = (TextView) findViewById(R.id.suggest);
		view_tvsex = (TextView)findViewById(R.id.tvsex);
		view_setsex = (TextView)findViewById(R.id.setsex);
	}
	//Listen for button clicks
	private void setListeners() {
		Log.d(TAG,"set listeners");
		button_calc.setOnClickListener(calcBMI);
		button_clear.setOnClickListener(cleanData);
		button_advice.setOnClickListener(report);
		group.setOnCheckedChangeListener(listener);
	}
	
	private RadioGroup.OnCheckedChangeListener listener = new RadioGroup.OnCheckedChangeListener() {
		
		
		public void onCheckedChanged(RadioGroup group, int checkedId) {
			// TODO Auto-generated method stub
			//int radioButtonId = rgroup.getCheckedRadioButtonId();			
			//RadioButton rb = (RadioButton)findViewById(radioButtonId)
			RadioButton rb = (RadioButton)findViewById(checkedId);
			view_tvsex.setText(getText(R.string.choose));
			view_setsex.setText(rb.getText());
		}
	};

	
	//clear data
	private  Button.OnClickListener cleanData = new Button.OnClickListener()
	{

		public void onClick(View v) {
			// TODO Auto-generated method stub
			field_height.setText(" ");
			field_weight.setText(" ");
			view_result.setText(" ");
			view_suggest.setText(" ");
			//view_tvsex.setText("你的性别是： ");
		}
		
	};	
	
	private Button.OnClickListener report = new Button.OnClickListener(){

		public void onClick(View v) {
			// TODO Auto-generated method stub
			Intent intent = new Intent();
			intent.setClass(BmiActivity.this,HealthReport.class);

			Bundle bundle = new Bundle();
			bundle.putString("KEY_HEIGHT", field_height.getText().toString());
			bundle.putString("KEY_WEIGHT", field_weight.getText().toString());
			bundle.putString("KEY_SEX", view_setsex.getText().toString());
			intent.putExtras(bundle);
			startActivity(intent);
		}
		
	};

	//calculate BMI
	private Button.OnClickListener calcBMI = new Button.OnClickListener()
	{
		public void onClick(View v)
		{
			try{
			DecimalFormat nf = new DecimalFormat("0.0");
			double height =
					Double.parseDouble(field_height.getText().toString())/100;
			double weight =
					Double.parseDouble(field_weight.getText().toString());
			
			double	BMI = weight / (height * height);
			


			
	//Present result
	view_result.setText(getText(R.string.bmi_result) + nf.format(BMI));
	//Give health advice
	
			if(BMI>25){
				view_suggest.setText(R.string.advice_heavy);
			}else if(BMI<20){
				view_suggest.setText(R.string.advice_light);
			}else{
			view_suggest.setText(R.string.advice_average);
			}
			openOptionsDialog1();
			}catch(Exception obj){
				Toast.makeText(BmiActivity.this, "Sorry!请输入完整的信息!!", Toast.LENGTH_SHORT).show();
			}
		}

		private void openOptionsDialog1() {
			// TODO Auto-generated method stub
			Toast.makeText(BmiActivity.this, "BMI计算器", Toast.LENGTH_SHORT).show();
		}
	};

	private void openOptionsDialog() {
	// TODO Auto-generated method stub
		new AlertDialog.Builder(this)
		.setTitle(R.string.about_title)
		.setMessage(R.string.about_msg)
		.setPositiveButton(R.string.ok_label, new DialogInterface.OnClickListener() {
			
			public void onClick(DialogInterface dialog, int i) {
				// TODO Auto-generated method stub
				
			}
		}).setNegativeButton(R.string.homepage_label, new DialogInterface.OnClickListener() {
			
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				Uri uri = Uri.parse("http://sites.google.com/site/gasodroid/");
				Intent intent = new Intent(Intent.ACTION_VIEW,uri);
				startActivity(intent);
			}
		}).show();
	}
	
	protected static final int MENU_ABOUT = Menu.FIRST;
	protected static final int MENU_Quit = Menu.FIRST+1;

@Override
public boolean onCreateOptionsMenu(Menu menu) {
	Log.d(TAG,"menu");
    getMenuInflater().inflate(R.menu.activity_bmi, menu);
    super.onCreateOptionsMenu(menu);
    menu.add(0,MENU_ABOUT,0,"关于...").setIcon(android.R.drawable.ic_menu_help);
    menu.add(0,MENU_Quit,0,"结束").setIcon(android.R.drawable.ic_menu_close_clear_cancel);
    return super.onCreateOptionsMenu(menu);
	}
@Override
public boolean onOptionsItemSelected(MenuItem item){
		switch(item.getItemId()){
			case MENU_ABOUT:
				openOptionsDialog();
				break;
			case MENU_Quit:
				finish();
				break;
		}
		return super.onOptionsItemSelected(item);	
	}
}

