package com.ccs.wedate.base;

import android.app.ProgressDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.ccs.wedate.R;

import java.io.*;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private ProgressDialog progressDialog;
    private Button button;
    private TextView textView;
    private String message;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button = (Button)findViewById(R.id.button);
        textView = (TextView)findViewById(R.id.textView);
        progressDialog = new ProgressDialog(this);
        progressDialog.setTitle("we chat");
        progressDialog.setMessage("Connectting...");

        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                new ConnectTask().execute();
            }
        });
    }

    public class ConnectTask extends AsyncTask<Void,Void,String>
    {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            progressDialog.show();
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            textView.setText(s);
            progressDialog.dismiss();
        }

        @Override
        protected void onProgressUpdate(Void... values) {
            super.onProgressUpdate(values);
        }

        @Override
        protected String doInBackground(Void...param){
            try {
                Socket s = new Socket("119.29.39.155", 10024);
                OutputStream out = s.getOutputStream();
                // 注意第二个参数据为true将会自动flush，否则需要需要手动操作out.flush()
                PrintWriter output = new PrintWriter(out, true);
                output.println("Let's Date!");
                BufferedReader input = new BufferedReader(new InputStreamReader(s
                        .getInputStream()));
                // read line(s)
                message = input.readLine();
                Log.d("Tcp Demo", "message From Server:" + message);
                s.close();

            }catch(Exception ex)
            {
                ex.printStackTrace();
            }
            return message;
        }
    };
}



