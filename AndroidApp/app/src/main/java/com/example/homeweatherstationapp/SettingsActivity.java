package com.example.homeweatherstationapp;

import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class SettingsActivity extends AppCompatActivity {

    CheckBox checkBox_view_mode1;
    CheckBox checkBox_TEMP_HOME;
    CheckBox checkBox_TEMP_STREET;
    CheckBox checkBox_HUM_STREET;
    CheckBox checkBox_HUM_HOME;
    CheckBox checkBox_PRESSURE;
    CheckBox checkBox_WIND_SPEED;
    CheckBox checkBox_WIND_DIRECT;
    CheckBox checkBox_RAIN;
    CheckBox checkBox_VBAT;
    public static String choose_chart_mode;
    public static Boolean TEMP_HOME_MODE;
    public static Boolean TEMP_STREET_MODE;
    public static Boolean HUM_STREET_MODE;
    public static Boolean HUM_HOME_MODE;
    public static Boolean PRESSURE_MODE;
    public static Boolean WIND_SPEED_MODE;
    public static Boolean WIND_DIRECT_MODE;
    public static Boolean RAIN_MODE;
    public static Boolean VBAT_MODE;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        choose_chart_mode = "nothing";
        TEMP_HOME_MODE = false;
        TEMP_STREET_MODE = false;
        HUM_STREET_MODE = false;
        HUM_HOME_MODE = false;
        PRESSURE_MODE = false;
        WIND_SPEED_MODE = false;
        WIND_DIRECT_MODE = false;
        RAIN_MODE = false;
        VBAT_MODE = false;

        checkBox_view_mode1 = (CheckBox) findViewById(R.id.checkBox_view_mode1);
        checkBox_TEMP_HOME = (CheckBox) findViewById(R.id.checkBox_TEMP_HOME);
        checkBox_TEMP_STREET = (CheckBox) findViewById(R.id.checkBox_TEMP_STREET);
        checkBox_HUM_STREET = (CheckBox) findViewById(R.id.checkBox_HUM_STREET);
        checkBox_HUM_HOME = (CheckBox) findViewById(R.id.checkBox_HUM_HOME);
        checkBox_PRESSURE = (CheckBox) findViewById(R.id.checkBox_PRESSURE);
        checkBox_WIND_SPEED = (CheckBox) findViewById(R.id.checkBox_WIND_SPEED);
        checkBox_WIND_DIRECT = (CheckBox) findViewById(R.id.checkBox_WIND_DIRECT);
        checkBox_RAIN = (CheckBox) findViewById(R.id.checkBox_RAIN);
        checkBox_VBAT = (CheckBox) findViewById(R.id.checkBox_VBAT);
        checkBox_view_mode1.setOnClickListener(CheckBoxClickListener);
        checkBox_TEMP_HOME.setOnClickListener(CheckBoxClickListener);
        checkBox_TEMP_STREET.setOnClickListener(CheckBoxClickListener);
        checkBox_HUM_STREET.setOnClickListener(CheckBoxClickListener);
        checkBox_HUM_HOME.setOnClickListener(CheckBoxClickListener);
        checkBox_PRESSURE.setOnClickListener(CheckBoxClickListener);
        checkBox_WIND_SPEED.setOnClickListener(CheckBoxClickListener);
        checkBox_WIND_DIRECT.setOnClickListener(CheckBoxClickListener);
        checkBox_RAIN.setOnClickListener(CheckBoxClickListener);
        checkBox_VBAT.setOnClickListener(CheckBoxClickListener);
    }
    View.OnClickListener CheckBoxClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            CheckBox checkBox = (CheckBox) view;
            switch (checkBox.getId()) {
                case R.id.checkBox_view_mode1:
                    if (checkBox.isChecked()) {
                        choose_chart_mode = "all_other";
                        checkBox_TEMP_HOME.setChecked(true);
                        checkBox_TEMP_HOME.setEnabled(false);
                        checkBox_TEMP_STREET.setChecked(true);
                        checkBox_TEMP_STREET.setEnabled(false);
                        checkBox_HUM_STREET.setChecked(true);
                        checkBox_HUM_STREET.setEnabled(false);
                        checkBox_HUM_HOME.setChecked(true);
                        checkBox_HUM_HOME.setEnabled(false);
                        checkBox_PRESSURE.setChecked(true);
                        checkBox_PRESSURE.setEnabled(false);
                        checkBox_WIND_SPEED.setChecked(true);
                        checkBox_WIND_SPEED.setEnabled(false);
                        checkBox_WIND_DIRECT.setChecked(true);
                        checkBox_WIND_DIRECT.setEnabled(false);
                        checkBox_RAIN.setChecked(true);
                        checkBox_RAIN.setEnabled(false);
                        checkBox_VBAT.setChecked(true);
                        checkBox_VBAT.setEnabled(false);
                    } else {
                        choose_chart_mode = "nothing";
                        checkBox_TEMP_HOME.setChecked(false);
                        checkBox_TEMP_HOME.setEnabled(true);
                        checkBox_TEMP_STREET.setChecked(false);
                        checkBox_TEMP_STREET.setEnabled(true);
                        checkBox_HUM_STREET.setChecked(false);
                        checkBox_HUM_STREET.setEnabled(true);
                        checkBox_HUM_HOME.setChecked(false);
                        checkBox_HUM_HOME.setEnabled(true);
                        checkBox_PRESSURE.setChecked(false);
                        checkBox_PRESSURE.setEnabled(true);
                        checkBox_WIND_SPEED.setChecked(false);
                        checkBox_WIND_SPEED.setEnabled(true);
                        checkBox_WIND_DIRECT.setChecked(false);
                        checkBox_WIND_DIRECT.setEnabled(true);
                        checkBox_RAIN.setChecked(false);
                        checkBox_RAIN.setEnabled(true);
                        checkBox_VBAT.setChecked(false);
                        checkBox_VBAT.setEnabled(true);
                    }
                    break;
                case R.id.checkBox_TEMP_HOME:
                    if (checkBox.isChecked()) {
                        TEMP_HOME_MODE = true;
                    }
                    else
                    {
                        TEMP_HOME_MODE = false;
                    }
                    break;
                case R.id.checkBox_TEMP_STREET:
                    if (checkBox.isChecked()) {
                        TEMP_STREET_MODE = true;
                    }
                    else
                    {
                        TEMP_STREET_MODE = false;
                    }
                    break;
                case R.id.checkBox_HUM_STREET:
                    if (checkBox.isChecked()) {
                        HUM_STREET_MODE = true;
                    }
                    else
                    {
                        HUM_STREET_MODE = false;
                    }
                    break;
                case R.id.checkBox_HUM_HOME:
                    if (checkBox.isChecked()) {
                        HUM_HOME_MODE = true;
                    }
                    else
                    {
                        HUM_HOME_MODE = false;
                    }
                    break;
                case R.id.checkBox_PRESSURE:
                    if (checkBox.isChecked()) {
                        PRESSURE_MODE = true;
                    }
                    else
                    {
                        PRESSURE_MODE = false;
                    }
                    break;
                case R.id.checkBox_WIND_SPEED:
                    if (checkBox.isChecked()) {
                        WIND_SPEED_MODE = true;
                    }
                    else
                    {
                        WIND_SPEED_MODE = false;
                    }
                    break;
                case R.id.checkBox_WIND_DIRECT:
                    if (checkBox.isChecked()) {
                        WIND_DIRECT_MODE = true;
                    }
                    else
                    {
                        WIND_DIRECT_MODE = false;
                    }
                    break;
                case R.id.checkBox_RAIN:
                    if (checkBox.isChecked()) {
                        RAIN_MODE = true;
                    }
                    else
                    {
                        RAIN_MODE = false;
                    }
                    break;
                case R.id.checkBox_VBAT:
                    if (checkBox.isChecked()) {
                        VBAT_MODE = true;
                    }
                    else
                    {
                        VBAT_MODE = false;
                    }
                    break;
            }
        }
    };
}
