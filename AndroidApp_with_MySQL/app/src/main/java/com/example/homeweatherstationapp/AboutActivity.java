package com.example.homeweatherstationapp;

import static android.app.PendingIntent.getActivity;

import android.os.Bundle;
import android.text.method.LinkMovementMethod;
import android.text.util.Linkify;
import android.view.View;
import android.widget.CheckBox;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.homeweatherstationapp.databinding.ActivityMainBinding;

public class AboutActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);

        TextView firebase_link = findViewById(R.id.firebase_link);
        firebase_link.setText("https://home-weather-station-ivnya-default-rtdb.europe-west1.firebasedatabase.app/");
        Linkify.addLinks(firebase_link, Linkify.ALL);
    }

}
